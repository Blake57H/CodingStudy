#include <iostream>
#include <unordered_set>
#include <vector>

/*
Good morning! Here's your coding interview problem for today.

This problem was recently asked by Google.

Given a list of numbers and a number k, return whether any two numbers from the list add up to k.

For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

Bonus: Can you do this in one pass?

*/

bool solve(std::vector<int> array, int k)
{
    std::unordered_set<int> hashset;

    for (int i = 0; i < array.size(); i++){
        if (hashset.find(array[i]) != hashset.end())
            return true;
        hashset.insert(k - array[i]);
    }

    return false;
}

int main(int argc, char *argv[])
{
    // hashset in C++: https://www.geeksforgeeks.org/unordered_set-in-cpp-stl/

    int k = 17;
    // int array1[] = {10, 15, 3, 7};
    std::vector<int> array1 = {10, 15, 3, 7};

    auto result = solve(array1, k);
    std::cout << "Result: " << result << "\n";
    return 0;
}