cmake_minimum_required(VERSION 3.10)
project(OS_Lab1)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Создаем три отдельных исполняемых файла
add_executable(Creator Creator.cpp)
add_executable(Reporter Reporter.cpp)
add_executable(Main Main.cpp)