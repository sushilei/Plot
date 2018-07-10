#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVector>
#include <QTimer>
#include <QTime>

class serialport : public QObject
{
    Q_OBJECT
public:
    explicit serialport(QObject *parent = nullptr);
    QSerialPort *mySerialPort;
    QTimer *timer1;

signals:
    void Usbreturn(QVector<float> SensorData);
public slots:
    void ReadUsb();
private slots:

    void test();

private:
    bool isStart;
    bool halfpass;
    quint8 Data_i;
    quint8 DataSum;
    QByteArray *Data;
};

#endif // SERIALPORT_H
