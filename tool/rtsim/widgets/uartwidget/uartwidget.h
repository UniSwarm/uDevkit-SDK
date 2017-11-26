#ifndef UARTWIDGET_H
#define UARTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QComboBox>

#include "driver/uart/uart.h"
#include "driver/uart/uart_sim.h"

#include <QSerialPort>

class UartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UartWidget(QWidget *parent = 0);
    UartWidget(uint16_t idPeriph, QWidget *parent = 0);

    void recFromUart(const QString &data);
    void setConfig(uart_dev config);

signals:
    void sendRequest(QString data);

protected slots:
    void sendToUart();
    void portChanged(int index);

protected:
    QLayout *_sendLayout;
    QLineEdit *_lineEdit;

    QPlainTextEdit *_logRec;
    QPlainTextEdit *_logSend;
    QLabel *_statusEnabled;
    QLabel *_params;

    QSerialPort *_port;
    QComboBox *_serialPortComboBox;
    void createWidget();

    uint16_t _idPeriph;
    uart_dev _config;
};

#endif // UARTWIDGET_H
