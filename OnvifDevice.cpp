/* Copyright(C) 2021 Björn Stresing
*
* This program is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.If not, see < http://www.gnu.org/licenses/>.
*/
#include "OnvifDevice.h"
#include "OnvifAnalyticsClient.h"
#include "OnvifDeviceClient.h"
#include "OnvifDiscoveryClient.h"
#include "OnvifDisplayClient.h"
#include "OnvifEventClient.h"
#include "OnvifImagingClient.h"
#include "OnvifMediaClient.h"
#include "OnvifMedia2Client.h"
#include "OnvifEventClient.h"
#include "OnvifImagingClient.h"
#include "OnvifPtzClient.h"
#include "OnvifReceiverClient.h"
#include "OnvifRecordingClient.h"
#include "OnvifReplayClient.h"
#include "SoapCtx.h"
#include "OnvifDeviceClient.h"
#include <QUrl>

#include "SoapHelper.h"

#include <QUuid>


struct OnvifDevicePrivate {

    OnvifDevicePrivate(OnvifDevice *pQ) :
        mpQ(pQ),
        mUserName(),
        mPassword(),
        mAnalyticsEndpoint(),
        mDeviceEndpoint(),
        mDiscoveryEndpoint(),
        mDisplayEndpoint(),
        mEventEndpoint(),
        mImagingEndpoint(),
        mMediaEndpoint(),
        mPtzEndpoint(),
        mReceiverEndpoint(),
        mRecordingEndpoint(),
        mReplayEndpoint(),
        mpOnvifAnalyticsClient(nullptr),
        mpOnvifDeviceClient(nullptr),
        mpOnvifDiscoveryClient(nullptr),
        mpOnvifDisplayClient(nullptr),
        mpOnvifEventClient(nullptr),
        mpOnvifImagingClient(nullptr),
        mpOnvifMediaClient(nullptr),
        mpOnvifMedia2Client(nullptr),
        mpOnvifPtzClient(nullptr),
        mpOnvifReceiverClient(nullptr),
        mpOnvifRecordingClient(nullptr),
        mpOnvifReplayClient(nullptr),
        mTokens() {}

    OnvifDevice *mpQ;
    QString mUserName;
    QString mPassword;
    QUrl mAnalyticsEndpoint;
    QUrl mDeviceEndpoint;
    QUrl mDiscoveryEndpoint;
    QUrl mDisplayEndpoint;
    QUrl mEventEndpoint;
    QUrl mImagingEndpoint;
    QUrl mMediaEndpoint;
    QUrl mMedia2Endpoint;
    QUrl mPtzEndpoint;
    QUrl mReceiverEndpoint;
    QUrl mRecordingEndpoint;
    QUrl mReplayEndpoint;
    OnvifAnalyticsClient *mpOnvifAnalyticsClient;
    OnvifDeviceClient *mpOnvifDeviceClient;
    OnvifDiscoveryClient *mpOnvifDiscoveryClient;
    OnvifDisplayClient *mpOnvifDisplayClient;
    OnvifEventClient *mpOnvifEventClient;
    OnvifImagingClient *mpOnvifImagingClient;
    OnvifMediaClient *mpOnvifMediaClient;
    OnvifMedia2Client *mpOnvifMedia2Client;
    OnvifPtzClient *mpOnvifPtzClient;
    OnvifReceiverClient *mpOnvifReceiverClient;
    OnvifRecordingClient *mpOnvifRecordingClient;
    OnvifReplayClient *mpOnvifReplayClient;
    QVector<QString> mTokens;
    QVector<QString> mOSDTokenList;
    int GetVideoSourceToken(QString *token);
    QString GetToken(int flag);
    bool genOSDRequest(Request<_trt__CreateOSD> &request, const struOSD &osdparm);
    bool setOSDRequest(Request<_trt__SetOSD> &request,const struOSD &osdparm);

};

OnvifDevice::OnvifDevice(const QUrl &rDeviceEndpoint, QObject *pParent /*= nullptr*/) :
    QObject(pParent), mpD(new OnvifDevicePrivate(this)) {

    mpD->mDeviceEndpoint = rDeviceEndpoint;
}

OnvifDevice::~OnvifDevice() {

    delete mpD;
}

