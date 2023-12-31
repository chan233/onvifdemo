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

    QVector<Preset> presets;
    bool ret = onvifdevice->GetPresets(presets);

    if(ret == false){
        return;
    }

    auto count = 0;
    ui->tableWidget_preset->setRowCount(presets.size());//设置列数
    for(auto p :presets){
        QTableWidgetItem *name = new QTableWidgetItem() ;
        QTableWidgetItem *token = new QTableWidgetItem() ;
        name->setText(p.name);
        token->setText(p.token);

        ui->tableWidget_preset->setItem(count,0,name);
        ui->tableWidget_preset->setItem(count,1,token);
        ++count;
    }






}


void MainWindow::on_pushButton_SetPreset_clicked()
{
    QString result;
    onvifdevice->SetPreset(result);
    on_pushButton_GetPresets_clicked();
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

    onvifdevice->ContinuousMove(0,1);
}

void MainWindow::on_pushButton_down_clicked()
{

    onvifdevice->ContinuousMove(0,-1);
}
void MainWindow::on_pushButton_leftup_clicked()
{
    onvifdevice->ContinuousMove(1,1);

}

void MainWindow::on_pushButton_rightup_clicked()
{
    onvifdevice->ContinuousMove(-1,1);
}


void MainWindow::on_pushButton_left_clicked()
{
    onvifdevice->ContinuousMove(1,0);
}

void MainWindow::on_pushButton_right_clicked()
{

    onvifdevice->ContinuousMove(-1,0);
}

void MainWindow::on_pushButton_reset_clicked()
{
    onvifdevice->ContinuousMove(0,0);

}




void MainWindow::on_pushButton_leftdown_clicked()
{
    onvifdevice->ContinuousMove(1,-1);
}




void MainWindow::on_pushButton_rightdown_clicked()
{

    onvifdevice->ContinuousMove(-1,-1);
}


void MainWindow::on_pushButton_zoomout_clicked()
{
    onvifdevice->ZoomOut();


}


void MainWindow::on_pushButton_zoomin_clicked()
{
    onvifdevice->ZoomIn();

}


void MainWindow::on_pushButton_fin_clicked()
{
    onvifdevice->FocusMove(1);
}

void MainWindow::on_pushButton_fout_clicked()
{
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
    onvifdevice->SetBrightness(position);

}


void MainWindow::on_horizontalSlider_ColorSaturation_sliderMoved(int position)
{
    ui->lineEdit_ColorSaturation->setText(QString::number(position));

    onvifdevice->SetColorSaturation(position);

}


void MainWindow::on_horizontalSlider_Contrast_sliderMoved(int position)
{
    ui->lineEdit_Contrast->setText(QString::number(position));

    onvifdevice->SetContrast(position);

}


void MainWindow::on_horizontalSlider_Sharpness_sliderMoved(int position)
{
    ui->lineEdit_Sharpness->setText(QString::number(position));

    onvifdevice->SetSharpness(position);
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


    QString name =  ui->lineEdit_username->text();
    QString passwd = ui->lineEdit_password->text();
    if(!init){

        QString addresss = ui->lineEdit_ip->text();
        auto devices = OnvifDevice::MulticastProbe(addresss);
        for  (auto device : devices){

            if(device.indexOf(addresss)){

                mPtzurl = device;
                ui->lineEdit_xaddr->setText(mPtzurl.toString());

                // QString xaddr = "http://" + addresss + "/onvif/device_service";
                onvifdevice = new OnvifDevice(QUrl(mPtzurl));
                qDebug()<<"current url :"<<mPtzurl;
                onvifdevice->SetAuth(name,passwd);

                onvifdevice->Initialize(ui->comboBox_timeout->currentText().toInt());

                init= true;

                auto profiles = onvifdevice->GetAllProfiles();
                setProfiles(profiles);
                //on_pushButton_GetImagingSettings_clicked();
            }

        }



    }


}


