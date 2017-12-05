#ifndef PHNSYSCONFIG_H
#define PHNSYSCONFIG_H

#include <stdint.h>

#include<QString>

class phnSysConfig
{
public:

    static uint8_t mStartAddess;
    static uint8_t mDestAddress;

    static void phnSysConfig_ReadConfig(QString path);
};

#endif // PHNSYSCONFIG_H
