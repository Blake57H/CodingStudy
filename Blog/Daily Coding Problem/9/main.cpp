#include <iostream>
#include <vector>
#include <string>
// #include <math.h>

int solve(std::vector<int> arr)
{
    if (arr.size() == 1)
        return arr[0];
    if (arr.size() == 2)
        return std::max(arr[0], arr[1]);

    int prev2 = arr[0], prev1 = std::max(arr[0], arr[1]), currVal;
    for (unsigned int i = 2; i < arr.size(); i += 1)
    {
        currVal = std::max(prev2 + arr[i], prev1);
        prev2 = prev1;
        prev1 = currVal;
    }

    return currVal;
}

std::string printVector(std::vector<int> arr)
{
    std::string toReturn = "[";
    for (int item : arr)
    {
        toReturn.append(std::to_string(item));
        toReturn.append(", ");
    }
    toReturn.append("]");
    return toReturn;
}

int main(int argc, char *argv[])
{
    std::vector<int> arr1{2, 4, 6, 2, 5}, arr2{5, 1, 1, 5};
    // auto result = solve(arr1);
    std::cout << "Result for " << printVector(arr1) << ": " << solve(arr1) << "\n";
    std::cout << "Result for " << printVector(arr2) << ": " << solve(arr2) << "\n";
    return 0;
}