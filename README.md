# 🐍 Snake Game (C++ / OOP Based)

## 🎮 Overview
This is a **terminal-based Snake Game** built in **C++**, designed using **Object-Oriented Programming (OOP)** principles.  
The game runs in the **Windows console** and demonstrates clean modular design with encapsulation, abstraction, and easy extensibility.

It supports:
- Multiple difficulty levels  
- Two game modes (Border / No Border)  
- **Obstacles in Hard Mode**  
- **Persistent High Score System**

---

## ✨ Features

✅ **OOP-Based Design**  
Organized into multiple classes (`Game`, `Snake`, `Food`, `Obstacle`, `Console`) for clarity and modularity.  

✅ **Difficulty Levels**
- **Easy:** Slow snake speed  
- **Medium:** Balanced speed  
- **Hard:** Fast snake + Random obstacles  

✅ **Game Modes**
- **Border Mode:** Hitting the wall = Game Over  
- **No Border Mode:** Snake wraps around screen edges  

✅ **Obstacles in Hard Mode**
- Random `#` walls appear on the board  
- Hitting any obstacle results in Game Over  

✅ **High Score Tracking**
- Highest score is stored in `highscore.txt`  
- Automatically updates when you set a new record  

✅ **Smooth Console Rendering**
- Uses Windows API `WriteConsoleOutput` for flicker-free visuals  

---

## 🧠 OOP Concepts Used

| Concept | Description | Example |
|----------|--------------|----------|
| **Class & Object** | Entities like `Snake`, `Food`, `Game`, and `Console` are classes instantiated as objects. | `Game game(60, 20);` |
| **Encapsulation** | Data & logic are bundled within classes. | `Snake::move()`, `Food::spawn()` |
| **Abstraction** | Complex logic hidden behind simple methods. | `game.run()` |
| **Inheritance (Extensible)** | Future scope for new food or game types. | `class BonusFood : public Food` |
| **Polymorphism (Optional)** | Same interface, different behavior (can be added later). | `virtual int getPoints()` |
| **Composition** | `Game` *has-a* `Snake`, `Food`, and `Obstacle` objects. | `Obstacle obstacle;` |

---

## 🕹️ Gameplay & Controls

| Key | Action |
|-----|---------|
| **W** | Move Up |
| **S** | Move Down |
| **A** | Move Left |
| **D** | Move Right |
| **X** | Quit the Game |

### Game Over Screen
- Displays your **Final Score** and **Highest Score**.  
- If you beat the previous record → shows `*** New High Score! ***`

---

## ⚙️ Installation & Setup

### 🧩 Requirements
- **Windows OS**
- **C++ Compiler** (MinGW, MSVC, Code::Blocks, or Dev-C++)
- Must support `<windows.h>` and `<conio.h>`

### 🧠 Compile and Run

#### Using Command Prompt:
```bash
g++ SnakeGame.cpp -o SnakeGame
SnakeGame.exe


🧱 Project Structure
SnakeGame/
│
├── SnakeGame.cpp        # Main source file
├── highscore.txt        # Automatically generated for storing high score
├── README.md            # Project documentation
└── (Optional) assets/   # Future files (textures, sounds, etc.)


🧩 Class Diagram (Simplified UML)
+--------------------+
|       Game         |
+--------------------+
| - WIDTH, HEIGHT    |
| - score, highScore |
| - Snake snake      |
| - Food food        |
| - Obstacle obstacle|
+--------------------+
| + run()            |
| + setup()          |
| + draw()           |
| + updateLogic()    |
+--------------------+

+--------------------+
|       Snake        |
+--------------------+
| - vector<Position> |
| - Direction dir    |
+--------------------+
| + move()           |
| + getHead()        |
| + hasSelfCollision()|
+--------------------+

+--------------------+
|        Food        |
+--------------------+
| - Position pos     |
+--------------------+
| + spawn()          |
| + getPosition()    |
+--------------------+

+--------------------+
|      Obstacle      |
+--------------------+
| - vector<Position> |
+--------------------+
| + spawnObstacles() |
| + isHit()          |
+--------------------+

+--------------------+
|      Console       |
+--------------------+
| + setupConsole()   |
| + hideCursor()     |
+--------------------+


🧱 Hard Mode Example (Obstacles)
When playing on Hard, the board includes random obstacles (#) that end the game if hit.
----------------------------------------------
|                     *                     |
|         ######                            |
|    ###                                    |
|                     oooO                  |
|                      oo                   |
|                       o                   |
----------------------------------------------


🧩 How High Score Works


The game saves your best score in highscore.txt.


When you surpass your old record, it automatically updates.


The file persists between runs, even after closing the game.



🧠 Learning Outcomes
This project helps you learn:


Practical OOP in C++


Real-time keyboard input using _kbhit() and _getch()


Console rendering with WriteConsoleOutput


File handling using <fstream>


Game loop and object interaction design



💡 Future Enhancements
You can extend the game with:


🧱 Custom wall patterns or levels


🥇 Power-ups and speed boosts


🔊 Sound effects using PlaySound()


💬 Restart option after Game Over


🧠 AI Snake (multiplayer or bot mode)



👨‍💻 Author
Priyanshu Soni
🎯 Solo Developer & C++ Enthusiast
📧 Designed using Object-Oriented Programming principles

🏁 License
This project is released under the MIT License — free for personal and educational use.

🚀 Run & Enjoy
g++ SnakeGame.cpp -o SnakeGame
SnakeGame.exe

Survive. Grow. Avoid walls & obstacles. Beat your high score! 🐍🔥

---

Would you like me to make a **“GitHub-optimized” version** next (with emojis, collapsible sections, and a preview image placeholder)?  
That’s perfect if you plan to upload this project to GitHub or showcase it in your portfolio.
