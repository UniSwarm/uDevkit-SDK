#ifndef UARTWIDGET_H
#define UARTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>

#include "driver/periph/uart/uart.h"
#include "driver/periph/uart/uart_sim.h"

class UartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UartWidget(QWidget *parent = 0);
    UartWidget(uint16_t idPeriph, QWidget *parent = 0);

    void recData(const QString &data);
    void setConfig(uart_dev config);

signals:
    void sendRequest(QString data);

protected slots:
    void send();

protected:
    QLineEdit *_lineEdit;
    QPlainTextEdit *_log;
    QLabel *_statusEnabled;
    QLabel *_params;
    void createWidget();

    uint16_t _idPeriph;
};

#endif // UARTWIDGET_H
