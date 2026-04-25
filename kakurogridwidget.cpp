#include "kakurogridwidget.h"

#include <QPainter>
#include <QFont>

KakuroGridWidget::KakuroGridWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 400);
}

void KakuroGridWidget::set_puzzle(const KakuroPuzzle *p) {
    puzzle = p;
    update();
}

void KakuroGridWidget::set_hints(const QVector<QVector<QPair<int,int>>> &h) {
    hints = h;
    update();
}

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

void KakuroGridWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if (!puzzle) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int rows = puzzle->get_rows();
    int cols = puzzle->get_cols();
    int sz = cell_size();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            draw_cell(painter, r, c);
        }
    }
}

void KakuroGridWidget::draw_cell(QPainter &painter, int row, int col) {
    int sz = cell_size();
    int x = col * sz;
    int y = row * sz;

    QRect rect(x, y, sz, sz);
    const Cell &cell = puzzle->get_cell(row, col);

    if (cell.is_black) {
        painter.fillRect(rect, Qt::black);
        painter.setPen(Qt::white);
        QFont font = painter.font();
        font.setPointSize(qMax(8, sz / 5));
        painter.setFont(font);

        int hor_hint = (row < hints.size() && col < hints[row].size()) ? hints[row][col].first : 0;
        int ver_hint = (row < hints.size() && col < hints[row].size()) ? hints[row][col].second : 0;

        if (hor_hint > 0) {
            painter.drawText(x + 4, y + sz / 3, QString::number(hor_hint));
        }
        if (ver_hint > 0) {
            painter.drawText(x + sz - sz / 4, y + sz - 4, QString::number(ver_hint));
        }
    } else {
        painter.fillRect(rect, QColor(240, 240, 240));
        painter.setPen(Qt::black);
        if (cell.value != 0) {
            QFont font = painter.font();
            font.setPointSize(qMax(10, sz / 3));
            painter.setFont(font);
            painter.drawText(rect, Qt::AlignCenter, QString::number(cell.value));
        }
    }
    painter.setPen(Qt::gray);
    painter.drawRect(rect);
}