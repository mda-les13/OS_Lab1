#include <iostream>
#include <fstream>
#include <cstring>
#include "Employee.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: Creator <filename> <number_of_records>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    int num_records = std::atoi(argv[2]);

    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    for (int i = 0; i < num_records; ++i)
    {
        employee emp;
        std::cout << "Enter employee number: ";
        std::cin >> emp.num;
        std::cout << "Enter employee name (max 9 chars): ";
        std::cin >> emp.name;
        std::cout << "Enter hours worked: ";
        std::cin >> emp.hours;

        file.write(reinterpret_cast<char*>(&emp), sizeof(emp));
    }

    file.close();
    return 0;
}