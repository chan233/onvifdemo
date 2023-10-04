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

#include "OnvifDeviceExport.h"
typedef  struct struOSD {
	QString token;
	QString PlainText;
	QString PositionType;
	float x;
	float y;
	int FontSize;
}struOSD;
struct OnvifDevicePrivate;

class  __declspec(dllexport) OnvifDevice : public QObject {

	//Q_OBJECT
		//init

public:
	OnvifDevice(const QUrl &rDeviceEndpoint, QObject *pParent = nullptr);
	virtual ~OnvifDevice();
	void SetAuth(const QString &rUserName, const QString &rPassword, AuthMode mode = AUTO);
	SimpleResponse Initialize();
	SimpleResponse InitializeTopicSet();

private:
	OnvifDevicePrivate *mpD;


	//interface
public:
	//probe
	bool MulticastProbe();
	bool UnicastProbe();
	//ptz
	bool RelativeMove(float x, float y, float speed);
	bool AbsoluteMove(float x, float y, float speed = 1);
	bool ContinuousMove(float x, float y, float speed = 1);
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
	bool GetSystemDateAndTime(QDateTime &dateTime);
	bool SetSystemDateAndTime(const QDateTime& dateTime);
	bool SystemReboot();
	//    bool SetIPAddressFilter();
	//    bool SetNetworkDefaultGateway();
	//    bool SetDNS();
	//    bool GetIPAddressFilter();
	//    bool GetNetworkDefaultGateway();
	//    bool GetDNS();

	// OSD
	bool  GetOSDs(QVector<struOSD>& osds);
	QString CreateOSD(const struOSD &osdparm);       // 创建OSD，成功后会返回设备上标识的OSD token
	bool SetOSD(const struOSD &osdparm);          //设置OSD。与CreateOSD基本一样，但该命令使用的是相机已经存在的OSDtoken
	bool DelOSD(QString OSDToken);
private:



};
