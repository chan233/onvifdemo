#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mPtzurl = "http://192.168.0.25:8080/onvif/device_service";

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_boradcast_clicked()
{
    onvifDevice = new OnvifDeviceClient(QUrl("http://192.168.0.25:8080/onvif/device_service"));
    onvifDevice->SetAuth("admin", "admin", AUTO);
    auto pool = QThreadPool::globalInstance();

    OnvifEventClient *onvifEvent = nullptr;

    Request<_tds__GetServices> request;
    request.IncludeCapability = false;
    auto servicesResponse = onvifDevice->GetServices(request);


}


void MainWindow::on_pushButton_GetDeviceInformation_clicked()
{
    onvifDevice = new OnvifDeviceClient(QUrl("http://192.168.0.25:8080/onvif/device_service"));
    onvifDevice->SetAuth("admin", "admin", AUTO);
    auto pool = QThreadPool::globalInstance();

    OnvifEventClient *onvifEvent = nullptr;
    Request<_tds__GetDeviceInformation> request;

    auto servicesResponse = onvifDevice->GetDeviceInformation(request);

}


void MainWindow::on_pushButton_Probe_clicked()
{
    auto discovery = new OnvifDiscoveryClient(mPtzurl);
    ProbeTypeRequest request;
    request.Types = "tds:Device";
    //    auto uuidOne = QString("uuid:%1").arg(SoapHelper::GenerateUuid());
    //    auto probeResponseTwo = discovery->Probe(request, uuidOne);
    //    request.Types = "tdn:NetworkVideoTransmitter";
    //    auto uuidTwo = QString("uuid:%1").arg(SoapHelper::GenerateUuid());
    //    auto probeResponseOne = discovery->Probe(request, uuidTwo);
}


void MainWindow::on_pushButton_GetPresets_clicked()
{
    OnvifPtzClient *ptzclient = new OnvifPtzClient(mPtzurl);
    Request<_tptz__GetPresets> rRequest;
    auto response = ptzclient->GetPresets(rRequest);
}


void MainWindow::on_pushButton_SetPreset_clicked()
{
    OnvifPtzClient *ptzclient = new OnvifPtzClient(mPtzurl);
    Request<_tptz__SetPreset> rRequest;

    auto response = ptzclient->SetPreset(rRequest);

}



void MainWindow::on_pushButton_CurrentPreset_clicked()
{
    OnvifPtzClient *ptzclient = new OnvifPtzClient(mPtzurl);
    Request<_tptz__SetPreset> rRequest;

    auto response = ptzclient->SetPreset(rRequest);
}


void MainWindow::on_pushButton_CurrentLoc_clicked()
{

}


void MainWindow::on_pushButton_CallStart_clicked()
{
    OnvifPtzClient *ptzclient = new OnvifPtzClient(mPtzurl);
    Request<_tptz__GotoHomePosition> rRequest;
    auto response = ptzclient->GotoHomePosition(rRequest);
}


void MainWindow::on_pushButton_SetStart_clicked()
{
    OnvifPtzClient *ptzclient = new OnvifPtzClient(mPtzurl);
    Request<_tptz__SetHomePosition> rRequest;

    auto response = ptzclient->SetHomePosition(rRequest);
}


void MainWindow::on_pushButton_GeoMove_clicked()
{
    OnvifPtzClient *ptzclient = new OnvifPtzClient(mPtzurl);
    Request<_tptz__GeoMove> rRequest;

    auto response = ptzclient->GeoMove(rRequest);
}


void MainWindow::on_pushButton_StopGeoMove_clicked()
{
    OnvifPtzClient *ptzclient = new OnvifPtzClient(mPtzurl);
    Request<_tptz__Stop> rRequest;
    auto response = ptzclient->Stop(rRequest);
}


void MainWindow::on_pushButton_leftup_clicked()
{

}


void MainWindow::on_pushButton_up_clicked()
{
    OnvifPtzClient *ptzclient = new OnvifPtzClient(mPtzurl);
    if(abusolute){

        Request<_tptz__AbsoluteMove> rRequest;
        auto response = ptzclient->AbsoluteMove(rRequest);
    }
    else if(continuous) {

        Request<_tptz__ContinuousMove> rRequest;
        auto response = ptzclient->ContinuousMove(rRequest);
    }
    else if(relative){

        Request<_tptz__RelativeMove> rRequest;
        auto response = ptzclient->RelativeMove(rRequest);
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

