#include"LensCtrl.h"
#include"LensConnect.h"

void ZoomSpeedChange() {
	int speedPPS = 0;
	uint16_t speedMin = 0;
	uint16_t speedMax = 0;
	ZoomSpeedMinRead(&speedMin);
	ZoomSpeedMaxRead(&speedMax);
	printf("\nPlease input PPS between %d to %d\n", speedMin, speedMax);
	scanf("%u", &speedPPS);
	ZoomSpeedWrite(speedPPS);
}

void FocusSpeedChange() {
	int speedPPS = 0;
	uint16_t speedMin = 0;
	uint16_t speedMax = 0;
	FocusSpeedMinRead(&speedMin);
	FocusSpeedMaxRead(&speedMax);
	printf("\nPleas input PPS between %d to %d\n", speedMin, speedMax);
	scanf("%u", &speedPPS);
	FocusSpeedWrite(speedPPS);
}
void IrisSpeedChange() {
	int speedPPS = 0;
	uint16_t speedMin = 0;
	uint16_t speedMax = 0;
	IrisSpeedMinRead(&speedMin);
	IrisSpeedMaxRead(&speedMax);
	printf("\nPlease input PPS between %d to %d\n", speedMin, speedMax);
	scanf("%u", &speedPPS);
	IrisSpeedWrite(speedPPS);
}
void ZoomBacklashToggleCtl() {
	uint16_t flag = 0;
	printf("\nZoom backlash correction ");
	ZoomBacklashRead(&flag);
	if (flag == ON) {
		ZoomBacklashWrite(OFF);
		printf("OFF\n");
	}
	else {
		ZoomBacklashWrite(ON);
		printf("ON\n");
	}
}
void FocusBacklashToggleCtl() {
	uint16_t flag = 0;
	printf("\nFocus backlash correction ");
	FocusBacklashRead(&flag);
	if (flag == ON) {
		FocusBacklashWrite(OFF);
		printf("OFF\n");
	}
	else {
		FocusBacklashWrite(ON);
		printf("ON\n");
	}
}
void IrisBacklashToggleCtl() {
	uint16_t flag = 0;
	printf("\nIris backlash correction ");
	IrisBacklashRead(&flag);
	if (flag == ON) {
		IrisBacklashWrite(OFF);
		printf("OFF\n");
	}
	else {
		IrisBacklashWrite(ON);
		printf("ON\n");
	}
}
