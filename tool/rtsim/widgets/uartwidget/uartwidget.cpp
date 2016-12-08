#include "uartwidget.h"

#include <QLayout>
#include <QPushButton>

UartWidget::UartWidget(QWidget *parent) : QWidget(parent)
{
    createWidget();
}

UartWidget::UartWidget(uint16_t idPeriph, QWidget *parent)
{
    _idPeriph = idPeriph;
    setWindowTitle(QString("uart %1").arg(idPeriph));
    createWidget();
}

void UartWidget::recData(const QString &data)
{
    _log->appendPlainText(data);
}

void UartWidget::setConfig(uart_dev config)
{
    if(config.enabled==0)
        _statusEnabled->setText("disabled");
    else
        _statusEnabled->setText("enabled");

    char parity;
    switch (config.bitParity)
    {
    case UART_BIT_PARITY_NONE:
        parity = 'N';
        break;
    case UART_BIT_PARITY_EVEN:
        parity = 'E';
        break;
    case UART_BIT_PARITY_ODD:
        parity = 'O';
        break;
    default:
        parity = 'U';
        break;
    }
    _params->setText(QString("%1%2%3").arg(config.baudSpeed)
                     .arg(parity)
                     .arg(config.bitStop));
}

void UartWidget::send()
{
    emit sendRequest(_lineEdit->text());
    _lineEdit->clear();
}

void UartWidget::createWidget()
{
    QLayout *layout = new QVBoxLayout();

    _log = new QPlainTextEdit();
    layout->addWidget(_log);

    QLayout *sendLayout = new QHBoxLayout();
    _lineEdit = new QLineEdit();
    sendLayout->addWidget(_lineEdit);
    QPushButton *sendButton = new QPushButton("Send");
    connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(send()));
    sendLayout->addWidget(sendButton);
    layout->addItem(sendLayout);

    QLayout *statusLayout = new QHBoxLayout();
    statusLayout->addWidget(new QLabel(QString("uart %1").arg(_idPeriph)));
    _statusEnabled = new QLabel("disabled");
    statusLayout->addWidget(_statusEnabled);
    _params = new QLabel("");
    statusLayout->addWidget(_params);
    layout->addItem(statusLayout);

    setLayout(layout);
}
