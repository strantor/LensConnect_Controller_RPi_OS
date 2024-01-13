 #include<limits.h>
#include"LensCtrl.h"
#include"LensConnect.h"

void PrintBinaly(uint16_t value) {
	int i = 0;
	unsigned int mask = (int)1 << (sizeof(value) * CHAR_BIT - 1);
	do {
		putchar(mask & value ? '1' : '0');
		i++;
		if (i == 4){
			putchar(' ');
			i = 0;
		}
	} while (mask >>= 1);
	printf("\n");
}

void GeneralInfo() {
	int retval;
	char version[7];
	char model[25];

	printf("\n***** General Information *****\n");

	retval = ProtocolVersion(version);
	if (retval == SUCCESS) {
		printf("Protocol version  = %s\n", version);
	}
	else {
		printf("%s", ErrorTxt(retval));
	}

	retval = FWVersion(version);
	if (retval == SUCCESS) {
		printf("Firemware version = %s\n", version);
	}
	else {
		printf("%s", ErrorTxt(retval));
	}
	
	int revision = 0;
	retval = LensRevision(&revision);
	if (retval == SUCCESS) {
		printf("Lens revision = %d\n", revision);
	}
	else {
		printf("%s", ErrorTxt(retval));
	}
	
	int i2cAddr = 0;
	retval = LensAddress(&i2cAddr);
	if (retval == SUCCESS) {
		printf("Lens I2C address = 0x%x (7bit)\n", i2cAddr);
	}
	else {
		printf("%s", ErrorTxt(retval));
	}
	
	retval = ModelName(model);
	if (retval == SUCCESS) {
		printf("Lens model name = %s\n", model);
	}
	else {
		printf("%s", ErrorTxt(retval));
	}
	uint16_t capabilities;
	retval = CapabilitiesRead(&capabilities);
	if (retval == SUCCESS) {
		printf("Capabilities = ");
		PrintBinaly(capabilities);
	}
	else {
		printf("%s", ErrorTxt(retval));
	}
	
	uint16_t status1 = 0;
	retval = Status1Read(&status1);
	if (retval == SUCCESS) {
		printf("Status1 = ");
		PrintBinaly(status1);
	}
	else {
		printf("%s", ErrorTxt(retval));
	}
	
	retval = Status2ReadSet();
	if (retval == SUCCESS) {
		printf("status2 = "); 
		PrintBinaly(status2);
	}
	else {
		printf("%s", ErrorTxt(retval));
	}
	
	int kelvinValue = 0;
	retval = TempKelvin(&kelvinValue);
	if (retval == SUCCESS) {
		int tempCels = (int)round(kelvinValue - KELVIN_TO_CELS);
		printf("Temperature = %u degree Celsius\n", tempCels);
	}
	else {
		printf("%s", ErrorTxt(retval));
	}
}
void ZoomInfo() {
	uint16_t flag;
	uint16_t speedPPS;
	uint32_t count;
	printf("\n***** ZOOM Information *****\n");
	printf("Current position = %d\n", zoomCurrentAddr);
	ZoomBacklashRead(&flag);
	printf("Backlash correction = %s\n", OnOff(flag));
	printf("Initialize position = %d\n", NoErrChk2BytesRead(ZOOM_INIT_POSITION));
	printf("Mechanical min = %d\n", NoErrChk2BytesRead(ZOOM_MECH_STEP_MIN));
	printf("Mechanical max = %d\n", NoErrChk2BytesRead(ZOOM_MECH_STEP_MAX));
	printf("Position min = %d\n", zoomMinAddr);
	printf("Position max = %d\n", zoomMaxAddr);
	printf("Speed value = %d\n", zoomSpeedPPS);
	ZoomSpeedMinRead(&speedPPS);
	printf("Speed min   = %d\n", speedPPS);
	ZoomSpeedMaxRead(&speedPPS);
	printf("Speed max   = %d\n", speedPPS);
	ZoomCountValRead(&count);
	printf("Count value = %d\n", count);
	ZoomCountMaxRead(&count);
	printf("Count max   = %d\n", count);

}
void FocusInfo() {
	uint16_t flag;
	uint16_t speedPPS;
	uint32_t count;
	printf("\n***** FOCUS Information *****\n");
	printf("Current position = %d\n", focusCurrentAddr);
	FocusBacklashRead(&flag);
	printf("Backlash correction = %s\n", OnOff(flag));
	printf("Initialize position = %d\n", NoErrChk2BytesRead(FOCUS_INIT_POSITION));
	printf("Mechanical min = %d\n", focusMinAddr);
	printf("Mechanical max = %d\n", focusMaxAddr);
	printf("Position min = %d\n", NoErrChk2BytesRead(FOCUS_POSITION_MIN));
	printf("Position max = %d\n", NoErrChk2BytesRead(FOCUS_POSITION_MAX));
	printf("Speed value = %d\n", focusSpeedPPS);
	FocusSpeedMinRead(&speedPPS);
	printf("Speed min   = %d\n", speedPPS);
	FocusSpeedMaxRead(&speedPPS);
	printf("Speed max   = %d\n", speedPPS);
	FocusCountValRead(&count);
	printf("Count value = %d\n", count);
	FocusCountMaxRead(&count);
	printf("Count max   = %d\n", count);
}
void IrisInfo() {
	uint16_t flag;
	uint16_t speedPPS;
	uint32_t count;
	printf("\n***** IRIS Information *****\n");
	printf("Current position = %d\n", irisCurrentAddr);
	IrisBacklashRead(&flag);
	printf("Backlash correction = %s\n", OnOff(flag));
	printf("Initialize position = %d\n", NoErrChk2BytesRead(IRIS_INIT_POSITION));
	printf("Mechanical min = %d\n", irisMinAddr);
	printf("Mechanical max = %d\n", irisMaxAddr);
	printf("Position min = %d\n", NoErrChk2BytesRead(IRIS_POSITION_MIN));
	printf("Position max = %d\n", NoErrChk2BytesRead(IRIS_POSITION_MAX));
	printf("Speed value = %d\n", irisSpeedPPS);
	IrisSpeedMinRead(&speedPPS);
	printf("Speed min   = %d\n", speedPPS);
	IrisSpeedMaxRead(&speedPPS);
	printf("Speed max   = %d\n", speedPPS);
	IrisCountValRead(&count);
	printf("Count value = %u\n", count);
	IrisCountMaxRead(&count);
	printf("Count max   = %u\n", count);
}
void OptFilterInfo() {
	uint32_t count;
	printf("\n***** OPTICAL FILTER Information *****\n");
	printf("Current position = %d\n", optCurrentAddr);
	printf("Initialize position = %d\n", NoErrChk2BytesRead(OPT_FILTER_INIT_POSITION));
	printf("Mechanical min = %d\n", 0);
	printf("Mechanical max = %d\n",optFilMaxAddr);
	printf("Position min = %d\n", 0);
	printf("Position max = %d\n", NoErrChk2BytesRead(OPT_FILTER_POSITION_MAX));
	OptFilterCountValRead(&count);
	printf("Count value = %d\n", count);
	OptFilterCountMaxRead(&count);
	printf("Count max   = %d\n", count);
}
