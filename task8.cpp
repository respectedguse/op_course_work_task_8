/*----------------------------------------------------------------<Header>-
Name: task8.cpp
Title: Kakuro puzzle solver

Group: TB-51
Student: Kucheriavyi V.Y.
Written: 25.04.2026
Revised: 02.05.2026

Description: This program solves Kakuro puzzle. 
             The user selects one of the three build-in test cases.
             After pressing button "Solve", a backtracking algorithm 
             fills the white celss with digits from 1 to 9 such that 
             the sums in horizontal and vertical blocks match
             the given sum, and digits within a block are not repeated.
             The result is displayed graphically using the Qt library. 
             The solving time is shown in the main window.
------------------------------------------------------------------</Header>-*/


#include <QApplication>
#include <iostream>

#include "mainwindow.h"

/*
    the main function creates a QAplication, displays the main window and starts the QT event loop.
*/

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}