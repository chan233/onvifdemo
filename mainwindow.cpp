#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mPtzurl = "http://192.168.0.25:8080/onvif/device_service";


    getIPv4();


    //onvifdevice = new OnvifDevice(mPtzurl);
   // onvifdevice->SetAuth("admin","admin");
   // onvifdevice->Initialize();




}

MainWindow::~MainWindow()
{
    delete ui;
}

QMap<QString , QHostAddress> MainWindow::getIPv4(){
    QList<QHostAddress> Addresses = QNetworkInterface::allAddresses();
    for(auto Address : Addresses){
        if (Address != QHostAddress::LocalHost &&Address.toIPv4Address()) {
            m_mapAddresses.insert(Address.toString(),Address);
            ui->comboBox_NetworkInterface->addItem(Address.toString());
        }
    }

    return m_mapAddresses;
}
void MainWindow::on_pushButton_boradcast_clicked()
{



}


void MainWindow::on_pushButton_GetDeviceInformation_clicked()
{


}


void MainWindow::on_pushButton_Probe_clicked()
{

    onvifdevice->Probe();

}

void MainWindow::on_pushButton_GetPresets_clicked()
{

    onvifdevice->GetPresets();
}


void MainWindow::on_pushButton_SetPreset_clicked()
{

    onvifdevice->SetPreset();
}





void MainWindow::on_pushButton_CurrentPreset_clicked()
{

}


void MainWindow::on_pushButton_CurrentLoc_clicked()
{

}


void MainWindow::on_pushButton_CallStart_clicked()
{
    onvifdevice->GotoHomePosition();
}


void MainWindow::on_pushButton_SetStart_clicked()
{
    onvifdevice->SetHomePosition();
}


void MainWindow::on_pushButton_GeoMove_clicked()
{

}


void MainWindow::on_pushButton_StopGeoMove_clicked()
{

    onvifdevice->Stop();
}


void MainWindow::on_pushButton_leftup_clicked()
{

}


void MainWindow::on_pushButton_up_clicked()
{

    float x = ui->comboBox_Xmove->currentText().toFloat();
    float y = ui->comboBox_Ymove->currentText().toFloat();
    float speed = ui->comboBox_SpeedMove->currentText().toFloat();
    if(abusolute){
        onvifdevice->AbsoluteMove(x,y,speed);
    }
    else if(continuous) {


        onvifdevice->ContinuousMove(x,y,speed);
    }
    else if(relative){


        onvifdevice->RelativeMove(x,y,speed);
    }


}


void MainWindow::on_pushButton_rightup_clicked()
{

}


void MainWindow::on_pushButton_left_clicked()
{

}


void MainWindow::on_pushButton_reset_clicked()
{


}


void MainWindow::on_pushButton_right_clicked()
{

}


void MainWindow::on_pushButton_leftdown_clicked()
{

}


void MainWindow::on_pushButton_down_clicked()
{

}


void MainWindow::on_pushButton_rightdown_clicked()
{

}


void MainWindow::on_pushButton_zoomout_clicked()
{

}


void MainWindow::on_pushButton_zoomin_clicked()
{

}


void MainWindow::on_pushButton_Stop_clicked()
{

}


void MainWindow::on_radioButton_Continuous_clicked()
{
    abusolute = false;
    continuous  = true;
    relative  = false;
    ui->radioButton_Continuous->setChecked(continuous);
    ui->radioButton_Abusolute->setChecked(abusolute);
    ui->radioButton_Relative->setChecked(relative);
}


void MainWindow::on_radioButton_Abusolute_clicked()
{
    abusolute = true;
    continuous  = false;
    relative  = false;
    ui->radioButton_Continuous->setChecked(continuous);
    ui->radioButton_Abusolute->setChecked(abusolute);
    ui->radioButton_Relative->setChecked(relative);
}


void MainWindow::on_radioButton_Relative_clicked()
{
    abusolute = false;
    continuous  = false;
    relative  = true;
    ui->radioButton_Continuous->setChecked(continuous);
    ui->radioButton_Abusolute->setChecked(abusolute);
    ui->radioButton_Relative->setChecked(relative);
}


void MainWindow::on_pushButton_GetNTP_clicked()
{

    onvifdevice->GetNTP();
}


void MainWindow::on_pushButton_SetNTP_clicked()
{

    onvifdevice->SetNTP();
}


void MainWindow::on_pushButton_GetHost_clicked()
{

    onvifdevice->GetHostname();
    onvifdevice->GetIPAddressFilter();
    onvifdevice->GetNetworkDefaultGateway();
    onvifdevice->GetDNS();

}


void MainWindow::on_pushButton_SetHost_clicked()
{

    onvifdevice->SetHostname();
    onvifdevice->SetIPAddressFilter();
    onvifdevice->SetNetworkDefaultGateway();
    onvifdevice->SetDNS();
}


void MainWindow::on_pushButton_SetImagingSettings_clicked()
{

    onvifdevice->SetImagingSettings();

}


void MainWindow::on_pushButton_GetImagingSettings_clicked()
{

    onvifdevice->GetImagingSettings();


}


void MainWindow::on_horizontalSlider_brightness_sliderMoved(int position)
{
    ui->lineEdit_brightness->setText(QString::number(position));
}


void MainWindow::on_horizontalSlider_ColorSaturation_sliderMoved(int position)
{
    ui->lineEdit_ColorSaturation->setText(QString::number(position));
}


void MainWindow::on_horizontalSlider_Contrast_sliderMoved(int position)
{
    ui->lineEdit_Contrast->setText(QString::number(position));
}


void MainWindow::on_horizontalSlider_Sharpness_sliderMoved(int position)
{
    ui->lineEdit_Sharpness->setText(QString::number(position));
}

