#include <iostream>
#include <vector>

// C++ implementation of solution from https://stackoverflow.com/a/62525133

int moveNegativeIntegerToArrayEnd(std::vector<int> &array)
{
    int start = 0, end = array.size() - 1;
    while (start < end) {
        if (array[end] <= 0){
            end -=1;
            continue;
        }
        if (array[start] > 0){
            start += 1;
            continue;
        }

        int tmp = array[end];
        array[end] = array[start];
        array[start] = tmp;
    }
    return array[start] <= 0 ? start : start + 1;
}

void markIndicesOfObservedPositiveIntegers(std::vector<int> &array, int &positive_array_length){
    for (int i = 0; i < positive_array_length; i+=1){
        int untampered_val = abs(array[i]);
        if (untampered_val <= positive_array_length) { // starts at 1, ends at array size()
            array[untampered_val-1] = -abs(array[untampered_val-1]);
        }
    }
}

int solve(std::vector<int> &array)
{
    int positive_array_size = moveNegativeIntegerToArrayEnd(array);
    markIndicesOfObservedPositiveIntegers(array, positive_array_size);
    for (int i = 0; i < positive_array_size; i++)
        if (array[i] > 0)
            return i+1;
    return positive_array_size+1;
}

int main(int argc, char *argv[])
{
    std::vector<int> arr1 = {3, 4, -1, 1}, arr2{1, 2, 0}, arr3{-1,-1,-1,-1};

    auto result = solve(arr1);
    std::cout << "Result: " << result << "\n";
    std::cout << "Result: " << solve(arr2) << "\n";
    std::cout << "Result: " << solve(arr3) << "\n";
    return 0;
}