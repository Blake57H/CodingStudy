#include <iostream>
#include <vector>
#include <random>
#include <ctime>

class OrderLog
{
    size_t N;
    std::vector<size_t> mOrders;

public:
    OrderLog(const size_t &N)
    {
        if (N == 0)
        {
            this->N = 1;
            return;
        }
        this->N = N;
    }

    void record(const size_t &orderID)
    {
        // recording the last N order ids. If item count maxed out, remove the first one.
        if (mOrders.size() == N)
            mOrders.pop_back();
        mOrders.push_back(orderID);
    }
    std::vector<size_t> getLast(const size_t &i)
    {
        return std::vector<size_t>{mOrders.end() - i, mOrders.end()};
    }
};

int solve()
{
    size_t n = 10; // recording last 10 logs
    OrderLog logs{n}; 
    std::srand(std::time(nullptr));
    for(size_t i = 0; i < n; i+=1){
        logs.record((size_t)std::rand());
    }
    std::cout << "Items: ";
    for(auto &i : logs.getLast(n)){
        std::cout << i << ' ';
    }
    std::cout << std::endl << std::endl;


    size_t lastI = 5; // getting last 5 items
    std::cout << "Last " << lastI << " ids: ";
    for(auto &i : logs.getLast(lastI)){
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    return 0;
}

int main(int argc, char *argv[])
{
    auto result = solve();
    std::cout << "Result: " << result << "\n";
    return 0;
}