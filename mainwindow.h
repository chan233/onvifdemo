#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThreadPool>
#include "onvifheads.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    OnvifDeviceClient *onvifDevice;
private slots:
    void on_pushButton_boradcast_clicked();

    void on_pushButton_GetDeviceInformation_clicked();

    void on_pushButton_Probe_clicked();

    void on_pushButton_GetPresets_clicked();

    void on_pushButton_SetPreset_clicked();



    void on_pushButton_CurrentPreset_clicked();

    void on_pushButton_CurrentLoc_clicked();

    void on_pushButton_CallStart_clicked();

    void on_pushButton_SetStart_clicked();

    void on_pushButton_GeoMove_clicked();

    void on_pushButton_StopGeoMove_clicked();

    void on_pushButton_leftup_clicked();

    void on_pushButton_up_clicked();

    void on_pushButton_rightup_clicked();

    void on_pushButton_left_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_leftdown_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_rightdown_clicked();

    void on_pushButton_zoomout_clicked();

    void on_pushButton_zoomin_clicked();

    void on_pushButton_Stop_clicked();

    void on_radioButton_Continuous_clicked();

    void on_radioButton_Abusolute_clicked();

    void on_radioButton_Relative_clicked();

private:
    Ui::MainWindow *ui;
    QUrl mPtzurl;
    bool abusolute = true;
    bool continuous  = false;
    bool relative  = false;
};
#endif // MAINWINDOW_H
