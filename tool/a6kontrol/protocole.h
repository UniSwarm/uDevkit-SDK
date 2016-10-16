#ifndef PROTOCOLE_H
#define PROTOCOLE_H

#include <QThread>
#include <QTimer>

#include <QSerialPort>

class Protocole : public QThread
{
    Q_OBJECT

public:
    Protocole();
    ~Protocole();

    void setVal(unsigned short adr, unsigned short val);
    void setInt(unsigned char val, unsigned char val2, unsigned char val3, unsigned char val4);

private:
    QSerialPort *_port;
    QTimer *timer;

    int val1, val2;
    int anc1,anc2;

    unsigned char nume;
    char data[25];

protected:
    void run();
    void connect_serial();

signals:
    void dataRec(QString buff);
    void sensor1Changed(int n);
    void sensor2Changed(int n);
    void accelChanged(int x, int y, int z);
    void posChanged(int x, int y, int t);

private slots:
    void timer_tick();
    void receive();
    void error(QSerialPort::SerialPortError errorCode);
};

#endif // PROTOCOLE_H
