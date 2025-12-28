#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

const int CELL_SIZE = 20;
const int GRID_SIZE = 15;
const int WIN_SIZE = CELL_SIZE * GRID_SIZE;

// 将 Point 改名为 SnakeNode 避免与 cv::Point 冲突
struct SnakeNode { 
    int x, y; 
};

int main() {
    // 初始状态
    std::vector<SnakeNode> snake = {{10, 10}, {10, 11}, {10, 12}};
    SnakeNode food = {5, 5};
    SnakeNode dir = {0, -1}; 
    int score = 0;

    while (true) {
        cv::Mat canvas = cv::Mat::zeros(WIN_SIZE, WIN_SIZE, CV_8UC3);

        // 画食物
        cv::rectangle(canvas, cv::Rect(food.x * CELL_SIZE, food.y * CELL_SIZE, CELL_SIZE, CELL_SIZE), cv::Scalar(0, 0, 255), -1);

        // 画蛇
        for (auto& p : snake) {
            cv::rectangle(canvas, cv::Rect(p.x * CELL_SIZE, p.y * CELL_SIZE, CELL_SIZE, CELL_SIZE), cv::Scalar(0, 255, 0), -1);
        }

        cv::imshow("Snake Game", canvas);

        int key = cv::waitKey(150);
        if (key == 27) break;
        if (key == 'w' && dir.y != 1)  dir = {0, -1};
        if (key == 's' && dir.y != -1) dir = {0, 1};
        if (key == 'a' && dir.x != 1)  dir = {-1, 0};
        if (key == 'd' && dir.x != -1) dir = {1, 0};

        // 移动逻辑
        SnakeNode nextHead = {snake.front().x + dir.x, snake.front().y + dir.y};

        if (nextHead.x < 0 || nextHead.x >= GRID_SIZE || nextHead.y < 0 || nextHead.y >= GRID_SIZE) {
            std::cout << "Game Over! Score: " << score << std::endl;
            break;
        }

        if (nextHead.x == food.x && nextHead.y == food.y) {
            score++;
            food = {rand() % GRID_SIZE, rand() % GRID_SIZE};
        } else {
            snake.pop_back();
        }
        
        snake.insert(snake.begin(), nextHead);
    }

    return 0;
}