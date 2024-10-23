#include <iostream>
#include <vector>
#include <map>
#include <sstream>

template <typename T>
std::string print_vector(const std::vector<T> &vtr)
{
    if (vtr.size() == 0)
        return "null";
    std::ostringstream oss;
    oss << '[';
    for (auto i = vtr.begin(); i != vtr.end(); i++)
    {
        oss << *i;
        if (i != vtr.end() - 1)
            oss << ", ";
    }
    oss << ']';
    return oss.str();
}

std::vector<int> solve_recursive(std::map<int, int> &map, const int &k)
{
    // check if value k is in the map;
    if (auto ptr = map.find(k); ptr != map.end() && ptr->second > 0)
        return {k};

    // iterate through map and bruce force the result
    auto curr_ptr = map.begin(); // select number
    while (curr_ptr != map.end())
    {
        std::map<int, int> map_copy = map;
        if(int& v = map_copy.at(curr_ptr->first); v==1)
            map_copy.erase(curr_ptr->first);
        else
            v--;

        auto child_result = solve_recursive(map_copy, k - curr_ptr->first);
        if (child_result.size() > 0)
        {
            auto result = child_result;
            result.insert(result.begin(), curr_ptr->first);
            return result;
        }
        else
        {
            // no possible result can be found
            // implies that with "curr_ptr->first", result is impossible
            // so continue finding result without value "curr_ptr->first"
            curr_ptr = map.erase(curr_ptr);
        }
    }
    return std::vector<int>();  // no result found, return empty vector
}

std::vector<int> solve(const std::vector<int> lst, const int &k)
{
    std::map<int, int> map;

    // counting number
    for (auto v : lst)
        if (v > k)
            continue; // ignore numbers that are definitely not gonna make it
        else if (auto ptr = map.find(v); ptr == map.end())
            map.emplace(v, 1);
        else
            (ptr->second)++;

    return solve_recursive(map, k);
}

int main(int argc, char *argv[])
{

    // test data <S, k>
    std::vector<std::pair<std::vector<int>, int>> test_data{
        // data1
        {{12, 1, 61, 5, 9, 2}, 24},
        // data2
        {{1, 2, 4, 8, 12, 12}, 24},
        // data3
        {{4, 5, 6, 100}, 24}
        // end of test data
    };
    for (auto &[S, k] : test_data)
    {
        std::cout << "Result: " << print_vector<int>(solve(S, k)) << "\n";
    }
    return 0;
}