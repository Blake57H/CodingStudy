#include <iostream>
#include <format>
#include <vector>
#include <stack>
#include <array>
#include <unordered_map>
#include <set>
#include <sstream>
#include <memory>

char PERIOD = '.', ASTERISK = '*';

// I can't...
/*
bool solve(std::string_view reg, std::string_view str)
{
    std::unique_ptr<char> period = std::make_unique<char>('.'), asterisk = std::make_unique<char>('*');
    std::vector<std::string> other_reg_part;        // just a storage to keep the string alive
    std::vector<char *> str_sequence;               // I'm using it like an index
    std::vector<std::pair<size_t, size_t>> str_pos; // starting position of each str_sequence element in "str" parameter, and its expected position
    {
        // split regular expression into special characters and normal string
        // store them in vector<char*>
        std::ostringstream str_part;
        // char* temp;
        for (const char &c : reg)
        {
            if (c == *period)
            {
                if (auto a = str_part.str(); !a.empty())
                {
                    other_reg_part.emplace_back(a);
                    str_sequence.emplace_back(other_reg_part.back().data());
                    str_part.flush();
                }
                str_sequence.emplace_back(period.get());
            }
            else if (c == *asterisk)
            {
                if (auto a = str_part.str(); !a.empty())
                {
                    other_reg_part.emplace_back(a);
                    str_sequence.emplace_back(other_reg_part.back().data());
                    str_part.flush();
                }
                str_sequence.emplace_back(asterisk.get());
            }
            else
            {
                str_part << c;
                // std::cout << (&c == &reg.back()) << std::endl;
                if (auto a = str_part.str(); &c == &reg.back())
                {
                    other_reg_part.emplace_back(a);
                    str_sequence.emplace_back(other_reg_part.back().data());
                    str_part.flush();
                }
            }
        }

        // greedy matching or not?
        // this block: try matching original string
        { // it = iterator;
            size_t npos = std::string::npos;
            size_t str_it = 0, other_str_it = 0, expected_pos = 0;
            std::vector<char *>::iterator seq_it = str_sequence.begin();
            std::stack<std::vector<char *>::iterator> after_asterisk; // rollback checkpoint
            while (str_it < str.length())
            {
                if (str_it == str.length())
                    return true;
                if (expected_pos != npos && str_it != expected_pos)
                {
                    std::cerr << std::format("Position mismatch: expected {}, got {}\n", expected_pos, str_it);
                    return false;
                }
                if (*seq_it == period.get())
                {
                    str_pos.emplace_back(std::make_pair(str_it, expected_pos));
                    seq_it++;
                    str_it++;
                    expected_pos = expected_pos == npos ? str_it : expected_pos++;
                }
                else if (*seq_it == asterisk.get())
                {
                    str_pos.emplace_back(std::make_pair(str_it, expected_pos));
                    seq_it++;
                    expected_pos = npos;
                }
                else
                {
                    std::string_view str_part_match_against = other_reg_part[other_str_it];
                    size_t pos = str.find_first_of(str_part_match_against, str_it);
                    if (pos == npos)
                    { // if string part not found, roll back seq_it to make previous asterisk more aggressive.
                        if (after_asterisk.size() == 0)
                        {
                            std::cerr << std::format("Unable to find sequence {} from pos {} in {}\n", str_part_match_against, str_it, str);
                            return false;
                        }
                    }
                    str_pos.emplace_back(std::make_pair(pos, expected_pos));
                    str_it = pos + str_part_match_against.length();
                    other_str_it++;
                    seq_it++;
                    // need to match a string
                }
            }
        }

        for (auto c : str_sequence)
        {
            if (c == period.get() || c == asterisk.get())
                std::cout << *c;
            else
                std::cout << c;
        }
        std::cout << '\n';
    }
    return 0;
}

*/


bool solve_2(std::string_view reg, std::string_view str)
{
    std::string_view::iterator curr_reg_it = reg.begin();
    // reg_it: initial regular expr position;
    // str_it: where char sequence should start comparing

    // using ordered set so that I can record the beginning of the expected next matching character sequence
    // if str.end() is in the reg.back()'s set value, then the expression-string is a match

    // give a regular expression string iterator, receive a collection of char iterators which should matches next regular expression string iterator
    // if regular expression string iterator is the last one, then it should receive .end() char iterator
    // if collection of char iterators doesn't match the next regular expression string iterator, then regular expression and string doesn't match
    std::unordered_map<std::string_view::iterator, std::set<std::string_view::iterator>> reg_str_map;

    // the python solution has one extra dimension on each side to make char sequence checking more unified.
    // Here I gotta be creative.. by using the .end() as the "extra dimension"
    reg_str_map.emplace(reg.end(), std::set<std::string_view::iterator>{str.begin()});
    std::set<std::string_view::iterator> curr_str_it_set;

    while (curr_reg_it != reg.end())
    {
        std::set<std::string_view::iterator> new_str_it_set;

        if (curr_reg_it == reg.begin())
            curr_str_it_set = reg_str_map.at(reg.end()); // just begun, there's no prev char
        else
            curr_str_it_set = reg_str_map.at(curr_reg_it - 1);

        if (*curr_reg_it == ASTERISK)
            for (auto str_it : curr_str_it_set)
                for (auto i = str_it; i <= str.end(); i++)
                {
                    new_str_it_set.emplace(i);
                    if (i == str.end())
                        break;
                }
        else if (*curr_reg_it == PERIOD)
            for (auto str_it : curr_str_it_set)
            {
                if (str_it != str.end())
                    new_str_it_set.emplace(str_it + 1);
            }
        else
            for (auto str_it : curr_str_it_set)
                if (*str_it == *curr_reg_it)
                    new_str_it_set.emplace(str_it + 1);

        reg_str_map.emplace(curr_reg_it, new_str_it_set);
        curr_reg_it++;
    }

    auto r = reg_str_map.at(reg.end() - 1);  // I can put it into if statement, but I need a breakpoint here to look into the value.
    if (r.find(str.end()) != r.end())
        return true;
    return false;
}

void begin(std::string_view reg, std::string_view str, const bool& expectation){
    std::cout << std::format("Result({}, {}): {} << {}\n", reg, str, solve_2(reg, str), expectation);
}

int main(int argc, char *argv[])
{
    std::cout << std::boolalpha;

    // problem test cases
    // std::cout << std::format("Result({}, {}): {}, expect true\n", "ra.", "ray", solve_2("ra.", "ray"));
    // std::cout << std::format("Result({}, {}): {}, expect false\n", "ra.", "raymond", solve_2("ra.", "raymond"));
    // std::cout << std::format("Result({}, {}): {}, expect true\n", ".*at", "chat", solve_2(".*at", "chat"));
    // std::cout << std::format("Result({}, {}): {}, expect false\n", ".*at", "chats", solve_2(".*at", "chats"));
    begin("ra.", "ray", true);
    begin("ra.", "raymond", false);
    begin(".*at", "chat", true);
    begin(".*at", "chats", false);

    // python solution's test case
    // std::cout << std::format("Result({}, {}): {}, expect true\n", ".*", "random-word", solve_2(".*", "random-word"));
    // std::cout << std::format("Result({}, {}): {}, expect false\n", ".*a", "random-word", solve_2(".*", "random-word"));
    begin(".*", "random-word", true);
    begin(".*a", "random-word", false);

    return 0;
}