#include "protocole.h"

#include <QtDebug>
#include <QRegExp>
#include <QSerialPortInfo>

Protocole::Protocole()
{
    for(int i=0;i<21;i++) data[i]=0;

    _port = NULL;
    connect_serial();

    //port->setTimeout(0, 10);

    //timer = new QTimer;
    //connect(_port,SIGNAL(readyRead()),this,SLOT(receive()));
    //timer->start(1);

    this->start();
}

Protocole::~Protocole()
{
    if(_port!=NULL)
        _port->close();
    this->terminate();
    delete _port;
}

void Protocole::timer_tick()
{
}

void Protocole::receive()
{
    /*char buffr[1024];
    port->readLine(buffr,1024);
    emit dataRec(QString(buffr));*/
}

void Protocole::error(QSerialPort::SerialPortError errorCode)
{
    qDebug()<<"error!!"<<errorCode;
}

void Protocole::setVal(unsigned short adr, unsigned short val)
{
    data[adr]=val;
    //send(data,20,0);
}

void Protocole::setInt(unsigned char val,unsigned char val2,unsigned char val3,unsigned char val4)
{
    data[2]=val;
    data[3]=val2;
    data[4]=val3;
    data[5]=val4;
    //send(data,20,0);
}

void Protocole::run()
{
    char buff[1024];
    QRegExp rx("d1:.*([0-9]+).*d2:.*([0-9]+).*x:.*([0-9]+).*y:([0-9]+).*t:(-*[0-9]+).*acx:(-*[0-9]+).*acy:(-*[0-9]+).*acz:(-*[0-9]+)");

    while(1)
    {
        if(_port==NULL)
        {
            connect_serial();
            QThread::msleep(100);
            continue;
        }

        if(_port->error() != QSerialPort::NoError)
        {
            qDebug()<<"disconnected";
            _port->deleteLater();
            _port = NULL;
            continue;
        }

        if(_port->bytesAvailable()>=20)
        {
            _port->readLine(buff,150);
            emit dataRec(QString(buff));
            if(rx.indexIn(buff)!=-1 && rx.captureCount()==8)
            {
                emit posChanged(rx.cap(3).toInt(), rx.cap(4).toInt(), rx.cap(5).toInt());
                int ax = rx.cap(6).toInt();
                ax = ax - 128;
                int ay = rx.cap(7).toInt();
                ay = ay - 128;
                int az = rx.cap(8).toInt();
                az = az - 128;
                emit accelChanged(ax, ay, az);
                emit sensor1Changed(rx.cap(1).toInt());
                emit sensor2Changed(rx.cap(2).toInt());
            }
        }
    }
}

void Protocole::connect_serial()
{
    foreach (QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        //qDebug()<<info.description()<<info.manufacturer();
        if(info.manufacturer().contains("Microchip"))
            _port =new QSerialPort(info.portName());
    }
    if(_port!=NULL)
    {
        qDebug()<<"connected";
        _port->open(QIODevice::ReadWrite);
        _port->setDataBits(QSerialPort::Data8);
        _port->setBaudRate(QSerialPort::Baud57600);
        _port->setParity(QSerialPort::NoParity);
        _port->setStopBits(QSerialPort::OneStop);
        _port->setFlowControl(QSerialPort::NoFlowControl);
        connect(_port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(error(QSerialPort::SerialPortError)));
    }
}
