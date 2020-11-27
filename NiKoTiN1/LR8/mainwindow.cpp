#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    widget = new PaintWidget(this);
    widget->setGeometry(0, 0, 800, 500);
    widget->updateGeometry();
    connect(ui->button_draw, SIGNAL(clicked()), this, SLOT(Draw()));
    connect(ui->button_clear, SIGNAL(clicked()), this, SLOT(Clear()));
}

MainWindow::~MainWindow() {
    delete widget;
    delete ui;
}

void MainWindow::Draw() {
    widget->SetDraw(true);
    repaint();
}

void MainWindow::Clear() {
    widget->SetDraw(false);
    repaint();
}
