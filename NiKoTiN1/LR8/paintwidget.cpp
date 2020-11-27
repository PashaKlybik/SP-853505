#include "paintwidget.h"
#include <QPainter>
#include <QPen>

void drawTree(QPainter &painter) {
    painter.setBrush(QBrush(QColor(210, 105, 30), Qt::SolidPattern));
    painter.drawRect(290, 400, 40, 50);

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(QColor(20, 225, 10), Qt::SolidPattern));

    QPolygon polygon;
    polygon << QPoint(390, 400) << QPoint(230, 400);
    polygon << QPoint(300, 350) << QPoint(250, 350);
    polygon << QPoint(300, 310) << QPoint(270, 310);
    polygon << QPoint(310, 270) << QPoint(350, 310);
    polygon << QPoint(320, 310) << QPoint(370, 350);
    polygon << QPoint(320, 350);

    painter.drawPolygon(polygon);
}

void drawSun(QPainter &painter) {
    painter.setBrush(QBrush(QColor(255, 255, 0), Qt::SolidPattern));
    painter.drawEllipse(100, 100, 99, 102);
}

void drawBall(QPainter &painter){
    painter.setBrush(QBrush(QColor(255, 160, 0), Qt::SolidPattern));
    painter.drawEllipse(400, 320, 59, 62);
}

void drawBackground(QPainter &painter) {
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(QColor(0, 100, 255), Qt::SolidPattern));
    painter.drawRect(0, 0, 799, 300);
    painter.setBrush(QBrush(QColor(10, 150, 0), Qt::SolidPattern));
    painter.drawRect(0, 300, 799, 400);
}

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent) {}

void PaintWidget::SetDraw(bool draw) {
    _draw = draw;
    repaint();
}

void PaintWidget::paintEvent(QPaintEvent *) {
    if (!_draw)
        return;
    QPainter painter(this); // Создаём объект отрисовщика
    // Устанавливаем кисть
    drawBackground(painter);
    drawSun(painter);
    drawBall(painter);
    drawTree(painter);
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawRect(520, 320, 150, 150);

    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(200,200,100,100);
    painter.drawLine(200,100,100,200);


    painter.setPen(QPen(Qt::black, 3, Qt::DashLine, Qt::FlatCap));
    painter.drawArc(525, 360, 60, 80, 100 * 16, 160 * 16);
    painter.drawArc(600, 360, 60, 80, -80 * 16, 160 * 16);


}
