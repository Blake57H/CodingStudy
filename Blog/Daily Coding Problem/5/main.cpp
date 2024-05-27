#include <iostream>

int cons(int a, int b){
    auto pair(int* f){
        return f(a, b);
    }
    return pair;
}

int main(int argc, char* argv[]){
    auto result = cons();
    std::cout << "Result: " << result << "\n";
    return 0;
}