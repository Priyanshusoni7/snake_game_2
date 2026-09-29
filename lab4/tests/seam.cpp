#define main snakeGameInteractiveMain
#include "../../snake_oop.cpp"
#undef main
#include "check.h"

class ScriptedFood : public FoodSource {
    std::vector<Position> positions;
    std::size_t current = 0;
public:
    explicit ScriptedFood(std::initializer_list<Position> answers) : positions(answers) {}
    Position getPosition() const override { return positions.at(current); }
    void spawn(int, int, const Snake&) override {
        positions.at(current + 1);
        ++current;
    }
};

void stoppedSnakeDoesNothing() {
    Snake snake(5, 5);
    ScriptedFood food{{6, 5}};
    Obstacle obstacle;
    GameProgress progress;
    advanceGame(snake, food, obstacle, progress, 12, 12, true, false);
    CHECK(snake.getHead() == Position(5, 5));
    CHECK(progress.score == 0);
    CHECK(!progress.gameOver);
}

void moveWithoutFoodPreservesLengthAndScore() {
    Snake snake(5, 5);
    snake.setDirection(RIGHT);
    ScriptedFood food{{1, 1}};
    Obstacle obstacle;
    GameProgress progress;
    advanceGame(snake, food, obstacle, progress, 12, 12, true, false);
    CHECK(snake.getHead() == Position(6, 5));
    CHECK(snake.getBody().size() == 3);
    CHECK(progress.score == 0);
    CHECK(progress.speed == 100);
}

void eatingGrowsAndScoresExactlyOnce() {
    Snake snake(5, 5);
    snake.setDirection(RIGHT);
    ScriptedFood food{{6, 5}, {1, 1}};
    Obstacle obstacle;
    GameProgress progress;
    advanceGame(snake, food, obstacle, progress, 12, 12, true, false);
    CHECK(snake.getHead() == Position(6, 5));
    CHECK(snake.getBody().size() == 4);
    CHECK(progress.score == 1);
    CHECK(progress.speed == 98);
    advanceGame(snake, food, obstacle, progress, 12, 12, true, false);
    CHECK(snake.getBody().size() == 4);
    CHECK(progress.score == 1);
}

void eatingDoesNotReduceMinimumSpeed() {
    Snake snake(5, 5);
    snake.setDirection(RIGHT);
    ScriptedFood food{{6, 5}, {1, 1}};
    Obstacle obstacle;
    GameProgress progress;
    progress.speed = 40;
    advanceGame(snake, food, obstacle, progress, 12, 12, true, false);
    CHECK(progress.speed == 40);
}

void borderModeEndsAtWall() {
    Snake snake(0, 5);
    snake.setDirection(LEFT);
    ScriptedFood food{{8, 8}};
    Obstacle obstacle;
    GameProgress progress;
    advanceGame(snake, food, obstacle, progress, 10, 10, true, false);
    CHECK(progress.gameOver);
    CHECK(snake.getHead() == Position(0, 5));
}

void noBorderModeWrapsLeftToRight() {
    Snake snake(0, 5);
    snake.setDirection(LEFT);
    ScriptedFood food{{8, 8}};
    Obstacle obstacle;
    GameProgress progress;
    advanceGame(snake, food, obstacle, progress, 10, 10, false, false);
    CHECK(!progress.gameOver);
    CHECK(snake.getHead() == Position(9, 5));
}

void noBorderModeWrapsRightToLeft() {
    Snake snake(9, 5);
    snake.setDirection(RIGHT);
    ScriptedFood food{{8, 8}};
    Obstacle obstacle;
    GameProgress progress;
    advanceGame(snake, food, obstacle, progress, 10, 10, false, false);
    CHECK(snake.getHead() == Position(0, 5));
}

void noBorderModeWrapsTopToBottom() {
    Snake snake(5, 0);
    snake.setDirection(UP);
    ScriptedFood food{{8, 8}};
    Obstacle obstacle;
    GameProgress progress;
    advanceGame(snake, food, obstacle, progress, 10, 10, false, false);
    CHECK(snake.getHead() == Position(5, 9));
}

void noBorderModeWrapsBottomToTop() {
    Snake snake(5, 9);
    snake.setDirection(DOWN);
    ScriptedFood food{{8, 8}};
    Obstacle obstacle;
    GameProgress progress;
    advanceGame(snake, food, obstacle, progress, 10, 10, false, false);
    CHECK(snake.getHead() == Position(5, 0));
}

void movingIntoBodyEndsGame() {
    Snake snake(5, 5);
    snake.setDirection(LEFT);
    ScriptedFood food{{8, 8}};
    Obstacle obstacle;
    GameProgress progress;
    advanceGame(snake, food, obstacle, progress, 10, 10, true, false);
    CHECK(progress.gameOver);
    CHECK(snake.getHead() == Position(5, 5));
}

int main() {
    int failures = 0;
    runTest("stopped snake does nothing", stoppedSnakeDoesNothing, failures);
    runTest("move without food preserves length and score", moveWithoutFoodPreservesLengthAndScore, failures);
    runTest("eating grows and scores exactly once", eatingGrowsAndScoresExactlyOnce, failures);
    runTest("eating respects minimum speed", eatingDoesNotReduceMinimumSpeed, failures);
    runTest("border mode ends at wall", borderModeEndsAtWall, failures);
    runTest("no-border wraps left to right", noBorderModeWrapsLeftToRight, failures);
    runTest("no-border wraps right to left", noBorderModeWrapsRightToLeft, failures);
    runTest("no-border wraps top to bottom", noBorderModeWrapsTopToBottom, failures);
    runTest("no-border wraps bottom to top", noBorderModeWrapsBottomToTop, failures);
    runTest("moving into body ends game", movingIntoBodyEndsGame, failures);
    return failures == 0 ? 0 : 1;
}
