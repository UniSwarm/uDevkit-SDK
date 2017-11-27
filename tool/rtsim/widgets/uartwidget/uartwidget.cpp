#include "uartwidget.h"

#include <QLayout>
#include <QPushButton>

#include <QSerialPortInfo>
#include <QDebug>
#include <QSettings>

UartWidget::UartWidget(QWidget *parent)
    : QWidget(parent)
{
    createWidget();
    _port = Q_NULLPTR;
}

UartWidget::UartWidget(uint16_t idPeriph, QWidget *parent)
    : QWidget(parent)
{
    _idPeriph = idPeriph;
    setWindowTitle(QString("UART %1").arg(_idPeriph+1));
    createWidget();
    _port = Q_NULLPTR;

    QSettings settings("UniSwarm", "RtSim");
    settings.beginGroup(QString("UART%1").arg(_idPeriph+1));

    QString port = settings.value("port", "").toString();

    if (!port.isEmpty())
    {
        int indexPortCom = _serialPortComboBox->findData(port);
        if (indexPortCom != -1)
            _serialPortComboBox->setCurrentIndex(indexPortCom);
    }
}

UartWidget::~UartWidget()
{
    if (_port)
    {
        _port->close();
        delete _port;
    }
}

void UartWidget::recFromUart(const QString &data)
{
    QString dataReceived = data.toHtmlEscaped();
    dataReceived = dataReceived.replace("\r","<b>\\r</b>");
    dataReceived = dataReceived.replace("\n","<b>\\n</b>");
    dataReceived = dataReceived.replace("\t","<b>\\t</b>");
    //dataReceived = dataReceived.replace("\0","<b>\\0</b>");
    _logRec->appendHtml(dataReceived);

    if (_port)
    {
        QByteArray badat;
        badat.append(data);
        _port->write(badat);
    }
}

void UartWidget::setConfig(uart_dev config)
{
    _config = config;
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

void UartWidget::sendToUart()
{
    QString dataToSend;

    if (_port == Q_NULLPTR)
    {
        dataToSend = _lineEdit->text();
        dataToSend = dataToSend.replace("\\r","\r");
        dataToSend = dataToSend.replace("\\n","\n");
        dataToSend = dataToSend.replace("\\t","\t");
    }
    else
    {
        QByteArray readenData = _port->readAll();
        qDebug()<<readenData;
        dataToSend = QString(readenData);
    }

    emit sendRequest(dataToSend);

    dataToSend = dataToSend.toHtmlEscaped();
    dataToSend = dataToSend.replace("\r","<b>\\r</b>");
    dataToSend = dataToSend.replace("\n","<b>\\n</b>");
    dataToSend = dataToSend.replace("\t","<b>\\t</b>");

    _logSend->appendHtml(dataToSend);

    //_lineEdit->clear();
}

void UartWidget::portChanged(int index)
{
    QSettings settings("UniSwarm", "RtSim");
    settings.beginGroup(QString("UART%1").arg(_idPeriph+1));

    if (_port != Q_NULLPTR)
    {
        _port->close();
        _port = Q_NULLPTR;
    }

    if (index == 0)
    {
        _sendButton->setEnabled(true);
        _lineEdit->setEnabled(true);

        settings.setValue("port", "");
    }
    else
    {
        _sendButton->setEnabled(false);
        _lineEdit->setEnabled(false);

        _port = new QSerialPort(_serialPortComboBox->itemData(index).toString(), this);
        _port->open(QIODevice::ReadWrite);
        _port->setBaudRate(115200/*_config.baudSpeed*/);
        qDebug()<<_config.baudSpeed;
        _port->setDataBits(QSerialPort::Data8);
        _port->setParity(QSerialPort::NoParity);
        _port->setStopBits(QSerialPort::OneStop);
        _port->setFlowControl(QSerialPort::NoFlowControl);

        connect(_port, SIGNAL(readyRead()), this, SLOT(sendToUart()));

        settings.setValue("port", _port->portName());
    }
}

void UartWidget::createWidget()
{
    QLayout *layout = new QVBoxLayout();

    _serialPortComboBox = new QComboBox();
    _serialPortComboBox->addItem("Simulated UART");

    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo portInfo, availablePorts)
    {
        _serialPortComboBox->addItem(portInfo.portName() + " (" + portInfo.description() + ", " + portInfo.manufacturer() + ")", portInfo.portName());
    }
    layout->addWidget(_serialPortComboBox);
    connect(_serialPortComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(portChanged(int)));

    _logRec = new QPlainTextEdit();
    layout->addWidget(_logRec);

    _logSend = new QPlainTextEdit();
    layout->addWidget(_logSend);

    QLayout *sendLayout = new QHBoxLayout();
    _lineEdit = new QLineEdit();
    sendLayout->addWidget(_lineEdit);
    _sendButton = new QPushButton("Send");
    connect(_sendButton, SIGNAL(clicked(bool)), this, SLOT(sendToUart()));
    connect(_lineEdit, SIGNAL(editingFinished()), this, SLOT(sendToUart()));
    sendLayout->addWidget(_sendButton);
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
