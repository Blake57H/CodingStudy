#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <format>

struct CharNode
{
    char current_char;
    std::unordered_set<std::shared_ptr<CharNode>> next_chars;

    CharNode(char c) : current_char(c) {};
};

// std::vector<std::string_view::iterator> longestCommonSubstringRecursive(const CharNode *map_root, std::string_view target, const size_t &curr_max_length)
// {
//     size_t max_length = 0, str_len = target.length();
//     std::vector<std::string_view::iterator> tgt_it, tgt_it_tmp;
//     // I gave up at this point...
//     // the python solution is much more clean.
// }

int solve(std::string_view src, std::string_view target)
{
    // root node
    std::unique_ptr<CharNode> root = std::make_unique<CharNode>('\0');

    // making source string tree, time=O(n^2+n), space=O(n) << reusing pointer to save space...?
    {
        std::unordered_map<std::string_view::iterator, std::shared_ptr<CharNode>> char_obj_map;
        for (auto i = src.begin(); i != src.end(); i++)
        {
            char_obj_map.emplace(i, std::make_shared<CharNode>(*i));
            root->next_chars.emplace(char_obj_map.at(i));
        }
        for (auto i = src.begin(); i != src.end(); i++)
            for (auto j = i + 1; j != src.end(); j++)
                char_obj_map.at(i)->next_chars.emplace(char_obj_map.at(j));
    }

    // getting most common substring
    std::vector<std::string_view::iterator> src_it, tgt_it; // source string iterator and target string iterator
    // this is checkpoint when looking for edit distances
    {
    }

    return 0;
}

// implement the python solution in c++
int solve2(std::string_view src, std::string_view target)
{
    std::vector<std::vector<size_t>> map(src.length() + 1, std::vector<size_t>(target.length() + 1, 0));

    for (size_t i = 0; i < src.length() + 1; i++)
        for (size_t j = 0; j < target.length() + 1; j++)
            if (i == 0)
                map[i][j] = j;
            else if (j == 0)
                map[i][j] = i;
            else if (src[i - 1] == target[j - 1])
                map[i][j] = map[i - 1][j - 1];
            else
                map[i][j] = 1 + std::min<size_t>({map[i][j - 1], map[i - 1][j], map[i - 1][j - 1]});


    // code below are a mess that should be ignored.........

    // printing the map
    for (size_t i = 0; i < src.length() + 1; i++)
    {
        std::cout << '[';
        for (size_t j = 0; j < target.length() + 1; j++)
        {
            std::cout << map[i][j] << ',';
        }
        std::cout << ']' << std::endl;
    }

    // try printing the process of turning source string to target string
    std::string sample_str = std::string(src);
    std::string_view ARROW = " --> ";
    const int INSERTION = 0, DELETION = 1, REPLACEMENT = 2;
    int mode;
    std::cout << sample_str;
    for (size_t i = 0, j = 0; i <= src.length() && j <= target.length();)
    {
        mode = REPLACEMENT;
        size_t min = j == target.length() || i == src.length() ? map[i][j] + 2 : map[i + 1][j + 1];
        if (j == target.length() || i < src.length() && min > map[i + 1][j])
        {
            min = map[i + 1][j];
            mode = DELETION;
        }
        else if (i == src.length() || j < target.length() && min > map[i][j + 1])
        {
            min = map[i][j + 1];
            mode = INSERTION;
        }

        switch (mode)
        {
        case INSERTION:
            // sample_str.insert(sample_str.begin()+j, target[j]);
            std::cout << std::format("Insert {} at position {} {} \n", target[j], j, ARROW);
            j++;
            break;
        case DELETION:
            // sample_str.erase(sample_str.begin()+i);
            std::cout << std::format("Delete {} at position {} {} \n", src[i], i, ARROW);
            i++;
            break;
        case REPLACEMENT:
            if (map[i][j] != min)
                std::cout << std::format("Replace {} at position {} with {} {}\n", src[i], i, target[j], ARROW);
            i++;
            j++;
            break;
        default:
            std::cerr << "err" << i << ' ' << j << '\n';
            break;
        }

        if(i==src.length() && j==target.length())
            break;
    }

    return map[src.length()][target.length()];
}

int main(int argc, char *argv[])
{
    auto result = solve2("kitten", "sitting");
    std::cout << "Result: " << result << "\n";

    // https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/#better-approach-using-memoization-om-n-time-and-om-n-space
    result = solve2("AXTY", "AYZX");
    std::cout << "Result: " << result << "\n";
    return 0;
}