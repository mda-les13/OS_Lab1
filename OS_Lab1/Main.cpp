#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <limits>
#include "Employee.h"

void runProcess(const std::string& command)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(NULL,   // No module name (use command line)
        const_cast<char*>(command.c_str()), // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)            // Pointer to PROCESS_INFORMATION structure
        )
    {
        std::cerr << "CreateProcess failed (" << GetLastError() << ")." << std::endl;
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void printBinaryFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    employee emp;
    while (file.read(reinterpret_cast<char*>(&emp), sizeof(emp)))
    {
        std::cout << "Number: " << emp.num << ", Name: " << emp.name << ", Hours: " << emp.hours << std::endl;
    }

    file.close();
}

void printReportFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening report file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }

    file.close();
}

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    std::string binaryFilename, reportFilename;
    int numRecords;
    double hourlyRate;

    std::cout << "Enter binary filename: ";
    std::cin >> binaryFilename;
    std::cout << "Enter number of records: ";
    std::cin >> numRecords;

    std::string creatorCommand = "OS_Lab1_Creator " + binaryFilename + " " + std::to_string(numRecords);
    runProcess(creatorCommand);

    std::cout << "\nBinary file contents:" << std::endl;
    printBinaryFile(binaryFilename);

    std::cout << "\nEnter report filename: ";
    std::cin >> reportFilename;
    std::cout << "Enter hourly rate: ";
    std::cin >> hourlyRate;

    std::string reporterCommand = "OS_Lab1_Reporter " + binaryFilename + " " + reportFilename + " " + std::to_string(hourlyRate);
    runProcess(reporterCommand);

    std::cout << "\nReport contents:" << std::endl;
    printReportFile(reportFilename);

    return 0;
}