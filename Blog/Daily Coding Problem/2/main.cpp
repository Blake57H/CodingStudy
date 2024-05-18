#include <iostream>
#include <vector>

/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Uber.

Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.

For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].

Follow-up: what if you can't use division?

*/

std::vector<int> solve(const std::vector<int> &array)
{
    int product = 1;
    int array_size = array.size();
    std::cout << "Array size: " << array_size << "\n";
    std::vector<int> new_array(array_size, 1); // assigning array means copying array?
    // std::cout << &new_array << "\n"
    //           << &array << "\n";
    for (int i = 0; i < array_size; i++)
    {
        new_array[i] *= product;
        product *= array[i];
    }

    product = 1;
    for (int i = array_size - 1; i >= 0; i--)
    {
        // std::cout << i << "\n";
        // break;
        new_array[i] *= product;
        product *= array[i];
    }

    return new_array;
}

int main(int argc, char *argv[])
{
    std::vector<int> array1{1, 2, 3, 4, 5}, array2{3, 2, 1};

    auto result1 = solve(array1);
    std::cout << "Result 1: [";
    for (auto i : result1)
    {
        std::cout << i << ", ";
    }
    std::cout << "] \n";

    auto result2 = solve(array2);
    std::cout << "Result 2: [";
    for (auto i : result2)
    {
        std::cout << i << ", ";
    }
    std::cout << "] \n";

    return 0;
}