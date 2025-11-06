#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <fstream> // for saving high score

using namespace std;

// ==============================================
// ENUMS & STRUCTS
// ==============================================

// Represents direction of snake movement
enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Represents position on the board (x = column, y = row)
struct Position
{
    int x, y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Position &other) const
    {
        return x == other.x && y == other.y;
    }
};

// ==============================================
// CONSOLE UTILITY CLASS
// Handles all console-related setup
// ==============================================
class Console
{
public:
    // Move cursor to coordinate
    static void gotoxy(int x, int y)
    {
        COORD coord{(SHORT)x, (SHORT)y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    // Hide blinking cursor
    static void hideCursor()
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    // Set console size
    static void setupConsole(int width, int height)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD bufferSize = {(SHORT)(width + 2), (SHORT)(height + 4)};
        SetConsoleScreenBufferSize(hConsole, bufferSize);
        SMALL_RECT windowSize = {0, 0, (SHORT)(width + 1), (SHORT)(height + 3)};
        SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
        hideCursor();
    }
};

// ==============================================
// SNAKE CLASS
// Handles snake body, direction, movement
// ==============================================
class Snake
{
private:
    vector<Position> body;
    Direction dir;

public:
    Snake(int startX, int startY)
    {
        dir = STOP;
        body.push_back(Position(startX, startY));
        body.push_back(Position(startX - 1, startY));
        body.push_back(Position(startX - 2, startY));
    }

    Direction getDirection() const { return dir; }
    void setDirection(Direction d) { dir = d; }

    const vector<Position> &getBody() const { return body; }
    Position getHead() const { return body.front(); }

    // Move snake (add head, remove tail if not eating)
    void move(Position newHead, bool ateFood)
    {
        body.insert(body.begin(), newHead);
        if (!ateFood)
            body.pop_back();
    }

    // Detect collision with itself
    bool hasSelfCollision(Position newHead) const
    {
        for (size_t i = 0; i < body.size() - 1; i++)
            if (body[i] == newHead)
                return true;
        return false;
    }

    // Check if snake occupies a position
    bool contains(Position pos) const
    {
        return find(body.begin(), body.end(), pos) != body.end();
    }
};

// ==============================================
// FOOD CLASS
// Handles food spawning and position
// ==============================================
class Food
{
private:
    Position pos;

public:
    Food() : pos(0, 0) {}
    Position getPosition() const { return pos; }

    void spawn(int width, int height, const Snake &snake)
    {
        do
        {
            pos.x = rand() % width;
            pos.y = rand() % height;
        } while (snake.contains(pos));
    }
};

// ==============================================
// OBSTACLE CLASS
// Adds obstacles in hard mode
// ==============================================
class Obstacle
{
private:
    vector<Position> blocks; // obstacle positions

public:
    const vector<Position> &getBlocks() const { return blocks; }

    // Create random obstacles on grid
    void spawnObstacles(int width, int height, const Snake &snake, const Food &food, int count)
    {
        blocks.clear();
        srand((unsigned int)time(0));
        while ((int)blocks.size() < count)
        {
            Position newPos(rand() % width, rand() % height);

            // Avoid overlap with snake and food
            if (!snake.contains(newPos) && !(food.getPosition() == newPos))
                blocks.push_back(newPos);
        }
    }

    // Check if snake hits an obstacle
    bool isHit(Position head) const
    {
        for (const auto &b : blocks)
            if (b == head)
                return true;
        return false;
    }
};

// ==============================================
// GAME CLASS
// Core game logic, loop, rendering, scoring
// ==============================================
class Game
{
private:
    const int WIDTH, HEIGHT;
    bool borderMode;
    int speed;
    int score;
    int highScore;
    bool gameOver;
    bool hardMode; // Hard mode = obstacles active
    Snake *snake;
    Food food;
    Obstacle obstacle; // obstacle object

public:
    Game(int w, int h) : WIDTH(w), HEIGHT(h)
    {
        borderMode = true;
        speed = 100;
        score = 0;
        highScore = loadHighScore();
        gameOver = false;
        hardMode = false;
        snake = nullptr;
    }

