#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <windows.h>
#else

#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QAction>
#include <cstring>

void Scan_Serial_Port(Ui::MainWindow *ui);

QString TCHARToString(const TCHAR* ptsz);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Scan_Serial_Port(ui);

    //시리얼 설정 코드
    port = new QSerialPort();
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    QObject::connect(port, SIGNAL(readyRead()), this, SLOT(text_Reading())); // 이 친구가 인터럽트 같은거
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::text_Reading(){
    QByteArray read_Data;
    read_Data = port->readAll();
    ui->textBrowser->append(read_Data);

    qDebug() << read_Data.length();
}

void MainWindow::on_pushButton_clicked() //Enter Key
{
    QByteArray send_Data;
    send_Data = ui->lineEdit->text().toUtf8();
    port->write(send_Data.data());    
}

void MainWindow::on_lineEdit_returnPressed()
{
    QByteArray send_Data;
    send_Data = ui->lineEdit->text().toUtf8();
    port->write(send_Data.data());
}

void MainWindow::on_serial_Button_clicked()//시리얼 포트 확인 버튼
{
    port->setPortName(ui->comboBox->currentText());//포트 값 가지고 오기

    if(!port->open(QIODevice::ReadWrite)){
        qDebug() << "\n Serial port open Error \n";
        ui->Flag_label->setText("Serial port Error");
    }
    else{
        ui->Flag_label->setText("Connet!");
    }
}



void Scan_Serial_Port(Ui::MainWindow *ui){ //열린 시리얼 포트 검색
    HKEY hKey; //엔 레지스트리에 접근하는 친구
    RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

    TCHAR szData[20], szName[100];
    DWORD index = 0, dwSize=100, dwSize2 = 20, dwType = REG_SZ;
    memset(szData, 0x00, sizeof(szData));  //초기화
    memset(szName, 0x00, sizeof(szName));

    while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL)){
       index++;

       RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
       QString tem = TCHARToString(szData);
       ui->comboBox->addItem(tem);

       memset(szData, 0x00, sizeof(szData));  //초기화
       memset(szName, 0x00, sizeof(szName));
       dwSize = 100;
       dwSize2 = 20;
   }

   RegCloseKey(hKey);
}

QString TCHARToString(const TCHAR* ptsz){ //자료형 변환 함수
 int len = wcslen((wchar_t*)ptsz);
 char* psz = new char[2*len + 1];
 wcstombs(psz, (wchar_t*)ptsz, 2*len + 1);
 QString s = psz;
 delete [] psz;
 return s;
}
