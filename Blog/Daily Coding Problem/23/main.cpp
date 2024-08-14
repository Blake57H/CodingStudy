#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <vector>
#include <cassert>
#include <format>

int calculate_distance(std::pair<int, int> start, std::pair<int, int> end)
{
    return abs(start.first - end.first) + abs(start.second - end.second);
}

struct Node
{
    int *node_addr, *prev_node_addr;
    std::pair<int, int> node_pos;
    int distance_from_start, distance_to_finish;

    int totalDistance()
    {
        return this->distance_from_start + this->distance_to_finish;
    }

    Node(int *addr, int *prev_addr, std::pair<int, int> node_pos, int distance_from_start, int distance_to_finish) : node_addr(addr), prev_node_addr(prev_addr), node_pos(node_pos), distance_from_start(distance_from_start), distance_to_finish(distance_to_finish) {};
};

std::vector<std::pair<int, int>> find_adjacent_node(const std::pair<int, int> &curr_pos, const std::pair<int, int> &map_size)
{
    std::vector<std::pair<int, int>> result;
    if (curr_pos.first > 0)
        result.emplace_back(std::make_pair(curr_pos.first - 1, curr_pos.second));
    if (curr_pos.first < map_size.first - 1)
        result.emplace_back(std::make_pair(curr_pos.first + 1, curr_pos.second));
    if (curr_pos.second > 0)
        result.emplace_back(std::make_pair(curr_pos.first, curr_pos.second - 1));
    if (curr_pos.second < map_size.second - 1)
        result.emplace_back(std::make_pair(curr_pos.first, curr_pos.second + 1));
    return result;
}

// map_size: (width, height);
int solve(int (&map)[4][4], std::pair<int, int> map_size, std::pair<int, int> start, std::pair<int, int> end)
{
    std::unordered_set<int *> visited_node;
    // std::pair<int, int> current_pos = start;
    std::shared_ptr<Node> curr_node;
    std::unordered_map<int *, std::shared_ptr<Node>> addr_node_data_map;

    // setup starting point
    // curr_node = std::make_shared<Node>(&map[end.first][end.second], nullptr, end, calculate_distance(start, end), calculate_distance(end, end));
    // addr_node_data_map.insert_or_assign(curr_node->node_addr, curr_node);
    curr_node = std::make_shared<Node>(&(map[start.first][start.second]), nullptr, start, calculate_distance(start, start), calculate_distance(start, end));
    addr_node_data_map.insert_or_assign(curr_node->node_addr, curr_node);
    // auto make_node = [=](std::pair<int, int>& node_pos)
    // { return std::make_shared<Node>(&(map[node_pos.first][node_pos.second]), curr_node->node_addr, node_pos, curr_node->distance_from_start + 1, calculate_distance(node_pos, end)); };

    // PathFindingQueue queue{start, end};
    // queue.putNode(curr_node);

    std::vector<int *> addr_queue;
    addr_queue.emplace_back(curr_node->node_addr);

    while (!addr_queue.empty())
    {
        curr_node = addr_node_data_map.at(addr_queue.front());
        std::cerr << curr_node->node_pos.first << ',' << curr_node->node_pos.second << std::endl;
        addr_queue.erase(addr_queue.begin());
        visited_node.insert(curr_node->node_addr);

        // check if current node is the destination
        if (calculate_distance(end, curr_node->node_pos) == 0)
        {
            std::cout << "destination reached\n";
            // backtrack
            std::vector<std::shared_ptr<Node>> route_backtrack;
            int *curr_node_addr = curr_node->node_addr;
            while (curr_node_addr != nullptr)
            {
                curr_node = addr_node_data_map.at(curr_node_addr);
                route_backtrack.insert(route_backtrack.begin(), curr_node);
                curr_node_addr = curr_node->prev_node_addr;
            }
            std::cout << "Route: ";
            for (auto node : route_backtrack)
            {
                std::cout << std::format("({}, {})", node->node_pos.first, node->node_pos.second);
                // std::cout << "(" << node->node_pos.first << ", " << node->node_pos.second << ")";
                if (node->node_addr != route_backtrack.back()->node_addr)
                {
                    std::cout << " -> ";
                }
            }
            std::cout << std::endl;
            return route_backtrack.size();
        }

        // add adjacent nodes if node is valid and not visited
        for (auto new_node_pos : find_adjacent_node(curr_node->node_pos, map_size))
        {
            int *new_node_addr = &map[new_node_pos.first][new_node_pos.second];

            // check if node is walkable (1 = walkable, 0 = obstacle)
            if (!*new_node_addr)
                continue;

            // checking if this "new" node has been visited
            if (visited_node.find(new_node_addr) != visited_node.end())
                continue;

            std::unordered_map<int *, std::shared_ptr<Node>>::iterator discovered_node = addr_node_data_map.find(new_node_addr);
            std::shared_ptr<Node> new_node_obj = std::make_shared<Node>(&(map[new_node_pos.first][new_node_pos.second]), curr_node->node_addr, new_node_pos, curr_node->distance_from_start + 1, calculate_distance(new_node_pos, end));
            assert(new_node_obj->node_addr == new_node_addr);
            if (discovered_node != addr_node_data_map.end())
            {
                // this new node has been discovered, but not visited.
                if (discovered_node->second->totalDistance() >= new_node_obj->totalDistance())
                {
                    // new route is shorter than previous route
                    // replacing old node data with current data
                    addr_node_data_map.insert_or_assign(new_node_addr, new_node_obj);

                    // remove node from queue (for node changed)
                    for (auto i = addr_queue.begin(); i != addr_queue.end(); i++)
                        if (*i == new_node_addr)
                        {
                            addr_queue.erase(i);
                            break;
                        }

                    {
                        // re-add node to queue
                        auto i = addr_queue.begin();
                        while (i != addr_queue.end())
                        {
                            if (addr_node_data_map.at(*i)->totalDistance() > new_node_obj->totalDistance())
                                break;
                            i++;
                        }
                        addr_queue.insert(i, new_node_addr);
                    }
                }
            }
            else
            {
                // this new node has not been discovered
                addr_node_data_map.insert_or_assign(new_node_addr, new_node_obj);
                {
                    auto i = addr_queue.begin();
                    while (i != addr_queue.end())
                    {
                        if (addr_node_data_map.at(*i)->totalDistance() > new_node_obj->totalDistance())
                            break;
                        i++;
                    }
                    addr_queue.insert(i, new_node_addr);
                }
            }

            // there shouldn't be any other conditions
        }
    }
    // ^ too fucking much nested if-else-for-while
    return 0;
}

int main(int argc, char *argv[])
{
    int f = true, t = !f; // I decided to make "true" the walkable path. if(node): walk;
    // int map[4][4] =
    //     {{f, f, f, f},
    //      {t, t, f, t},
    //      {f, f, f, f},
    //      {f, f, f, f}};
    int map[4][4] =
        {{f, f, f, f},
         {t, t, t, f},
         {f, f, t, f},
         {f, f, f, f}};
    auto result = solve(map, std::make_pair(4, 4), std::make_pair(3, 0), std::make_pair(0, 0));
    std::cout << "Result: " << result << "\n";
    return 0;
}