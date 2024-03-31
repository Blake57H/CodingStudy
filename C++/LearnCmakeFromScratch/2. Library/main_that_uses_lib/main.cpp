#include <iostream>
#include "..\add_lib\add.h"

int main(){
    std::cout << somemath::add(1, 2) << std::endl;
    std::cout << somemath::add(1.2f, 2.3f) << std::endl;
}