#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Employee.h"

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    char* filename = argv[1];
    int count = std::stoi(argv[2]);

    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        employee emp;
        std::cout << "Enter ID, Name, Hours for employee " << i + 1 << ": ";
        std::cin >> emp.num >> emp.name >> emp.hours;
        out.write(reinterpret_cast<const char*>(&emp), sizeof(employee));
    }

    out.close();
    return 0;
}