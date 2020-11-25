#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->button_add_2, SIGNAL(clicked()), this, SLOT(Add()));
    connect(ui->button_clear_2, SIGNAL(clicked()), this, SLOT(Clear()));
    connect(ui->button_to_right_2, SIGNAL(clicked()), this, SLOT(ToRight()));
    connect(ui->button_delete_2, SIGNAL(clicked()), this, SLOT(Delete()));
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::Contains(QListWidget *list, QString text) {
    return !list->findItems(text, Qt::MatchFlag::MatchExactly).empty();
}

void MainWindow::Add() {
    auto edit = ui->edit_2;
    auto text = edit->text();
    if (text.count(' ') == text.length())
        return;
    if (!Contains(ui->list_left_2, text)) {
        ui->list_left_2->addItem(text);
        edit->setText("");
    }
}

void MainWindow::Clear() {
    ui->list_left_2->clear();
    ui->list_right_2->clear();
}

void MainWindow::ToRight() {
    QString selected = ui->list_left_2->selectedItems().first()->text();
    if (!Contains(ui->list_right_2, selected)) {
        ui->list_right_2->addItem(selected);
    }
}

void MainWindow::Delete() {
    delete ui->list_left_2->takeItem(ui->list_left_2->currentRow());
    delete ui->list_right_2->takeItem(ui->list_right_2->currentRow());
}
