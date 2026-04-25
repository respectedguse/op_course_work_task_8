#ifndef KAKUROGRIDWIDGET_H
#define KAKUROGRIDWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPair>

#include "puzzle.h"

/*---------------------------------------------------------------------[<]-
    Class: KakuroGridWidget
    Synopsis: Qt widget that draws the Kakuro puzzle grid. Displays
              black cells with hints, white cells with entered digits.
  ---------------------------------------------------------------------[>]-*/
class KakuroGridWidget : public QWidget {
    Q_OBJECT
public:
    KakuroGridWidget(QWidget *parent = nullptr);
    void set_puzzle(const KakuroPuzzle *puzzle);
    void set_hints(const QVector<QVector<QPair<int,int>>> &hints);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void draw_cell(QPainter &painter, int row, int col);
    int cell_size() const;

    const KakuroPuzzle *puzzle = nullptr;
    QVector<QVector<QPair<int,int>>> hints;
};

#endif