#include <iostream>
#include <vector>
#include <map>
#include <format>
#include <algorithm>

void print_round(const std::vector<std::pair<size_t, size_t>> &living_cells, const size_t &round)
{
    using namespace std;

    size_t min_i = living_cells.front().first,
           min_j = living_cells.front().second,
           max_i = living_cells.back().first,
           max_j = living_cells.back().second;

    cout << "Round " << round << ": ";
    for (auto cell : living_cells)
    {
        cout << format("({}, {})", cell.first, cell.second);
        if (cell != living_cells.back())
            cout << ", ";
        if (cell.second > max_j)
            max_j = cell.second;
        if (cell.second < min_j)
            min_j = cell.second;
    }

    // print the map
    cout << endl;
}

std::vector<std::pair<size_t, size_t>> find_neightbour_cells(const std::pair<size_t, size_t> &cell)
{
    std::vector<std::pair<size_t, size_t>> neightbour_cells;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (i != 0 || j != 0)
                neightbour_cells.emplace_back(std::make_pair(cell.first + i, cell.second + j));
            else
                continue;
    return neightbour_cells;
}

int solve(std::vector<std::pair<size_t, size_t>> &living_cells)
{
    size_t round_counter = 0;
    std::map<std::pair<size_t, size_t>, size_t> neightbour_cells;

    std::cout << "Starting. ";
    print_round(living_cells, round_counter);
    while (living_cells.size() > 0 && round_counter < 10) // hardcode a limit to test out / avoid infinite loop
    {
        neightbour_cells.clear();
        // count neightbour cell
        for (auto living_cell : living_cells)
            for (auto neightbour_cell : find_neightbour_cells(living_cell))
            {
                if (auto c = neightbour_cells.find(neightbour_cell); c != neightbour_cells.end())
                    c->second++;
                else
                    neightbour_cells.insert({neightbour_cell, 1});
            }

        // conclude this round's living cell
        for (auto ptr = living_cells.begin(); ptr != living_cells.end();)
        {
            if (auto c = neightbour_cells.find(*ptr); c == neightbour_cells.end())
            { // living cell has no neightbour, it will die
                ptr = living_cells.erase(ptr);
                continue;
            }
            else if (2 > c->second || 3 < c->second)
            { // living cell has too few or too much neightbour, it will die
                ptr = living_cells.erase(ptr);
                neightbour_cells.erase(c->first); // erase to avoid conflict when reviving cell
                continue;
            }
            else
                neightbour_cells.erase(c->first); // erase to avoid conflict when reviving cell
            // else, it remains alive;
            ptr++;
        }

        // at this point, "neightbour_cells" should only contains dead cells.
        for (auto c = neightbour_cells.begin(); c != neightbour_cells.end(); c++)
            if (c->second == 3)
                living_cells.emplace_back(c->first);

        // round end
        std::sort(living_cells.begin(), living_cells.end());
        print_round(living_cells, ++round_counter);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    std::vector<std::pair<size_t, size_t>> cells{{5, 5}, {5, 4}, {5, 3}, {6, 5}};
    std::cout << "Result: " << solve(cells) << "\n";
    return 0;
}