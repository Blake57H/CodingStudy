#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <format>

void print_matrix(const std::vector<std::vector<size_t>> &matrix)
{
    using namespace std;
    cout << '\n';
    for (auto i : matrix)
    {
        cout << '[';
        for (auto j : i)
            cout << j << ' ';
        cout << ']' << '\n';
    }
}

enum NextMove
{
    UP,
    LEFT,
    UP_LEFT
};

std::string backtrack_fails_1(const size_t &str_len, std::string_view str, const std::vector<std::vector<size_t>> &matrix)
{
    std::vector<char> front_insert, back_insert, result_str(str.begin(), str.end());
    size_t front_insert_off = 0, back_insert_off = str_len, offset = 0;
    std::ostringstream oss;
    // if(matrix[str_len][str_len] == matrix[str_len-1][str_len-1] && str.front() < str.back())
    //     front_insert_off++;
    for (size_t i = str_len, j = str_len; i > 0 && j > 0;)
    {
        // check top and/or left
        if (i > 1 || j > 1)
        {
            if (i > 1 && j > 1 && matrix[i - 1][j - 1] == matrix[i][j])
            {
                // for same value top left, top priority

                offset++;
                front_insert.emplace_back(str[str_len - i]);
                back_insert.insert(back_insert.begin(), str[j - 1]);

                if (i == str_len && j == str_len)
                {
                    if (str.front() < str.back())
                        front_insert_off++;
                }
                i--;
                j--;
                continue;
            }

            // for same value top or left, second priority
            if (i > 1 && matrix[i - 1][j] == matrix[i][j])
            {
                // j == 1, and move up, adding front char to the back
                // back_insert.insert(back_insert.begin(), str[str_len - i]);

                result_str.insert(result_str.begin() + back_insert_off, str[str_len - i]);
                front_insert_off++;

                i--;
                continue;
            }
            else if (j > 1 && matrix[i][j - 1] == matrix[i][j])
            {
                // i == 1, and move left, adding back char to the front
                // front_insert.emplace_back(str[j - 1]);

                result_str.insert(result_str.begin() + front_insert_off, str[j - 1]);
                back_insert_off++;

                j--;
                continue;
            }

            // otherwise, expect difference of 1 between current cell and top left, and move to top left
            else
            {
                // -1 == matrix[i - 1][j - 1] - matrix[i][j]
                // If I'm initialize result_str with original_str and inserting new characters to it,
                // I shouldn't need to do anything cos the char is already there.

                front_insert_off++;

                j--;
                i--;
                continue;
            }
        }

        // i == 1 && j == 1, last cell to read
        if (matrix[i][j] == 0)
        {
            front_insert.emplace_back(str[str_len - i]);
            back_insert.insert(back_insert.begin(), str[j]);
        }
        else
        {
            //  do nothing because that string's first and last character is the same
        }
        i--;
        j--; // loop should exit after this line
    }

    if (matrix[str_len][str_len] == matrix[str_len - 1][str_len - 1])
    {
        if (str.front() < str.back())
            // two possible result string.
            // need to find which one is alphabetically smaller
            oss << str.substr(0, offset)
                << std::string(front_insert.begin(), front_insert.end())
                << str.substr(offset, str_len - offset - front_insert.size())
                << str.substr(str_len - front_insert.size(), front_insert.size())
                << std::string(back_insert.begin(), back_insert.end());
        else
            oss
                << std::string(front_insert.begin(), front_insert.end())
                << str.substr(0, offset)
                << str.substr(offset, str_len - offset - front_insert.size())
                << std::string(back_insert.begin(), back_insert.end())
                << str.substr(str_len - front_insert.size(), front_insert.size());
    }
    else
        // otherwise doesn't matter, since either "back_insert" or "front_insert" will be empty
        oss
            << std::string(front_insert.begin(), front_insert.end())
            << str.substr(0, offset)
            << str.substr(offset, str_len - offset - front_insert.size())
            << std::string(back_insert.begin(), back_insert.end())
            << str.substr(str_len - front_insert.size(), front_insert.size());

    // return oss.str();
    return std::string(result_str.begin(), result_str.end());
}

