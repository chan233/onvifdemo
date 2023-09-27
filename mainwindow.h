#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThreadPool>
#include <QMap>
#include <QHostAddress>
#include <QNetworkInterface>

// #include "onvifheads.h"
#include "OnvifDevice.h"
#include "viedoframe.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

    void on_pushButton_GetNTP_clicked();

    void on_pushButton_SetNTP_clicked();

    void on_pushButton_GetHost_clicked();

    void on_pushButton_SetHost_clicked();

    void on_pushButton_SetImagingSettings_clicked();

    void on_pushButton_GetImagingSettings_clicked();



    void on_horizontalSlider_brightness_sliderMoved(int position);

    void on_horizontalSlider_ColorSaturation_sliderMoved(int position);

    void on_horizontalSlider_Contrast_sliderMoved(int position);

    void on_horizontalSlider_Sharpness_sliderMoved(int position);

    void on_pushButton_left_released();

    void on_pushButton_right_released();



    void on_pushButton_init_clicked();

    void on_pushButton_GetOSD_clicked();

    void on_pushButton_AddOSD_clicked();

    void on_pushButton_ModifyOSD_clicked();

    void on_pushButton_DelOSD_clicked();

    void on_pushButton_GetTIme_clicked();

    void on_pushButton_SetTime_clicked();



    void on_comboBox_Position_currentIndexChanged(int index);

    void on_pushButton_SystemReboot_clicked();

private:
    void hideButton();
    struOSD getUIOsd();
    QMap <QString , QHostAddress>getIPv4();
    QMap <QString , QHostAddress>m_mapAddresses;
    Ui::MainWindow *ui;
    QUrl mPtzurl;
    QString mUsername;
    QString mUserPassword;
    bool abusolute = true;
    bool continuous  = false;
    bool relative  = false;
    OnvifDevice *onvifdevice;
    ViedoFrame *videoframe;
    bool init = false;
};
#endif // MAINWINDOW_H
