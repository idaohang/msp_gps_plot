#include <QtSerialPort>
#include <QString>
#include <QStringList>

#ifndef MSPCOMMS_H
#define MSPCOMMS_H

class MspComms
{
public:
    MspComms();

    static QStringList getPortNames();
};

#endif // MSPCOMMS_H
