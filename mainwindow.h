#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>
#include <QDebug>
#include "serialport.h"

namespace Ui {
class MainWindow;
}

using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QLineSeries * series1;
    QLineSeries * series2;
    QLineSeries * series3;
    QLineSeries * series4;
    QLineSeries * series5;
    QLineSeries * series_1;
    QLineSeries * series_2;
    QLineSeries * series_3;
    QLineSeries * series_4;
    QLineSeries * series_5;
    QValueAxis *axisX;
    QValueAxis *axis_X;
    QValueAxis *axisY;
    QValueAxis *axis_Y;
    QChart *chart;
    QChart *chart_complete;
    int XLength;
    int X2Length;
    serialport* myserialport;

    void checkout();
    bool openSerial();
public slots:
    void receive(QVector<float> SensorData);

private slots:
    void on_start_clicked();

    void on_stop_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
