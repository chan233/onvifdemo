#include "testclass.h"

TestClass::TestClass()
{

}



void TestClass::cleanupTestCase(){
    delete testObject;
    testObject  = nullptr;
}
void TestClass::initTestCase(){
    qDebug()<<"start testing...";
    QString name("admin");
    QString passwd("glhr12345");
    QString addresss("192.168.1.84");

    auto devices = OnvifDevice::MulticastProbe(addresss);
    QVERIFY(devices.size() == 1);
    QVERIFY(devices.at(0).indexOf(addresss));
    testObject = new OnvifDevice(QUrl(devices.at(0)));
    testObject->SetAuth(name,passwd);
    auto res = testObject->Initialize(3000);
    QVERIFY(res.IsSuccess());

}

void TestClass::testGetPTZToken(){
    QString token;
    bool ret = testObject->GetPTZToken(token);
    QVERIFY(ret == false);

    testObject->GetAllProfiles();
    testObject->SetTokenIndex(0);

    ret = testObject->GetPTZToken(token);
    QVERIFY(ret == true);

    testObject->SetTokenIndex(99999);
    ret = testObject->GetPTZToken(token);
    QVERIFY(ret == false);

}

void TestClass::testGetVideSourceToken(){



    QString token;
    bool ret = testObject->GetVideSourceToken(token);
    QVERIFY(ret == false);

    testObject->GetAllVideoSource();
    testObject->SetVideoSourceTokenIndex(0);

    ret = testObject->GetVideSourceToken(token);
    QVERIFY(ret == true);

    testObject->SetVideoSourceTokenIndex(99999);
    ret = testObject->GetVideSourceToken(token);
    QVERIFY(ret == false);

}

void TestClass::testContinuousMove(){


    QVERIFY(testObject != nullptr);



    testObject->SetTokenIndex(9999);
    bool ret = testObject->ContinuousMove(1,1);
    QVERIFY(ret == false);

    testObject->SetTokenIndex(-9999);
    ret = testObject->ContinuousMove(1,1);
    QVERIFY(ret == false);

    testObject->SetTokenIndex(0);
    ret = testObject->ContinuousMove(1,1);
    QVERIFY(ret == true);

    ret = testObject->ContinuousMove(1,0);
    QVERIFY(ret == true);
    ret = testObject->ContinuousMove(1,-1);
    QVERIFY(ret == true);
    ret = testObject->ContinuousMove(-1,1);
    QVERIFY(ret == true);
    ret = testObject->ContinuousMove(-1,0);
    QVERIFY(ret == true);
    ret = testObject->ContinuousMove(-1,-1);
    QVERIFY(ret == true);
    ret = testObject->ContinuousMove(0,1);
    QVERIFY(ret == true);
    ret = testObject->ContinuousMove(0,0);
    QVERIFY(ret == true);
    ret = testObject->ContinuousMove(0,-1);
    QVERIFY(ret == true);


    ret = testObject->ContinuousMove(2,-1);
    QVERIFY(ret == false);
    ret = testObject->ContinuousMove(0,9999);
    QVERIFY(ret == false);
    ret = testObject->ContinuousMove(-9999,-9999);
    QVERIFY(ret == false);
    ret = testObject->ContinuousMove(9999,9999);
    QVERIFY(ret == false);






}



void TestClass::testStopMove(){
    bool ret = testObject->StopMove();
    QVERIFY(ret == true);
}

void  TestClass::testZoomIn(){
    bool ret = testObject->ZoomIn();
    QVERIFY(ret == true);

    ret = testObject->ZoomIn(9999);
    QVERIFY(ret == false);
    ret = testObject->ZoomIn(-9999);
    QVERIFY(ret == false);
}

void TestClass::testZoomOut(){
    bool ret = testObject->ZoomOut();
    QVERIFY(ret == true);

    ret = testObject->ZoomOut(9999);
    QVERIFY(ret == false);
    ret = testObject->ZoomOut(-9999);
    QVERIFY(ret == false);
}
void TestClass::testStopZoom(){

    bool ret = testObject->StopZoom();

    QVERIFY(ret == true);
}
void TestClass::testFocusMove(){



    testObject->SetVideoSourceTokenIndex(9999);
    bool ret = testObject->FocusMove(1);
    QVERIFY(ret == false);


    testObject->SetVideoSourceTokenIndex(-9999);
    ret = testObject->FocusMove(1);
    QVERIFY(ret == false);

    testObject->SetVideoSourceTokenIndex(0);
    ret = testObject->FocusMove(1);
    QVERIFY(ret == true);



    ret = testObject->FocusMove(0);
    QVERIFY(ret == true);


    ret = testObject->FocusMove(-1);
    QVERIFY(ret == true);


    ret = testObject->FocusMove(9999);
    QVERIFY(ret == false);



    ret = testObject->FocusMove(-9999);
    QVERIFY(ret == false);
}
void TestClass::testStop(){

    bool ret = testObject->Stop();
    QVERIFY(ret == true);
}

