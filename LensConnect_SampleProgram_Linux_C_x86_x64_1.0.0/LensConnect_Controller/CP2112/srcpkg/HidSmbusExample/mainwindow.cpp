#include "mainwindow.h"
#include "Utilities.h"
#include <list>
#include <limits.h>
#include <stdio.h>
DWORD  numDevices;
list<HID_SMBUS_DEVICE> deviceList;
MainWindow::MainWindow()
{
    UpdateDeviceList();
}

MainWindow::~MainWindow()
{
    list<HID_SMBUS_DEVICE>::iterator it;
    for (it = deviceList.begin(); it != deviceList.end(); ++it)
    {
        Disconnect(*it);
    }
    deviceList.clear();
}

// Populate the device list combobox with connected device serial strings
// - Save previous device serial string selection
// - Fill the device list with connected device serial strings
// - Restore previous device selection

void MainWindow::UpdateDeviceList()
{

    DWORD				i;
    string				selText;

    // Get current device selection
    // Reset the device list
    deviceList.clear();
    HidSmbus_GetNumDevices(&numDevices, VID, PID);
    if(numDevices<=0){
        printf("No device connected. \n");
        return;
    }
    // Display connected HID SMBus device serial strings in the combo box
    for (i = 0; i < numDevices; i++)
    {
        printf("Device %d Information: \n", i);
        Connect(i);
    }
}

// Retrieve device information strings and display on the dialog
void MainWindow::UpdateDeviceInformation(bool connected)
{
    BOOL					opened;
    HID_SMBUS_DEVICE_STR	deviceString;
    WORD					vid;
    WORD					pid;
    WORD					releaseNumber;
    BYTE					partNumber;
    BYTE					version;

    char devicePathString[PATH_MAX];
    string				vidString;
    string				pidString;
    string				releaseNumberString;
    string				partNumberString;
    string				versionString;
    string				serialString;
    string				pathString;
    string				manufacturerString;
    string				productString;

    // If we're already connected to the device, then we can call the
    // opened version of the device information functions
    if (connected == TRUE &&
        HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS &&
        opened == TRUE)
    {
        // Update device information (opened)

        if (HidSmbus_GetOpenedAttributes(m_hidSmbus, &vid, &pid, &releaseNumber) == HID_SMBUS_SUCCESS)
        {
            printf("VID = 0x%04X \n",vid);
            printf("PID = 0x%04X \n",pid);
            printf("Release Number = %X.%02X \n", (UINT)(releaseNumber >> 8), (UINT)((BYTE)releaseNumber));
        }
        if (HidSmbus_GetPartNumber(m_hidSmbus, &partNumber, &version) == HID_SMBUS_SUCCESS)
        {
            printf("Part Number = %d \n",partNumber);
            printf("Version = %d \n",version);
        }
        if (HidSmbus_GetOpenedString(m_hidSmbus, deviceString, HID_SMBUS_GET_SERIAL_STR) == HID_SMBUS_SUCCESS)
        {
            printf("Serial = %s \n",deviceString);
        }
        if (HidSmbus_GetOpenedString(m_hidSmbus, devicePathString, HID_SMBUS_GET_PATH_STR) == HID_SMBUS_SUCCESS)
        {
            printf("Device Path = %s \n",devicePathString);
        }
        if (HidSmbus_GetOpenedString(m_hidSmbus, deviceString, HID_SMBUS_GET_MANUFACTURER_STR) == HID_SMBUS_SUCCESS)
        {
            printf("Manufacturer = %s \n",deviceString);
        }
        if (HidSmbus_GetOpenedString(m_hidSmbus, deviceString, HID_SMBUS_GET_PRODUCT_STR) == HID_SMBUS_SUCCESS)
        {
            printf("Product = %s \n",deviceString);
        }
    }
}

// Search for an HID device with a matching device serial string
// If the device was found return TRUE and return the device number
// in deviceNumber
// Otherwise return FALSE

BOOL MainWindow::FindDevice(string serial, DWORD* deviceNum)
{
    BOOL					found			= FALSE;

    HID_SMBUS_DEVICE_STR	deviceString;

    if (HidSmbus_GetNumDevices(&numDevices, VID, PID) == HID_SMBUS_SUCCESS)
    {
        DWORD i;
        for (i = 0; i < numDevices; i++)
        {
            if (HidSmbus_GetString(i, VID, PID, deviceString, HID_SMBUS_GET_SERIAL_STR) == HID_SMBUS_SUCCESS)
            {
                if(serial.compare(deviceString)==0)
                {
                    found		= TRUE;
                    *deviceNum	= i;
                    break;
                }
            }
        }
    }

    return found;
}

