#include <iostream>
#include <vector>
#include <format>

inline size_t diff_abs(const size_t &a, const size_t &b)
{ // calculate absolute value of difference of a and b
    // abs(a-b), but with unsigned long long
    return a > b ? a - b : b - a;
}

std::vector<std::vector<std::pair<size_t, size_t>>> solve_recursive(const size_t &N, const size_t &curren_n, std::vector<std::pair<size_t, size_t>> &placed_queen)
{
    std::vector<std::vector<std::pair<size_t, size_t>>> placement_result;
    if (curren_n == N)
    {
        // summarize current placement and return;
        placement_result.emplace_back(placed_queen);
        return placement_result;
    }

    // placing queen at row "current_n", and find which column to put the queen
    for (size_t i = 0; i < N; i++)
    {
        bool can_place_queen = true;
        for (auto q : placed_queen)
        {
            // row is guaranteed to be different, no checking needed.
            if (q.second == i)
                can_place_queen = false; // check if same column
            if (diff_abs(curren_n, q.first) == diff_abs(i, q.second))
                can_place_queen = false; // check if same diagonal
            if (!can_place_queen)
                break;
        }
        if (!can_place_queen)
            continue;

        // place queen
        std::vector<std::pair<size_t, size_t>> copied_placed_queen(placed_queen);
        copied_placed_queen.emplace_back(std::make_pair(curren_n, i));
        for (auto child_result : solve_recursive(N, curren_n + 1, copied_placed_queen))
            placement_result.emplace_back(child_result);
    }
    return placement_result;
}

void print_placement_result(const std::vector<std::vector<std::pair<size_t, size_t>>> placement_results)
{
    using namespace std;
    for (size_t i = 0; i < placement_results.size(); i++)
    {
        cout << '[';
        for (size_t j = 0; j < placement_results[i].size(); j++)
        {
            cout << format("({}, {})", placement_results[i][j].first, placement_results[i][j].second);
            if (j + 1 < placement_results[i].size())
                cout << ", ";
        }
        cout << "]\n";
    }
}

int solve(const size_t &N)
{
    std::vector<std::vector<std::pair<size_t, size_t>>> placement_results;
    std::vector<std::pair<size_t, size_t>> placement; // empty vector
    for (auto result_item : solve_recursive(N, 0, placement))
        placement_results.emplace_back(result_item);
    print_placement_result(placement_results);
    return placement_results.size();
}

int main(int argc, char *argv[])
{
    std::cout << "Result: " << solve(5) << "\n";
    return 0;
}