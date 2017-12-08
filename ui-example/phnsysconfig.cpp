#include "phnsysconfig.h"


#include <QFile>
#include <QTextStream>

uint8_t phnSysConfig::mRecvAddess = 0x00;
uint8_t phnSysConfig::mTransAddress = 0x00;

void phnSysConfig::phnSysConfig_ReadConfig(QString path)
{


    QString configFile  = path + "/system/sys.conf";
    QFile file(configFile);

    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if(fields.size() >=2)
        {
               if(fields[0].compare("recv") == 0)
               {
                    QByteArray cmd = QByteArray::fromHex(fields[1].toUtf8());
                    mRecvAddess = cmd[0];
               }
               else if(fields[0].compare("trans")== 0)
               {
                   QByteArray cmd = QByteArray::fromHex(fields[1].toUtf8());
                   mTransAddress = cmd[0];
               }
        }
    }

    file.close();
}
