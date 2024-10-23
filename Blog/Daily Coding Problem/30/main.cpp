#include <iostream>
#include <vector>
#include <cmath>
#include <format>
#include <sstream>

int solve(const std::vector<size_t> &map)
{
    if (map.size() == 0)
        return 0;

    // size of map is at least 1,
    size_t volume = 0;
    std::vector<size_t>::const_iterator start_pos = map.begin();
    for (auto pos = map.begin() + 1; pos != map.end(); pos++)
    {
        // assume code won't reach here wen pos==map.begin()
        if (pos + 1 == map.end() || (*pos > *(pos - 1) && *(pos + 1) < *pos))
        {
            // marking ending height (between starting pos and ending pos, a valley will be formed)
            // start calculating how much water can be trapped in this valley
            auto shorter_height = std::min(*start_pos, *pos);
            for (auto i = start_pos + 1; i < pos; i++)
            {
                if (*i < shorter_height)
                    volume += shorter_height - *i;
            }
            start_pos = pos;
        }
    }

    return volume;
}

std::string print_map(const std::vector<size_t> &map)
{
    std::ostringstream oss;
    oss << '[';
    for (auto &i : map)
    {
        oss << i;
        if (&i != &map.back())
            oss << ',' << ' ';
    }
    oss << ']';
    return oss.str();
}

int main(int argc, char *argv[])
{
    auto maps = std::vector<std::vector<size_t>>{
        {2, 1, 2},
        {3, 0, 1, 3, 0, 5},
        {3, 0, 1, 4, 4, 4},
        {3, 0, 1, 4, 3, 4},
        {3, 0, 1, 4, 3, 2},
        {0, 0, 0, 0, 0, 0, 0},
        {3, 4, 5, 4, 5, 4},
        {3, 4, 5, 6, 5, 4},
        {3, 0, 1, 4, 5, 4}};
    for (auto map : maps)
        std::cout << std::format("Result of {}: {}\n", print_map(map), solve(map));
    return 0;
}