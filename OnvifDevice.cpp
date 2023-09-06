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
        mpOnvifReplayClient(nullptr) {}

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
    if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
        device->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
    }

    OnvifEventClient *onvifEvent = nullptr;

    Request<_tds__GetServices> request;
    request.IncludeCapability = false;
    auto servicesResponse = device->GetServices(request);
    if(servicesResponse) {
        for(auto service : servicesResponse.GetResultObject()->Service) {
            if(service->Namespace == OnvifAnalyticsClient::GetServiceNamespace()) {
                qDebug() << "ONVIF analytics service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifAnalyticsClient = new OnvifAnalyticsClient(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifAnalyticsClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            }
            if(service->Namespace == OnvifDeviceClient::GetServiceNamespace()) {
                qDebug() << "ONVIF device service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifDeviceClient = new OnvifDeviceClient(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifDeviceClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            } else if(service->Namespace == OnvifDisplayClient::GetServiceNamespace()) {
                qDebug() << "ONVIF display service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifDisplayClient = new OnvifDisplayClient(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifDisplayClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            } else if(service->Namespace == OnvifEventClient::GetServiceNamespace()) {
                qDebug() << "ONVIF event service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifEventClient = new OnvifEventClient(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifEventClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            } else if(service->Namespace == OnvifImagingClient::GetServiceNamespace()) {
                qDebug() << "ONVIF imaging service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifImagingClient = new OnvifImagingClient(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifImagingClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            } else if(service->Namespace == OnvifMediaClient::GetServiceNamespace()) {
                qDebug() << "ONVIF media service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifMediaClient = new OnvifMediaClient(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifMediaClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            } else if(service->Namespace == OnvifMedia2Client::GetServiceNamespace()) {
                qDebug() << "ONVIF media2 service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifMedia2Client = new OnvifMedia2Client(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifMedia2Client->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            } else if(service->Namespace == OnvifPtzClient::GetServiceNamespace()) {
                qDebug() << "ONVIF ptz service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifPtzClient = new OnvifPtzClient(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifPtzClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            } else if(service->Namespace == OnvifReceiverClient::GetServiceNamespace()) {
                qDebug() << "ONVIF receiver service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifReceiverClient = new OnvifReceiverClient(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifReceiverClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            } else if(service->Namespace == OnvifRecordingClient::GetServiceNamespace()) {
                qDebug() << "ONVIF recording service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifRecordingClient = new OnvifRecordingClient(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifRecordingClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            } else if(service->Namespace == OnvifReplayClient::GetServiceNamespace()) {
                qDebug() << "ONVIF replay service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
                auto url = QUrl(qPrintable(service->XAddr));
                url.setPort(mpD->mDeviceEndpoint.port());
                mpD->mpOnvifReplayClient = new OnvifReplayClient(url, ctx, this);
                if(!mpD->mUserName.isNull() || !mpD->mPassword.isNull()) {
                    mpD->mpOnvifReplayClient->SetAuth(mpD->mUserName, mpD->mPassword, AUTO);
                }
            } else {
                qDebug() << "Unknown service"
                         << "namespace:" << qPrintable(service->Namespace) << "Url:" << qPrintable(service->XAddr);
            }
        }
    } else {
        qWarning() << "Couldn't receive response: " << servicesResponse.GetCompleteFault();
    }

    /*
    Request<_tds__GetCapabilities> r;
    auto res = device->GetCapabilities(r);
    if(auto rr = res.GetResultObject()) {
     auto capa = res.GetResultObject()->Capabilities;
     if(capa->Device) {
      //	TODO: Print
     }
    }*/

    InitializeTopicSet();

    Request<_tds__GetEndpointReference> endpointRefRequest;
    auto endpointRefResponse = mpD->mpOnvifDeviceClient->GetEndpointReference(endpointRefRequest);
    if(endpointRefResponse) {
        if(auto endpointRef = endpointRefResponse.GetResultObject()) {

        } else {
            qWarning() << "Couldn't extract the device endpoint reference";
        }
    } else {
        qWarning() << endpointRefResponse;
    }

    return SimpleResponse();
}

