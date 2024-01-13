#include <time.h>	// for nanosleep
#include "LensCtrl.h"

#define MILLI_SEC 1000000L

uint16_t zoomMaxAddr, zoomMinAddr, focusMaxAddr, focusMinAddr;
uint16_t irisMaxAddr, irisMinAddr, optFilMaxAddr;
uint16_t zoomCurrentAddr, focusCurrentAddr, irisCurrentAddr, optCurrentAddr;
uint16_t zoomSpeedPPS, focusSpeedPPS, irisSpeedPPS;
uint16_t status2;

void MsSleep(int n) {
	struct timespec ts;
	ts.tv_sec  = 0;
	ts.tv_nsec = MILLI_SEC;
	nanosleep(&ts, NULL);
}

uint16_t NoErrChk2BytesRead(uint16_t segmentOffset) {
	UsbRead(segmentOffset, 2);


	return UsbRead2Bytes();
}
int ModelName(char* model) {
	int retval = UsbRead(LENS_MODEL_NAME, LENSMODEL_LENGTH);
	strncpy(model, (const char*)receivedData, (LENSMODEL_LENGTH ));
	model[LENSMODEL_LENGTH] ='\0';
	return retval;
}
int UserAreaRead(char* userName) {
	int retval =  UsbRead(USER_AREA, USERAREA_LENGTH);
	strncpy(userName, (const char*)receivedData, (USERAREA_LENGTH));
	userName[USERAREA_LENGTH] = '\0';
	return retval;
}

int FWVersion(char* version) {
	int retval = UsbRead(FIRMWARE_VERSION, DATA_LENGTH);
	if ((retval == HID_SMBUS_SUCCESS) & (receivedData != NULL)) {
		sprintf(version, "%d.%02d", receivedData[0], receivedData[1]);
	}
	else {
		version[0] = '\0';
	}
	return retval;
}
int ProtocolVersion(char* version) {
	int retval = UsbRead(PROTOCOL_VERSION, DATA_LENGTH);
	if ((retval == HID_SMBUS_SUCCESS) & (receivedData != NULL)) {
		sprintf(version, "%d.%02d", receivedData[0], receivedData[1]);
	}
	else {
		version[0] = '\0';
	}
	return retval;
}

int LensRevision(int* revision) {
	int retval = UsbRead(LENS_REVISION, DATA_LENGTH);
	*revision = UsbRead2Bytes();
	return retval;
}

