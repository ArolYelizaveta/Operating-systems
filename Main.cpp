#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include "employee.h"

void startProcess(std::string cmdLine) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Создание процесса
    if (!CreateProcessA(NULL, &cmdLine[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
        return;
    }

    // Ожидание завершения (согласно условию)
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    std::string binFileName;
    int empCount;

    std::cout << "Enter binary file name: ";
    std::cin >> binFileName;
    std::cout << "Enter number of records: ";
    std::cin >> empCount;

    // 1. Запуск Creator
    std::string creatorCmd = "Creator.exe " + binFileName + " " + std::to_string(empCount);
    startProcess(creatorCmd);

    // 2. Чтение бинарного файла на консоль
    std::ifstream in(binFileName, std::ios::binary);
    employee emp;
    std::cout << "\nBinary file content:\n";
    while (in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        std::cout << emp.num << " " << emp.name << " " << emp.hours << "\n";
    }
    in.close();

    // 3. Запуск Reporter
    std::string reportFileName;
    double pay;
    std::cout << "\nEnter report file name: ";
    std::cin >> reportFileName;
    std::cout << "Enter pay per hour: ";
    std::cin >> pay;

    std::string reporterCmd = "Reporter.exe " + binFileName + " " + reportFileName + " " + std::to_string(pay);
    startProcess(reporterCmd);

    // 4. Вывод отчета
    std::ifstream rep(reportFileName);
    std::string line;
    std::cout << "\nFinal Report:\n";
    while (std::getline(rep, line)) {
        std::cout << line << "\n";
    }

    return 0;
}