// Connect to the device with the serial string selected
// in the device list
// - Connect to the device specified in the device list
// - Update the device information text boxes
// - Set Connect button caption
// - Enable/disable device combobox
BOOL MainWindow::Connect(DWORD	deviceNum)
{
    BOOL		connected = FALSE;
    string     serial;
    HID_SMBUS_STATUS status = HidSmbus_Open(&m_hidSmbus, deviceNum, VID, PID);

    printf("HidSmbus_Open(): %s \n" ,HidSmbus_DecodeErrorStatus(status));
    // Attempt to open the device
    if (status == HID_SMBUS_SUCCESS)
    {
        connected = TRUE;
        deviceList.push_back(m_hidSmbus);
    }
    else
    {
        printf("Connection Error: %s \n" ,HidSmbus_DecodeErrorStatus(status));
    }

    // Update the device information now that we are connected to it
    // (this will give us the part number and version if connected)
    UpdateDeviceInformation(true);
    // Update all device settings for all tabs
    SetFromDevice();

    return connected;
}

// Disconnect from the currently connected device
// - Disconnect from the current device
// - Output any error messages
// - Display "Not Connected" in the status bar
// - Update the device information text boxes (clear text)
// - Set Connect button caption
// - Enable/disable device combobox
BOOL MainWindow::Disconnect(HID_SMBUS_DEVICE m_hidSmbus)
{
    bool disconnected = false;

    // Disconnect from the current device
    HID_SMBUS_STATUS status = HidSmbus_Close(m_hidSmbus);
    m_hidSmbus = NULL;

    printf("==================== HidSmbus_Close(): %s \n",HidSmbus_DecodeErrorStatus(status));
    // Output an error message if the close failed
    if (status != HID_SMBUS_SUCCESS)
    {
        printf("Connection Error: %s \n" ,HidSmbus_DecodeErrorStatus(status));
    }
    else
    {
        disconnected = TRUE;
    }
    return disconnected;
}


// Set control values by getting the device configuration
void MainWindow::SetFromDevice()
{
    // Update control values
    GetSmbusConfig(false);
    GetTimeouts(false);
    GetGpioConfig(false);
    ReadLatch(false);
    GetUsbConfig(false);
    GetLock(false);
    GetManufacturer(false);
    GetProduct(false);
    GetSerial(false);
}

// Update control values
DWORD    bitRate;
void MainWindow::GetSmbusConfig(bool silent)
{
    BOOL opened;

    // Make sure that the device is opened
    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        BOOL    sclLowTimeout;
        BOOL    autoRespond;
        BYTE	ackAddress;
        WORD	writeTimeout;
        WORD	readTimeout;
        WORD	transferRetries;

        // Get the SMBus configuration
        HID_SMBUS_STATUS status = HidSmbus_GetSmbusConfig(m_hidSmbus, &bitRate, &ackAddress, &autoRespond, &writeTimeout, &readTimeout, &sclLowTimeout, &transferRetries);
        if (status == HID_SMBUS_SUCCESS)
        {
            printf("Bit Rate = %d Hz \n", bitRate);
            printf("Slave Address = %02X \n",ackAddress);
            printf("Auto Send Read Response = %s \n",autoRespond==true? "true":"false");
            printf("Write Timeout = %d ms \n", writeTimeout);
            printf("Read Timeout = %d ms \n", readTimeout);
            printf("Transfer Retries = %d \n", transferRetries);
            printf("SCL Low Timeout = %s \n",sclLowTimeout==true? "true":"false");
        }

        if (!silent)
        {
            // Output status to status bar
            // And play an audible alert if the status is not HID_SMBUS_SUCCESS
            printf("==================== HidSmbus_GetSmbusConfig():%s \n",HidSmbus_DecodeErrorStatus(status));
        }
    }
};
DWORD responseTimeout;
void MainWindow::GetTimeouts(bool silent)
{
    BOOL opened;

    // Make sure that the device is opened
    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        // Get response timeouts
        HID_SMBUS_STATUS status = HidSmbus_GetTimeouts(m_hidSmbus, &responseTimeout);

        if (status == HID_SMBUS_SUCCESS)
        {
            printf("Response Timeout = %d ms \n", responseTimeout);
        }

        if (!silent)
        {
            // Output status to status bar
            // And play an audible alert if the status is not HID_SMBUS_SUCCESS
            printf("==================== HidSmbus_GetTimeouts():%s \n",HidSmbus_DecodeErrorStatus(status));
        }
    }
};
void MainWindow::GetGpioConfig(bool silent)
{
    BOOL opened;

    // Make sure that the device is opened
    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        BYTE direction;
        BYTE mode;
        BYTE function;
        BYTE clkDiv;

        // Get GPIO direction, mode, and function bitmasks
        HID_SMBUS_STATUS status = HidSmbus_GetGpioConfig(m_hidSmbus, &direction, &mode, &function, &clkDiv);

        if (status == HID_SMBUS_SUCCESS)
        {
            // Update controls to reflect direction, mode, and function bitmasks
            SetPinDirection(direction, mode,function);

            // Update clock divider and frequency controls
            printf("Clock Out Divider = %d \n", clkDiv);
            UpdateClkFrequency(clkDiv);
        }

        if (!silent)
        {
            // Output status to status bar
            // And play an audible alert if the status is not HID_SMBUS_SUCCESS
            printf("==================== HidSmbus_GetGpioConfig():%s \n",HidSmbus_DecodeErrorStatus(status));
        }
    }
};


