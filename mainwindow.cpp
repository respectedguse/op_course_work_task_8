#include "mainwindow.h"
#include "kakurogridwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <chrono>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), current_puzzle(nullptr), current_solver(nullptr) {
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *main_layout = new QVBoxLayout(central);

    grid_widget = new KakuroGridWidget(this);
    grid_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_layout->addWidget(grid_widget, 1);

    grid_widget->hide();

    QString intro_text = 
        "<h2 style='text-align: center; color: #E0E0E0;'>Welcome to the Kakuro Puzzle!</h2>"
        "<p style='color: #CCCCCC; line-height: 1.5;'>"
        "<b>About the game:</b> Kakuro is a logic-based math puzzle. The goal is to fill empty "
        "cells with digits from 1 to 9 so that the sum of each horizontal and vertical block matches "
        "the clue written in the adjacent black cells.<br><br>"
        "<span style='color: #FFFFFF;'><b>The main rule:</b> Digits cannot be repeated within the same sum block!</span>"
        "</p>"
        "<p style='color: #CCCCCC; line-height: 1.5;'>"
        "<b>Algorithm overview:</b> This solver implements a <i>backtracking</i> algorithm optimized with "
        "combination pre-generation. Initially, the program calculates all possible valid digits sets for "
        "each required sum. It then begins filling the grid block by block. Upon detecting an invalid "
        "intersection between horizontal and vertical blocks, the algorithm backtracks to the previous valid "
        "state and evaluates alternative paths, continuing this process until the puzzle is completely resolved."
        "</p>"
        "<p style='text-align: center; color: #A0A0A0;'><br/><i>Choose Test 1, 2 or 3 to start the game.</i></p>";

    intro_label = new QLabel(intro_text, this);
    intro_label->setWordWrap(true);
    intro_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    intro_label->setMargin(20);
    main_layout->addWidget(intro_label, 1);
    
    time_label = new QLabel("Time taken to solve the puzzle: 0.000000 second(s)", this);
    time_label->setAlignment(Qt::AlignCenter);
    time_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    main_layout->addWidget(time_label, 0);

    QHBoxLayout *button_layout = new QHBoxLayout();
    test1_button = new QPushButton("Test 1", this);
    test2_button = new QPushButton("Test 2", this);
    test3_button = new QPushButton("Test 3", this);
    solve_button = new QPushButton("Solve", this);
    button_layout->addWidget(test1_button);
    button_layout->addWidget(test2_button);
    button_layout->addWidget(test3_button);
    button_layout->addWidget(solve_button);
    main_layout->addLayout(button_layout);

    connect(test1_button, &QPushButton::clicked, this, &MainWindow::on_test1_clicked);
    connect(test2_button, &QPushButton::clicked, this, &MainWindow::on_test2_clicked);
    connect(test3_button, &QPushButton::clicked, this, &MainWindow::on_test3_clicked);
    connect(solve_button, &QPushButton::clicked, this, &MainWindow::on_solve_clicked);

    setWindowTitle("Kakuro Puzzle");
    resize(600, 600);
}

MainWindow::~MainWindow() {
    delete current_puzzle;
    delete current_solver;
}

void MainWindow::on_test1_clicked() {
    setup_puzzle_from_test(1);
}

void MainWindow::on_test2_clicked() {
    setup_puzzle_from_test(2);
}

void MainWindow::on_test3_clicked() {
    setup_puzzle_from_test(3);
}

void MainWindow::setup_puzzle_from_test(int test_id) {
    intro_label->hide();
    grid_widget->show();

    delete current_puzzle;
    delete current_solver;
    current_solver = nullptr;

    time_label->setText("Time taken to solve the puzzle: 0.000000 second(s)");

    if (test_id == 1) {
        current_puzzle = create_test1();
    } else if (test_id == 2) {
        current_puzzle = create_test2();
    } else if (test_id == 3) {
        current_puzzle = create_test3();
    } else {
        return;
    }

    compute_hints_from_blocks();
    grid_widget->set_puzzle(current_puzzle);
    grid_widget->set_hints(hints);
    grid_widget->update();
}

KakuroPuzzle *MainWindow::create_test1() {
    KakuroPuzzle *puzzle = new KakuroPuzzle(10, 10);

    for (int i = 0; i < 10; ++i) {
        puzzle->set_black_cell(0, i);
    }

    vector<pair<int, int>> black_cells = {
        {1, 0}, {1, 7},
        {2, 0}, {2, 7},
        {3, 0}, {3, 4},
        {4, 0}, {4, 3},
        {5, 0}, {5, 1}, {5, 2}, {5, 5}, {5, 8}, {5, 9},
        {6, 0}, {6, 7},
        {7, 0}, {7, 6},
        {8, 0}, {8, 3},
        {9, 0}, {9, 3}
    };

    for (const auto &black_cell: black_cells) {
        puzzle->set_black_cell(black_cell.first, black_cell.second);
    }

    vector<vector<int>> horizontal_sum = {
        {}, 
        {39, 3}, 
        {23, 9}, 
        {24, 29}, 
        {17, 23}, 
        {4, 17}, 
        {39, 13}, 
        {26, 23}, 
        {11, 27}, 
        {3, 23}
    };

    vector<vector<int>> vertical_sums = {
        {}, 
        {23, 10}, 
        {28, 22}, 
        {22, 17}, 
        {5, 21}, 
        {28, 28}, 
        {28, 5}, 
        {22, 22}, 
        {10, 23}, 
        {26, 13}
    };

    puzzle->build_blocks(horizontal_sum, vertical_sums, combo_gen);

    return puzzle;
}

