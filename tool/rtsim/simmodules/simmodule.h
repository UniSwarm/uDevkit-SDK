#ifndef SIMMODULE_H
#define SIMMODULE_H

#include <QObject>

class SimModule : public QObject
{
    Q_OBJECT
public:
    explicit SimModule(uint16_t idPeriph);

    uint16_t idPeriph() const;

signals:

public slots:
    virtual void pushData(uint16_t functionId, const QByteArray &data) =0;

protected:
    uint16_t _idPeriph;
};

#endif // SIMMODULE_H
