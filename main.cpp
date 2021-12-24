#include <QSerialPort>
#include <QSerialPortInfo>
QSerialPort serial;
#include <iostream>
#include <string>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <stdio.h>

using namespace std;

void txt(QByteArray data) //Funkce pro zápis dat do souboru
{
    QFile file("test.txt");
    file.open(QIODevice:: Append);
    file.write(data);
    file.close();
}

int main()
{
    //Vypis portu
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo>::iterator i;

    string port_name[20];
    int j = 0;

    for(i = ports.begin(); i != ports.end(); i++)
    {
        cout << j << " ";
        printf(" - (Name): %s%s%s%s%s%s%s\n", (*i).portName().toStdString().data(), " | (Description): ", (*i).description().toStdString().data(), " | (Manufacturer): ", (*i).manufacturer().toStdString().data(), " | (Serial number): ", (*i).serialNumber().toStdString().data());
        port_name[j] = (*i).portName().toStdString().data();
        j++;
    }



    //Uživatelský výběr portu
    printf("zadejte číslo portu: \n");
    string vybrany_port;
    string vybirani;
    cin >> vybirani;
    vybrany_port = port_name[atoi(vybirani.c_str())];
    string vysledny_port = "/dev/" + vybrany_port;
    //cout << vysledny_port << "\n";
    //printf("%s", &vysledny_port);
    //printf("%s", vysledny_port.c_str());



    //Nastavení portu
    //serial.setPortName("/dev/ttyUSB0");
    serial.setPortName(QString::fromStdString(vysledny_port));
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QIODevice::ReadWrite);



    //Vyčitání dat
    int beh = 0;
    while(serial.isOpen())
    {
        if(!serial.waitForReadyRead(-1)) //blokace dokud nedorazi nova data
            cout << "Cekani na nová data" << endl;
        else
        {
            //cout << "Dorazila nova data" << endl;
            QByteArray data = serial.readAll();
            txt(data);
            if ((beh == 0) || (beh % 100 == 0))
                cout << "Probíhá vycitani dat \n";
            //printf(data);
            beh++;
        }
    }
}
