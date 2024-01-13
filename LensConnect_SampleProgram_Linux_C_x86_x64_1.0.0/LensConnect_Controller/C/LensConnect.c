#include"LensCtrl.h"
#include"LensConnect.h"

#define PROGRAM_VERSION "1.0.0"
int ItemNum;
int detailSelect;
int fineNum;
BOOL USBOpen_flag = FALSE;
BOOL withZoom = FALSE;
BOOL withFocus = FALSE;
BOOL withIris = FALSE;
BOOL withOptFil = FALSE;


const char* OnOff(uint16_t flag) {
	if (flag == 1)
		return "ON";
	else
		return "OFF";
}

void ScanUSBLensInfo() {
	DWORD numDevices = 0;
	char snString[260];	// SnString is 260bytes according to the instructions of the USB IC
	char model[25];
	UsbGetNumDevices(&numDevices);
	if (numDevices >= 1) {
		printf("No.: S/N\n");
		for (uint16_t i = 0; i < numDevices; i++) {
			int retval = UsbGetSnDevice(i, snString);
			if (retval == SUCCESS){
				printf(" %d : %s, ", i, snString);
				UsbOpen(i);
				ModelName(model);
				printf("%s, ", model);
				UserIDRead();
				UsbClose();
			} else {
				printf(" %d : %s\n", i, snString);
			}
		}
	}
	else
	{
		printf("No LensConnect is connected.\r\n");
	}
	printf("\n");
}	

void UsbConnect(int deviceNumber) {
	uint16_t capabilities;
	int retval = UsbOpen(deviceNumber);
	if (retval != SUCCESS) {
		printf("%s\n", ErrorTxt(retval));
		return;
	}
	retval = UsbSetConfig();
	if (retval != SUCCESS) {
		printf("%s\n", ErrorTxt(retval));
		return;
	}
	printf("opened\r\n");
	CapabilitiesRead(&capabilities);
	Status2ReadSet();

	if (capabilities & ZOOM_MASK) {
		ZoomParameterReadSet();
		if ((status2 & ZOOM_MASK) == INIT_COMPLETED)
			ZoomCurrentAddrReadSet();
		withZoom = TRUE;
	}
	if (capabilities & FOCUS_MASK) {
		FocusParameterReadSet();
		if ((status2 & FOCUS_MASK) == INIT_COMPLETED)
			FocusCurrentAddrReadSet();
		withFocus = TRUE;
	}
	if (capabilities & IRIS_MASK) {
		IrisParameterReadSet();
		if ((status2 & IRIS_MASK) == INIT_COMPLETED)
			IrisCurrentAddrReadSet();
		withIris = TRUE;
	}
	if (capabilities & OPT_FILTER_MASK) {
		OptFilterParameterReadSet();
		if ((status2 & OPT_FILTER_MASK) == INIT_COMPLETED)
			OptFilterCurrentAddrReadSet();
		withOptFil = TRUE;
	}
	USBOpen_flag = TRUE;
}

void UsbDisconnect(){
	UsbClose();
	USBOpen_flag = FALSE;
	withZoom = FALSE;
	withFocus = FALSE;
	withIris = FALSE;
	withOptFil = FALSE;
}

