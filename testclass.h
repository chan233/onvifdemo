#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>
#include <QtTest/QtTest>
#include "OnvifDevice.h"
class TestClass : public QObject
{
    Q_OBJECT
public:
    TestClass();
private:
    OnvifDevice *testObject = nullptr;

private slots:


    void initTestCase();//在第一个测试函数执行前调用。
    void cleanupTestCase();//在最后一个测试函数执行后调用。

    //    void init(); //在每一个测试函数执行前调用。
    //    void cleanup();//在每一个测试函数执行后调用

    void testGetPTZToken();

    void testGetVideSourceToken();
    void testContinuousMove();
    void testStopMove();
    void testZoomIn();

    void testZoomOut();
    void testStopZoom();
    void testFocusMove();
    void testStop();

    void testGetStreamUri();
    //    void testRelativeMove();
    //    void testAbsoluteMove();

    //images

    void testSetBrightness();
    void testSetContrast();
    void testSetColorSaturation();
    void testSetSharpness();
    void testGetBrightness();
    void testGetContrast();
    void testGetColorSaturation();
    void testGetSharpness();


    //preset
    void testGetPresets();
    void testSetPreset();
    // OSD
    void testGetOSDs();
    void testCreateOSD();
    void testSetOSD();
    void testDelOSD();



};

#endif // TESTCLASS_H
