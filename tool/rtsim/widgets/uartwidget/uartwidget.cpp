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
    setWindowTitle(QString("UART %1").arg(idPeriph+1));
    createWidget();
}

void UartWidget::recData(const QString &data)
{
    QString dataReceived = data;
    dataReceived = dataReceived.replace("\r","<b>\\r</b>");
    dataReceived = dataReceived.replace("\n","<b>\\n</b>");
    dataReceived = dataReceived.replace("\t","<b>\\t</b>");
    //dataReceived = dataReceived.replace("\0","<b>\\0</b>");
    _log->appendHtml(dataReceived);
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
    QString dataToSend = _lineEdit->text();
    dataToSend = dataToSend.replace("\\r","\r");
    dataToSend = dataToSend.replace("\\n","\n");
    dataToSend = dataToSend.replace("\\t","\t");
    //dataToSend = dataToSend.replace("\\0","\0");
    emit sendRequest(dataToSend);
    //_lineEdit->clear();
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
    connect(_lineEdit, SIGNAL(editingFinished()), this, SLOT(send()));
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
