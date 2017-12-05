#include "phnsysconfig.h"


#include <QFile>
#include <QTextStream>

uint8_t phnSysConfig::mStartAddess = 0x00;
uint8_t phnSysConfig::mDestAddress = 0x00;

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
               if(fields[0].compare("start") == 0)
               {
                    QByteArray cmd = QByteArray::fromHex(fields[1].toUtf8());
                    mStartAddess = cmd[0];
               }
               else if(fields[0].compare("dest")== 0)
               {
                   QByteArray cmd = QByteArray::fromHex(fields[1].toUtf8());
                   mDestAddress = cmd[0];
               }
        }
    }

    file.close();
}