SimpleResponse OnvifDevice::InitializeTopicSet() {

    if(mpD->mpOnvifEventClient) {
        Request<_tev__GetEventProperties> request;
        auto response = mpD->mpOnvifEventClient->GetParsedEventProperties(request);
        if(response) {
            for(auto topic : response.GetResultObject().GetTopics()) {
                auto topicPath = topic.GetTopicPath().join("/");
                if(topicPath.isEmpty()) topicPath.append("/");
                qDebug() << "\nTopic name" << topic.GetName();
                qDebug() << "Topic path" << topicPath;
                for(auto item : topic.GetItems()) {
                    if(item.GetPrimitiveType() == SimpleItemInfo::PRIMITIVE_UNKNOWN) {
                        qDebug() << "    Unknown Item" << item.GetName() << "type" << item.GetSoapTypeQname();
                    } else {
                        QString primitive;
                        switch(item.GetPrimitiveType()) {
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
        } else {
            qWarning() << "Couldn't get event properties" << response.GetCompleteFault();
        }
    }
    return SimpleResponse();
}

void OnvifDevice::SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode /*= AUTO*/) {

    mpD->mUserName = rUserName;
    mpD->mPassword = rPassword;
}

bool OnvifDevice::isError(int errorcode){
    if(errorcode != SOAP_OK){
        return false;
    }
    return true;
}
bool OnvifDevice::AbsoluteMove(float x,float y,float speed){

    Request<_tptz__AbsoluteMove> rRequest;
    QString ProfileToken;


    rRequest.Position->PanTilt->x = x;
    rRequest.Position->PanTilt->y = y;

    auto response = mpD->mpOnvifPtzClient->AbsoluteMove(rRequest);

    return isError(response.GetErrorCode());

}
bool OnvifDevice::ContinuousMove(float x,float y,float speed){
    Request<_tptz__ContinuousMove> rRequest;
    QString ProfileToken;
    rRequest.ProfileToken = ProfileToken;
    rRequest.Velocity->PanTilt->x = x;
    rRequest.Velocity->PanTilt->y = y;
    auto response = mpD->mpOnvifPtzClient->ContinuousMove(rRequest);
    return isError(response.GetErrorCode());
}

bool OnvifDevice::RelativeMove(float x,float y,float speed){
    Request<_tptz__RelativeMove> rRequest;
    QString ProfileToken;
    rRequest.ProfileToken = ProfileToken;
    rRequest.Speed->PanTilt->x = x;
    rRequest.Speed->PanTilt->y = y;

    auto response = mpD->mpOnvifPtzClient->RelativeMove(rRequest);
    return isError(response.GetErrorCode());
}

bool OnvifDevice::Zoom(int x){
    Request<_tptz__ContinuousMove> rRequest;
    QString ProfileToken;
    rRequest.ProfileToken = ProfileToken;
    rRequest.Velocity->Zoom->x = x;
    auto response = mpD->mpOnvifPtzClient->ContinuousMove(rRequest);
    return isError(response.GetErrorCode());
}



bool OnvifDevice::FocusMove(float fSpeed){

    Request<_timg__Move> rRequest;
    QString ProfileToken;
    rRequest.Focus->Continuous->Speed = fSpeed;
    rRequest.Focus->Absolute = nullptr;
    rRequest.Focus->Relative = nullptr;
    rRequest.VideoSourceToken = ProfileToken;
    auto response = mpD->mpOnvifImagingClient->Move(rRequest);

    return isError(response.GetErrorCode());
}
bool OnvifDevice::Stop(){
    Request<_tptz__Stop> rRequest;
    QString ProfileToken;
    rRequest.ProfileToken = ProfileToken;
    auto response = mpD->mpOnvifPtzClient->Stop(rRequest);
    return isError(response.GetErrorCode());
}
bool OnvifDevice::GetPresets(){
    Request<_tptz__GetPresets> rRequest;
    QString ProfileToken;
    rRequest.ProfileToken = ProfileToken;
    auto response = mpD->mpOnvifPtzClient->GetPresets(rRequest);
    return isError(response.GetErrorCode());
}

bool OnvifDevice::SetPreset(){
    Request<_tptz__SetPreset> rRequest;
    QString ProfileToken;
    rRequest.ProfileToken = ProfileToken;
    auto response = mpD->mpOnvifPtzClient->SetPreset(rRequest);
    return isError(response.GetErrorCode());
}


bool OnvifDevice::SetImagingSettings(){


    Request<_timg__SetImagingSettings> rRequest;
    QString ProfileToken;
    rRequest.VideoSourceToken = ProfileToken;

    auto response = mpD->mpOnvifImagingClient->SetImagingSettings(rRequest);
    return isError(response.GetErrorCode());

}
bool OnvifDevice::GetImagingSettings(){


    Request<_timg__GetImagingSettings> rRequest;
    QString ProfileToken;
    rRequest.VideoSourceToken = ProfileToken;
    auto response = mpD->mpOnvifImagingClient->GetImagingSettings(rRequest);
    return isError(response.GetErrorCode());

}
bool OnvifDevice::SetHostname(){
    Request<_tds__SetHostname> HostnameRequest;
    auto response =    mpD->mpOnvifDeviceClient->SetHostname(HostnameRequest);
    return isError(response.GetErrorCode());


}
bool OnvifDevice::SetIPAddressFilter(){


    Request<_tds__SetIPAddressFilter> SetIPAddressFilterRequest;
    auto response =    mpD->mpOnvifDeviceClient->SetIPAddressFilter(SetIPAddressFilterRequest);
    return isError(response.GetErrorCode());


}
bool OnvifDevice::SetNetworkDefaultGateway(){

    Request<_tds__SetNetworkDefaultGateway> SetNetworkDefaultGatewayRequest;
    auto response =    mpD->mpOnvifDeviceClient->SetNetworkDefaultGateway(SetNetworkDefaultGatewayRequest);

    return isError(response.GetErrorCode());

}
bool OnvifDevice::SetDNS(){

    Request<_tds__SetDNS> SetDNSRequest;
    auto response =    mpD->mpOnvifDeviceClient->SetDNS(SetDNSRequest);
    return isError(response.GetErrorCode());
}

bool OnvifDevice::GetHostname(){
    Request<_tds__GetHostname> HostnameRequest;

    auto response = mpD->mpOnvifDeviceClient->GetHostname(HostnameRequest);
    return isError(response.GetErrorCode());

}

bool OnvifDevice::GetIPAddressFilter(){


    Request<_tds__GetIPAddressFilter> GetIPAddressFilterRequest;
    auto response = mpD->mpOnvifDeviceClient->GetIPAddressFilter(GetIPAddressFilterRequest);
    return isError(response.GetErrorCode());


}

bool OnvifDevice::GetNetworkDefaultGateway(){

    Request<_tds__GetNetworkDefaultGateway> GetNetworkDefaultGatewayRequest;
    auto response = mpD->mpOnvifDeviceClient->GetNetworkDefaultGateway(GetNetworkDefaultGatewayRequest);

    return isError(response.GetErrorCode());

}

bool OnvifDevice::GetDNS(){

    Request<_tds__GetDNS> GetDNSRequest;
    auto response = mpD->mpOnvifDeviceClient->GetDNS(GetDNSRequest);
    return isError(response.GetErrorCode());
}

bool OnvifDevice::SetNTP(){
    Request<_tds__SetNTP> request;

    auto response = mpD->mpOnvifDeviceClient->SetNTP(request);
    return isError(response.GetErrorCode());
}
bool OnvifDevice::GetNTP(){
    Request<_tds__GetNTP> request;

    auto response = mpD->mpOnvifDeviceClient->GetNTP(request);
    return isError(response.GetErrorCode());
}

bool OnvifDevice::GotoHomePosition(){
    Request<_tptz__GotoHomePosition> rRequest;
    auto response = mpD->mpOnvifPtzClient->GotoHomePosition(rRequest);
    return isError(response.GetErrorCode());
}


bool OnvifDevice::SetHomePosition(){

    Request<_tptz__SetHomePosition> rRequest;

    auto response = mpD->mpOnvifPtzClient->SetHomePosition(rRequest);
    return isError(response.GetErrorCode());
}

bool OnvifDevice::Probe(){
    auto ctxBuilder = SoapCtx::Builder();

    ctxBuilder.SetSendTimeout(1000);
    ctxBuilder.SetReceiveTimeout(1000);

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
    return true;
}
