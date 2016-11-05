#ifndef SIMMODULE_H
#define SIMMODULE_H

#include <QObject>

class SimModule : public QObject
{
    Q_OBJECT
public:
    explicit SimModule(QObject *parent = 0);

signals:

public slots:
    virtual void pushData(uint16_t functionId, const QByteArray &data) =0;
};

#endif // SIMMODULE_H