static int use_orig_str_front_char = 2; // 2==undefined

void insert_offset_mod(size_t &front_insert_off, size_t &back_insert_off, std::string_view &orig_str, const size_t &front_insert_str_len, const size_t &back_insert_str_len)
{
    if (*(orig_str.begin() + front_insert_off) == *(orig_str.begin() + back_insert_off))
    {
        std::cerr << "this should not happen\n";
        exit(-1);
    }
    // for determining which result string to generate
    // check if offset is already modified | this mod should only happen once
    if (front_insert_off != 0 || back_insert_off != orig_str.length())
        return;

    if (orig_str.front() < orig_str.back())
    // prefer using orig_str's beginning char
    {
        front_insert_off += back_insert_str_len;
        use_orig_str_front_char = 1;
    }
    else
    {
        back_insert_off -= front_insert_str_len;
        use_orig_str_front_char = 0;
    }
}

std::string backtrack_fails_2(const size_t &str_len, std::string_view str, const std::vector<std::vector<size_t>> &matrix)
{
    std::vector<char> front_insert, back_insert, result_str(str.begin(), str.end());
    size_t front_insert_off = 0, back_insert_off = str_len,
           front_insert_ignore = 0, back_insert_ignore = 0; // this backtrack method will introduce extra character when moving up or left
                                                            // cause the matrix is kinda symmetric

    for (size_t i = str_len, j = str_len; i > 0 && j > 0;)
    {

        // special cases when reaching matrix edge (only 1~ste_len is valid, 0 is the extra row/column)
        // if (i <= 1 && j > 0)
        //     goto move_left;
        // if (j <= 1 && i > 0)
        //     goto move_up;
        if (1 == j || 1 == i)
            goto move_up_left; // the (matrix[i][j] - matrix[i-1][j-1] == 1) up left

        // by reaching the following if, I expect i>1 && j>1
        if (matrix[i][j] == matrix[i - 1][j - 1])
        {
            // add front char to back and back char to front. Push into cache vector and flush later
            front_insert.emplace_back(str[j - 1]);
            back_insert.emplace_back(str[str_len - i]);
            i--;
            j--;
            // continue;
        }
        else if (matrix[i][j] == matrix[i - 1][j])
        {
            // add front char to back, flush insert_front cache, and move up
            if (back_insert_ignore > 0)
            {
                back_insert_ignore--;
                goto move_up;
            }
            back_insert.insert(back_insert.begin(), str[str_len - i]);
            front_insert_ignore++;
        move_up:
            insert_offset_mod(front_insert_off, back_insert_off, str, front_insert.size(), back_insert.size());
            for (auto char_ptr = front_insert.begin(), insert_pos = result_str.begin() + front_insert_off; char_ptr != front_insert.end(); char_ptr++)
                insert_pos = result_str.insert(insert_pos, *char_ptr);
            front_insert.clear();
            i--;
            continue;
        }
        else if (matrix[i][j] == matrix[i][j - 1])
        {
            // add back char to front, flush insert_back cache, move left
            if (front_insert_ignore > 0)
            {
                front_insert_ignore--;
                goto move_left;
            }
            front_insert.emplace_back(str[j - 1]);
            back_insert_ignore++;
        move_left:
            insert_offset_mod(front_insert_off, back_insert_off, str, front_insert.size(), back_insert.size());
            for (auto char_ptr = back_insert.begin(), insert_pos = result_str.begin() + back_insert_off; char_ptr != back_insert.end(); char_ptr++)
                insert_pos = result_str.insert(insert_pos, *char_ptr);
            back_insert.clear();
            j--;
            continue;
        }
        else
        {
            // char can be reused, no char to add
        move_up_left:
            i--;
            j--;
            // continue;
        }

        // reaching here means last move was up left.
        // check if 0 == j && 0 == i, if so then flush the remaining cache and string should be good to go
        if (0 == j && 0 == i)
        {
            for (auto char_ptr = back_insert.begin(), insert_pos = result_str.begin() + back_insert_off; char_ptr != back_insert.end(); char_ptr++)
                insert_pos = result_str.insert(insert_pos, *char_ptr);
            for (auto char_ptr = front_insert.begin(), insert_pos = result_str.begin() + front_insert_off; char_ptr != front_insert.end(); char_ptr++)
                insert_pos = result_str.insert(insert_pos, *char_ptr);
        }
    }
    return std::string(result_str.begin(), result_str.end());
}

