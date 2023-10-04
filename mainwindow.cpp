#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    hideButton();
    getIPv4();
//videoframe = new ViedoFrame;
//    ui->verticalLayout_17->addWidget(videoframe);
//    ui->verticalLayout_17->setStretch(0,0);
//    ui->verticalLayout_17->setStretch(1,0);
//    ui->verticalLayout_17->setStretch(2,0);
//    ui->verticalLayout_17->setStretch(3,8);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::hideButton(){
    ui->pushButton_clear->setVisible(false);
    ui->pushButton_SystemReboot->setVisible(false);
    ui->pushButton_CapPic->setVisible(false);
    ui->pushButton_RSS->setVisible(false);
    ui->pushButton_GetNTP->setVisible(false);
    ui->pushButton_SetNTP->setVisible(false);
    ui->pushButton_GetInformation->setVisible(false);
    ui->pushButton_GetDeviceInformation->setVisible(false);
    ui->label_config->setVisible(false);
    ui->lineEdit_config->setVisible(false);

    ui->comboBox_OSDType->setVisible(false);

    ui->label_OSDType->setVisible(false);





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

    onvifdevice->MulticastProbe();

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
    onvifdevice->ContinuousMove(-1,-1);
}


void MainWindow::on_pushButton_up_clicked()
{

    //    float x = ui->comboBox_Xmove->currentText().toFloat();
    //    float y = ui->comboBox_Ymove->currentText().toFloat();
    //    float speed = ui->comboBox_SpeedMove->currentText().toFloat();
    //    if(abusolute){
    //        onvifdevice->AbsoluteMove(x,y,speed);
    //    }
    //    else if(continuous) {


    //        onvifdevice->ContinuousMove(x,y,speed);
    //    }
    //    else if(relative){


    //        onvifdevice->RelativeMove(x,y,speed);
    //    }
    onvifdevice->ContinuousMove(0,-1);

}


void MainWindow::on_pushButton_rightup_clicked()
{
    onvifdevice->ContinuousMove(1,-1);
}


void MainWindow::on_pushButton_left_clicked()
{
    onvifdevice->ContinuousMove(-1,1);
}


void MainWindow::on_pushButton_reset_clicked()
{
    onvifdevice->ContinuousMove(0,0);

}


void MainWindow::on_pushButton_right_clicked()
{
    onvifdevice->ContinuousMove(1,1);
}


void MainWindow::on_pushButton_leftdown_clicked()
{
    onvifdevice->ContinuousMove(-1,1);
}


void MainWindow::on_pushButton_down_clicked()
{
    onvifdevice->ContinuousMove(0,1);
}


void MainWindow::on_pushButton_rightdown_clicked()
{
    onvifdevice->ContinuousMove(1,1);
}


void MainWindow::on_pushButton_zoomout_clicked()
{
    //onvifdevice->ZoomOut();

    onvifdevice->FocusMove(1);
}


void MainWindow::on_pushButton_zoomin_clicked()
{
    //onvifdevice->ZoomIn();
    onvifdevice->FocusMove(-1);
}


