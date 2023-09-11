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
#pragma once
#include "Response.h"
#include "Client.h"
#include <QObject>
#include <QUrl>


struct OnvifDevicePrivate;

class OnvifDevice : public QObject {

    Q_OBJECT
    //init
public:
    OnvifDevice(const QUrl &rDeviceEndpoint, QObject *pParent = nullptr);
    virtual ~OnvifDevice();
    void SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode = AUTO);
    SimpleResponse Initialize();
    SimpleResponse InitializeTopicSet();

private:
    OnvifDevicePrivate *mpD;
    bool isError(int errorcode);
    //interface
public:
    //probe
    bool Probe();
    //ptz
    bool RelativeMove(float x,float y,float speed);
    bool AbsoluteMove(float x,float y,float speed =1);
    bool ContinuousMove(float x,float y,float speed= 1);
    bool StopMove();
    bool ZoomIn(int x = -1);
    bool ZoomOut(int x = 1);
    bool StopZoom();
    bool FocusMove(float fSpeed);
    bool Stop();
    //preset
    bool GetPresets();
    bool SetPreset();
    bool GotoHomePosition();
    bool SetHomePosition();

    //images
   // bool SetImagingSettings(float Brightness,float Contrast,float ColorSaturation,float Sharpness);
     //bool GetImagingSettings();
    bool SetBrightness(float Brightness);
    bool SetContrast(float Contrast);
    bool SetColorSaturation(float ColorSaturation);
    bool SetSharpness(float Sharpness);
    float GetBrightness();
    float GetContrast();
    float GetColorSaturation();
    float GetSharpness();


    //host
    QString GetHostname();
    bool SetHostname(QString name);
    bool GetNTP();
    bool SetNTP();

//    bool SetIPAddressFilter();
//    bool SetNetworkDefaultGateway();
//    bool SetDNS();
//    bool GetIPAddressFilter();
//    bool GetNetworkDefaultGateway();
//    bool GetDNS();
    // OSD

    bool GetOSD();
    bool SetOSD();
    bool ModifyOSD();
    bool DelOSD();








};