// Convert the clock output frequency using the clock output divider
// Clock Frequency = 48000000 / (2 x clkDiv)
// If clkDiv = 0, then Clock Frequency = 48000000
void MainWindow::UpdateClkFrequency(int clkDiv)
{
    //int clkDiv = [m_textClkDiv intValue];
    if (clkDiv == 0)
    {
        printf("Clock Out Divider = 48000000 \n");
    }
    else if (clkDiv >= 0 && clkDiv <= 255)
    {
        int clkFreq = 48000000 / (2 * clkDiv);
        printf("Clock Out Divider = %d \n",clkFreq);
    }
    else
    {
        printf("Clock Out Divider = Invalid \n");
    }
}

// Update the GPIO combobox selections based on the direction, mode, and function bitmasks
void MainWindow::SetPinDirection(BYTE direction,BYTE mode,BYTE function)
{
    int gpioSel[8] = {
        GPIO_INPUT_OPEN_DRAIN,
        GPIO_INPUT_OPEN_DRAIN,
        GPIO_INPUT_OPEN_DRAIN,
        GPIO_INPUT_OPEN_DRAIN,
        GPIO_INPUT_OPEN_DRAIN,
        GPIO_INPUT_OPEN_DRAIN,
        GPIO_INPUT_OPEN_DRAIN,
        GPIO_INPUT_OPEN_DRAIN
    };
    for(int i=0; i<=7; i++){
        if((i==0) && (function & HID_SMBUS_MASK_FUNCTION_GPIO_0_TXT)){
            gpioSel[i] = GPIO_SPECIAL_PUSH_PULL;
        }else if((i==1) && (function & HID_SMBUS_MASK_FUNCTION_GPIO_1_RXT)){
            gpioSel[i] = GPIO_SPECIAL_PUSH_PULL;
        }else if((i==7) && (function & HID_SMBUS_MASK_FUNCTION_GPIO_7_CLK)){
            gpioSel[i] = GPIO_SPECIAL_PUSH_PULL;
        }else{
            if ((direction & HID_SMBUS_MASK_GPIO(i)) && (mode & HID_SMBUS_MASK_GPIO(i)))		gpioSel[i] = GPIO_OUTPUT_PUSH_PULL;
            else if ((direction & HID_SMBUS_MASK_GPIO(i)) && !(mode & HID_SMBUS_MASK_GPIO(i)))	gpioSel[i] = GPIO_OUTPUT_OPEN_DRAIN;
        }
        printf("GPIO%dMode = %s \n",i,HidSmbus_DecodeGPIOStatus(gpioSel[i]));
    }
}