KakuroPuzzle *MainWindow::create_test2() {
    KakuroPuzzle *puzzle = new KakuroPuzzle(7, 7);

    for (int i = 0; i < 7; ++i) {
        puzzle->set_black_cell(0, i);
    }

    vector<pair<int, int>> black_cells = {
        {1, 0}, {1, 1}, {1, 2}, {1, 5}, {1, 6},
        {2, 0}, {2, 1},
        {3, 0}, {3, 3}, {3, 4},
        {4, 0}, {4, 6},
        {5, 0}, {5, 1},
        {6, 0}, {6, 1}
    };

    for (const auto &black_cell: black_cells)  {
        puzzle->set_black_cell(black_cell.first, black_cell.second);
    }

    vector<vector<int>> horizontal_sum = {
        {}, 
        {15}, 
        {26}, 
        {12, 7}, 
        {27}, 
        {34}, 
        {26}
    };

    vector<vector<int>> vertical_sums = {
        {}, 
        {16}, 
        {35}, 
        {7, 9}, 
        {16, 19}, 
        {35}, 
        {4, 6}
    };

    puzzle->build_blocks(horizontal_sum, vertical_sums, combo_gen);

    return puzzle;
}

KakuroPuzzle *MainWindow::create_test3() {
    KakuroPuzzle *puzzle = new KakuroPuzzle(10, 10);

    for (int i = 0; i < 10; ++i) {
        puzzle->set_black_cell(0, i);
    }

    vector<pair<int, int>> black_cells = {
        {1, 0}, {1, 4}, {1, 5}, {1, 9},
        {2, 0}, {2, 4},
        {3, 0}, {3, 1}, {3, 6},
        {4, 0}, {4, 1}, {4, 2}, {4, 6}, {4, 7},
        {5, 0},
        {6, 0}, {6, 3}, {6, 4}, {6, 8}, {6, 9},
        {7, 0}, {7, 4}, {7, 9}, 
        {8, 0}, {8, 6},
        {9, 0}, {9, 1}, {9, 5}, {9, 6}
    };

    for (auto const &black_cell: black_cells) {
        puzzle->set_black_cell(black_cell.first, black_cell.second);
    }

    vector<vector<int>> horizontal_sum = {
        {}, 
        {21, 11}, 
        {11, 29}, 
        {27, 8}, 
        {21, 15}, 
        {45}, 
        {8, 13}, 
        {20, 12},
        {29, 11}, 
        {12, 22}
    };

    vector<vector<int>> vertical_sums = {
        {}, 
        {17, 11}, 
        {15, 34}, 
        {32, 10}, 
        {21, 16}, 
        {28}, 
        {16, 21}, 
        {7, 17}, 
        {16, 9}, 
        {29, 16}
    };

    puzzle->build_blocks(horizontal_sum, vertical_sums, combo_gen);

    return puzzle;
}

void MainWindow::compute_hints_from_blocks() {
    if (!current_puzzle) {
        return;
    }

    int rows = current_puzzle->get_rows();
    int cols = current_puzzle->get_cols();

    hints.clear();
    hints.resize(rows, QVector<QPair<int,int>>(cols, {0, 0}));

    const auto &h_blocks = current_puzzle->get_horizontal_blocks();
    for (size_t i = 0; i < h_blocks.size(); ++i) {
        const Block &bl = h_blocks[i];
        if (bl.cells.empty()) {
            continue;
        }
        int first_cell_index = bl.cells[0];
        int row = first_cell_index / cols;
        int col = first_cell_index % cols;
        if (col > 0) {
            int hint_row = row;
            int hint_col = col - 1;
            if (current_puzzle->get_cell(hint_row, hint_col).is_black) {
                hints[hint_row][hint_col].first = bl.sum;
            }
        }
    }

    const auto &v_blocks = current_puzzle->get_vertical_blocks();
    for (size_t i = 0; i < v_blocks.size(); ++i) {
        const Block &bl = v_blocks[i];
        if (bl.cells.empty()) {
            continue;
        }
        int first_cell_index = bl.cells[0];
        int row = first_cell_index / cols;
        int col = first_cell_index % cols;
        if (row > 0) {
            int hint_row = row - 1;
            int hint_col = col;
            if (current_puzzle->get_cell(hint_row, hint_col).is_black) {
                hints[hint_row][hint_col].second = bl.sum;
            }
        }
    }
}

void MainWindow::on_solve_clicked() {
    if (!current_puzzle) {
        QMessageBox::warning(this, "No puzzle", "Please select a test first.");
        return;
    }

    delete current_solver;
    current_solver = new KakuroSolver(*current_puzzle);

    auto start = chrono::high_resolution_clock::now();
    
    bool is_solved = current_solver->solve();
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    QString time_text = QString("Time taken to solve the puzzle: %1 second(s)").arg(elapsed.count(), 0, 'f', 6);
    time_label->setText(time_text);

    if (is_solved) {
        grid_widget->update();
    } else {
        QMessageBox::warning(this, "Failure", "No solution exists.");
    }
}