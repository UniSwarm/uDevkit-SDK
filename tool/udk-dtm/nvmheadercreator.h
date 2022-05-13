#ifndef NVMHEADERCREATOR_H
#define NVMHEADERCREATOR_H

#include "headercreator.h"

class NvmHeaderCreator : public HeaderCreator
{
public:
    NvmHeaderCreator(const EdcDb &db, const QString &picFilter, const QString &fileName);
};

#endif  // NVMHEADERCREATOR_H
