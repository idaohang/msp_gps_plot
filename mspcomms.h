#include <QObject>

#include <QString>
#include <QStringList>
#include <QTimer>

#include <QSerialPort>


#ifndef MSPCOMMS_H
#define MSPCOMMS_H

class MspComms : public QObject
{
    Q_OBJECT

public:
    explicit MspComms(QString portname, QObject *parent = 0);

    void startQueryGPS(unsigned int interval_msec);

    void sendMSPCommand(char command, QByteArray data);

    static QStringList getPortNames();
private:
    QSerialPort *port;
    QTimer *timer;

signals:
    void newGPSData();

private slots:
    void sendGPSQuery();
    void dataReceived();
};

#endif // MSPCOMMS_H
