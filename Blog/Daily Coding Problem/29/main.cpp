#include <iostream>
#include <sstream>
#include <format>

std::string encode(const std::string_view orig_str)
{
    if (orig_str.length() == 0)
        return orig_str.data();
    std::ostringstream oss;
    std::string_view::iterator prev_char = orig_str.begin();
    size_t char_counter = 1;
    for (auto curr_char = prev_char + 1; curr_char != orig_str.end(); curr_char++)
    {
        if (*curr_char != *prev_char)
        {
            oss << char_counter << *prev_char;
            char_counter = 0;
            prev_char = curr_char;
        }
        char_counter++;
    }
    // closing the last character when the for loop reaches its end
    oss << char_counter << *prev_char;
    return oss.str();
}

std::string decode(const std::string_view encoded_str)
{
    if (encoded_str.length() == 0)
        return encoded_str.data();
    size_t char_count = 0;
    std::ostringstream oss;
    char ZERO = '0', NINE = '9';
    std::string_view::iterator curr_char = encoded_str.begin();
    while (curr_char != encoded_str.end())
    {
        if (ZERO <= *curr_char && *curr_char <= NINE)
            char_count = char_count * 10 + (size_t)(*curr_char - ZERO);
        else
        {
            // if encoded char is valid, last character should not be a digit.
            // based on the assumption of "encoded string is valid", I don't need to write a check function.
            for (size_t i = 0; i < char_count; i++)
                oss << *curr_char;
            char_count = 0;
        }
        curr_char++;
    }
    return oss.str();
}

void solve(std::string_view test_string)
{
    std::string encoded = encode(test_string), decoded = decode(encoded);
    std::cout << std::format("Source  string: '{}'\n", test_string)
              << std::format("Encoded string: '{}'\n", encoded)
              << std::format("Decoded string: '{}'\n", decoded)
              << std::endl;
}

int main(int argc, char *argv[])
{
    solve("AAAABBBCCDAA");
    solve("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBCCDAA");
    return 0;
}