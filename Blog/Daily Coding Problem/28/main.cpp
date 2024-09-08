#include <iostream>
#include <sstream>
#include <vector>
#include <format>
#include <algorithm>
#include <cassert>

const char SPACE = ' ';

std::string buffer_to_str(const std::vector<std::string_view> &buffer, const size_t &k, const size_t &buffer_char_count)
{
    std::ostringstream oss;
    size_t remaining_space = k + 1 - buffer_char_count - buffer.size(),
           space_distributed_loop = buffer.size() == 1 ? remaining_space : remaining_space / (buffer.size() - 1), // avoid "divided by 0" if buffer has only one word
        space_distributed_remainder = remaining_space - space_distributed_loop * std::max(1ULL, buffer.size() - 1);

    // flushing buffer to result;
    oss.flush(); // make sure oss is empty
    for (size_t j = 0; j < buffer.size(); j++)
    {
        oss << buffer[j];
        // don't need tailing space at last word, with the exception of one-word-buffer.
        if ((0 != j && j + 1 == buffer.size()))
            continue;
        // check if the "one-word-buffer" has some tailing space to fill
        if (buffer[j].length() == k)
            continue;
        // this space is reserved for buffer with multiple words
        if (buffer.size() > 1)
            oss << SPACE;
        for (size_t i = 0; i < space_distributed_loop; i++)
            oss << SPACE;
        if (j < space_distributed_remainder)
            oss << SPACE;
    }

    // assertion
    if (auto a = oss.str().length(); a != k)
        std::cerr << std::format("Incorrect string length: len(\"{}\")=={}!={}\n", oss.str(), a, k);
    return oss.str();
}

std::vector<std::string> solve(const std::vector<std::string> &words, const size_t &k)
{
    std::vector<std::string> result;
    std::vector<std::string_view> word_buffer;
    size_t word_char_count = 0;
    for (auto &word : words)
    {
        // buffer contains nothing
        if (word_buffer.size() == 0)
        {
            word_buffer.emplace_back(word);
            word_char_count += word.length();
            continue;
        }
        // if buffer is full, flush buffer
        if (auto i = word_char_count + word_buffer.size(); i + word.length() > k)
        {
            result.emplace_back(buffer_to_str(word_buffer, k, word_char_count));
            word_char_count = 0;
            word_buffer.clear();
        }
        // add string to buffer
        word_buffer.emplace_back(word);
        word_char_count += word.length();
    }

    // clear remaining buffer
    if (word_buffer.size() > 0)
        result.emplace_back(buffer_to_str(word_buffer, k, word_char_count));
    return result;
}

void test(const std::vector<std::string> &test_case, const size_t &k)
{
    std::cout << "Result: \n";
    for (auto &i : solve(test_case, k))
    {
        std::cout << std::format("'{}'\n", i);
    }
    std::cout << "ResultEOF\n";
}

int main(int argc, char *argv[])
{
    test(std::vector<std::string>{"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"}, 16);
    test(std::vector<std::string>{"brown", "the", "quick", "two", "words", "AndAShorterText", "f", "f", "ha", "f", "f", "f", "f", "f", "andAVeeryLongText", "vs"}, 17);
    return 0;
}