// implement the python solution in C++

#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <format>

std::string solve(std::string_view str)
{
    // std::cout << str << std::endl;
    {
        std::string str1{str.begin(), str.end()}, str2{str.rbegin(), str.rend()};
        if (str1 == str2)
            return str1;
    }

    size_t length = str.length();
    std::ostringstream oss;

    if (str.front() == str.back())
    {
        oss << str.front() << solve(str.substr(1, length - 2)) << str.front();
        return oss.str();
    }

    std::string result1, result2;
    // oss.flush();
    // std::cout << std::format("{}, {}, ", str.substr(1, length - 1), str.substr(0, length - 1));
    oss << str.front() << solve(str.substr(1, length - 1)) << str.front();
    result1 = oss.str();
    oss.clear();
    oss.str(std::string());
    oss << str.back() << solve(str.substr(0, length - 1)) << str.back();
    result2 = oss.str();

    // std::cout << (result1 > result2) << ", " << result1 << ", " << result2 << "\n";


    if (result1.length() < result2.length())
        return result1;
    else if (result1.length() > result2.length())
        return result2;
    else
        return result1 < result2 ? result1 : result2;
}

int main(int argc, char *argv[])
{
    // std::string a{"racecar"}, b{"ecarace"};
    // std::cout << strcmp(a.c_str(), b.c_str()) << "\n";
    // std::cout << (a > b) << "\n";

    std::cout << "Result: " << solve("race") << "\n";
    std::cout << "Result: " << solve("google") << "\n";
    std::cout << "Result: " << solve("egoogle") << "\n";
    std::cout << "Result: " << solve("ogle") << "\n";
    std::cout << "Result: " << solve("elgo") << "\n";
    std::cout << "Result: " << solve("abccdefg") << "\n";
    return 0;
}