void CommandList() {
	printf("\n----- LensConnect Control -----\n");
	printf(" 0 : Command list\n");
	if (withZoom == TRUE) {
		printf("----- ZOOM  -----\n");
		printf(" 1 : Initialize zoom\n");
		if ((status2 & ZOOM_MASK) == 0) {
			printf("11 : Move zoom(%d - %d)\n", zoomMinAddr, zoomMaxAddr);
			printf("12 : Displays the current zoom  address\n\n");
		}
	}
	if (withFocus == TRUE) {
		printf("----- FOCUS -----\n");
		printf(" 2 : Initialize focus\n");
		if ((status2 & FOCUS_MASK) == 0) {
			printf("21 : Move focus(%d - %d)\n", focusMinAddr, focusMaxAddr);
			printf("22 : Displays the current focus address\n");
			printf("23 : Fine move focus control\n");
			printf("24 : Fine step number setting\n\n");
		}
	}
	if (withIris == TRUE) {
		printf("----- IRIS  -----\n");
		printf(" 3 : Initialize iris\n");
		if ((status2 & IRIS_MASK) == 0) {
			printf("31 : Move iris(%d - %d)\n", irisMinAddr, irisMaxAddr);
			printf("32 : Displays the current iris  address\n\n");
		}
	}
	if (withOptFil == TRUE) {
		printf("----- Optical Fiter  -----\n");
		printf(" 4 : Initialize optical filter\n");
		if ((status2 & OPT_FILTER_MASK) == 0) {
			printf("41 : Move Optical filter(0 - %d)\n", optFilMaxAddr);
			printf("42 : Show current the optical filter address\n\n");
		}
	}
	printf("----- Other -----\n");
	printf(" 5 : Parameter setup\n");
	printf(" 6 : Displays the information\n");
	printf(" 7 : Displays the user name\n");
	printf("71 : Write User area\n");
	printf(" 8 : Close USB (Other Lens)\n");
	printf(" 9 : Exit application\n\n");
}
void CommandSetupList() {
	printf("\n");
	if (withZoom == TRUE) {
		printf(" 1: Zoom \n");
	}
	if (withFocus == TRUE) {
		printf(" 2: Focus \n");
	}
	if (withIris == TRUE) {
		printf(" 3: Iris  \n");
	}
	printf(" 5: Return to main\n\n");
}
void DetailSetupList(int motorNumber) {
	uint16_t flag;
	printf("\n 1: Speed change. ");
	switch(motorNumber) {
	case ZOOM:
		printf("Current zoom speed is %d\n", zoomSpeedPPS);
		break;
	case FOCUS:
		printf("Current focus speed is %d\n", focusSpeedPPS);
		break;
	case IRIS:
		printf("Current iris speed is %d\n", irisSpeedPPS);
		break;
	}
	printf(" 2: Backlash correction change. ");
	switch (motorNumber) {
	case ZOOM:
		ZoomBacklashRead(&flag);
		printf("Currently %s\n", OnOff(flag));
		break;
	case FOCUS:
		FocusBacklashRead(&flag);
		printf("Currently %s\n", OnOff(flag));
		break;
	case IRIS:
		IrisBacklashRead(&flag);
		printf("Currently %s\n", OnOff(flag));
		break;
	}
	printf(" 5: Back (Cancel)\n\n");
}
void CommandLensInfoList() {
	printf("\n----- Information -----\n");
	printf(" 0: Displays General\n");
	if (withZoom == TRUE) {
		printf(" 1: Displays Zoom\n");
	}
	if (withFocus == TRUE) {
		printf(" 2: Displays Focus\n");
	}
	if (withIris == TRUE) {
		printf(" 3: Displays Iris\n");
	}
	if (withOptFil == TRUE) {
		printf(" 4: Displays Opticalfilter\n");
	}
	printf(" 5: Return to main\n\n");
}



void MainExe(int number) {
	int num;
	switch (number) {
	case 0:						// +CommandList();
		break;
	case 1:
		printf("Initializing\n");
		ZoomInit();				// +CommandList();
		break;
	case 11:
		MoveLens(ZOOM);
		break;
	case 12:
		printf("\nZoom current address = %u\n\n", zoomCurrentAddr);
		break;
	case 2:
		printf("Initializing\n");
		FocusInit();			// +CommandList();
		break;
	case 21:
		MoveLens(FOCUS);
		break;
	case 22:
		printf("\nFocus current address %u\n\n", focusCurrentAddr);
		break;
	case 23:
		printf("\nFine move focus mode:\n z -> Near / x -> Far / enter -> End, fine step = %u\n", fineNum);
		FineFocusMove();
		break;
	case 24:
		printf("Fine monve step number = ");
		scanf("%u", &num);
		fineNum = num;
		break;
	case 3:
		printf("Initializing\n");
		IrisInit();				// +CommandList();
		break;
	case 31:
		MoveLens(IRIS);
		break;
	case 32:
		printf("\nIris current address %u\n\n", irisCurrentAddr);
		break;
	case 4:
		OptFilterInit();		// +CommandList();
		break;
	case 41:
		MoveLens(OPT);
		break;
	case 42:
		printf("\nOptical filter current address %u\n\n", optCurrentAddr);
		break;
	case 5:
		CommandSetupList();
		ItemNum = SETUP;
		break;
	case 6:
		CommandLensInfoList();
		ItemNum = INFO;
		break;
	case 7:
		printf("\n");
		UserIDRead();
		printf("\n");
		break;
	case 71:
		UserIDWrite();
		break;
	case 8:
		UsbDisconnect();
		break;
	default:
		printf("\nWrong number entered.\n\n");
	}
	if (number <= 4)
		CommandList();
}

