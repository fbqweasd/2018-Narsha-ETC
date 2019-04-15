#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QLayout>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    //Serial
    QWidget *main_Widget;
    QGridLayout *layout;
    QPushButton *push_Button;
    QLabel *Message;
    QSerialPort *port;
    QLineEdit *line_Edit;
    QLabel *Data;


private slots:
    void on_pushButton_clicked();
    void text_Sending();
    void text_Reading();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
