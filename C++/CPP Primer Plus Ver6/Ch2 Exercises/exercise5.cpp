#include <iostream>

double celsius2fahrenheit(double celsius)
{
    return celsius * 1.8 + 32;
}

int main()
{
    double celsius;
    std::cout << "Enter a Celsius value: ";
    std::cin >> celsius;
    std::cout << celsius << " degree(s) Celsius is " << celsius2fahrenheit(celsius) << " degree(s) Fahrenheit." << std::endl;
    return 0;
}
