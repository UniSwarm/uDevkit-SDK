#ifndef SIMMODULEGUI_H
#define SIMMODULEGUI_H

#include <QObject>

#include "simmodule.h"

#include "module/gui/gui.h"
#include "module/gui/gui_sim.h"

#include "widgets/guiwidget/guiwidget.h"

class SimModuleGui : public SimModule
{
    Q_OBJECT
public:
    SimModuleGui(SimClient *client, uint16_t idPeriph);

    QWidget *widget() const;

public slots:
    void pushData(uint16_t functionId, const QByteArray &data);

protected:
    GuiWidget *_guiWidget;
};

#endif // SIMMODULEGUI_H
