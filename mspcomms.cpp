#include <QList>
#include <QStringList>
#include <QByteArray>
#include <QtEndian>
#include <QDebug>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QTimer>

#include "mspcomms.h"


MspComms::MspComms(QString portname, QObject *parent) : QObject(parent)
{
    port = new QSerialPort(portname, this);
    port->open(QIODevice::ReadWrite);
}

void MspComms::startQueryGPS(unsigned int interval_msec) {
    timer = new QTimer(this);
    timer->setInterval(interval_msec);
    timer->setSingleShot(false);

    connect(timer, SIGNAL(timeout()), this, SLOT(sendGPSQuery()));
    connect(port, SIGNAL(readyRead()), this, SLOT(dataReceived()));

    timer->start();
}

void MspComms::sendMSPCommand(char command, QByteArray payload = NULL) {
    QByteArray data = "";
    char checksum = 0;

    data.append("$M<"); // Header

    if(payload != NULL) {
        data.append(payload.length());     // Data length
        checksum ^= payload.length();
    } else {
        data.append((char)0);                    // Data length
    }

    data.append(command);   // Command

    checksum ^= command;

    if(payload != NULL) {
        for(int i = 0; i < payload.length(); i++) {
            data.append(payload.at(i));
            checksum ^= payload.at(i);
        }
    }

    data.append(checksum);

    qDebug() << "Sending: ";
#if 0
    for(int i = 0; i < data.length(); i++) {
        if((int)data.at(i) > 31)
            qDebug() << (uint)data.at(i) << " (" << (char)data.at(i) << ")";
        else
            qDebug() << (uint)data.at(i);
    }
#endif

    int written = port->write(data);
    if(written != data.length()) {
        qWarning() << "Error writing data";
    }
}

void MspComms::sendGPSQuery() {
    sendMSPCommand(106);
}

void MspComms::dataReceived() {
    qDebug() << "Received data:";
    QByteArray data = port->readAll();

#if 1
    for(int i = 0; i < data.length(); i++) {
        if((int)data.at(i) > 31)
            qDebug() << (uint)data.at(i) << " (" << (char)data.at(i) << ")";
        else
            qDebug() << (uint)data.at(i);
    }
#endif

    if(!data.startsWith("$M>")) // Not a MSP packet
        return;

    if(data.at(4) != (char)106) // Not GPS data
        return;

    if(data.length() != 22) // Invalid length
        return;

    QByteArray payload = data.mid(5,16);
    bool fix  = (bool)payload.at(0);
    quint8 sats = payload.at(1);
    qint32 lat  = qFromBigEndian<qint32>((uchar*)payload.mid(2, 4).data());
    qint32 lon  = qFromBigEndian<qint32>((uchar*)payload.mid(6, 4).data());
    quint16 alt = qFromBigEndian<quint16>((uchar*)payload.mid(10, 2).data());
    quint16 spd = qFromBigEndian<quint16>((uchar*)payload.mid(12, 2).data());
    quint16 hdg = qFromBigEndian<quint16>((uchar*)payload.mid(14,2).data());

    qDebug() << "GPS Fix:  " << fix;
    qDebug() << "GPS Sats: " << sats;
    qDebug() << "GPS Lat:  " << lat;
    qDebug() << "GPS Lon:  " << lon;
    qDebug() << "GPS Alt:  " << alt;
    qDebug() << "GPS Spd:  " << spd;
    qDebug() << "GPS Hdg:  " << hdg;
}

QStringList MspComms::getPortNames() {
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    QStringList port_names = QList<QString>();
    for(int i = 0; i < ports.length(); i++) {
        port_names.append(ports.at(i).portName());
    }

    return port_names;
}
