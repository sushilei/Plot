#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    checkout();
    series1 = new QLineSeries();
    series2 = new QLineSeries();
    series3 = new QLineSeries();
    series4 = new QLineSeries();
    series5 = new QLineSeries();
    series_1 = new QLineSeries();
    series_2 = new QLineSeries();
    series_3 = new QLineSeries();
    series_4 = new QLineSeries();
    series_5 = new QLineSeries();
    chart = new QChart();
    chart_complete = new QChart();
    ui->graphicsView->setChart(chart);
    ui->graphicsView_2->setChart(chart_complete);
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->addSeries(series4);
    chart->addSeries(series5);
    chart->setTitle("Simple line chart example");
    chart_complete->addSeries(series_1);
    chart_complete->addSeries(series_2);
    chart_complete->addSeries(series_3);
    chart_complete->addSeries(series_4);
    chart_complete->addSeries(series_5);
    chart_complete->setTitle("Simple line chart_complete example");

    axisX = new QValueAxis; //定义X轴
    axisX->setRange(0, 310); //设置范围
    axisX->setLabelFormat("%g"); //设置刻度的格式
    axisX->setTitleText("X Axis"); //设置X轴的标题
    axisX->setGridLineVisible(true); //设置是否显示网格线
    axisX->setMinorTickCount(9); //设置小刻度线的数目
   // axisX->setLabelsVisible(false); //设置刻度是否显示

    axis_X = new QValueAxis; //定义X轴
    axis_X->setRange(0, 310); //设置范围
    axis_X->setLabelFormat("%g"); //设置刻度的格式
    axis_X->setTitleText("X Axis"); //设置X轴的标题
    axis_X->setGridLineVisible(true); //设置是否显示网格线
    axis_X->setMinorTickCount(9); //设置小刻度线的数目
   // axis_X->setLabelsVisible(false); //设置刻度是否显示

    axisY = new QValueAxis;
    axisY->setRange(0, 100);
    axisY->setTitleText("Y Axis");
    axisY->setTickCount(11);
    axisY->setLabelFormat("%.2f");
    axisY->setGridLineVisible(true);

    axis_Y = new QValueAxis;
    axis_Y->setRange(0, 100);
    axis_Y->setTitleText("Y Axis");
    axis_Y->setTickCount(11);
    axis_Y->setLabelFormat("%.2f");
    axis_Y->setGridLineVisible(true);

    chart->setAxisX(axisX,series1);
    chart->setAxisY(axisY,series1);
    chart->setAxisX(axisX,series2);
    chart->setAxisY(axisY,series2);
    chart->setAxisX(axisX,series3);
    chart->setAxisY(axisY,series3);
    chart->setAxisX(axisX,series4);
    chart->setAxisY(axisY,series4);
    chart->setAxisX(axisX,series5);
    chart->setAxisY(axisY,series5);

    chart_complete->setAxisX(axis_X,series_1);
    chart_complete->setAxisY(axis_Y,series_1);
    chart_complete->setAxisX(axis_X,series_2);
    chart_complete->setAxisY(axis_Y,series_2);
    chart_complete->setAxisX(axis_X,series_3);
    chart_complete->setAxisY(axis_Y,series_3);
    chart_complete->setAxisX(axis_X,series_4);
    chart_complete->setAxisY(axis_Y,series_4);
    chart_complete->setAxisX(axis_X,series_5);
    chart_complete->setAxisY(axis_Y,series_5);

    ui->graphicsView->repaint();
    ui->graphicsView_2->repaint();
    myserialport = new serialport();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkout()
{
    ui->PortBox->clear();
    int count = 0;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(!info.portName().startsWith("tty",Qt::CaseSensitive))
        {
            //排除一些自带端口，usbmodem14411是JLink的端口
            if(!(info.portName()=="cu.SOC"||info.portName()=="cu.MALS" \
                    ||info.portName()=="cu.Bluetooth-Incoming-Port"||info.portName()=="cu.usbmodem14411"))
            {
                ui->PortBox->addItem(info.portName());
                count ++;
            }
        }
    }
}

bool MainWindow::openSerial()
{
    //设置串口名
    myserialport->mySerialPort->setPortName(ui->PortBox->currentText());
    //设置波特率
    myserialport->mySerialPort->setBaudRate(115200);
    myserialport->mySerialPort->setDataBits(QSerialPort::Data8);
    myserialport->mySerialPort->setParity(QSerialPort::NoParity);
    myserialport->mySerialPort->setStopBits(QSerialPort::OneStop);
    myserialport->mySerialPort->setFlowControl(QSerialPort::NoFlowControl);
    if(myserialport->mySerialPort->open(QIODevice::ReadWrite))
    {
        return true;
    }
    qDebug() << tr("串口打开失败");
    return false;
}

