#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include "Employee.h"

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

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

        while (true)
        {
            std::cout << "Enter employee number: ";
            if (std::cin >> emp.num)
            {
                clearInputBuffer();
                break;
            }
            else
            {
                std::cerr << "Invalid input. Please enter an integer." << std::endl;
                clearInputBuffer();
            }
        }

        while (true)
        {
            std::cout << "Enter employee name (max 9 chars): ";
            if (std::cin.getline(emp.name, sizeof(emp.name)))
            {
                if (strlen(emp.name) <= 9)
                {
                    break;
                }
                else
                {
                    std::cerr << "Name too long. Please enter up to 9 characters." << std::endl;
                }
            }
            else
            {
                std::cerr << "Invalid input. Please try again." << std::endl;
                clearInputBuffer();
            }
        }

        while (true)
        {
            std::cout << "Enter hours worked: ";
            if (std::cin >> emp.hours)
            {
                clearInputBuffer();
                break;
            }
            else
            {
                std::cerr << "Invalid input. Please enter a number." << std::endl;
                clearInputBuffer();
            }
        }

        file.write(reinterpret_cast<char*>(&emp), sizeof(emp));
    }

    file.close();
    return 0;
}