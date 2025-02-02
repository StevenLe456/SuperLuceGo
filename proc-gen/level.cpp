#include "CXXGraph.hpp"

#include <algorithm>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <vector>

// Function headers
std::vector<int> create_level(std::map<std::string, std::vector<int>>);
int get_index(int, int, int);
std::vector<int> verify_level(int, std::vector<int>, std::vector<int>, std::map<std::string, std::vector<int>>, bool flag);

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
        if ((i - 2) % level.at(1)) {
            std::cout << "\n" + std::to_string(level.at(i));
        }
        else {
            std::cout << std::to_string(level.at(i));
        }
    }
}

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
    level.at(get_index(width, height - 1, 0)) = rooms.at("jesus").at(0);
    important_locs.push_back(get_index(width, height - 1, 0));
    level.at(get_index(width, height - 1, 1)) = rooms.at("luce-start").at(0);
    important_locs.push_back(get_index(width, height - 1, 1));
    level.at(get_index(width, height - 1, 2)) = rooms.at("demon-intro").at(0);
    important_locs.push_back(get_index(width, height - 1, 2));
    level.at(get_index(width, height - 1, 3)) = rooms.at("mary-intercession").at(0);
    important_locs.push_back(get_index(width, height - 1, 3));
    level.at(get_index(width, height - 1, 4)) = rooms.at("demon-task").at(0);
    important_locs.push_back(get_index(width, height - 1, 4));

    // Put the ending room at the optimal spot based on the height
    if (height % 2 == 0) {
        level.at(get_index(width, 0, 0)) = rooms.at("end").at(0);
        important_locs.push_back(get_index(width, 0, 0));
    }
    else {
        level.at(get_index(width, 0, width - 1)) = rooms.at("end").at(0);
        important_locs.push_back(get_index(width, 0, width - 1));
    }

    // Fill in the beginning or end of a row with a moving platform and populate the room right above with an open space
    int temp = -1;
    for (int i = height - 1; i >= 0 ; i--) {
        std::vector slice = std::vector<int>(level.begin() + get_index(width, i, 0), level.begin() + get_index(width, i, width - 1));
        int idx = -1;
        if (i % 2 == 0) {
            idx = std::find(slice.begin(), slice.end(), -1) - slice.begin();
        }
        else {
            idx = slice.rend() - std::find(slice.rbegin(), slice.rend(), -1);
        }
        if (idx == width) {
            idx = 0;
        }
        if (idx == temp) {
            idx++;
        }
        temp = idx;
        std::cout << idx << std::endl;
        level.at(get_index(width, i, idx)) = rooms.at("moving-platform").at(0);
        if (i > 0) {
            level.at(get_index(width, i - 1, idx)) = rooms.at("open-space").at(0);
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

    // Verify level; if invalid level, dilate room spaces until valid 
    int dilate = 1;
    bool failure = false; // Debugging bullshit
    std::vector<int> missing = verify_level(width, level, important_locs, rooms, true);
    while (missing.size() > 0) {
        for (int i : missing) {
            int left = i - dilate;
            int right = i + dilate;
            if (left >= 2 && left < level.size()) {
                if ((left / height) <= (height / 3)) {
                    level.at(left) = rooms.at("easy").at((rand() % rooms.at("easy").size()));
                }
                else if ((left / height) >= (2 * height / 3)) {
                    float p = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
                    if (p <= 0.2) {
                        level.at(left) = rooms.at("easy").at((rand() % rooms.at("easy").size()));
                    }
                    else if (p >= 0.5) {
                        level.at(left) = rooms.at("hard").at((rand() % rooms.at("hard").size()));
                    }
                    else {
                        level.at(left) = rooms.at("medium").at((rand() % rooms.at("medium").size()));
                    }
                }
                else {
                    float p = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
                    if (p <= 0.3) {
                        level.at(left) = rooms.at("easy").at((rand() % rooms.at("easy").size()));
                    }
                    else {
                        level.at(left) = rooms.at("medium").at((rand() % rooms.at("medium").size()));
                    }
                }
            }
            if (right >= 2 && right < level.size()) {
                if ((right / height) <= (height / 3)) {
                    level.at(right) = rooms.at("easy").at((rand() % rooms.at("easy").size()));
                }
                else if ((right / height) >= (2 * height / 3)) {
                    float p = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
                    if (p <= 0.2) {
                        level.at(right) = rooms.at("easy").at((rand() % rooms.at("easy").size()));
                    }
                    else if (p >= 0.5) {
                        level.at(right) = rooms.at("hard").at((rand() % rooms.at("hard").size()));
                    }
                    else {
                        level.at(right) = rooms.at("medium").at((rand() % rooms.at("medium").size()));
                    }
                }
                else {
                    float p = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
                    if (p <= 0.3) {
                        level.at(right) = rooms.at("easy").at((rand() % rooms.at("easy").size()));
                    }
                    else {
                        level.at(right) = rooms.at("medium").at((rand() % rooms.at("medium").size()));
                    }
                }
            }
        }
        dilate++;
        if (dilate == width) {
            failure = true;
            break;
        }
        missing = verify_level(width, level, important_locs, rooms, true);
    }

    // Get rid of disconnected rooms
    std::vector<int> connected = verify_level(width, level, important_locs, rooms, false);
    for (int i = 7; i < level.size(); i++) {
        if (std::find(connected.begin(), connected.end(), i) - connected.begin() == level.size()) {
            level.at(i) = 0;
        }
    }

    return level;
}

// Function to calculate index of level vector based on grid coordinates
int get_index(int width, int row, int column) {
    return 2 + row * width + column;
}

// Function to verify level using graph algorithms
std::vector<int> verify_level(int width, std::vector<int> level, std::vector<int> important_locs, std::map<std::string, std::vector<int>> rooms, bool flag) {
    // Create graph to store path information
    std::vector<CXXGraph::Node<int>> nodes;
    CXXGraph::T_EdgeSet<int> edgeSet;

    // Create nodes
    for (int i = 2; i < level.size(); i++) {
        nodes.push_back(CXXGraph::Node<int>(std::to_string(i), i));
    }

    // Populate graph with path information
    int cnt = 1;
    for (int i = 2; i < level.size(); i++) {
        int up = i + width;
        int right = i + 1;
        if (up >= 2 && up < level.size() && level.at(i) == rooms.at("moving-platform").at(0) && level.at(up) == rooms.at("open-space").at(0)) {
            CXXGraph::UndirectedEdge<int> edge(cnt++, nodes.at(i), nodes.at(up));
            edgeSet.insert(std::make_shared<CXXGraph::Edge<int>>(edge));
        }
        if (right >= 2 && right < level.size() && level.at(i) != 0 && level.at(right) != 0) {
            CXXGraph::UndirectedEdge<int> edge(cnt++, nodes.at(i), nodes.at(right));
            edgeSet.insert(std::make_shared<CXXGraph::Edge<int>>(edge));
        }
    }
    CXXGraph::Graph<int> g(edgeSet);

    // Use graph slicing algorithm to check if all important places are connected to beginning room
    std::vector<CXXGraph::Node<int>> n = g.graph_slicing(nodes.at(1));
    std::vector<int> n_int;
    for (CXXGraph::Node nod : n) {
        n_int.push_back(nod.getId());
    }
    std::vector<int> missing;
    for (int i : important_locs) {
        if (std::find(n_int.begin(), n_int.end(), i) - n_int.begin() == n_int.size()) {
            missing.push_back(i);
        }
    }

    if (flag) {
        return missing;
    }
    else {
        return n_int;
    }
}