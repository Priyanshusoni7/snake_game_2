#define main snakeGameBaselineMain
#include "base-snake.cpp"
#undef main
#include "check.h"

void selfCollisionRecognizesOccupiedBodyCell() {
    Snake snake(5, 5);
    snake.move(Position(6, 5), true); // Growth runs as arrangement, not as an asserted rule.
    CHECK(snake.hasSelfCollision(Position(5, 5)));
    CHECK(!snake.hasSelfCollision(Position(9, 9)));
}

void spawnedObstacleReportsAHit() {
    std::srand(643);
    Snake snake(10, 10);
    Food food;
    food.spawn(20, 20, snake);
    Obstacle obstacle;
    obstacle.spawnObstacles(20, 20, snake, food, 1);
    CHECK(obstacle.getBlocks().size() == 1);
    CHECK(obstacle.isHit(obstacle.getBlocks().front()));
    CHECK(!obstacle.isHit(Position(25, 25)));
}

int main() {
    int failures = 0;
    runTest("self collision recognizes occupied body cell", selfCollisionRecognizesOccupiedBodyCell, failures);
    runTest("spawned obstacle reports a hit", spawnedObstacleReportsAHit, failures);
    return failures == 0 ? 0 : 1;
}
