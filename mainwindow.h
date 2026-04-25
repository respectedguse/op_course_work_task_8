#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPair>

#include "puzzle.h"
#include "solver.h"
#include "combinations.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class KakuroGridWidget;
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_solve_clicked();
    void on_test1_clicked();
    void on_test2_clicked();
    void on_test3_clicked();

private:
    void setup_puzzle_from_test(int test_id);
    void update_grid_from_puzzle();
    void compute_hints_from_blocks();

    KakuroPuzzle *create_test1();
    KakuroPuzzle *create_test2();
    KakuroPuzzle *create_test3();

    KakuroGridWidget *grid_widget;
    QLabel *time_label;
    QLabel *intro_label;
    QPushButton *solve_button;
    QPushButton *test1_button;
    QPushButton *test2_button;
    QPushButton *test3_button;

    CombinationGenerator combo_gen;
    KakuroPuzzle *current_puzzle;
    KakuroSolver *current_solver;

    QVector<QVector<QPair<int,int>>> hints;
};

#endif