#ifndef SIMMODULEUART_H
#define SIMMODULEUART_H

#include <QObject>

#include "simmodule.h"
#include "widgets/uartwidget/uartwidget.h"

#include "driver/uart/uart.h"
#include "driver/uart/uart_sim.h"

class SimModuleUart : public SimModule
{
    Q_OBJECT
public:
    SimModuleUart(SimClient *client, uint16_t idPeriph);

    [[nodiscard]] QWidget *widget() const override;

public slots:
    void pushData(uint16_t functionId, const QByteArray &data) override;

protected slots:
    void sendData(QString str);

protected:
    uart_dev _config_uart;
    UartWidget *_uartWidget;
};

#endif  // SIMMODULEUART_H
