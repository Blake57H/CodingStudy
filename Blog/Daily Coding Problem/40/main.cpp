#include <iostream>
#include <vector>

int solve(const std::vector<int> &arr)
{
    std::vector<int> bit_masks;
    // int int_size = sizeof(int);
    for (int i = 1, mask = 1; i <= 8 * sizeof(int) - 1; i++, mask *= 2)
        bit_masks.emplace_back(mask); // expect len(bit_masks)==32
    std::vector<size_t> bit_count(bit_masks.size(), 0);
    for (int j = 0; j < arr.size(); j++)
    {
        int val = arr[j];
        for (int i = 0; i < bit_masks.size(); i++)
        {
            if (val & 1)
                bit_count[i]++;
            val = val >> 1;
            if (val == 0)
                break;
        }
    }

    // construct the unique value from bits
    int result = 0;
    for (auto i = bit_count.rbegin(); i != bit_count.rend(); i++)
    {
        result += *i % 3;  // bit's remainder is either 0 or 1. That 1 would come from unique value.
        if (i + 1 != bit_count.rend())
            result = result << 1;
    }
    return result;
}

int main(int argc, char *argv[])
{
    // on my Windows 11 machine, "int" is 32-bit (4 bytes).
    // asserting 32 bit when solving this problem.
    std::cout << sizeof(int) << ',' << sizeof(size_t) << std::endl;
    std::vector<int>
        data1{6, 1, 3, 3, 3, 6, 6},
        data2{13, 19, 13, 13},
        data3{1, 2, 3, 1, 2, 3, 1, 2, 3, 4};
    std::cout << "Result: " << solve(data1) << "\n";
    std::cout << "Result: " << solve(data2) << "\n";
    std::cout << "Result: " << solve(data3) << "\n";
    return 0;
}