void TestClass::testSetBrightness(){

    testObject->SetVideoSourceTokenIndex(9999);
    bool ret = testObject->SetBrightness(1);
    QVERIFY(ret == false);

    testObject->SetVideoSourceTokenIndex(-9999);
    ret = testObject->SetBrightness(1);
    QVERIFY(ret == false);

    testObject->SetVideoSourceTokenIndex(0);
    ret = testObject->SetBrightness(1);
    QVERIFY(ret == true);


    ret = testObject->SetBrightness(-9999);
    QVERIFY(ret == false);
    ret = testObject->SetBrightness(9999);
    QVERIFY(ret == false);
    ret = testObject->SetBrightness(50);
    QVERIFY(ret == true);

}
void TestClass::testSetContrast(){
    testObject->SetVideoSourceTokenIndex(9999);
    bool ret = testObject->SetContrast(1);
    QVERIFY(ret == false);

    testObject->SetVideoSourceTokenIndex(-9999);
    ret = testObject->SetContrast(1);
    QVERIFY(ret == false);

    testObject->SetVideoSourceTokenIndex(0);
    ret = testObject->SetContrast(1);
    QVERIFY(ret == true);


    ret = testObject->SetContrast(-9999);
    QVERIFY(ret == false);
    ret = testObject->SetContrast(9999);
    QVERIFY(ret == false);
    ret = testObject->SetContrast(50);
    QVERIFY(ret == true);


}
void TestClass::testSetColorSaturation(){
    testObject->SetVideoSourceTokenIndex(9999);
    bool ret = testObject->SetColorSaturation(1);
    QVERIFY(ret == false);

    testObject->SetVideoSourceTokenIndex(-9999);
    ret = testObject->SetColorSaturation(1);
    QVERIFY(ret == false);

    testObject->SetVideoSourceTokenIndex(0);
    ret = testObject->SetColorSaturation(1);
    QVERIFY(ret == true);


    ret = testObject->SetColorSaturation(-9999);
    QVERIFY(ret == false);
    ret = testObject->SetColorSaturation(9999);
    QVERIFY(ret == false);
    ret = testObject->SetColorSaturation(50);
    QVERIFY(ret == true);

}
void TestClass::testSetSharpness(){
    testObject->SetVideoSourceTokenIndex(9999);
    bool ret = testObject->SetSharpness(1);
    QVERIFY(ret == false);

    testObject->SetVideoSourceTokenIndex(-9999);
    ret = testObject->SetSharpness(1);
    QVERIFY(ret == false);

    testObject->SetVideoSourceTokenIndex(0);
    ret = testObject->SetSharpness(1);
    QVERIFY(ret == true);


    ret = testObject->SetSharpness(-9999);
    QVERIFY(ret == false);
    ret = testObject->SetSharpness(9999);
    QVERIFY(ret == false);
    ret = testObject->SetSharpness(50);
    QVERIFY(ret == true);
}
void TestClass::testGetBrightness(){
    float ret = testObject->GetBrightness();
    QVERIFY(ret != 0);
}
void TestClass::testGetContrast(){
    float ret = testObject->GetContrast();
    QVERIFY(ret != 0);
}
void TestClass::testGetColorSaturation(){
    float ret = testObject->GetColorSaturation();
    QVERIFY(ret != 0);
}
void TestClass::testGetSharpness(){
    float ret = testObject->GetSharpness();
    QVERIFY(ret != 0);
}

void TestClass::testGetStreamUri(){
    QString address;
    testObject->SetTokenIndex(0);
    bool ret = testObject->GetStreamUri(address);
    QVERIFY(ret == true);

    testObject->SetTokenIndex(9999);
    ret = testObject->GetStreamUri(address);
    QVERIFY(ret == false);

    testObject->SetTokenIndex(-9999);
    ret = testObject->GetStreamUri(address);
    QVERIFY(ret == false);
}

//preset
void TestClass::testGetPresets(){

    QVector<Preset> p;
    testObject->SetTokenIndex(0);
    bool ret = testObject->GetPresets(p);
    QVERIFY(ret == true);

    testObject->SetTokenIndex(9999);
    ret = testObject->GetPresets(p);
    QVERIFY(ret == false);

    testObject->SetTokenIndex(-9999);
    ret = testObject->GetPresets(p);
    QVERIFY(ret == false);


}
void TestClass::testSetPreset(){

    QString result;
    testObject->SetTokenIndex(0);
    bool ret = testObject->SetPreset(result);
    QVERIFY(ret == true);

    ret = testObject->RemovePreset(result);
    QVERIFY(ret == true);


    testObject->SetTokenIndex(9999);
    ret = testObject->SetPreset(result);
    QVERIFY(ret == false);

    testObject->SetTokenIndex(-9999);
    ret = testObject->SetPreset(result);
    QVERIFY(ret == false);

}

void TestClass::testGetOSDs(){

    QVector<struOSD> OSDs;
    bool ret = testObject->GetOSDs(OSDs);
    QVERIFY(ret == true);

}
void TestClass::testCreateOSD(){}
void TestClass::testSetOSD(){}
void TestClass::testDelOSD(){}





