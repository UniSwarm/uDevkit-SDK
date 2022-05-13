/**
 ** This file is part of the UDK-SDK project.
 ** Copyright 2019 UniSwarm sebastien.caux@uniswarm.eu
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef UARTWIDGET_H
#define UARTWIDGET_H

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QWidget>

#include "driver/uart/uart.h"
#include "driver/uart/uart_sim.h"

#include <QSerialPort>

class UartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UartWidget(QWidget *parent = Q_NULLPTR);
    UartWidget(uint16_t idPeriph, QWidget *parent = Q_NULLPTR);
    ~UartWidget() override;

    void recFromUart(const QString &data);
    void setConfig(uart_dev config);

signals:
    void sendRequest(QString data);

protected slots:
    void sendToUart();
    void portChanged(int index);

protected:
    QPushButton *_sendButton;
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

#endif  // UARTWIDGET_H
