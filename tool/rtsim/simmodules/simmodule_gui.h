#ifndef SIMMODULEGUI_H
#define SIMMODULEGUI_H

#include <QObject>

#include "simmodule.h"

#include "module/gui/gui.h"
#include "module/gui/gui_sim.h"

#include "widgets/screenwidget.h"

class SimModuleGui : public SimModule
{
public:
    SimModuleGui(uint16_t idPeriph);

public slots:
    void pushData(uint16_t functionId, const QByteArray &data);

protected:
    ScreenWidget *_screenWidget;
};

#endif // SIMMODULEGUI_H
