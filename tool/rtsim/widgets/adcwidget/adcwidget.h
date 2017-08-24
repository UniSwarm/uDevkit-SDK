#ifndef ADCWIDGET_H
#define ADCWIDGET_H

#include <QWidget>
#include <QDial>
#include <QLabel>

#include "driver/adc/adc.h"
#include "driver/adc/adc_sim.h"

class AdcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdcWidget(QWidget *parent = 0);
    AdcWidget(uint16_t idPeriph, QWidget *parent = 0);

    void recData(const QString &data);

signals:
    void sendRequest(QByteArray data);

protected slots:
    void send();

protected:
    QDial *_dial;
    QLabel *_statusEnabled;
    QLabel *_params;
    void createWidget();

    uint16_t _idPeriph;
};

#endif // ADCWIDGET_H
