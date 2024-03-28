#include <iostream>

double lightYear2AstronomicalUnits(double lightYear){
    return lightYear * 63240;
}

int main(){
    double lightYear;
    std::cout << "Enter the number of light year: ";
    std::cin >> lightYear;
    std::cout << lightYear << " light year(s) = " << lightYear2AstronomicalUnits(lightYear) << " astronomical unit(s)." << std::endl;
    return 0;
}

