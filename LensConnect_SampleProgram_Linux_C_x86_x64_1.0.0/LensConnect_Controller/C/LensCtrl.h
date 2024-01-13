#ifndef _LensCtrl_h
#define _LensCtrl_h 1

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>	// for strncpy
#include "Types.h"
#include "SLABCP2112.h"
#include "devAddr.h"
#include "ConfigVal.h"

extern HID_SMBUS_DEVICE connectedDevice;
extern BYTE i2cAddr;
extern BYTE receivedData[80];

extern uint16_t zoomCurrentAddr, focusCurrentAddr, irisCurrentAddr, optCurrentAddr;
extern uint16_t zoomMaxAddr, zoomMinAddr, focusMaxAddr, focusMinAddr, irisMaxAddr, irisMinAddr, optFilMaxAddr;
extern uint16_t zoomSpeedPPS, focusSpeedPPS, irisSpeedPPS;
extern uint16_t status2;

// UsbCrtl.c
int UsbGetNumDevices(DWORD* numdevices);
int UsbGetSnDevice(uint16_t index, char* SnString);
int UsbOpen(DWORD deviceNumber);
void UsbClose();
int UsbSetConfig();
int UsbRead(uint16_t segmentOffset, uint16_t receiveSize);
uint16_t UsbRead2Bytes();
uint32_t CountRead();
int UsbWrite(uint16_t segmentOffset, uint16_t writeData);

// LensCtrl.c
void sleep(int n);
uint16_t NoErrChk2BytesRead(uint16_t segmentOffset);
int ModelName(char* model);
int UserAreaRead(char* userName);
int FWVersion(char* version);
int ProtocolVersion(char* version);
int LensRevision(int* revision);
int LensAddress(int* i2cAddress);
int CapabilitiesRead(uint16_t* capabilities);
int Status1Read(uint16_t* status1);
int Status2ReadSet();
int TempKelvin(int* kelvinValue);
int UserAreaWrite(char* userName);
int WaitCalc(uint16_t moveVal, int speedPPS);

int ZoomCurrentAddrReadSet();
int ZoomParameterReadSet();
int ZoomBacklashRead(uint16_t* flag);
int ZoomBacklashWrite(uint16_t flag);
int ZoomSpeedMinRead(uint16_t* speedPPS);
int ZoomSpeedMaxRead(uint16_t* speedPPS);
int ZoomSpeedWrite(uint16_t speedPPS);
int ZoomCountValRead(uint32_t* count);
int ZoomCountMaxRead(uint32_t* count);
int ZoomInit();
int ZoomMove(uint16_t addrData);

int FocusCurrentAddrReadSet();
int FocusParameterReadSet();
int FocusBacklashRead(uint16_t* flag);
int FocusBacklashWrite(uint16_t flag);
int FocusSpeedMinRead(uint16_t* speedPPS);
int FocusSpeedMaxRead(uint16_t* speedPPS);
int FocusSpeedWrite(uint16_t speedPPS);
int FocusCountValRead(uint32_t* count);
int FocusCountMaxRead(uint32_t* count);
int FocusInit();
int FocusMove(uint16_t addrData);

int IrisCurrentAddrReadSet();
int IrisParameterReadSet();
int IrisBacklashRead(uint16_t* flag);
int IrisBacklashWrite(uint16_t flag);
int IrisSpeedMinRead(uint16_t* speedPPS);
int IrisSpeedMaxRead(uint16_t* speedPPS);
int IrisSpeedWrite(uint16_t speedPPS);
int IrisCountValRead(uint32_t* count);
int IrisCountMaxRead(uint32_t* count);
int IrisInit();
int IrisMove(uint16_t addrData);

int OptFilterCurrentAddrReadSet();
int OptFilterParameterReadSet();
int OptFilterCountValRead(uint32_t* count);
int OptFilterCountMaxRead(uint32_t* count);
int OptFilterInit();
int OptFilterMove(uint16_t addrData);

int DeviceMove(uint16_t segmentOffset, uint16_t* addrData, uint16_t mask, int waitTime);
int StatusWait(uint16_t segmentOffset, uint16_t statusMask, int waitTime);
const char* ErrorTxt(int retval);

#endif // _LensCtrl_h
