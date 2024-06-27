#include <iostream>
#include <vector>

void solve(std::vector<int> &arr, const size_t &k)
{
    if (k == 1)
        return; // time=O(1), memory=O(0);
    if (k == 2)
    { // time=O(n), memory=O(1) (Correct me if this is wrong)
        for (size_t i = 0; i + 1 < arr.size(); i++)
            arr[i] = arr[i] > arr[i + 1] ? arr[i] : arr[i + 1];
        return;
    }

    std::vector<size_t> deque(k);
    // calculating the 1st element
    for(size_t i = 0; i < k; i++){
        while(deque.size()>0 && arr[deque.back()] < arr[i])
            deque.pop_back();
        deque.emplace_back(i);
    }
    arr[0] = arr[deque[0]];
    size_t arrPtr = 1;
    //generating the rest of the resultant elements
    for(size_t i = k; i < arr.size(); i++){
        while(deque.size()>0 && deque[0] <= i-k)
            deque.erase(deque.begin());
        while(deque.size()>0 && arr[deque.back()] <= arr[i])
            deque.pop_back();
        deque.emplace_back(i);
        arr[arrPtr] = arr[deque.front()];
        arrPtr+=1;
    }
    return;
}

int main(int argc, char *argv[])
{
    std::vector<int> arr = {10, 5, 2, 7, 8, 7};  // [10, 7, 8, 8]
    size_t k = 3;
    solve(arr, k);
    std::cout << "Result: ";
    for (size_t i = 0; i < arr.size() - k + 1; i++)
        std::cout << arr[i] << ',';
    std::cout << std::endl;

    arr = {10, 5, 9, 7, 8, 7};  // 10 9 9 8
    solve(arr, k);
    std::cout << "Result: ";
    for (size_t i = 0; i < arr.size() - k + 1; i++)
        std::cout << arr[i] << ',';
    std::cout << std::endl;

    arr = {10, 5, 9, 7, 8, 7};
    k = 4;
    solve(arr, k); // 10 9 9
    std::cout << "Result: ";
    for (size_t i = 0; i < arr.size() - k + 1; i++)
        std::cout << arr[i] << ',';
    std::cout << std::endl;
    return 0;
}