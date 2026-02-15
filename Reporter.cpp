#include <iostream>
#include <fstream>
#include <string>
#include "Employee.h"

int main(int argc, char* argv[]) {
    if (argc < 4) return 1;

    std::string binFile = argv[1];
    std::string reportFile = argv[2];
    double payPerHour = std::stod(argv[3]);

    std::ifstream in(binFile, std::ios::binary);
    std::ofstream out(reportFile);

    if (!in || !out) return 1;

    out << "Report for file: " << binFile << "\n";
    out << "ID, Name, Hours, Salary\n";

    employee emp;
    while (in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        double salary = emp.hours * payPerHour;
        out << emp.num << " " << emp.name << " " << emp.hours << " " << salary << "\n";
    }

    in.close();
    out.close();
    return 0;
}