#include "kakurogridwidget.h"

#include <QPainter>
#include <QFont>

/*---------------------------------------------------------------------[<]-
    Function: KakuroGridWidget
    Synopsis: Constructor that sets minimum widget size.
  ---------------------------------------------------------------------[>]-*/
KakuroGridWidget::KakuroGridWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 400);
}

/*---------------------------------------------------------------------[<]-
    Function: set_puzzle
    Synopsis: Sets the puzzle to display and refresh the widget.
  ---------------------------------------------------------------------[>]-*/
void KakuroGridWidget::set_puzzle(const KakuroPuzzle *p) {
    puzzle = p;
    update();
}

/*---------------------------------------------------------------------[<]-
    Function: set_hints
    Synopsis: Stores hints pairs for black cells.
  ---------------------------------------------------------------------[>]-*/
void KakuroGridWidget::set_hints(const QVector<QVector<QPair<int,int>>> &h) {
    hints = h;
    update();
}

/*---------------------------------------------------------------------[<]-
    Function: cell_size
    Synopsis: Computes cell size based on widget dimensions and grid size.
  ---------------------------------------------------------------------[>]-*/
int KakuroGridWidget::cell_size() const {
    if (!puzzle) {
        return 50;
    }

    int rows = puzzle->get_rows();
    int cols = puzzle->get_cols();

    if (rows == 0 || cols == 0) {
        return 50;
    }

    int w = width() / cols;
    int h = height() / rows;

    return qMin(w, h);
}

/*---------------------------------------------------------------------[<]-
    Function: pantEvent
    Synopsis: Overridden paint event. Draws all grid cells.
  ---------------------------------------------------------------------[>]-*/
void KakuroGridWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if (!puzzle) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int rows = puzzle->get_rows();
    int cols = puzzle->get_cols();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            draw_cell(painter, r, c);
        }
    }
}

/*---------------------------------------------------------------------[<]-
    Function: draw_cell
    Synopsis: Draws a single black/white cell.
  ---------------------------------------------------------------------[>]-*/
void KakuroGridWidget::draw_cell(QPainter &painter, int row, int col) {
    int size = cell_size();
    int x = col * size;
    int y = row * size;

    QRect rect(x, y, size, size);
    const Cell &cell = puzzle->get_cell(row, col);

    if (cell.is_black) {
        painter.fillRect(rect, Qt::black);
        painter.setPen(Qt::white);
        QFont font = painter.font();
        font.setPointSize(qMax(8, size / 5));
        painter.setFont(font);

        int hor_hint = (row < hints.size() && col < hints[row].size()) ? hints[row][col].first : 0;
        int ver_hint = (row < hints.size() && col < hints[row].size()) ? hints[row][col].second : 0;

        if (hor_hint > 0) {
            painter.drawText(x + 4, y + size / 3, QString::number(hor_hint));
        }
        if (ver_hint > 0) {
            painter.drawText(x + size - size / 4, y + size - 4, QString::number(ver_hint));
        }
    } else {
        painter.fillRect(rect, QColor(240, 240, 240));
        painter.setPen(Qt::black);
        if (cell.value != 0) {
            QFont font = painter.font();
            font.setPointSize(qMax(10, size / 3));
            painter.setFont(font);
            painter.drawText(rect, Qt::AlignCenter, QString::number(cell.value));
        }
    }
    painter.setPen(Qt::gray);
    painter.drawRect(rect);
}