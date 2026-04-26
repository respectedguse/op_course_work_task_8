cmake_minimum_required(VERSION 3.16)
project(KakuroSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/cygdrive/c/Qt/6.11.0/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(KakuroSolver
    task8.cpp
    mainwindow.cpp mainwindow.h
    kakurogridwidget.cpp kakurogridwidget.h
    puzzle.cpp puzzle.h
    solver.cpp solver.h
    combinations.cpp combinations.h
)

target_compile_options(KakuroSolver PRIVATE -Wall)
target_link_libraries(KakuroSolver Qt6::Widgets)

add_executable(KakuroTests
    tests.cpp
    puzzle.cpp puzzle.h
    solver.cpp solver.h
    combinations.cpp combinations.h
)

target_compile_options(KakuroTests PRIVATE -Wall)