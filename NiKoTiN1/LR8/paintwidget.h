#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);

    void SetDraw(bool draw);
protected:
    void paintEvent(QPaintEvent *) override;

private:
    bool _draw = false;
};

#endif // PAINTWIDGET_H
