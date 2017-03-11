#ifndef SIMMODULE_H
#define SIMMODULE_H

#include <QObject>

class SimClient;

class SimModule : public QObject
{
    Q_OBJECT
public:
    explicit SimModule(SimClient *client, uint16_t idModule, uint16_t idPeriph);

    SimClient *client() const;
    uint16_t idModule() const;
    uint16_t idPeriph() const;

    void writeData(uint16_t functionId, const QByteArray &data);

    virtual QWidget *widget() const =0;

signals:

public slots:
    virtual void pushData(uint16_t functionId, const QByteArray &data) =0;

protected:
    SimClient *_client;
    uint16_t _idModule;
    uint16_t _idPeriph;
};

#endif // SIMMODULE_H
