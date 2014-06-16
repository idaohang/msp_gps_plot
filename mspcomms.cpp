#include <QList>
#include <QStringList>

#include "mspcomms.h"

MspComms::MspComms()
{
}

QStringList MspComms::getPortNames() {
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    QStringList port_names = QList<QString>();
    for(int i = 0; i < ports.length(); i++) {
        port_names.append(ports.at(i).portName());
    }

    return port_names;
}
