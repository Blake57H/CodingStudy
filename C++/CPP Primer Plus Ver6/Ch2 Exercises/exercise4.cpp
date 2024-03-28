#include <iostream>

int main()
{
    int age_year;

    std::cout << "Enter your age: ";
    std::cin >> age_year;

    int age_month = age_year * 12;
    std::cout << "Your age in month is " << age_month << "." << std::endl;

    return 0;
}
