#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SLABCP2112.h"
#include <string>
////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define VID									0x10C4
#define PID									0xEA90

// GPIO ComboBox Selections
#define GPIO_INPUT_OPEN_DRAIN				0
#define GPIO_OUTPUT_OPEN_DRAIN				1
#define GPIO_OUTPUT_PUSH_PULL				2
#define GPIO_SPECIAL_PUSH_PULL				3

#define GPIO_OUTPUT_START					GPIO_OUTPUT_OPEN_DRAIN
#define GPIO_PUSH_PULL_START				GPIO_OUTPUT_PUSH_PULL

#define HID_SMBUS_MASK_GPIO(i)				(1<<i)
using namespace std;
class MainWindow
{

    HID_SMBUS_DEVICE		m_hidSmbus;
public:
    MainWindow();
    ~MainWindow();
    void UpdateDeviceList();
    void connected(bool connected);
    BOOL GetSelectedDevice(string& serial);
    BOOL FindDevice(string serial, DWORD* deviceNum);
    BOOL Connect(DWORD	deviceNum);
    BOOL Disconnect(HID_SMBUS_DEVICE m_hidSmbus);
    void EnableDeviceCtrls(BOOL enable);
    void UpdateDeviceInformation(bool connected);
    void SetFromDevice();
    void SetDefaults();

    // Update control values
    void GetSmbusConfig(bool smBusConfig);
    void GetTimeouts(bool timeOut);
    void GetGpioConfig(bool gpioConfig);
    void ReadLatch(bool latchValue);
    void GetUsbConfig(bool usbConfig);
    void GetLock(bool lock);
    void GetManufacturer(bool manufacture);
    void GetProduct(bool product);
    void GetSerial(bool serial);
    BOOL ValidateConfiguration();
    void initGPIOConfig();
    void SetPinDirection(BYTE direction,BYTE mode,BYTE function);
    void UpdateClkFrequency(int clkDiv);

    void on_btConnect_clicked();

    void on_btReset_clicked();

    void on_cbDeviceList_currentTextChanged(const string &arg1);

    void on_cbDeviceList_currentIndexChanged(int index);

    void on_pbGetConfig_clicked();

    void on_pbSetConfig_clicked();

    void on_pbGetTimeout_clicked();

    void on_pbSetTimeout_clicked();

    void on_pbGetGPIOConfig_clicked();

    void on_pbSetGPIOConfig_clicked();

    void on_pbReadLatch_clicked();

    void on_pbWriteLatch_clicked();

private:
};
#endif // MAINWINDOW_H
