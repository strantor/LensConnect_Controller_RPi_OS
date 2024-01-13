#include"LensCtrl.h"
#include"LensConnect.h"
#include<unistd.h>
#include<termios.h>

void MoveLens(int motor) {
	int addrData = 0;
	printf("\nEnter the address you want to go ");
	scanf("%u", &addrData);
	switch (motor) {
	case ZOOM:
		ZoomMove((uint16_t)addrData);
		break;
	case FOCUS :
		FocusMove((uint16_t)addrData);
		break;
	case IRIS:
		IrisMove((uint16_t)addrData);
		break;
	case OPT:
		OptFilterMove((uint16_t)addrData);
		break;
	}
	printf("\n");
}
void UserIDRead() {
	char userName[33];
	UserAreaRead(userName);
	printf("%s\n", userName);

}
void UserIDWrite() {
	char userName[33];
	char dummy;
	printf("\nPlease fill in the user area(32byte full)\n");
	printf("12345678901234567890123456789012\n");
	scanf("%[\n]",&dummy);
	scanf("%[^\n]", userName);
	UserAreaWrite(userName);
	printf("\n");
}

void FineFocusMove(){
#define QUIT_CHAR 0x0d	// Enter key
struct termios CookedTermIos;
struct termios RawTermIos;
	tcgetattr(STDIN_FILENO, &CookedTermIos);
	RawTermIos = CookedTermIos;
	cfmakeraw(&RawTermIos);
	tcsetattr(STDIN_FILENO, 0, &RawTermIos);
	int c;
	uint16_t addrData;
	while ((c = getchar()) != QUIT_CHAR) {
		switch(c) {
		case 'z':
			addrData = focusCurrentAddr + fineNum;
			LimFocusMove(addrData);
			break;
		case 'x':
			addrData = focusCurrentAddr - fineNum;
			LimFocusMove(addrData);
			break;
		default :
			break;
		}
	}
	printf("\r\nEnd fine move focus mode\n");
	tcsetattr(STDIN_FILENO, 0, &CookedTermIos);
	putchar('\n');
}

void LimFocusMove(uint16_t addrData) {
	if ((focusMaxAddr >= addrData) & (addrData >= focusMinAddr)){
		int retval = FocusMove(addrData);
		if (retval == SUCCESS)
			printf("\rAddr= %d", focusCurrentAddr);
	} else {
		printf("\rLimit      ");
	}
}	