struct CharToAdd
{
    size_t where;
    char what;
    bool near_back;

    CharToAdd(size_t where, char what, bool near_back) : where(where), what(what), near_back(near_back) {};

    void print()
    {
        std::cout << std::format(R"( "where={}, what={}, near_back={}" )", this->where, this->what, this->near_back);
    }
    // friend std::ostream& operator<< (const std::ostream& os, const CharToAdd& obj){
    //     return os << std::format(R"( (where={}, what={}), near_back={}) )");
    // }
};

std::string backtrack(const size_t &str_len, std::string_view str, const std::vector<std::vector<size_t>> &matrix)
{
    int last_movement = 0;                    // 0 = undefined, 1 = left, 2 = up;
    std::vector<CharToAdd> char_to_add_front; // <where to add(position in result str, before adding), which char to add(position in str)>
    std::vector<char> result_str(str.begin(), str.end());
    size_t insert_chat_at_front = 0;
    for (size_t i = str_len, j = str_len; i > 1 && j > 1;)
    {
        if (matrix[i][j] == matrix[i - 1][j - 1])
        {
            // decide go up or go left
            if (last_movement == 0)
                last_movement = str[str_len - i] < str[j - 1] ? 2 : 1;

            if (last_movement == 2)
                goto up;
            if (last_movement == 1)
                goto left;
        }
        else if (last_movement == 1 || matrix[i][j] == matrix[i][j - 1])
        {
        // go left, insert str[j-1] at str[str_len-j]
        left:
            char_to_add_front.emplace_back(CharToAdd(str_len - j, str[j - 1], false));
            insert_chat_at_front++;
            j--;
            continue;
        }
        else if (last_movement == 2 || matrix[i][j] == matrix[i - 1][j])
        {
        // go up, insert str[str_len-i] at str[i-1]
        up:
            char_to_add_front.emplace_back(CharToAdd(i, str[str_len - i], true));
            i--;
            continue;
        }
        else
        {
            // go up and left, this character can be reused
            i--;
            j--;
        }
    }

    // sort char_to_add
    std::sort(char_to_add_front.begin(), char_to_add_front.end(), [](const CharToAdd &l, const CharToAdd &r)
              { return l.where < r.where; });

    for (auto c : char_to_add_front)
    {
        c.print();
    }
    std::cout << std::endl;
    for (auto c : char_to_add_front)
    {
        if (!c.near_back)
            result_str.insert(result_str.begin() + c.where, c.what);
        else
            result_str.insert(result_str.end() - str_len + c.where, c.what);
    }
    return std::string(result_str.begin(), result_str.end());
}

std::string solve(std::string_view str)
{

    size_t str_len = str.length(); // STRing LENgth
    // initialize matrix with default value 0
    std::vector<std::vector<size_t>> matrix(str_len + 1, std::vector<size_t>(str_len + 1, 0));

    for (size_t i = 1; i <= str_len; i++)
        for (size_t j = 1; j <= str_len; j++)
        {
            matrix[i][j] = matrix[i - 1][j - 1];
            if (str[str_len - i] == str[j - 1])
                matrix[i][j]++;
            if (matrix[i][j] < matrix[i - 1][j])
                matrix[i][j] = matrix[i - 1][j];
            if (matrix[i][j] < matrix[i][j - 1])
                matrix[i][j] = matrix[i][j - 1];
        }
    print_matrix(matrix);
    return backtrack(str_len, str, matrix);
}

int main(int argc, char *argv[])
{
    // std::cout << "Result: " << solve("google") << "\n";
    // std::cout << "Result: " << solve("egoogle") << "\n";
    // std::cout << "Result: " << solve("ogle") << "\n";
    std::cout << "Result: " << solve("elgo") << "\n"; // elgo gle
    return 0;
}