void SetupExe(int number) {
	static int motorNumber;
	if (detailSelect == OFF) {
		switch (number) {
		case ZOOM:
			motorNumber = ZOOM;
			break;
		case FOCUS:
			motorNumber = FOCUS;
			break;
		case IRIS:
			motorNumber = IRIS;
			break;
		case BACK_MAIN:
			ItemNum = MAIN;
			CommandList();
			break;
		default:
			printf("\nWrong number entered.\n\n");
			CommandSetupList();
		}
		if ((number == ZOOM) | (number == FOCUS) | (number == IRIS)) {
			DetailSetupList(motorNumber);
			detailSelect = ON;
		}
	}
	else {					// detailSelect == ON
		switch (number) {
		case 1:
			switch (motorNumber) {
			case ZOOM:
				ZoomSpeedChange();
				break;
			case FOCUS:
				FocusSpeedChange();
				break;
			case IRIS:
				IrisSpeedChange();
				break;
			}
			break;
		case 2:
			switch (motorNumber) {
			case ZOOM:
				ZoomBacklashToggleCtl();
				break;
			case FOCUS:
				FocusBacklashToggleCtl();
				break;
			case IRIS:
				IrisBacklashToggleCtl();
				break;
			}
			break;
		case 5:
			break;
		default:
			printf("\nWrong number entered.\n\n");
			break;
		}
		CommandSetupList();
		detailSelect = OFF;
	}
}
void InfoExe(int number) {
	switch (number) {
	case GENE:
		GeneralInfo();
		break;
	case ZOOM:
		ZoomInfo();
		break;
	case FOCUS:
		FocusInfo();
		break;
	case IRIS:
		IrisInfo();
		break;
	case OPT:
		OptFilterInfo();
		break;
	case BACK_MAIN:
		ItemNum = MAIN;
		CommandList();
		break;
	default:
		printf("\nWrong number entered.\n\n");
	}
	if (number!= BACK_MAIN) 
		CommandLensInfoList();
}
int main()
{
	int number;
	ItemNum = MAIN;
	fineNum = 2;
	printf("LensConnect Control %s\n", PROGRAM_VERSION);
	while (TRUE)
	{
		if (USBOpen_flag == FALSE) {			// When not Open
			ScanUSBLensInfo();					// Up to 8lenses
			printf(" 8 : Scan device\n");
			printf(" 9 : Exit application\n");
			printf("\nPlease select connect lens No.");
			scanf("%u", &number);
			if (number == 9) {
				UsbDisconnect();
				break;
			}
			if (number != 8) {
				printf(" No.%u lens ", number);
				UsbConnect(number);
				CommandList();
			}
		}
		else {									// When Open
			printf("Select number:");
			scanf("%u", &number);
			switch (ItemNum) {
			case MAIN:
				if (number == 9) {
				UsbDisconnect();
				return 1;
				}
				if (number == 8) {
				UsbDisconnect();
				}
				MainExe(number);
				break;
			case SETUP:
				SetupExe(number);
				break;
			case INFO:
				InfoExe(number);
				break;
			}
		}
	}
}