int LensAddress(int* i2cAddress) {
	int retval = UsbRead(LENS_ADDRESS, LENSADDRESS_LENGTH);
	*i2cAddress = receivedData[0];
	return retval;
}
int CapabilitiesRead(uint16_t* capabilities) {
	int retval = UsbRead(CAPABILITIES, DATA_LENGTH);
	*capabilities = UsbRead2Bytes();
	return retval;
}
int Status1Read(uint16_t* status1) {
	int retval = UsbRead(STATUS1, DATA_LENGTH);
	*status1 = UsbRead2Bytes();
	return retval;
}
int Status2ReadSet() {
	int retval = UsbRead(STATUS2, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	status2 = UsbRead2Bytes();
	return retval;
}
int TempKelvin(int* kelvinValue) {
	int retval = UsbRead(TEMPERATURE_VAL, DATA_LENGTH);
	*kelvinValue = UsbRead2Bytes();
	return retval;
}

int UserAreaWrite(char* userName) {
	char sendData[USERAREA_LENGTH + SEGMENTOFFSET_LENGTH + 1];
	sendData[0] = USER_AREA >> 8;
	sendData[1] = USER_AREA;
	strncpy(sendData + SEGMENTOFFSET_LENGTH, userName, USERAREA_LENGTH + 1);
	int retval = HidSmbus_WriteRequest(connectedDevice, i2cAddr, 
	(unsigned char*)sendData, USERAREA_LENGTH + SEGMENTOFFSET_LENGTH);
	return retval;
}
int WaitCalc(uint16_t moveValue, int speedPPS) {
	int waitTime = WAIT_MAG * moveValue / speedPPS;
	if (MINIMUM_WAIT > waitTime)
		waitTime = MINIMUM_WAIT;
	return waitTime;
}

int ZoomCurrentAddrReadSet() {
	int retval = UsbRead(ZOOM_POSITION_VAL, DATA_LENGTH);
	zoomCurrentAddr = UsbRead2Bytes();
	return retval;
}
int ZoomParameterReadSet() {
	int retval = UsbRead(ZOOM_POSITION_MIN, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	zoomMinAddr = UsbRead2Bytes();

	retval = UsbRead(ZOOM_POSITION_MAX, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	zoomMaxAddr = UsbRead2Bytes();

	retval = UsbRead(ZOOM_SPEED_VAL, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	zoomSpeedPPS = UsbRead2Bytes();

	return retval;
}
int ZoomBacklashRead(uint16_t* flag) {
	int retval = UsbRead(ZOOM_BACKLASH_CANCEL, DATA_LENGTH);
	*flag = UsbRead2Bytes();
	return retval;
}
int ZoomBacklashWrite(uint16_t flag) {
	int retval = UsbWrite(ZOOM_BACKLASH_CANCEL, flag);
	return retval;
}
int ZoomSpeedMinRead(uint16_t* speedPPS) {
	int retval = UsbRead(ZOOM_SPEED_MIN, DATA_LENGTH);
	*speedPPS = UsbRead2Bytes();
	return retval;
}
int ZoomSpeedMaxRead(uint16_t* speedPPS) {
	int retval = UsbRead(ZOOM_SPEED_MAX, DATA_LENGTH);
	*speedPPS = UsbRead2Bytes();
	return retval;
}
int ZoomSpeedWrite(uint16_t speedPPS) {
	int retval = UsbWrite(ZOOM_SPEED_VAL, speedPPS);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	MsSleep(1);
	retval = UsbRead(ZOOM_SPEED_VAL, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	zoomSpeedPPS = UsbRead2Bytes();
	return retval;
}
int ZoomCountValRead(uint32_t* count) {
	int retval = UsbRead(ZOOM_COUNT_VAL, LENSCOUNT_LENGTH);
	*count = CountRead();
	return retval;
}
int ZoomCountMaxRead(uint32_t* count) {
	int retval = UsbRead(ZOOM_COUNT_MAX, LENSCOUNT_LENGTH);
	*count = CountRead();
	return retval;
}
int ZoomInit() {
	int waitTime = WaitCalc((zoomMaxAddr - zoomMinAddr), zoomSpeedPPS);
	int retval = UsbWrite(ZOOM_INITIALIZE, INIT_RUN_BIT);
	if (retval == HID_SMBUS_SUCCESS) {
		retval = StatusWait(STATUS1, ZOOM_MASK, waitTime);
		if (retval == HID_SMBUS_SUCCESS) {
			retval = UsbRead(ZOOM_POSITION_VAL, DATA_LENGTH);
			if (retval == HID_SMBUS_SUCCESS) {
				zoomCurrentAddr = UsbRead2Bytes();
				Status2ReadSet();
				return retval;
			}
		}
	}
	return retval;
}
int ZoomMove(uint16_t addrData) {
	uint16_t moveVal = abs(addrData - zoomCurrentAddr);
	int waitTime = WaitCalc(moveVal, zoomSpeedPPS);
	int retval = DeviceMove(ZOOM_POSITION_VAL, &addrData, ZOOM_MASK, waitTime);
	if (retval == HID_SMBUS_SUCCESS)
		zoomCurrentAddr = addrData;
	return retval;
}

int FocusCurrentAddrReadSet() {
	int retval = UsbRead(FOCUS_POSITION_VAL, DATA_LENGTH);
	focusCurrentAddr = UsbRead2Bytes();
	return retval;
}
int FocusParameterReadSet() {
	int retval = UsbRead(FOCUS_MECH_STEP_MIN, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	focusMinAddr = UsbRead2Bytes();

	retval = UsbRead(FOCUS_MECH_STEP_MAX, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	focusMaxAddr = UsbRead2Bytes();

	retval = UsbRead(FOCUS_SPEED_VAL, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	focusSpeedPPS = UsbRead2Bytes();

	return retval;
}
int FocusBacklashRead(uint16_t* flag) {
	int retval = UsbRead(FOCUS_BACKLASH_CANCEL, DATA_LENGTH);
	*flag = UsbRead2Bytes();
	return retval;
}
int FocusBacklashWrite(uint16_t flag) {
	int retval = UsbWrite(FOCUS_BACKLASH_CANCEL, flag);
	return retval;
}
int FocusSpeedMinRead(uint16_t* speedPPS) {
	int retval = UsbRead(FOCUS_SPEED_MIN, DATA_LENGTH);
	*speedPPS = UsbRead2Bytes();
	return retval;
}
int FocusSpeedMaxRead(uint16_t* speedPPS) {
	int retval = UsbRead(FOCUS_SPEED_MAX, DATA_LENGTH);
	*speedPPS = UsbRead2Bytes();
	return retval;
}
int FocusSpeedWrite(uint16_t speedPPS) {
	int retval = UsbWrite(FOCUS_SPEED_VAL, speedPPS);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	MsSleep(1);
	retval = UsbRead(FOCUS_SPEED_VAL, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	focusSpeedPPS = UsbRead2Bytes();
	return retval;
}
int FocusCountValRead(uint32_t* count) {
	int retval = UsbRead(FOCUS_COUNT_VAL, LENSCOUNT_LENGTH);
	*count = CountRead();
	return retval;
}
int FocusCountMaxRead(uint32_t* count) {
	int retval = UsbRead(FOCUS_COUNT_MAX, LENSCOUNT_LENGTH);
	*count = CountRead();
	return retval;
}
int FocusInit() {
	int waitTime = WaitCalc((focusMaxAddr - focusMinAddr), focusSpeedPPS);
	int retval = UsbWrite(FOCUS_INITIALIZE, INIT_RUN_BIT);
	if (retval == HID_SMBUS_SUCCESS) {
		retval = StatusWait(STATUS1, FOCUS_MASK, waitTime);
		if (retval == HID_SMBUS_SUCCESS) {
			retval = UsbRead(FOCUS_POSITION_VAL, DATA_LENGTH);
			if (retval == HID_SMBUS_SUCCESS) {
				focusCurrentAddr = UsbRead2Bytes();
				Status2ReadSet();
				return retval;
			}
		}
	}
	return retval;
}
int FocusMove(uint16_t addrData) {
	uint16_t moveVal = abs(addrData - focusCurrentAddr);
	int waitTime = WaitCalc(moveVal, focusSpeedPPS);
	int retval = DeviceMove(FOCUS_POSITION_VAL, &addrData, FOCUS_MASK, waitTime);
	if (retval == HID_SMBUS_SUCCESS)
		focusCurrentAddr = addrData;
	return retval;
}

int IrisCurrentAddrReadSet() {
	int retval = UsbRead(IRIS_POSITION_VAL, DATA_LENGTH);
	irisCurrentAddr = UsbRead2Bytes();
	return retval;
}
int IrisParameterReadSet() {
	int retval = UsbRead(IRIS_MECH_STEP_MIN, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	irisMinAddr = UsbRead2Bytes();

	retval = UsbRead(IRIS_MECH_STEP_MAX, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	irisMaxAddr = UsbRead2Bytes();

	retval = UsbRead(IRIS_SPEED_VAL, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	irisSpeedPPS = UsbRead2Bytes();

	return retval;
}
int IrisBacklashRead(uint16_t* flag) {
	int retval = UsbRead(IRIS_BACKLASH_CANCEL, DATA_LENGTH);
	*flag = UsbRead2Bytes();
	return retval;
}
int IrisBacklashWrite(uint16_t flag) {
	int retval = UsbWrite(IRIS_BACKLASH_CANCEL, flag);
	return retval;
}
int IrisSpeedMinRead(uint16_t* speedPPS) {
	int retval = UsbRead(IRIS_SPEED_MIN, DATA_LENGTH);
	*speedPPS = UsbRead2Bytes();
	return retval;
}
int IrisSpeedMaxRead(uint16_t* speedPPS) {
	int retval = UsbRead(IRIS_SPEED_MAX, DATA_LENGTH);
	*speedPPS = UsbRead2Bytes();
	return retval;
}
int IrisSpeedWrite(uint16_t speedPPS) {
	int retval = UsbWrite(IRIS_SPEED_VAL, speedPPS);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	MsSleep(1);
	retval = UsbRead(IRIS_SPEED_VAL, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	irisSpeedPPS = UsbRead2Bytes();
	return retval;
}
int IrisCountValRead(uint32_t* count) {
	int retval = UsbRead(IRIS_COUNT_VAL, LENSCOUNT_LENGTH);
	*count = CountRead();
	return retval;
}
int IrisCountMaxRead(uint32_t* count) {
	int retval = UsbRead(IRIS_COUNT_MAX, LENSCOUNT_LENGTH);
	*count = CountRead();
	return retval;
}
int IrisInit() {
	int waitTime = WaitCalc((irisMaxAddr - irisMinAddr), irisSpeedPPS);
	int retval = UsbWrite(IRIS_INITIALIZE, INIT_RUN_BIT);
	if (retval == HID_SMBUS_SUCCESS) {
		retval = StatusWait(STATUS1, IRIS_MASK, waitTime);
		if (retval == HID_SMBUS_SUCCESS) {
			retval = UsbRead(IRIS_POSITION_VAL, DATA_LENGTH);
			if (retval == HID_SMBUS_SUCCESS) {
				irisCurrentAddr = UsbRead2Bytes();
				Status2ReadSet();
				return retval;
			}
		}
	}
	return retval;
}
int IrisMove(uint16_t addrData) {
	uint16_t moveVal = abs(addrData - irisCurrentAddr);
	int waitTime = WaitCalc(moveVal, irisSpeedPPS);
	int retval = DeviceMove(IRIS_POSITION_VAL, &addrData, IRIS_MASK, waitTime);
	if (retval == HID_SMBUS_SUCCESS)
		irisCurrentAddr = addrData;
	return retval;
}

int OptFilterCurrentAddrReadSet() {
	int retval = UsbRead(OPT_FILTER_POSITION_VAL, DATA_LENGTH);
	optCurrentAddr = UsbRead2Bytes();
	return retval;
}
int OptFilterParameterReadSet() {
	int retval = UsbRead(OPT_FILTER_MECH_STEP_MAX, DATA_LENGTH);
	if (retval != HID_SMBUS_SUCCESS)
		return retval;
	optFilMaxAddr = UsbRead2Bytes();

	retval = OptFilterCurrentAddrReadSet();
	return retval;
}
int OptFilterCountValRead(uint32_t* count) {
	int retval = UsbRead(OPT_FILTER_COUNT_VAL, LENSCOUNT_LENGTH);
	*count = CountRead();
	return retval;
}
int OptFilterCountMaxRead(uint32_t* count) {
	int retval = UsbRead(OPT_FILTER_COUNT_MAX, LENSCOUNT_LENGTH);
	*count = CountRead();
	return retval;
}
int OptFilterInit() {
	int waitTime = WaitCalc((optFilMaxAddr + 1), OPT_FILTER_SPEED);
	int retval = UsbWrite(OPT_FILTER_INITIALIZE, INIT_RUN_BIT);
	if (retval == HID_SMBUS_SUCCESS) {
		retval = StatusWait(STATUS1, OPT_FILTER_MASK, waitTime);
		if (retval == HID_SMBUS_SUCCESS) {
			retval = UsbRead(OPT_FILTER_POSITION_VAL, DATA_LENGTH);
			if (retval == HID_SMBUS_SUCCESS) {
				optCurrentAddr = UsbRead2Bytes();
				Status2ReadSet();
				return retval;
			}
		}
	}
	return retval;
}
int OptFilterMove(uint16_t addrData) {
	uint16_t moveVal = abs(addrData - optCurrentAddr);
	int waitTime = WaitCalc((moveVal + 1), OPT_FILTER_SPEED);
	int retval = DeviceMove( OPT_FILTER_POSITION_VAL, &addrData, OPT_FILTER_MASK, waitTime);
	if (retval == HID_SMBUS_SUCCESS)
		optCurrentAddr = addrData;
	return retval;
}
int DeviceMove(uint16_t segmentOffset, uint16_t *addrData, uint16_t mask , int waitTime) {
	int retval = UsbWrite(segmentOffset, *addrData);
	if (retval == HID_SMBUS_SUCCESS) {
		retval = StatusWait(STATUS1, mask, waitTime);
		if (retval == HID_SMBUS_SUCCESS) {
			retval = UsbRead(segmentOffset, DATA_LENGTH);
			if (retval != HID_SMBUS_SUCCESS)
				return retval;
			*addrData = UsbRead2Bytes();
			return retval;
		}
		return retval;
	}
	return retval;
}
int StatusWait(uint16_t segmentOffset, uint16_t statusMask, int waitTime) {
	int tmp = 0;
	uint16_t readStatus;
	int retval;
	do {
		retval = UsbRead(segmentOffset, DATA_LENGTH);
		if (retval != HID_SMBUS_SUCCESS)
			return retval;

		readStatus = UsbRead2Bytes();
		tmp += 1;
		if (tmp >= LOW_HIGH_WAIT)
			return LOWHI_ERROR;

	} while ((readStatus & statusMask) != statusMask);

	tmp = 0;
	do {
		retval = UsbRead(segmentOffset, DATA_LENGTH);
		if (retval != HID_SMBUS_SUCCESS)
			return retval;

		readStatus = UsbRead2Bytes();
		tmp += 1;
		if (tmp >= waitTime)
			return HILOW_ERROR;
		
		MsSleep(1);
	} while ((readStatus & statusMask) != 0);

	return retval;
}
const char *ErrorTxt(int retval) {
	switch (retval) {
	case 0x01:
		return "Device not found.\n";
	case 0x02:
		return "Invalid handle.\n";
	case 0x03:
		return "Invalid device object.\n";
	case 0x04:
		return "Invalid parameter.\n";
	case 0x05:
		return "Invalid request length.\n";
	case 0x10:
		return "Read error.\n";
	case 0x11:
		return "Write error.\n";
	case 0x12:
		return "Read time out.\n";
	case 0x13:
		return "Write time out.\n";
	case 0x14:
		return "Device IO failed.\n";
	case 0x15:
		return "Device access error.\r\nThe device may already be running.\n";
	case 0x16:
		return "Device not supported.\n";
	case 0x50:
		return "StatusBit hi error.\n";
	case 0x51:
		return "StatusBit low error.\n";
	}
	return "";
}