void MainWindow::on_pushButton_Stop_clicked()
{
    onvifdevice->StopZoom();

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
void MainWindow::on_pushButton_GetTIme_clicked()
{

    QDateTime dateTime;
    onvifdevice->GetSystemDateAndTime(dateTime);
    ui->dateTimeEdit->setDateTime(dateTime);

}


void MainWindow::on_pushButton_SetTime_clicked()
{
    QDateTime dateTime =  ui->dateTimeEdit->dateTime();
    onvifdevice->SetSystemDateAndTime(dateTime);

}


void MainWindow::on_pushButton_GetHost_clicked()
{

    //    onvifdevice->GetHostname();
    //    onvifdevice->GetIPAddressFilter();
    //    onvifdevice->GetNetworkDefaultGateway();
    //    onvifdevice->GetDNS();

}


void MainWindow::on_pushButton_SetHost_clicked()
{

    //    onvifdevice->SetHostname();
    //    onvifdevice->SetIPAddressFilter();
    //    onvifdevice->SetNetworkDefaultGateway();
    //    onvifdevice->SetDNS();
}


void MainWindow::on_pushButton_SetImagingSettings_clicked()
{

    float brightness = ui->lineEdit_brightness->text().toFloat();
    float ColorSaturation = ui->lineEdit_ColorSaturation->text().toFloat();
    float Contrast = ui->lineEdit_Contrast->text().toFloat();
    float Sharpness = ui->lineEdit_Sharpness->text().toFloat();

    onvifdevice->SetBrightness(brightness);
    onvifdevice->SetColorSaturation(ColorSaturation);
    onvifdevice->SetContrast(Contrast);
    onvifdevice->SetSharpness(Sharpness);


}


void MainWindow::on_pushButton_GetImagingSettings_clicked()
{


    float Brightness = onvifdevice->GetBrightness();
    float Contrast= onvifdevice->GetContrast();
    float ColorSaturation = onvifdevice->GetColorSaturation();
    float Sharpness = onvifdevice->GetSharpness();

    ui->lineEdit_brightness->setText(QString::number(Brightness));
    ui->lineEdit_ColorSaturation->setText(QString::number(Contrast));
    ui->lineEdit_Contrast->setText(QString::number(ColorSaturation));
    ui->lineEdit_Sharpness->setText(QString::number(Sharpness));


    ui->horizontalSlider_brightness->setValue(Brightness);
    ui->horizontalSlider_ColorSaturation->setValue(Contrast);
    ui->horizontalSlider_Contrast->setValue(ColorSaturation);
    ui->horizontalSlider_Sharpness->setValue(Sharpness);


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


void MainWindow::on_pushButton_left_released()
{
    onvifdevice->StopMove();
}


void MainWindow::on_pushButton_right_released()
{
    onvifdevice->StopMove();
}




void MainWindow::on_pushButton_init_clicked()
{

    mPtzurl = ui->comboBox_2->itemText(0);
    QString name =  ui->lineEdit_username->text();
    QString passwd = ui->lineEdit_password->text();
    if(!init){
        onvifdevice = new OnvifDevice(mPtzurl);
        onvifdevice->SetAuth(name,passwd);
        onvifdevice->Initialize();
        init= true;
    }


}


void MainWindow::on_pushButton_GetOSD_clicked()
{
    QVector<struOSD> OSDs;
    if(!onvifdevice->GetOSDs(OSDs)){
        return;
    }


    ui->lineEdit_token->setText(OSDs.at(0).token);
    ui->lineEdit_plaintext->setText(OSDs.at(0).PlainText);

}

struOSD MainWindow::getUIOsd(){
    struOSD osd = {0};
    int index = ui->comboBox_Position->currentIndex();
    if(index == 0){
        osd.PositionType = "Custom";
        osd.x = ui->comboBox_x->currentText().toFloat();
        osd.y = ui->comboBox_y->currentText().toFloat();
    }
    else{
        switch(index){
        case 1:
            osd.PositionType = "UpperLeft";
            break;
        case 2:
            osd.PositionType = "UpperRight";
            break;
        case 3:
            osd.PositionType = "LowerLeft";
            break;
        case 4:
            osd.PositionType = "LowerRight";
            break;
        default:
            break;
        }
    }


    osd.PlainText= ui->lineEdit_plaintext->text();
    osd.FontSize = ui->comboBox_fontsize->currentText().toFloat();

    return osd;

}
/*
PositionType:
    UpperLeft 左上
    UpperRight 右上
    LowerLeft 左下
    LowerRight 右下
    Custom 自定义
*/
void MainWindow::on_pushButton_AddOSD_clicked()
{
    struOSD osd = getUIOsd();
    //创建OSD成功后,会返回设备上标识的OSD token
    osd.token = onvifdevice->CreateOSD(osd);
}


void MainWindow::on_pushButton_ModifyOSD_clicked()
{
    struOSD osd = getUIOsd();
    osd.token = ui->lineEdit_token->text();
    onvifdevice->SetOSD(osd);
}


void MainWindow::on_pushButton_DelOSD_clicked()
{

    onvifdevice->DelOSD(ui->lineEdit_token->text());
}






void MainWindow::on_comboBox_Position_currentIndexChanged(int index)
{
    if(index !=0){


        ui->comboBox_x->setEnabled(false);
           ui->comboBox_y->setEnabled(false);
    }
    else{

        ui->comboBox_x->setEnabled(true);
           ui->comboBox_y->setEnabled(true);
    }
}


void MainWindow::on_pushButton_SystemReboot_clicked()
{
    onvifdevice->SystemReboot();
}

