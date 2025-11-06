# 🐍 Snake Game (C++ / OOP-Based Terminal Game)

## 🏁 Introduction

The **Snake Game** is a classic arcade-style terminal game built entirely in **C++**, following **Object-Oriented Programming (OOP)** principles.  
The player controls a snake that moves around a grid, eats food to grow, and avoids collisions with walls, obstacles, or itself.  
This project demonstrates real-time input handling, clean modular design, and practical implementation of OOP concepts.

---

## 🎮 Overview

This is a **Windows console-based game** that showcases how C++ classes and encapsulation can be used to build an interactive application.  
The project also implements persistent **high score tracking**, multiple **difficulty levels**, and **game modes** for extended playability.

It supports:
- Multiple **difficulty levels** (Easy, Medium, Hard)  
- **Two game modes**: Border Mode / No Border Mode  
- **Obstacles** in Hard Mode  
- **Persistent high score system** saved in a text file  

---

## ✨ Features

✅ **OOP-Based Modular Design**  
Organized into multiple classes (`Game`, `Snake`, `Food`, `Obstacle`, `Console`) for clarity and maintainability.  

✅ **Difficulty Levels**
- **Easy:** Slow snake speed  
- **Medium:** Balanced  
- **Hard:** Faster speed with random obstacles  

✅ **Game Modes**
- **Border Mode:** Hitting the wall = Game Over  
- **No Border Mode:** Snake wraps around screen edges  

✅ **Obstacles in Hard Mode**
- Random `#` walls appear on the grid  
- Colliding with any obstacle results in Game Over  

✅ **High Score Tracking**
- Saved in `highscore.txt` file  
- Automatically updates when a new record is achieved  

✅ **Smooth Rendering**
- Uses Windows API `WriteConsoleOutput()` for flicker-free visuals  

---

## 🧠 OOP Concepts Used

| Concept | Description | Example |
|----------|--------------|----------|
| **Class & Object** | Each game entity is represented as a class. | `Game game(60, 20);` |
| **Encapsulation** | Data and related logic are grouped within classes. | `Snake::move()`, `Game::updateLogic()` |
| **Abstraction** | Hides complexity behind easy-to-use functions. | `game.run()` |
| **Inheritance (Extensible)** | Can be extended with new features like `BonusFood`. | `class BonusFood : public Food` |
| **Polymorphism (Optional)** | Enables flexibility for different food or snake types. | `virtual void spawn()` |
| **Composition** | The `Game` object contains `Snake`, `Food`, and `Obstacle` objects. | `Obstacle obstacle;` |

---

## 🕹️ Gameplay & Controls

| Key | Action |
|-----|---------|
| **W** | Move Up |
| **S** | Move Down |
| **A** | Move Left |
| **D** | Move Right |
| **X** | Quit Game |

### 🎯 Game Over Screen
- Displays **Final Score** and **Highest Score**.  
- If you beat your previous record → shows `*** New High Score! ***`.

---

## ⚙️ Installation & Setup

### 🧩 Requirements
- **Windows OS**
- **C++ Compiler** (e.g., MinGW, MSVC, Code::Blocks, or Dev-C++)
- Must support `<windows.h>` and `<conio.h>`

### 🧠 Compile and Run

```bash
g++ SnakeGame.cpp -o SnakeGame
SnakeGame.exe


🧱 Project Structure
SnakeGame/
│
├── SnakeGame.cpp        # Main source file
├── highscore.txt        # Automatically created for saving high score
├── README.md            # Documentation
└── (Optional) assets/   # For future extensions (sound, textures, etc.)

💾 High Score System

The game automatically creates a highscore.txt file in the project directory.

Your best score is saved even after closing the game.

If you beat your high score, the file is updated instantly.

🧱 Hard Mode Example (Obstacles)

When playing on Hard Mode, random obstacles (#) are generated on the board:

----------------------------------------------
|                     *                     |
|         ######                            |
|    ###                                    |
|                     oooO                  |
|                      oo                   |
|                       o                   |
----------------------------------------------


## 🧰 Tech Stack

| Category | Technology Used |
|-----------|-----------------|
| **Language** | C++ |
| **Paradigm** | Object-Oriented Programming |
| **Libraries** | `<iostream>`, `<vector>`, `<windows.h>`, `<conio.h>`, `<fstream>`, `<ctime>`, `<algorithm>`, `<string>` |
| **Platform** | Windows Console Application |
| **Compiler** | GCC / MinGW / MSVC |
| **IDE (Optional)** | Code::Blocks, Dev-C++, Visual Studio Code |

---

## 👨‍💻 Authors

| Name | Role |
|------|------|
| **Priyanshu Dhrangdhariya** | Developer |
| **Kriti Patel** | Developer |
| **Kushal Thakkar** | Developer |
| **Jay Unadkat** | Developer |
