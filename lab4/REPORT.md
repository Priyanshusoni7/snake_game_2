# Lab 4 — The tests you cannot write

Repository: https://github.com/Priyanshusoni7/snake_game_2  
Base: `lab4-base` at `613037e45c818a645a7a87bdefd9609c5ea47ee0`  
Pull request: `lab4` → `main`

## 1. Five rules

These were recorded in `PART-A.md` before the C++ source was opened.

1. Eating food grows the snake and increases the score.
2. In border mode, touching a wall ends the game.
3. With borders disabled, crossing an edge wraps the snake to the opposite edge.
4. Moving the snake's head into its own body ends the game.
5. In hard mode, hitting an obstacle ends the game.

## 2. Tests against `lab4-base`

**Result: 2 of 5 rules can be tested completely without changing production source.** The baseline suite includes only assertions supported by the public API; it does not add getters, preprocess private members, or reproduce the game algorithm in a test.

| Rule | Test written? | Blocking dependency in `lab4-base` |
|---|---:|---|
| Eating grows the snake and increments score | No (complete rule) | Growth can be arranged through `Snake::move` at `snake_oop.cpp:100`, but the score and food decision are private inside `Game::updateLogic` at `snake_oop.cpp:414` and `snake_oop.cpp:476`; the concrete `Food` and score state are private at `snake_oop.cpp:193` and `snake_oop.cpp:198`. |
| Border collision ends the game | No | The branch is in private `Game::updateLogic` at `snake_oop.cpp:414` and uses private `borderMode` / `gameOver` at `snake_oop.cpp:191` and `snake_oop.cpp:195`. |
| No-border movement wraps | No | The wrap branch is in private `Game::updateLogic` at `snake_oop.cpp:414`; the mode is selected by `cin` at `snake_oop.cpp:249` and stored privately at `snake_oop.cpp:191`. |
| Self collision ends the game | Yes | `Snake::hasSelfCollision` is public at `snake_oop.cpp:108`; `lab4/tests/baseline.cpp:6` verifies occupied and unoccupied cells. |
| Hard-mode obstacle collision ends the game | Yes | `Obstacle::isHit` and its blocks are public at `snake_oop.cpp:174` and `snake_oop.cpp:154`; `lab4/tests/baseline.cpp:13` verifies a spawned obstacle is detected. |

The other major process dependencies are `_kbhit` / `_getch` inside input handling (`snake_oop.cpp:382`), `Sleep` in the loop (`snake_oop.cpp:497`), and `rand` / `time` in food and obstacle creation (`snake_oop.cpp:140`, `snake_oop.cpp:161`). Naming “user input” alone would be imprecise: the calls and private boundaries above are the actual blockers.

## 3. Coverage versus verification

Coverage was measured with `g++ --coverage -O0 -g` and `gcov -b`.

| Suite | Production source | Line coverage | Branches executed |
|---|---|---:|---:|
| Baseline | generated verbatim from `lab4-base:snake_oop.cpp` | 16.48% of 267 | 15.63% of 256 |
| Seam | current `snake_oop.cpp` | 23.99% of 271 | 22.69% of 260 |

Rule 1 illustrates the difference between running code and checking behavior. In the baseline self-collision test, `Snake::move(..., true)` executes the growth path at `snake_oop.cpp:100-105` as arrangement. No assertion checks the length change, and the score update at `snake_oop.cpp:482` never runs. The missing assertion is that eating increases the body length and score by exactly one. Thus executed lines do not establish the full rule.

Raw summaries and test output are committed under `lab4/evidence/`.

## 4. One seam, two commits

| Item | Result |
|---|---|
| Commit 1 | `d39a15a` — `refactor: expose game tick through a food collaborator seam` |
| Commit 2 | This report and the tests; no production source is changed. |
| Seam kind | Object seam (`FoodSource`) |
| Enabling point | `advanceGame` at `snake_oop.cpp:198`, called from `Game::updateLogic` at `snake_oop.cpp:496` |
| Production code gave up | A small amount of encapsulation: the tick operation and `GameProgress` became callable state, and food access now uses virtual dispatch. In return, the same game decisions run without console input, delay, or random food placement. |

Commit 1 changes structure only. It moves the existing update decisions into `advanceGame`, makes `Food` implement `FoodSource`, and has the interactive game delegate to that function. Movement, collision, score, speed, and rendering behavior stay the same. Commit 2 adds only tests and documentation.

## 5. Name the double

`ScriptedFood` is a **stub**. `advanceGame` asks it for the current food position; on `spawn`, it advances to a canned next answer. The assertions inspect snake and game state rather than verifying that calls happened, so it is not a mock or spy.

## 6. Two smells in the new tests

1. **Eager test — `lab4/tests/seam.cpp:42`.** `eatingGrowsAndScoresExactlyOnce` checks movement, growth, score, speed, and a second tick in one test. One-line fix: split growth/score, speed, and one-time consumption into focused tests.
2. **Assertion roulette — `lab4/tests/baseline.cpp:13`.** `spawnedObstacleReportsAHit` has three bare checks, so a failure says only which expression failed without naming the scenario. One-line fix: give each invariant its own named test (or add scenario text to `CHECK`).

These smells are reported rather than hidden; fixing them was optional for this assignment.

## Verification

- Baseline suite: 2/2 tests pass.
- Seam suite: 10/10 tests pass.
- Current game source compiles with MinGW `g++`; the two signed/unsigned comparison warnings at current lines 438 and 448 already existed at base lines 358 and 368.
