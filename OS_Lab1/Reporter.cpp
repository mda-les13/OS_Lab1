#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Employee.h"

bool compareEmployees(const employee& a, const employee& b)
{
    return a.num < b.num;
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: Reporter <input_filename> <output_filename> <hourly_rate>" << std::endl;
        return 1;
    }

    const char* inputFilename = argv[1];
    const char* outputFilename = argv[2];
    double hourlyRate = std::atof(argv[3]);

    std::ifstream inputFile(inputFilename, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file!" << std::endl;
        return 1;
    }

    std::vector<employee> employees;
    employee emp;
    while (inputFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        employees.push_back(emp);
    }

    inputFile.close();

    std::sort(employees.begin(), employees.end(), compareEmployees);

    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return 1;
    }

    outputFile << "Report \"" << inputFilename << "\"" << std::endl;
    outputFile << std::setw(10) << "Number" << std::setw(10) << "Name" << std::setw(10) << "Hours" << std::setw(15) << "Salary" << std::endl;

    for (const auto& e : employees) {
        double salary = e.hours * hourlyRate;
        outputFile << std::setw(10) << e.num << std::setw(10) << e.name << std::setw(10) << e.hours << std::setw(15) << salary << std::endl;
    }

    outputFile.close();
    return 0;
}