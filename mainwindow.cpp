#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mPtzurl = "http://192.168.0.25:8080/onvif/device_service";


    getIPv4();



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

    auto ctxBuilder = SoapCtx::Builder();

    ctxBuilder.SetSendTimeout(1000);
    ctxBuilder.SetReceiveTimeout(1000);

    mUsername = ui->lineEdit_username->text();
    mUserPassword = ui->lineEdit_password->text();
    auto discovery = new OnvifDiscoveryClient(QUrl("soap.udp://239.255.255.250:3702"),ctxBuilder.Build());

    ProbeTypeRequest request;
    request.Types = "tds:Device";
    auto uuidOne = QString("uuid:%1").arg(SoapHelper::GenerateUuid());
    auto probeResponseTwo = discovery->Probe(request, uuidOne);
    request.Types = "tdn:NetworkVideoTransmitter";
    auto uuidTwo = QString("uuid:%1").arg(SoapHelper::GenerateUuid());
    auto probeResponseOne = discovery->Probe(request, uuidTwo);
    if(probeResponseOne && probeResponseTwo) {
        qDebug() << "Searching ONVIF devices for" << 3000/ 1000 << "seconds";
        auto foundMatches = 0;
        auto beginTs = QDateTime::currentMSecsSinceEpoch();
        while(QDateTime::currentMSecsSinceEpoch() < beginTs + 3000) {
            auto matchResp = discovery->ReceiveProbeMatches();
            if(matchResp && matchResp.GetResultObject()) {
                auto relatesTo = matchResp.GetSoapHeaderRelatesTo();
                if(!relatesTo.isNull() && (uuidOne.compare(relatesTo) == 0 || uuidTwo.compare(relatesTo) == 0)) {
                    if(auto matchs = matchResp.GetResultObject()) {
                        if(matchs->wsdd__ProbeMatches) {
                            for(auto i = 0; i < matchs->wsdd__ProbeMatches->__sizeProbeMatch; ++i) {
                                wsdd__ProbeMatchesType match = matchs->wsdd__ProbeMatches[i];
                                for(auto ii = 0; ii < match.__sizeProbeMatch; ++ii) {
                                    foundMatches++;
                                    auto probe = match.ProbeMatch[ii];
                                    qDebug() << "Found match:";
                                    qDebug() << "    Type:" << probe.Types;
                                    qDebug() << "    Endpoint:" << probe.XAddrs;
                                    if(probe.wsa5__EndpointReference.Address) {
                                        qDebug() << "     Reference:" << probe.wsa5__EndpointReference.Address;
                                    }
                                    if(probe.Scopes) {
                                        auto scopeList = QString::fromLocal8Bit(probe.Scopes->__item).split(' ');
                                        auto matchBy = QString::fromLocal8Bit(probe.Scopes->MatchBy);
                                        if(!matchBy.isEmpty()) {
                                            qDebug() << "    Match:" << matchBy;
                                        }
                                        qDebug() << "    Scope:";
                                        for(auto scope : scopeList) {
                                            if(!scope.isEmpty()) qDebug() << "        " << scope;
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    qDebug() << "Skipping non related message with id:" << relatesTo;
                }
            }
        }
        qDebug() << "Found" << (foundMatches == 0 ? "no" : QString::number(foundMatches)) << (foundMatches > 1 ? "matches" : "match");
    } else {
        if(!probeResponseOne)
            qDebug() << probeResponseOne.GetCompleteFault();
        else
            qDebug() << probeResponseTwo.GetCompleteFault();
    }

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


void MainWindow::on_pushButton_GetNTP_clicked()
{
    onvifDevice = new OnvifDeviceClient(QUrl("http://192.168.0.25:8080/onvif/device_service"));
    onvifDevice->SetAuth("admin", "admin", AUTO);

    Request<_tds__GetNTP> request;

    auto servicesResponse = onvifDevice->GetNTP(request);
}


void MainWindow::on_pushButton_SetNTP_clicked()
{
    onvifDevice = new OnvifDeviceClient(QUrl("http://192.168.0.25:8080/onvif/device_service"));
    onvifDevice->SetAuth("admin", "admin", AUTO);

    Request<_tds__SetNTP> request;


    auto servicesResponse = onvifDevice->SetNTP(request);
}


void MainWindow::on_pushButton_GetHost_clicked()
{
    onvifDevice = new OnvifDeviceClient(QUrl("http://192.168.0.25:8080/onvif/device_service"));
    onvifDevice->SetAuth("admin", "admin", AUTO);

    Request<_tds__GetHostname> HostnameRequest;
    auto HostnameResponse = onvifDevice->GetHostname(HostnameRequest);

    Request<_tds__GetIPAddressFilter> GetIPAddressFilterRequest;
    auto GetIPAddressFilterResponse = onvifDevice->GetIPAddressFilter(GetIPAddressFilterRequest);

    Request<_tds__GetNetworkDefaultGateway> GetNetworkDefaultGatewayRequest;
    auto GetNetworkDefaultGatewayResponse = onvifDevice->GetNetworkDefaultGateway(GetNetworkDefaultGatewayRequest);


    Request<_tds__GetDNS> GetDNSRequest;
    auto GetDNSResponse = onvifDevice->GetDNS(GetDNSRequest);




}


void MainWindow::on_pushButton_SetHost_clicked()
{
    onvifDevice = new OnvifDeviceClient(QUrl("http://192.168.0.25:8080/onvif/device_service"));
    onvifDevice->SetAuth("admin", "admin", AUTO);

    Request<_tds__SetHostname> HostnameRequest;
    auto HostnameResponse = onvifDevice->SetHostname(HostnameRequest);

    Request<_tds__SetIPAddressFilter> SetIPAddressFilterRequest;
    auto SetIPAddressFilterResponse = onvifDevice->SetIPAddressFilter(SetIPAddressFilterRequest);

    Request<_tds__SetNetworkDefaultGateway> SetNetworkDefaultGatewayRequest;
    auto SetNetworkDefaultGatewayResponse = onvifDevice->SetNetworkDefaultGateway(SetNetworkDefaultGatewayRequest);


    Request<_tds__SetDNS> SetDNSRequest;
    auto SetDNSResponse = onvifDevice->SetDNS(SetDNSRequest);
}


void MainWindow::on_pushButton_SetImagingSettings_clicked()
{

    ImagingClient = new OnvifImagingClient(QUrl("http://192.168.0.25:8080/onvif/device_service"));
    ImagingClient->SetAuth("admin", "admin", AUTO);

    Request<_timg__SetImagingSettings> rRequest;

    auto response = ImagingClient->SetImagingSettings(rRequest);


}


void MainWindow::on_pushButton_GetImagingSettings_clicked()
{
    ImagingClient = new OnvifImagingClient(QUrl("http://192.168.0.25:8080/onvif/device_service"));
    ImagingClient->SetAuth("admin", "admin", AUTO);

    Request<_timg__GetImagingSettings> rRequest;

    auto response = ImagingClient->GetImagingSettings(rRequest);


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

