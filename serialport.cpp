#include "serialport.h"

serialport::serialport(QObject *parent) : QObject(parent)
{
    timer1 = new QTimer();
//    connect(timer1,&QTimer::timeout,this,&serialport::test);
//    timer1->start(1000);
    mySerialPort = new QSerialPort();
    Data = new QByteArray();
}

void serialport::test()
{
    QVector<float> SensorData;
    qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));
    for(int i = 0; i < 5; i++)
    {
        SensorData.append(qrand()%4096);
    }
    emit Usbreturn(SensorData);
}

void serialport::ReadUsb()
{
    QByteArray requestData(mySerialPort->readAll());
        for(int i = 0;i < requestData.count(); i++)
        {
            quint8 simpleData = static_cast<quint8>(requestData.at(i));//char可以强制转换成int
            if((!isStart)&&(!halfpass))
            {
                if(simpleData == 0xAA)
                {
                    halfpass = true;
                }
            }else if((!isStart)&&(halfpass)){
                if(simpleData == 0xBB)
                {
                    isStart = true;
                    Data_i = 1;
                    DataSum = 0x65;
                }
            }else if(isStart){
                Data_i ++;
                if(Data_i == 12)
                {
                    if(simpleData == DataSum)
                    {
                        isStart = false;
                        halfpass = false;
                        QVector<float> SensorData;
                        for(int i = 0; i < 10;)
                        {
                            SensorData.append((static_cast<unsigned char>(Data->at(i))*256 + static_cast<unsigned char>(Data->at(i+1)))/10.0f);
                            i += 2;
                        }
                        emit Usbreturn(SensorData);
                        Data->clear();
                        Data_i = 0;
                    }else{
                        isStart = false;
                        halfpass = false;
                        Data->clear();
                        Data_i = 0;
                    }
                }else{
                    DataSum += simpleData;
                    Data->append(static_cast<char>(simpleData));
                }
            }
        }
}