void MainWindow::receive(QVector<float> SensorData)
{
    if(series1->count() > XLength)
    {
        for(int i = 0; i < XLength; i++)
        {
            series1->replace(i,i,series1->at(i+1).y());
            series2->replace(i,i,series2->at(i+1).y());
            series3->replace(i,i,series3->at(i+1).y());
            series4->replace(i,i,series4->at(i+1).y());
            series5->replace(i,i,series5->at(i+1).y());
        }
        series1->replace(XLength,XLength,static_cast<qreal>(SensorData.at(0)));
        series2->replace(XLength,XLength,static_cast<qreal>(SensorData.at(1)));
        series3->replace(XLength,XLength,static_cast<qreal>(SensorData.at(2)));
        series4->replace(XLength,XLength,static_cast<qreal>(SensorData.at(3)));
        series5->replace(XLength,XLength,static_cast<qreal>(SensorData.at(4)));
    }else{
        series1->append(series1->count() + 1,static_cast<qreal>(SensorData.at(0)));
        series2->append(series2->count() + 1,static_cast<qreal>(SensorData.at(1)));
        series3->append(series3->count() + 1,static_cast<qreal>(SensorData.at(2)));
        series4->append(series4->count() + 1,static_cast<qreal>(SensorData.at(3)));
        series5->append(series5->count() + 1,static_cast<qreal>(SensorData.at(4)));
    }
    axisX->setRange(0,series1->count()+2);
    ui->graphicsView->repaint();


    if(X2Length != 0)
    {
        if(series_1->count() > X2Length)
        {
            for(int i = 0; i < X2Length; i++)
            {
                series_1->replace(i,i,series_1->at(i+1).y());
                series_2->replace(i,i,series_2->at(i+1).y());
                series_3->replace(i,i,series_3->at(i+1).y());
                series_4->replace(i,i,series_4->at(i+1).y());
                series_5->replace(i,i,series_5->at(i+1).y());
            }
            series_1->replace(X2Length,X2Length,static_cast<qreal>(SensorData.at(0)));
            series_2->replace(X2Length,X2Length,static_cast<qreal>(SensorData.at(1)));
            series_3->replace(X2Length,X2Length,static_cast<qreal>(SensorData.at(2)));
            series_4->replace(X2Length,X2Length,static_cast<qreal>(SensorData.at(3)));
            series_5->replace(X2Length,X2Length,static_cast<qreal>(SensorData.at(4)));
        }else{
            series_1->append(series_1->count() + 1,static_cast<qreal>(SensorData.at(0)));
            series_2->append(series_2->count() + 1,static_cast<qreal>(SensorData.at(1)));
            series_3->append(series_3->count() + 1,static_cast<qreal>(SensorData.at(2)));
            series_4->append(series_4->count() + 1,static_cast<qreal>(SensorData.at(3)));
            series_5->append(series_5->count() + 1,static_cast<qreal>(SensorData.at(4)));
        }
    }else{
        series_1->append(series_1->count() + 1,static_cast<qreal>(SensorData.at(0)));
        series_2->append(series_2->count() + 1,static_cast<qreal>(SensorData.at(1)));
        series_3->append(series_3->count() + 1,static_cast<qreal>(SensorData.at(2)));
        series_4->append(series_4->count() + 1,static_cast<qreal>(SensorData.at(3)));
        series_5->append(series_5->count() + 1,static_cast<qreal>(SensorData.at(4)));
    }
    axis_X->setRange(0,series_1->count()+2);
    ui->graphicsView->repaint();
}

void MainWindow::on_start_clicked()
{
    if(ui->up->text().isEmpty())
    {
        XLength = 310;
    }else{
        XLength = ui->up->text().toInt();
    }
    if(ui->down->text().isEmpty())
    {
        X2Length = 0;
    }else{
        X2Length = ui->down->text().toInt();
    }
    if(openSerial()){
        connect(myserialport,&serialport::Usbreturn,this,&MainWindow::receive);
        connect(myserialport->mySerialPort,&QSerialPort::readyRead,myserialport,&serialport::ReadUsb);
        ui->start->setEnabled(false);
        ui->stop->setEnabled(true);
        this->repaint();
    }
}

void MainWindow::on_stop_clicked()
{
    myserialport->mySerialPort->clear();
    myserialport->mySerialPort->close();
    disconnect(myserialport,&serialport::Usbreturn,this,&MainWindow::receive);
    disconnect(myserialport->mySerialPort,&QSerialPort::readyRead,myserialport,&serialport::ReadUsb);
    ui->start->setEnabled(true);
    ui->stop->setEnabled(false);
    this->repaint();
}