void MainWindow::ReadLatch(bool silent){
    BOOL opened;

    // Make sure that the device is opened
    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        BYTE latchValue;

        // Read GPIO latch value
        HID_SMBUS_STATUS status = HidSmbus_ReadLatch(m_hidSmbus, &latchValue);

        if (status == HID_SMBUS_SUCCESS)
        {
            // Update controls to reflect latch value
            printf("LatchValue = 0x%02X \n",latchValue);
        }

        if (!silent)
        {
            // Output status to status bar
            // And play an audible alert if the status is not HID_SMBUS_SUCCESS
            printf("==================== HidSmbus_ReadLatch: %s \n",HidSmbus_DecodeErrorStatus(status));
        }
    }
};
void MainWindow::GetUsbConfig(bool silent){
    BOOL opened;

    // Make sure that the device is opened
    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        WORD vid;
        WORD pid;
        BYTE power;
        BYTE powerMode;
        WORD releaseVersion;

        // Get USB Configuration
        HID_SMBUS_STATUS status = HidSmbus_GetUsbConfig(m_hidSmbus, &vid, &pid, &power, &powerMode, &releaseVersion);

        if (status == HID_SMBUS_SUCCESS)
        {
            printf("Custom Vid: 0x%04X \n",vid);
            printf("Custom Pid: 0x%04X \n",pid);
            printf("Custom Power: %d mA\n",power * 2);
            printf("Custom Power Mode: %s \n",HidSmbus_DecodePower(powerMode));
            printf("Release Version: %02X.%02X \n",(releaseVersion >> 8),(releaseVersion & 0xFF));
        }

        if (!silent)
        {
            // Output status to status bar
            // And play an audible alert if the status is not HID_SMBUS_SUCCESS
            printf("==================== HidSmbus_GetUsbConfig: %s \n",HidSmbus_DecodeErrorStatus(status));
        }
    }
};
void MainWindow::GetLock(bool silent){
    BOOL opened;

    // Make sure that the device is opened
    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        BYTE lock = 0x00;

        // Get lock byte
        HID_SMBUS_STATUS status = HidSmbus_GetLock(m_hidSmbus, &lock);

        if (status == HID_SMBUS_SUCCESS)
        {
            // Check the field lock checkbox if the field is unlocked
            // Once a field is locked, it cannot be unlocked
            printf("HID_SMBUS_LOCK_VID: %d\n", (lock & HID_SMBUS_LOCK_VID)==HID_SMBUS_LOCK_VID);
            printf("HID_SMBUS_LOCK_PID: %d\n", (lock & HID_SMBUS_LOCK_PID)==HID_SMBUS_LOCK_PID);
            printf("HID_SMBUS_LOCK_POWER: %d\n", (lock & HID_SMBUS_LOCK_POWER)==HID_SMBUS_LOCK_POWER);
            printf("HID_SMBUS_LOCK_POWER_MODE: %d\n", (lock & HID_SMBUS_LOCK_POWER_MODE)==HID_SMBUS_LOCK_POWER_MODE);
            printf("HID_SMBUS_LOCK_RELEASE_VERSION: %d\n", (lock & HID_SMBUS_LOCK_RELEASE_VERSION)==HID_SMBUS_LOCK_RELEASE_VERSION);
            printf("HID_SMBUS_LOCK_MFG_STR: %d\n", (lock & HID_SMBUS_LOCK_MFG_STR)==HID_SMBUS_LOCK_MFG_STR);
            printf("HID_SMBUS_LOCK_PRODUCT_STR: %d\n", (lock & HID_SMBUS_LOCK_PRODUCT_STR)==HID_SMBUS_LOCK_PRODUCT_STR);
            printf("HID_SMBUS_LOCK_SERIAL_STR: %d\n", (lock & HID_SMBUS_LOCK_SERIAL_STR)==HID_SMBUS_LOCK_SERIAL_STR);
        }

        if (!silent)
        {
            // Output status to status bar
            // And play an audible alert if the status is not HID_SMBUS_SUCCESS
            printf("==================== HidSmbus_GetLock: %s \n",HidSmbus_DecodeErrorStatus(status));
        }
    }
};
void MainWindow::GetManufacturer(bool silent){
    BOOL opened;

    // Make sure that the device is opened
    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        HID_SMBUS_CP2112_MFG_STR	manufacturingString;
        BYTE						strlen					= 0;

        // Get manufacturer string
        HID_SMBUS_STATUS status = HidSmbus_GetManufacturingString(m_hidSmbus, manufacturingString, &strlen);

        if (status == HID_SMBUS_SUCCESS)
        {
            printf("Manufacturing String: %s \n", manufacturingString);
        }

        if (!silent)
        {
            // Output status to status bar
            // And play an audible alert if the status is not HID_SMBUS_SUCCESS
            printf("==================== HidSmbus_GetManufacturingString: %s \n", HidSmbus_DecodeErrorStatus(status));
        }
    }
};
void MainWindow::GetProduct(bool silent){
    BOOL opened;

    // Make sure that the device is opened
    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        HID_SMBUS_CP2112_PRODUCT_STR	productString;
        BYTE							strlen			= 0;

        // Get product string
        HID_SMBUS_STATUS status = HidSmbus_GetProductString(m_hidSmbus, productString, &strlen);

        if (status == HID_SMBUS_SUCCESS)
        {
            printf("Product String: %s \n", productString);
        }

        if (!silent)
        {
            // Output status to status bar
            // And play an audible alert if the status is not HID_SMBUS_SUCCESS
            printf("==================== HidSmbus_GetProductString: %s \n", HidSmbus_DecodeErrorStatus(status));
        }
    }
};
void MainWindow::GetSerial(bool silent){
    BOOL opened;

    // Make sure that the device is opened
    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        HID_SMBUS_CP2112_SERIAL_STR		serialString;
        BYTE							strlen			= 0;

        // Get serial string
        HID_SMBUS_STATUS status = HidSmbus_GetSerialString(m_hidSmbus, serialString, &strlen);

        if (status == HID_SMBUS_SUCCESS)
        {
            printf("Serial String: %s \n", serialString);
        }

        if (!silent)
        {
            // Output status to status bar
            // And play an audible alert if the status is not HID_SMBUS_SUCCESS
            printf("==================== HidSmbus_GetSerialString: %s \n", HidSmbus_DecodeErrorStatus(status));
        }
    }
};


void MainWindow::on_pbGetTimeout_clicked()
{
    GetTimeouts(FALSE);
}
