#include <iostream>
#include <vector>
#include <random>
#include <ctime>

int main(int argc, char* argv[]){
    std::mt19937_64 generator{std::random_device{}()};
    std::vector<size_t> streamElements;
    for(size_t i = 0; i < 15; i++){
        streamElements.emplace_back(i);
    }
    // auto result = solve(streamElements);
    std::cout << "Result: "; // << result << "\n";
    std::uniform_int_distribution d(0, (int)streamElements.size()-1);
    for (size_t i = 0; i < 15; i+=1)
        std::cout << streamElements[d(generator)] << " ";
    std::cout <<std::endl;
    return 0;
}