SimpleResponse OnvifDevice::Initialize() {

    auto builder = SoapCtx::Builder();
    auto ctx = builder
        #ifndef NDEBUG
            //.EnableOMode(SOAP_XML_INDENT)
        #endif
            .Build();


    qDebug() << "Using device endpoint: " << mpD->mDeviceEndpoint.toString();
    auto device = mpD->mpOnvifDeviceClient = new OnvifDeviceClient(mpD->mDeviceEndpoint, ctx, this);
    if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
        device->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
    }

    OnvifEventClient *onvifEvent = nullptr;

    Request<_tds__GetServices> request;
    request.IncludeCapability = false;
    auto servicesResponse = device->GetServices(request);
    if (servicesResponse) {
        for (auto service : servicesResponse.GetResultObject()->Service) {
            if (service->Namespace == OnvifAnalyticsClient::GetServiceNamespace()) {
                qDebug() << "ONVIF analytics service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifAnalyticsClient = new OnvifAnalyticsClient(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifAnalyticsClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            }
            if (service->Namespace == OnvifDeviceClient::GetServiceNamespace()) {
                qDebug() << "ONVIF device service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifDeviceClient = new OnvifDeviceClient(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifDeviceClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            }
            else if (service->Namespace == OnvifDisplayClient::GetServiceNamespace()) {
                qDebug() << "ONVIF display service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifDisplayClient = new OnvifDisplayClient(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifDisplayClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            }
            else if (service->Namespace == OnvifEventClient::GetServiceNamespace()) {
                qDebug() << "ONVIF event service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifEventClient = new OnvifEventClient(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifEventClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            }
            else if (service->Namespace == OnvifImagingClient::GetServiceNamespace()) {
                qDebug() << "ONVIF imaging service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifImagingClient = new OnvifImagingClient(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifImagingClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);

                }
            }
            else if (service->Namespace == OnvifMediaClient::GetServiceNamespace()) {
                qDebug() << "ONVIF media service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifMediaClient = new OnvifMediaClient(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifMediaClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);

                }
            }
            else if (service->Namespace == OnvifMedia2Client::GetServiceNamespace()) {
                qDebug() << "ONVIF media2 service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifMedia2Client = new OnvifMedia2Client(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifMedia2Client->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);


                }
            }
            else if (service->Namespace == OnvifPtzClient::GetServiceNamespace()) {
                qDebug() << "ONVIF ptz service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifPtzClient = new OnvifPtzClient(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifPtzClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);

                }
            }
            else if (service->Namespace == OnvifReceiverClient::GetServiceNamespace()) {
                qDebug() << "ONVIF receiver service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifReceiverClient = new OnvifReceiverClient(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifReceiverClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            }
            else if (service->Namespace == OnvifRecordingClient::GetServiceNamespace()) {
                qDebug() << "ONVIF recording service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifRecordingClient = new OnvifRecordingClient(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifRecordingClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            }
            else if (service->Namespace == OnvifReplayClient::GetServiceNamespace()) {
                qDebug() << "ONVIF replay service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifReplayClient = new OnvifReplayClient(url, ctx, this);
                if (!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifReplayClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            }
            else {
                qDebug() << "Unknown service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
            }
        }
    }
    else {
        qWarning() << "Couldn't receive response: " << servicesResponse.GetCompleteFault();
    }


    Request<_tds__GetCapabilities> r;
    auto res = device->GetCapabilities(r);

    if (auto rr = res.GetResultObject()) {
        auto capa = res.GetResultObject()->Capabilities;
        //     if(capa->Device) {
        //      //	TODO: Print
        //     }
        if (capa->Media) {
            //	TODO: Print
            //            capa->Media->XAddr;
            //            Request<_trt__GetProfiles> rRequest;
            //            auto re = mpD->mpOnvifMediaClient->GetProfiles(rRequest);
            //            auto pro = re.GetResultObject()->Profiles;
            //            for(auto p : pro){

            //                qDebug() << "found token :"<<p->token;
            //                mpD->mTokens << p->token;

            //            }

        }

    }

    InitializeTopicSet();

    Request<_tds__GetEndpointReference> endpointRefRequest;
    auto endpointRefResponse = mpD->mpOnvifDeviceClient->GetEndpointReference(endpointRefRequest);
    if (endpointRefResponse) {
        if (auto endpointRef = endpointRefResponse.GetResultObject()) {

        }
        else {
            qWarning() << "Couldn't extract the device endpoint reference";
        }
    }
    else {
        qWarning() << endpointRefResponse;
    }

    return SimpleResponse();
}

SimpleResponse OnvifDevice::InitializeTopicSet() {

    if (mpD->mpOnvifEventClient) {
        Request<_tev__GetEventProperties> request;
        auto response = mpD->mpOnvifEventClient->GetParsedEventProperties(request);
        if (response) {
            for (auto topic : response.GetResultObject().GetTopics()) {
                auto topicPath = topic.GetTopicPath().join("/");
                if (topicPath.isEmpty()) topicPath.append("/");
                qDebug() << "\nTopic name" << topic.GetName();
                qDebug() << "Topic path" << topicPath;
                for (auto item : topic.GetItems()) {
                    if (item.GetPrimitiveType() == SimpleItemInfo::PRIMITIVE_UNKNOWN) {
                        qDebug() << "    Unknown Item" << item.GetName() << "type" << item.GetSoapTypeQname();
                    }
                    else {
                        QString primitive;
                        switch (item.GetPrimitiveType()) {
                        case SimpleItemInfo::PRIMITIVE_BOOL:
                            primitive = "boolean";
                            break;
                        case SimpleItemInfo::PRIMITIVE_INTEGER:
                            primitive = "integer";
                            break;
                        case SimpleItemInfo::PRIMITIVE_REAL:
                            primitive = "real";
                            break;
                        case SimpleItemInfo::PRIMITIVE_STRING:
                            primitive = "string";
                            break;
                        default:
                            primitive = "unknown";
                            break;
                        }
                        qDebug() << "    Item" << item.GetName() << "type" << item.GetSoapTypeQname() << "primitive" << primitive;
                    }
                }
            }
        }
        else {
            qWarning() << "Couldn't get event properties" << response.GetCompleteFault();
        }
    }
    return SimpleResponse();
}

void OnvifDevice::SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode /*= AUTO*/) {

    mpD->mUserName = rUserName;
    mpD->mPassword = rPassword;
}


bool OnvifDevice::AbsoluteMove(float x, float y, float speed) {

    Request<_tptz__AbsoluteMove> rRequest;
    QString ProfileToken;
    rRequest.ProfileToken = "Profile_1";
    rRequest.Speed = new tt__PTZSpeed;
    rRequest.Position = new tt__PTZVector;
    rRequest.Position->PanTilt = new tt__Vector2D;
    rRequest.Speed->PanTilt = new tt__Vector2D;
    rRequest.Position->PanTilt->x = x;
    rRequest.Position->PanTilt->y = y;
    rRequest.Position->PanTilt->x = speed;
    rRequest.Position->PanTilt->y = speed;
    auto response = mpD->mpOnvifPtzClient->AbsoluteMove(rRequest);

    return response.IsFault();
}
bool OnvifDevice::RelativeMove(float x, float y, float speed) {

    Request<_tptz__RelativeMove> rRequest;
    QString ProfileToken;
    rRequest.ProfileToken = "Profile_1";
    rRequest.Speed = new tt__PTZSpeed;
    rRequest.Speed->PanTilt = new tt__Vector2D;
    rRequest.Translation = new tt__PTZVector;
    rRequest.Speed->PanTilt->x = x;
    rRequest.Speed->PanTilt->y = y;
    rRequest.Translation->PanTilt = new tt__Vector2D;

    auto response = mpD->mpOnvifPtzClient->RelativeMove(rRequest);
    return response.IsFault();
}

bool OnvifDevice::ContinuousMove(float x, float y, int flag,float speed) {
    Request<_tptz__ContinuousMove> rRequest;

    if(flag == 1){
        rRequest.ProfileToken = "Profile_1";
    }
    else{
        rRequest.ProfileToken = QString("Profile_")+QString::number(flag);
    }


    rRequest.Velocity = new tt__PTZSpeed;
    rRequest.Velocity->PanTilt = new tt__Vector2D;
    rRequest.Velocity->PanTilt->x = x;
    rRequest.Velocity->PanTilt->y = y;

    auto response = mpD->mpOnvifPtzClient->ContinuousMove(rRequest);
    return response.IsFault();
}
bool OnvifDevice::StopMove() {
    Request<_tptz__Stop> rRequest;
    rRequest.ProfileToken = "Profile_1";
    bool *_PanTilt = new bool;
    bool *_Zoom = new bool;
    *_PanTilt = true;
    *_Zoom = false;
    rRequest.PanTilt = _PanTilt;
    rRequest.Zoom = _Zoom;
    auto response = mpD->mpOnvifPtzClient->Stop(rRequest);
    return response.IsFault();
}



bool OnvifDevice::ZoomIn(int x) {
    Request<_tptz__ContinuousMove> rRequest;
    rRequest.ProfileToken = "Profile_2";
    rRequest.Velocity = new tt__PTZSpeed;
    rRequest.Velocity->Zoom = new tt__Vector1D;
    rRequest.Velocity->Zoom->x = x;
    auto response = mpD->mpOnvifPtzClient->ContinuousMove(rRequest);
    return response.IsFault();

}
bool OnvifDevice::ZoomOut(int x) {

    Request<_tptz__ContinuousMove> rRequest;
    rRequest.ProfileToken = "Profile_2";

    rRequest.Velocity = new tt__PTZSpeed;
    rRequest.Velocity->Zoom = new tt__Vector1D;
    rRequest.Velocity->Zoom->x = x;
    auto response = mpD->mpOnvifPtzClient->ContinuousMove(rRequest);
    return response.IsFault();
}
bool OnvifDevice::StopZoom() {
    Request<_tptz__Stop> rRequest;
    rRequest.ProfileToken = "Profile_2";

    bool *_PanTilt = new bool;
    bool *_Zoom = new bool;
    *_PanTilt = false;
    *_Zoom = true;
    rRequest.PanTilt = _PanTilt;
    rRequest.Zoom = _Zoom;
    auto response = mpD->mpOnvifPtzClient->Stop(rRequest);
    return response.IsFault();
}

bool OnvifDevice::FocusMove(float fSpeed) {

    Request<_timg__Move> rRequest;
    QString ProfileToken;
    rRequest.Focus = new tt__FocusMove;
    rRequest.Focus->Absolute = nullptr;
    rRequest.Focus->Relative = nullptr;

    rRequest.Focus->Continuous = new tt__ContinuousFocus;
    rRequest.Focus->Continuous->Speed = fSpeed;

    rRequest.VideoSourceToken = "VideoSource_1";
    auto response = mpD->mpOnvifImagingClient->Move(rRequest);

    return response.IsFault();
}
bool OnvifDevice::Stop() {
    Request<_tptz__Stop> rRequest;
    rRequest.ProfileToken = "Profile_2";

    auto response = mpD->mpOnvifPtzClient->Stop(rRequest);
    return response.IsFault();
}

bool OnvifDevice::GetPresets() {
    Request<_tptz__GetPresets> rRequest;

    rRequest.ProfileToken = mpD->GetToken(1);
    auto response = mpD->mpOnvifPtzClient->GetPresets(rRequest);
    auto preset = response.GetResultObject()->Preset;

    for (auto p : preset) {
        qDebug() << p->Name;
    }
    return response.IsFault();
}

bool OnvifDevice::SetPreset() {



    Request<_tptz__SetPreset> rRequest;
    QString ProfileToken;
    rRequest.ProfileToken = ProfileToken;
    //rRequest.PresetToken = "perest_1";
    auto response = mpD->mpOnvifPtzClient->SetPreset(rRequest);
    return response.IsFault();
}


//bool OnvifDevice::SetImagingSettings(float Brightness,float Contrast,float ColorSaturation,float Sharpness){


//    Request<_timg__SetImagingSettings> rRequest;
//    rRequest.VideoSourceToken = "VideoSource_1";
//    rRequest.ImagingSettings = new tt__ImagingSettings20;
//    float *_Brightness = new float;
//    *_Brightness = Brightness;
//    float *_Contrast= new float;
//    *_Contrast = Contrast;

//    float *_ColorSaturation = new float;
//    *_ColorSaturation = ColorSaturation;
//    float *_Sharpness = new float;
//    *_Sharpness = Sharpness;

//    rRequest.ImagingSettings->Brightness= _Brightness;
//    rRequest.ImagingSettings->Contrast=  _Contrast;
//    rRequest.ImagingSettings->ColorSaturation =_ColorSaturation;
//    rRequest.ImagingSettings->Sharpness = _Sharpness;
//    auto response = mpD->mpOnvifImagingClient->SetImagingSettings(rRequest);
//    return response.IsFault();

//}

bool OnvifDevice::SetBrightness(float Brightness) {


    Request<_timg__SetImagingSettings> rRequest;
    rRequest.VideoSourceToken = "VideoSource_1";
    rRequest.ImagingSettings = new tt__ImagingSettings20;
    float *_Brightness = new float;
    *_Brightness = Brightness;
    rRequest.ImagingSettings->Brightness = _Brightness;

    auto response = mpD->mpOnvifImagingClient->SetImagingSettings(rRequest);

    return response.IsFault();

}

bool OnvifDevice::SetContrast(float Contrast) {


    Request<_timg__SetImagingSettings> rRequest;
    rRequest.VideoSourceToken = "VideoSource_1";
    rRequest.ImagingSettings = new tt__ImagingSettings20;
    float *_Contrast = new float;
    *_Contrast = Contrast;
    rRequest.ImagingSettings->Contrast = _Contrast;

    auto response = mpD->mpOnvifImagingClient->SetImagingSettings(rRequest);
    return response.IsFault();

}


bool OnvifDevice::SetColorSaturation(float ColorSaturation) {


    Request<_timg__SetImagingSettings> rRequest;
    rRequest.VideoSourceToken = "VideoSource_1";
    rRequest.ImagingSettings = new tt__ImagingSettings20;
    float *_ColorSaturation = new float;
    *_ColorSaturation = ColorSaturation;
    rRequest.ImagingSettings->ColorSaturation = _ColorSaturation;

    auto response = mpD->mpOnvifImagingClient->SetImagingSettings(rRequest);
    return response.IsFault();

}


bool OnvifDevice::SetSharpness(float Sharpness) {


    Request<_timg__SetImagingSettings> rRequest;
    rRequest.VideoSourceToken = "VideoSource_1";
    rRequest.ImagingSettings = new tt__ImagingSettings20;
    float *_Sharpness = new float;
    *_Sharpness = Sharpness;
    rRequest.ImagingSettings->Sharpness = _Sharpness;

    auto response = mpD->mpOnvifImagingClient->SetImagingSettings(rRequest);
    return response.IsFault();

}


//bool OnvifDevice::GetImagingSettings(){


//    Request<_timg__GetImagingSettings> rRequest;
//    rRequest.VideoSourceToken = "VideoSource_1";

//    auto response = mpD->mpOnvifImagingClient->GetImagingSettings(rRequest);
//    return response.IsFault();

//}

float OnvifDevice::GetBrightness() {


    Request<_timg__GetImagingSettings> rRequest;
    QString ProfileToken = "VideoSource_1";
    rRequest.VideoSourceToken = ProfileToken;
    auto response = mpD->mpOnvifImagingClient->GetImagingSettings(rRequest);
    if(response.IsFault()){
        return 0;
    }

    return *(response.GetResultObject()->ImagingSettings->Brightness);

}
float OnvifDevice::GetContrast() {


    Request<_timg__GetImagingSettings> rRequest;
    QString ProfileToken = "VideoSource_1";
    rRequest.VideoSourceToken = ProfileToken;
    auto response = mpD->mpOnvifImagingClient->GetImagingSettings(rRequest);

    if(response.IsFault()){
        return 0;
    }
    return *(response.GetResultObject()->ImagingSettings->Contrast);

}


float OnvifDevice::GetColorSaturation() {


    Request<_timg__GetImagingSettings> rRequest;
    QString ProfileToken = "VideoSource_1";
    rRequest.VideoSourceToken = ProfileToken;
    auto response = mpD->mpOnvifImagingClient->GetImagingSettings(rRequest);
    if(response.IsFault()){
        return 0;
    }
    return *(response.GetResultObject()->ImagingSettings->ColorSaturation);

}

float OnvifDevice::GetSharpness() {


    Request<_timg__GetImagingSettings> rRequest;
    QString ProfileToken = "VideoSource_1";
    rRequest.VideoSourceToken = ProfileToken;
    auto response = mpD->mpOnvifImagingClient->GetImagingSettings(rRequest);
    if(response.IsFault()){
        return 0;
    }
    return *(response.GetResultObject()->ImagingSettings->Sharpness);

}


bool OnvifDevice::SetHostname(QString name) {
    Request<_tds__SetHostname> HostnameRequest;

    HostnameRequest.Name = name;
    auto response = mpD->mpOnvifDeviceClient->SetHostname(HostnameRequest);
    return response.IsFault();


}


//使用 meida1 的接口来获取OSDs
bool OnvifDevice::GetOSDs(QVector<struOSD>& OSDs) {
    Request<_trt__GetOSDs> request;
    auto response = mpD->mpOnvifMediaClient->GetOSDs(request);

    if(!response.GetResultObject()){
        qDebug()<< response.GetCompleteFault();
        qDebug()<<  response.GetSoapFaultDetail();
        return false;
    }

    if(response.GetResultObject()->OSDs.empty()){
        return false;
    }


    if (!mpD->mOSDTokenList.empty()) {
        mpD->mOSDTokenList.clear();
    }

    for (auto OSD : response.GetResultObject()->OSDs) {
        qDebug() << "osd token ==>" << OSD->token << endl;
        struOSD osdTmp = { 0 };
        mpD->mOSDTokenList << OSD->token;


        if (OSD->TextString->PlainText) {
            QString  text = *OSD->TextString->PlainText;
            osdTmp.PlainText = text;
            qDebug() << text;
        }


        osdTmp.token = OSD->token;
        osdTmp.x = *OSD->Position->Pos->x;
        osdTmp.y = *OSD->Position->Pos->y;
        osdTmp.FontSize = *OSD->TextString->FontSize;
        osdTmp.PositionType = OSD->Position->Type;

        OSDs << osdTmp;

    }

    return true;
}

QString OnvifDevice::CreateOSD(const struOSD &osdparm) {

    Request<_trt__CreateOSD> request;
    bool ret = mpD->genOSDRequest(request,osdparm);

    if(ret == false){
        return "";
    }


    auto response = mpD->mpOnvifMediaClient->CreateOSD(request);
    if (response.IsFault()) {
        qDebug()<<response.GetCompleteFault();
        return "";
    }
    mpD->mOSDTokenList<<response.GetResultObject()->OSDToken;
    return response.GetResultObject()->OSDToken;

}
bool OnvifDevice::SetOSD(const struOSD &osdparm) {


    Request<_trt__SetOSD> request;
    bool ret = mpD->setOSDRequest(request,osdparm);
    if(ret == false){
        return false;
    }

    request.OSD->token = osdparm.token;

    auto response = mpD->mpOnvifMediaClient->SetOSD(request);
    if (response.IsFault()) {
        qDebug()<<response.GetCompleteFault();
        return false;
    }
    return true;


}
void tranformPos(float x, float y)
{
    int pox = 0;
    int poy = 0;

    // 获取分辨率
    int width = 0;
    int height = 0;
    //getsolution(&width, &height);

    // 转换为实际坐标 -> pox poy
    pox = (1.0 + x) * ((float)width) / 2.0;
    poy = (1.0 - y) * ((float)height) / 2.0;

    //onvif_debug(6, "org pos: (%.2f, %.2f) --> (%d, %d)\n", x, y, pox, poy);
}


bool OnvifDevice::DelOSD(QString OSDToken) {
    Request<_trt__DeleteOSD> request;
    request.OSDToken = OSDToken;
    auto response = mpD->mpOnvifMediaClient->DeleteOSD(request);
    if(response.IsSuccess()){
        mpD->mOSDTokenList.removeOne(OSDToken);
        return true;
    }
    return false;

}

//bool OnvifDevice::SetIPAddressFilter(){


//    Request<_tds__SetIPAddressFilter> SetIPAddressFilterRequest;
//    auto response =    mpD->mpOnvifDeviceClient->SetIPAddressFilter(SetIPAddressFilterRequest);
//    return response.IsFault();


//}
//bool OnvifDevice::SetNetworkDefaultGateway(){

//    Request<_tds__SetNetworkDefaultGateway> SetNetworkDefaultGatewayRequest;
//    auto response =    mpD->mpOnvifDeviceClient->SetNetworkDefaultGateway(SetNetworkDefaultGatewayRequest);

//    return response.IsFault();

//}
//bool OnvifDevice::SetDNS(){

//    Request<_tds__SetDNS> SetDNSRequest;
//    auto response =    mpD->mpOnvifDeviceClient->SetDNS(SetDNSRequest);
//    return response.IsFault();
//}

QString OnvifDevice::GetHostname() {
    Request<_tds__GetHostname> HostnameRequest;

    auto response = mpD->mpOnvifDeviceClient->GetHostname(HostnameRequest);
    if (response.IsFault()) {
        return "";
    }
    return *(response.GetResultObject()->HostnameInformation->Name);


}

//bool OnvifDevice::GetIPAddressFilter(){


//    Request<_tds__GetIPAddressFilter> GetIPAddressFilterRequest;
//    auto response = mpD->mpOnvifDeviceClient->GetIPAddressFilter(GetIPAddressFilterRequest);
//    return response.IsFault();


//}

//bool OnvifDevice::GetNetworkDefaultGateway(){

//    Request<_tds__GetNetworkDefaultGateway> GetNetworkDefaultGatewayRequest;
//    auto response = mpD->mpOnvifDeviceClient->GetNetworkDefaultGateway(GetNetworkDefaultGatewayRequest);

//    return response.IsFault();

//}

//bool OnvifDevice::GetDNS(){

//    Request<_tds__GetDNS> GetDNSRequest;
//    auto response = mpD->mpOnvifDeviceClient->GetDNS(GetDNSRequest);
//    return response.IsFault();
//}

bool OnvifDevice::SetNTP() {
    Request<_tds__SetNTP> request;

    auto response = mpD->mpOnvifDeviceClient->SetNTP(request);
    return response.IsFault();
}
bool OnvifDevice::GetNTP() {
    Request<_tds__GetNTP> request;
    auto response = mpD->mpOnvifDeviceClient->GetNTP(request);

    return response.IsFault();
}


bool OnvifDevice::GetSystemDateAndTime(QDateTime &dateTime) {

    Request<_tds__GetSystemDateAndTime> request;
    auto response = mpD->mpOnvifDeviceClient->GetSystemDateAndTime(request);
    auto time = response.GetResultObject()->SystemDateAndTime;
    QDate date(time->UTCDateTime->Date->Year, time->UTCDateTime->Date->Month, time->UTCDateTime->Date->Day);
    QTime qtime(time->UTCDateTime->Time->Hour, time->UTCDateTime->Time->Minute, time->UTCDateTime->Time->Second);
    dateTime.setDate(date);
    dateTime.setTime(qtime);
    return response.IsFault();
}

bool OnvifDevice::SetSystemDateAndTime(const QDateTime& dateTime) {

    Request<_tds__SetSystemDateAndTime> request;
    request.UTCDateTime->Date->Year = dateTime.date().year();
    request.UTCDateTime->Date->Month = dateTime.date().month();
    request.UTCDateTime->Date->Day = dateTime.date().day();


    request.UTCDateTime->Time->Hour = dateTime.time().hour();
    request.UTCDateTime->Time->Minute = dateTime.time().minute();
    request.UTCDateTime->Time->Second = dateTime.time().second();

    auto response = mpD->mpOnvifDeviceClient->SetSystemDateAndTime(request);

    return response.IsFault();
}
QString OnvifDevice::GetStreamUri(){
    Request<_trt__GetStreamUri> rRequest;
    rRequest.ProfileToken;
    rRequest.StreamSetup->Stream;
  auto response =   mpD->mpOnvifMediaClient->GetStreamUri(rRequest);
    return response.GetResultObject()->MediaUri->Uri;
}
bool OnvifDevice::SystemReboot() {
    Request<_tds__SystemReboot> request;

    auto response = mpD->mpOnvifDeviceClient->SystemReboot(request);
    return response.IsFault();

}
bool OnvifDevice::GotoHomePosition() {
    Request<_tptz__GotoHomePosition> rRequest;
    auto response = mpD->mpOnvifPtzClient->GotoHomePosition(rRequest);
    return response.IsFault();
}


bool OnvifDevice::SetHomePosition() {

    Request<_tptz__SetHomePosition> rRequest;

    auto response = mpD->mpOnvifPtzClient->SetHomePosition(rRequest);
    return response.IsFault();
}
bool OnvifDevice::UnicastProbe() {
    return false;
}
bool OnvifDevice::MulticastProbe() {
    auto ctxBuilder = SoapCtx::Builder();

    ctxBuilder.SetSendTimeout(1000);
    ctxBuilder.SetReceiveTimeout(1000);

    auto discovery = new OnvifDiscoveryClient(QUrl("soap.udp://239.255.255.250:3702"), ctxBuilder.Build());

    ProbeTypeRequest request;
    // request.Types = "tds:Device";
    auto uuidOne = QString("uuid:%1").arg(SoapHelper::GenerateUuid());
    auto probeResponseTwo = discovery->Probe(request, uuidOne);
    // request.Types = "tdn:NetworkVideoTransmitter";
    auto uuidTwo = QString("uuid:%1").arg(SoapHelper::GenerateUuid());
    auto probeResponseOne = discovery->Probe(request, uuidTwo);
    if (probeResponseOne && probeResponseTwo) {
        qDebug() << "Searching ONVIF devices for" << 3000 / 1000 << "seconds";
        auto foundMatches = 0;
        auto beginTs = QDateTime::currentMSecsSinceEpoch();
        while (QDateTime::currentMSecsSinceEpoch() < beginTs + 3000) {
            auto matchResp = discovery->ReceiveProbeMatches();
            if (matchResp && matchResp.GetResultObject()) {
                auto relatesTo = matchResp.GetSoapHeaderRelatesTo();
                if (!relatesTo.isNull() && (uuidOne.compare(relatesTo) == 0 || uuidTwo.compare(relatesTo) == 0)) {
                    if (auto matchs = matchResp.GetResultObject()) {
                        if (matchs->wsdd__ProbeMatches) {
                            for (auto i = 0; i < matchs->wsdd__ProbeMatches->__sizeProbeMatch; ++i) {
                                wsdd__ProbeMatchesType match = matchs->wsdd__ProbeMatches[i];
                                for (auto ii = 0; ii < match.__sizeProbeMatch; ++ii) {
                                    foundMatches++;
                                    auto probe = match.ProbeMatch[ii];
                                    qDebug() << "Found match:";
                                    qDebug() << "    Type:" << probe.Types;
                                    qDebug() << "    Endpoint:" << probe.XAddrs;
                                    if (probe.wsa5__EndpointReference.Address) {
                                        qDebug() << "     Reference:" << probe.wsa5__EndpointReference.Address;
                                    }
                                    if (probe.Scopes) {
                                        auto scopeList = QString::fromLocal8Bit(probe.Scopes->__item).split(' ');
                                        auto matchBy = QString::fromLocal8Bit(probe.Scopes->MatchBy);
                                        if (!matchBy.isEmpty()) {
                                            qDebug() << "    Match:" << matchBy;
                                        }
                                        qDebug() << "    Scope:";
                                        for (auto scope : scopeList) {
                                            if (!scope.isEmpty()) qDebug() << "        " << scope;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    qDebug() << "Skipping non related message with id:" << relatesTo;
                }
            }
        }
        qDebug() << "Found" << (foundMatches == 0 ? "no" : QString::number(foundMatches)) << (foundMatches > 1 ? "matches" : "match");
    }
    else {
        if (!probeResponseOne)
            qDebug() << probeResponseOne.GetCompleteFault();
        else
            qDebug() << probeResponseTwo.GetCompleteFault();
    }
    return true;
}
int OnvifDevicePrivate::GetVideoSourceToken(QString *token)
{

    Request<_trt__GetProfiles> request;
    auto response = this->mpOnvifMediaClient->GetProfiles(request);
    if (SOAP_OK != response.GetErrorCode())
    {
        qDebug() << "GetProfiles error.\n";
        return -1;
    }
    ///< 可能会有好几路流，相应的也会有好几个profile,这里只取第一路码流
    *token = response.GetResultObject()->Profiles[0]->VideoSourceConfiguration->token;
    qDebug() << "GetProfiles token"<<*token ;
    return 0;
}

QString OnvifDevicePrivate::GetToken(int flag) {
    Request<_trt__GetProfiles> request;
    auto response = this->mpOnvifMediaClient->GetProfiles(request);
    if (SOAP_OK != response.GetErrorCode())
    {
        qDebug() << "GetProfiles error.\n";
        return "";
    }
    ///< 可能会有好几路流，相应的也会有好几个profile,这里只取第一路码流
    if (flag == 1) {
        auto Profiles = response.GetResultObject()->Profiles;
        for(auto Profile : Profiles ){

            qDebug()<< "profile name ==>"<<Profile->Name;
            qDebug() << "GetProfiles PTZConfiguration==>"<<Profile->token;

        }
        return response.GetResultObject()->Profiles[0]->PTZConfiguration->token;
    }
    else {
        qDebug() << "GetProfiles VideoSourceConfiguration ==>"<<response.GetResultObject()->Profiles[0]->VideoSourceConfiguration->token;
        return response.GetResultObject()->Profiles[0]->VideoSourceConfiguration->token;
    }

}

bool OnvifDevicePrivate::genOSDRequest(Request<_trt__CreateOSD> &request,const struOSD &osdparm){
    if(this->mOSDTokenList.size() >= 5){
        return false;
    }
    if(osdparm.FontSize < 0){
        qDebug()<<"font size to small;";
        return false;
    }
    float *pos_x = new float;
    float *pos_y = new float;
    QString * PlainText = new QString;
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();

    int *fontSize = new int;
    *fontSize = osdparm.FontSize;
    *PlainText = osdparm.PlainText;

    request.OSD = new tt__OSDConfiguration;
    request.OSD->TextString = new tt__OSDTextConfiguration;
    request.OSD->TextString->PlainText = PlainText;
    request.OSD->TextString->FontSize = fontSize;
    request.OSD->TextString->Type = "Plain";


    request.OSD->VideoSourceConfigurationToken = new tt__OSDReference;
    request.OSD->VideoSourceConfigurationToken->__item="VideoSourceToken";

    request.OSD->Type = tt__OSDType::Text;
    request.OSD->token = strId;


    request.OSD->Position = new tt__OSDPosConfiguration;
    request.OSD->Position->Pos = new tt__Vector;
    request.OSD->Position->Type = "Custom";

    if (osdparm.PositionType == "Custom") {
        *pos_x = osdparm.x;
        *pos_y = osdparm.y;
    }
    else if (osdparm.PositionType== "UpperLeft") {
        *pos_x = -1;
        *pos_y = 1;

    }
    else if (osdparm.PositionType == "UpperRight") {
        *pos_x = 1;
        *pos_y = 1;
    }
    else if (osdparm.PositionType == "LowerLeft") {
        *pos_x = -1;
        *pos_y = -1;

    }
    else if (osdparm.PositionType == "LowerRight") {
        *pos_x = 1;
        *pos_y = -1;

    }

    request.OSD->Position->Pos->x = pos_x;
    request.OSD->Position->Pos->y = pos_y;

    return true;

}
bool OnvifDevicePrivate::setOSDRequest(Request<_trt__SetOSD> &request,const struOSD &osdparm){
    if(this->mOSDTokenList.size() >= 5){
        return false;
    }
    if(osdparm.FontSize < 0){
        qDebug()<<"font size to small;";
        return false;
    }
    float *pos_x = new float;
    float *pos_y = new float;
    QString * PlainText = new QString;

    int *fontSize = new int;
    *fontSize = osdparm.FontSize;
    *PlainText = osdparm.PlainText;

    request.OSD = new tt__OSDConfiguration;
    request.OSD->TextString = new tt__OSDTextConfiguration;
    request.OSD->TextString->PlainText = PlainText;
    request.OSD->TextString->FontSize = fontSize;
    request.OSD->TextString->Type = "Plain";


    request.OSD->VideoSourceConfigurationToken = new tt__OSDReference;
    request.OSD->VideoSourceConfigurationToken->__item="VideoSourceToken";

    request.OSD->Type = tt__OSDType::Text;



    request.OSD->Position = new tt__OSDPosConfiguration;
    request.OSD->Position->Pos = new tt__Vector;
    request.OSD->Position->Type = "Custom";

    if (osdparm.PositionType == "Custom") {
        *pos_x = osdparm.x;
        *pos_y = osdparm.y;
    }
    else if (osdparm.PositionType== "UpperLeft") {
        *pos_x = -1;
        *pos_y = 1;

    }
    else if (osdparm.PositionType == "UpperRight") {
        *pos_x = 1;
        *pos_y = 1;
    }
    else if (osdparm.PositionType == "LowerLeft") {
        *pos_x = -1;
        *pos_y = -1;

    }
    else if (osdparm.PositionType == "LowerRight") {
        *pos_x = 1;
        *pos_y = -1;

    }

    request.OSD->Position->Pos->x = pos_x;
    request.OSD->Position->Pos->y = pos_y;

    return true;

}

