#include <iostream>

void printTime(const int hour, const int minute);

int main()
{
    int hour, minute;
    std::cout << "Enter the number of hours: ";
    std::cin >> hour;
    std::cout << "Enter the number of miinutes: ";
    std::cin >> minute;

    hour += minute / 60;
    minute = minute % 60;
    printTime(hour, minute);
    return 0;
}

void printTime(const int hour, const int minute)
{
    std::cout << "Time: " << hour << ":" << minute << std::endl;
}