    ~Game() { delete snake; }

    // Load highest score from file
    int loadHighScore()
    {
        ifstream fin("highscore.txt");
        int hs = 0;
        if (fin)
            fin >> hs;
        return hs;
    }

    // Save high score
    void saveHighScore()
    {
        ofstream fout("highscore.txt");
        fout << highScore;
    }

    // Initialize the game
    void setup()
    {
        system("cls");
        Console::setupConsole(WIDTH, HEIGHT);
        snake = new Snake(WIDTH / 2, HEIGHT / 2);
        srand((unsigned int)time(0));
        food.spawn(WIDTH, HEIGHT, *snake);
        score = 0;
        gameOver = false;

        // ✅ Add obstacles if Hard mode
        if (hardMode)
            obstacle.spawnObstacles(WIDTH, HEIGHT, *snake, food, 20); // 20 random walls
    }

    // Choose border type
    void chooseMode()
    {
        cout << "Choose Game Mode:\n";
        cout << "1. Border Mode (hit wall = game over)\n";
        cout << "2. No Borders (snake wraps around)\n";
        cout << "Enter choice (1 or 2): ";
        char choice;
        cin >> choice;
        borderMode = (choice == '1');
    }

    // Choose difficulty
    void chooseDifficulty()
    {
        cout << "Select Difficulty:\n";
        cout << "1. Easy\n2. Medium\n3. Hard (with obstacles)\n";
        cout << "Enter choice (1/2/3): ";
        char diff;
        cin >> diff;
        switch (diff)
        {
        case '1':
            speed = 130;
            hardMode = false;
            break;
        case '3':
            speed = 90;
            hardMode = true;
            break;
        default:
            speed = 100;
            hardMode = false;
            break;
        }
    }

    // Draw everything on screen
    void draw()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        int totalHeight = HEIGHT + 4;
        int totalWidth = WIDTH + 2;
        CHAR_INFO *buffer = new CHAR_INFO[totalWidth * totalHeight];

        for (int i = 0; i < totalWidth * totalHeight; i++)
        {
            buffer[i].Char.AsciiChar = ' ';
            buffer[i].Attributes = 7;
        }

        int idx = 0;
        // Top border
        for (int i = 0; i < totalWidth; i++)
            buffer[idx++].Char.AsciiChar = '-';

        // Main area
        for (int i = 0; i < HEIGHT; i++)
        {
            buffer[idx++].Char.AsciiChar = '|';
            for (int j = 0; j < WIDTH; j++)
            {
                char ch = ' ';
                short color = 7;

                Position foodPos = food.getPosition();
                const vector<Position> &body = snake->getBody();

                // Snake head
                if (i == body[0].y && j == body[0].x)
                {
                    ch = 'O';
                    color = 10;
                }
                // Snake body
                else if (any_of(body.begin() + 1, body.end(),
                                [&](const Position &p)
                                { return p.x == j && p.y == i; }))
                {
                    ch = 'o';
                    color = 10;
                }
                // Food
                else if (i == foodPos.y && j == foodPos.x)
                {
                    ch = '*';
                    color = 12;
                }
                // ✅ Obstacles in Hard mode
                else if (hardMode && any_of(obstacle.getBlocks().begin(), obstacle.getBlocks().end(),
                                            [&](const Position &p)
                                            { return p.x == j && p.y == i; }))
                {
                    ch = '#';
                    color = 8; // gray walls
                }

                buffer[idx].Char.AsciiChar = ch;
                buffer[idx].Attributes = color;
                idx++;
            }
            buffer[idx++].Char.AsciiChar = '|';
        }

        // Bottom border
        for (int i = 0; i < totalWidth; i++)
            buffer[idx++].Char.AsciiChar = '-';

