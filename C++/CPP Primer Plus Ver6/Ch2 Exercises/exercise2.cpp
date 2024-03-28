#include <iostream>

/* convert furlongs to yards (1 furlong = 220 yards) */
double exercise2(double furlongs){
    return 220*furlongs;
}

int main(){
    double furlong;
    std::cout << "Enter furlong: ";
    std::cin >> furlong;
    std::cout << furlong << " furlong(s) is " << exercise2(furlong) << " yard(s)" << std::endl;
}
