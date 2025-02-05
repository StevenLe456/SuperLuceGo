#include <cmath>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

// Function headers
std::vector<int> create_level(std::map<std::string, std::vector<int>>);
int get_index(int, int, int);

// Test this shit out
int main() {
    std::map<std::string, std::vector<int>> rooms;
    rooms.insert({"jesus", std::vector<int>{1}});
    rooms.insert({"luce-start", std::vector<int>{2}});
    rooms.insert({"demon-intro", std::vector<int>{3}});
    rooms.insert({"mary-intercession", std::vector<int>{4}});
    rooms.insert({"demon-task", std::vector<int>{5, 6, 7, 8, 9}});
    rooms.insert({"moving-platform", std::vector<int>{10}});
    rooms.insert({"open-space", std::vector<int>{11}});
    rooms.insert({"easy", std::vector<int>{12, 13, 14}});
    rooms.insert({"medium", std::vector<int>{15, 16, 17, 18}});
    rooms.insert({"hard", std::vector<int>{19, 20, 21}});
    rooms.insert({"end", std::vector<int>{22}});

    std::vector<int> level = create_level(rooms);

    for (int i = 2; i < level.size(); i++) {
        if ((i - 2) % level.at(1) == level.at(1) - 1) {
            if (level.at(i) / 10 == 0) {
                std::cout << "0" << level.at(i) << " \n"; 
            }
            else {
                std::cout << level.at(i) << " \n";
            }
        }
        else {
            if (level.at(i) / 10 == 0) {
                std::cout << "0" << level.at(i) << " "; 
            }
            else {
                std::cout << level.at(i) << " ";
            }
        }
    }
    std::cout << std::endl;
    return 0;
}

std::vector<int> create_level(std::map<std::string, std::vector<int>> rooms) {
    // Seed random number generator
    srand((unsigned)time(NULL));
    
    // Randomly choose height and width
    int height = (rand() % 11) + 10;
    int width = (rand() % 11) + 10;
    
    // Create vector that stores level information
    std::vector<int> level(height * width, 0);

    // Store height and width as first two elements in level information vector
    level.insert(level.begin(), width);
    level.insert(level.begin(), height);

    // Generate basic path from start to end
    int idx_1 = -1;
    int idx_2 = -1;
    std::vector<int> ends;
    for (int h = 0; h < height; h++) {
        idx_1 = idx_1 == -1 ? rand() % width : idx_2;
        idx_2 = rand() % width;
        while (std::abs(idx_2 - idx_1) < 2) {
            idx_2 = rand() % width;
        }
        if (idx_1 < idx_2) {
            std::fill(level.begin() + get_index(width, h, idx_1), level.begin() + get_index(width, h, idx_2) + 1, 99);
        }
        else {
            std::fill(level.begin() + get_index(width, h, idx_2), level.begin() + get_index(width, h, idx_1) + 1, 99);  
        }
        ends.push_back(idx_2);
    }

    for (int i = 0; i < height - 1; i++) {
        level.at(get_index(width, i, ends.at(i))) = rooms.at("open-space").at(0);
        level.at(get_index(width, i + 1, ends.at(i))) = rooms.at("moving-platform").at(0);
    }

    return level;
}

// Function to calculate index of level vector based on grid coordinates
int get_index(int width, int row, int column) {
    return 2 + row * width + column;
}