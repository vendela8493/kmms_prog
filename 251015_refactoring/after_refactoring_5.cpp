#include <cmath>
#include <iostream>

void calculate_day_of_week(int date, int month, int year);
void print_day_of_week(int day);

int main() { 
    int const date, month, year;
    std::cout << "Введите день" << std::endl;
    std::cin >> date;
    std::cout << "Введите число месяца" << std::endl;
    std::cin >> month;
    std::cout << "Введите год" << std::endl;
    std::cin >> year;

    int day = calculate_day_of_week(date, month, year);
    print_day_of_week(day);

    return 0;
}

void calculate_day_of_week(int date, int month, int year) {
    int year_of_century = year % 100;
    int century = year / 100;
    int day = (
        date + 
        (13 * month-1) / 5 + 
        year_of_century / 4 + 
        century / 4 - 
        2 * century + 
        777
    ) % 7;

    return day;  
}

void print_day_of_week(const int day) {
    std::cout << "День недели: ";

    switch (day) {
        case 0:
            std::cout << "Воскресенье" << std::endl;
            break;
        case 1:
            std::cout << "Понедельник" << std::endl;
            break;
        case 2:
            std::cout << "Вторник" << std::endl;
            break;
        case 3:
            std::cout << "Среда" << std::endl;
            break;
        case 4:
            std::cout << "Четверг" << std::endl;
            break;
        case 5:
            std::cout << "Пятница" << std::endl;
            break;
        case 6:
            std::cout << "Суббота" << std::endl;
            break;
    }
}
