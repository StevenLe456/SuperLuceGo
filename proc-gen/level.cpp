#include "CXXGraph.hpp"

#include <algorithm>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <vector>

// Function headers
std::vector<int> create_level(std::map<std::string, std::vector<int>>);
int get_index(int, int, int);

// Function to procedurally generate level
std::vector<int> create_level(std::map<std::string, std::vector<int>> rooms) {
    // Seed random number generator
    srand((unsigned)time(NULL));
    
    // Randomly choose height and width
    int height = (rand() % 7) + 8;
    int width = (rand() % 7) + 8;
    
    // Create vector that stores level information
    std::vector<int> level(height * width, 0);


    // Store height and width as first two elements in level information vector
    level.insert(level.begin(), width);
    level.insert(level.begin(), height);

    // Randomly choose a float value for the probabililty of room-filling in the level
    float prob = 0.4 + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / 0.3));

    // Fill level with basic room information based on probability
    for (int i = 2; i < level.size(); i++) {
        float f = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
        if (f >= prob) {
            level.at(i) = -1;
        }
    }

    // Create a vector to store important locations
    std::vector<int> important_locs;

    // Automatically fill in the first five rooms with predefined level stuff
    level.at(get_index(height, height - 1, 0)) = rooms.at("jesus").at(0);
    important_locs.push_back(get_index(height, height - 1, 0));
    level.at(get_index(height, height - 1, 1)) = rooms.at("luce-start").at(0);
    important_locs.push_back(get_index(height, height - 1, 1));
    level.at(get_index(height, height - 1, 2)) = rooms.at("demon-intro").at(0);
    important_locs.push_back(get_index(height, height - 1, 2));
    level.at(get_index(height, height - 1, 3)) = rooms.at("mary-intercession").at(0);
    important_locs.push_back(get_index(height, height - 1, 3));
    level.at(get_index(height, height - 1, 4)) = rooms.at("demon-task").at(0);
    important_locs.push_back(get_index(height, height - 1, 4));

    // Put the ending room at the optimal spot based on the height
    if (height % 2 == 0) {
        level.at(get_index(height, 0, 0)) = rooms.at("end").at(0);
        important_locs.push_back(get_index(height, 0, 0));
    }
    else {
        level.at(get_index(height, 0, width - 1)) = rooms.at("end").at(0);
        important_locs.push_back(get_index(height, 0, width - 1));
    }

    // Fill in the beginning of a row with a moving platform and populate the room right above with an open space
    int temp = -1;
    for (int i = 0; i < height; i++) {
        std::vector slice = std::vector<int>(level.begin() + get_index(height, i, 0), level.begin() + get_index(height, i, width - 1));
        int idx = std::find(slice.begin(), slice.end(), -1) - slice.begin();
        if (idx == width) {
            idx = 0;
        }
        if (idx == temp) {
            idx++;
        }
        temp = idx;
        level.at(get_index(height, i, idx)) = rooms.at("moving-platform").at(0);
        if (i > 0) {
            level.at(get_index(height, i - 1, idx)) = rooms.at("open-space").at(0);
        }
    }

    // Randomly choose places for the demon task rooms
    int dummy = 4;
    while (dummy != 0) {
        int d = (rand() % (level.size() - 7)) + 8;
        if (level.at(d) == 0 || level.at(d) == -1) {
            level.at(d) = rooms.at("demon-task").at(dummy);
            important_locs.push_back(d);
        } 
    }

    // Fill in the rest of the space with varying rooms
    for (int i = 7; i < level.size(); i++) {
        if (level.at(i) == -1) {
            if ((i / height) <= (height / 3)) {
                level.at(i) = rooms.at("easy").at((rand() % rooms.at("easy").size()));
            }
            else if ((i / height) >= (2 * height / 3)) {
                float p = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
                if (p <= 0.2) {
                    level.at(i) = rooms.at("easy").at((rand() % rooms.at("easy").size()));
                }
                else if (p >= 0.5) {
                    level.at(i) = rooms.at("hard").at((rand() % rooms.at("hard").size()));
                }
                else {
                    level.at(i) = rooms.at("medium").at((rand() % rooms.at("medium").size()));
                }
            }
            else {
                float p = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
                if (p <= 0.3) {
                    level.at(i) = rooms.at("easy").at((rand() % rooms.at("easy").size()));
                }
                else {
                    level.at(i) = rooms.at("medium").at((rand() % rooms.at("medium").size()));
                }
            }
        }
    }

    // Create graph to store path information
    CXXGraph::Graph<int> g;

    // Populate graph with path information
    for (int i = 2; i < level.size(); i++) {
        int up = i + width;
        int right = i + 1;
        if (up >= 2 && up < level.size() && level.at(i) == rooms.at("moving-platform").at(0) && level.at(up) == rooms.at("open-space").at(0)) {
            CXXGraph::Node<int> node1(std::to_string(i), i);
            CXXGraph::Node<int> node2(std::to_string(up), up);
            std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(&node1, &node2);
            CXXGraph::UndirectedEdge<int> edge(1, pairNode);
            g.addEdge(&edge);
        }
        if (right >= 2 && right < level.size() && level.at(i) != 0 && level.at(right) != 0) {
            CXXGraph::Node<int> node1(std::to_string(i), i);
            CXXGraph::Node<int> node2(std::to_string(right), right);
            std::pair<const CXXGraph::Node<int> *, const CXXGraph::Node<int> *> pairNode(&node1, &node2);
            CXXGraph::UndirectedEdge<int> edge(1, pairNode);
            g.addEdge(&edge);
        }
    }

    return level;
}

// Function to calculate index of level vector based on grid coordinates
int get_index(int height, int row, int column) {
    return 2 + row * height + column;
}