        // Score + High score display
        string scoreStr = "Score: " + to_string(score) + "   High: " + to_string(highScore);
        for (size_t i = 0; i < scoreStr.length() && i < totalWidth; i++)
        {
            buffer[idx].Char.AsciiChar = scoreStr[i];
            idx++;
        }
        while (idx % totalWidth != 0)
            buffer[idx++].Char.AsciiChar = ' ';

        // Controls info
        string inst = "Use W/A/S/D to move. Press X to quit.";
        for (size_t i = 0; i < inst.length() && i < totalWidth; i++)
        {
            buffer[idx].Char.AsciiChar = inst[i];
            idx++;
        }

        COORD bufferSize = {(SHORT)totalWidth, (SHORT)totalHeight};
        COORD bufferCoord = {0, 0};
        SMALL_RECT writeRegion = {0, 0, (SHORT)(totalWidth - 1), (SHORT)(totalHeight - 1)};
        WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &writeRegion);
        delete[] buffer;
    }

    // Handle keyboard input
    void handleInput()
    {
        if (_kbhit())
        {
            char key = toupper(_getch());
            Direction d = snake->getDirection();
            switch (key)
            {
            case 'A':
                if (d != RIGHT)
                    snake->setDirection(LEFT);
                break;
            case 'D':
                if (d != LEFT)
                    snake->setDirection(RIGHT);
                break;
            case 'W':
                if (d != DOWN)
                    snake->setDirection(UP);
                break;
            case 'S':
                if (d != UP)
                    snake->setDirection(DOWN);
                break;
            case 'X':
                gameOver = true;
                break;
            }
        }
    }

    // Core game logic: movement, collision, food
    void updateLogic()
    {
        Direction dir = snake->getDirection();
        if (dir == STOP)
            return;

        Position head = snake->getHead();

        // Move in direction
        switch (dir)
        {
        case LEFT:
            head.x--;
            break;
        case RIGHT:
            head.x++;
            break;
        case UP:
            head.y--;
            break;
        case DOWN:
            head.y++;
            break;
        default:
            break;
        }

        // Wall collision
        if (borderMode)
        {
            if (head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT)
            {
                gameOver = true;
                return;
            }
        }
        else
        {
            if (head.x < 0)
                head.x = WIDTH - 1;
            else if (head.x >= WIDTH)
                head.x = 0;
            if (head.y < 0)
                head.y = HEIGHT - 1;
            else if (head.y >= HEIGHT)
                head.y = 0;
        }

        // Self collision
        if (snake->hasSelfCollision(head))
        {
            gameOver = true;
            return;
        }

        // ✅ Obstacle collision
        if (hardMode && obstacle.isHit(head))
        {
            gameOver = true;
            return;
        }

        bool ateFood = (head == food.getPosition());
        snake->move(head, ateFood);

        if (ateFood)
        {
            score++;
            if (speed > 40)
                speed -= 2;
            food.spawn(WIDTH, HEIGHT, *snake);
        }
    }

    // Run the game loop
    void run()
    {
        setup();
        while (!gameOver)
        {
            draw();
            handleInput();
            updateLogic();
            Sleep(speed);
        }

        // Game over screen
        system("cls");
        cout << "#########################\n";
        cout << "#      GAME OVER!       #\n";
        cout << "#########################\n";
        cout << "Final Score: " << score << "\n";

        if (score > highScore)
        {
            highScore = score;
            saveHighScore();
            cout << "*** New High Score! ***\n";
        }
        else
        {
            cout << "Highest Score: " << highScore << "\n";
        }

        cout << "\nPress any key to exit...";
        _getch();
    }
};

// ==============================================
// MAIN FUNCTION
// ==============================================
int main()
{
    system("cls");
    cout << "=====================================\n";
    cout << "         WELCOME TO SNAKE GAME       \n";
    cout << "=====================================\n\n";

    Game game(60, 20);
    game.chooseMode();
    system("cls");
    game.chooseDifficulty();
    cout << "\nPress any key to start...";
    _getch();
    system("cls");

    game.run();
    return 0;
}
