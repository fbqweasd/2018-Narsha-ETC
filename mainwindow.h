#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//시리얼 통신을 위한 라이브러리
#include <QtSerialPort/QSerialPort>
#include <QLayout>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Serial
    QWidget *main_Widget;
    QGridLayout *layout;
    QPushButton *push_Button;
    QLabel *Message;
    QSerialPort *port;
    QLineEdit *line_Edit;
    QLabel *Data;

private slots:
    //시리얼 슬롯
    void on_pushButton_clicked(); //시리얼 신호 전송 버튼
    void text_Reading();

    void on_serial_Button_clicked(); //시리얼 포트 등록 버튼

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
