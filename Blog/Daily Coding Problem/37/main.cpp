#include <iostream>
#include <set>  // I could use unordered set but I wanna see the order of data emplecement
#include <sstream>

std::string print_set(std::set<int> s)
{
    std::ostringstream oss;
    oss << '{';
    for(auto item : s)
        oss << item << ',';
    oss << '}';
    return oss.str();
}

std::set<std::set<int>> solve(const std::set<int>& s)
{
    std::set<std::set<int>> result;

    for(int val : s)
    {
        std::set<int> copied_set(s);  // duplicate data for subset calculation
        copied_set.erase(val);  // remove one element at a time
        for(std::set<int> item : solve(copied_set))
            result.emplace(item);
    }
    result.emplace(s);  // result will include the set itself
    return result;
}

int main(int argc, char *argv[])
{
    std::set<int> test1{1, 2, 3};
    std::cout << "Result: ";
    auto result = solve(test1);
    for(auto i : result) 
        std::cout << print_set(i) << ", ";
    std::cout << std::endl;
    return 0;
}