void MainWindow::setProfiles(const QVector<QString> &profiles){

    ui->comboBox_profiles->clear();
    for(auto profile : profiles){
        ui->comboBox_profiles->addItem(profile);
    }

}
void MainWindow::on_pushButton_GetOSD_clicked()
{
    QVector<struOSD> OSDs;
    if(onvifdevice->GetOSDs(OSDs) == -1){
        return;
    }

    if(OSDs.empty()){
        return;
    }
    ui->comboBox_osdtoken->clear();
    for(auto _osd : OSDs){

        ui->comboBox_osdtoken->addItem( _osd.token);
    }



}
/*
PositionType:
    UpperLeft 左上
    UpperRight 右上
    LowerLeft 左下
    LowerRight 右下
    Custom 自定义
*/
struOSD MainWindow::getOSDParam(){
    struOSD osd = {0};
    int index = ui->comboBox_Position->currentIndex();
    switch(index){
    case 0:
        osd.PositionType = "Custom";
        osd.x = ui->comboBox_x->currentText().toFloat();
        osd.y = ui->comboBox_y->currentText().toFloat();
        break;
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

    osd.PlainText= ui->lineEdit_plaintext->text();
    osd.FontSize = ui->comboBox_fontsize->currentText().toFloat();
    osd.token = ui->comboBox_osdtoken->currentText();
    return osd;

}

void MainWindow::on_pushButton_AddOSD_clicked()
{
    struOSD osd = getOSDParam();
    //创建OSD成功后,会返回设备上标识的OSD token

    bool ret = onvifdevice->CreateOSD(osd,osd.token);
    on_pushButton_GetOSD_clicked();
}


void MainWindow::on_pushButton_ModifyOSD_clicked()
{
    struOSD osd = getOSDParam();
    osd.token = ui->comboBox_osdtoken->currentText();
    onvifdevice->SetOSD(osd);
    //    for(int i =0;i < 10000;i++){
    //        osd.PlainText = QString::number(i);

    //    }

}


void MainWindow::on_pushButton_DelOSD_clicked()
{


    bool ret = onvifdevice->DelOSD(ui->comboBox_osdtoken->currentText());
    if(ret){
        on_pushButton_GetOSD_clicked();
    }
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






void MainWindow::on_pushButton_getservice_clicked()
{
    auto addresss  = onvifdevice->GetServiceAddress();

    QTableWidgetItem *item0 = new QTableWidgetItem() ;
    QTableWidgetItem *item1 = new QTableWidgetItem() ;
    QTableWidgetItem *item2 = new QTableWidgetItem() ;
    QTableWidgetItem *item3 = new QTableWidgetItem() ;
    QTableWidgetItem *item4 = new QTableWidgetItem() ;
    QTableWidgetItem *item5 = new QTableWidgetItem() ;

    item0->setText(addresss.ipAddress);
    item1->setText(addresss.xAddresss);
    item2->setText(addresss.ptzAddresss);
    item3->setText(addresss.mediadresss);
    item4->setText(addresss.eventAddresss);


    bool ret = onvifdevice->GetStreamUri(addresss.rtspaddress);
    if(ret){
        item5->setText(addresss.rtspaddress);
    }


    ui->tableWidget_service->setItem(0,0,item0);
    ui->tableWidget_service->setItem(1,0,item1);
    ui->tableWidget_service->setItem(2,0,item2);
    ui->tableWidget_service->setItem(3,0,item3);
    ui->tableWidget_service->setItem(4,0,item4);
    ui->tableWidget_service->setItem(5,0,item5);
}

void MainWindow::on_pushButton_DelPresets_clicked()
{
    if(ui->tableWidget_preset->rowCount() == 0){
        return;
    }
    if(mCurrentColumn != 1){
        return;
    }
    auto item = ui->tableWidget_preset->item(mCurrentRow,mCurrentColumn);

    onvifdevice->RemovePreset(item->text());
    on_pushButton_GetPresets_clicked();
}

void MainWindow::on_tableWidget_preset_cellClicked(int row, int column)
{
    mCurrentRow = row;
    mCurrentColumn = column;
}

void MainWindow::on_pushButton_getallprofiles_clicked()
{
    auto profiles = onvifdevice->GetAllProfiles();
    setProfiles(profiles);
}

void MainWindow::on_comboBox_profiles_currentIndexChanged(int index)
{
    onvifdevice->SetTokenIndex(index);
}

void MainWindow::on_pushButton_getvideosource_clicked()
{
    auto source = onvifdevice->GetAllVideoSource();
    setVideoSource(source);
}


void MainWindow::setVideoSource(const QVector<QString> &source){

    ui->comboBox_videosource->clear();
    for(auto s : source){
        ui->comboBox_videosource->addItem(s);
    }

}
void MainWindow::on_comboBox_videosource_currentIndexChanged(int index)
{
    onvifdevice->SetVideoSourceTokenIndex(index);

}

void MainWindow::on_comboBox_5_currentIndexChanged(const QString &arg1)
{

}

void MainWindow::on_pushButton_release_clicked()
{
    delete onvifdevice;
    onvifdevice = nullptr;
    init= false;

}
