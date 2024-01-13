TARGET := LensConnect_Controller
CC := g++
#CFLAGS := -m32 -Wall				# for 32bit user
CFLAGS := -Wall						# for 64bit user
#LDFLAGS = -L../CP2112/lib/x86_32	# for 32bit user
LDFLAGS = -L../CP2112/lib/x86_64	# for 64bit user
LDLIBS = -pthread -lslabhidtosmbus -lslabhiddevice -lusb-1.0 -ludev
INCLUDE = -I../CP2112/include

$(TARGET):UsbCtrl.o LensCtrl.o LensAccess.o LensSetup.o LensInfo.o LensConnect.o
	$(CC) $(LDFLAGS) -o $@ UsbCtrl.o LensCtrl.o LensAccess.o LensSetup.o LensInfo.o LensConnect.o $(LDLIBS) $(LDFLAGS2)$(LDLIBS2)

UsbCtrl.o:UsbCtrl.c 
	$(CC) $(CFLAGS) $(INCLUDE) -c $*.c

LensCtrl.o:LensCtrl.c 
	$(CC) $(CFLAGS) $(INCLUDE) -c $*.c

LensAccess.o:LensAccess.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $*.c

LensSetup.o:LensSetup.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $*.c

LensInfo.o:LensInfo.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $*.c

LensConnect.o:LensConnect.c 
	$(CC) $(CFLAGS) $(INCLUDE) -c $*.c

clean:
	rm UsbCtrl.o LensCtrl.o LensAccess.o LensSetup.o LensInfo.o LensConnect.o


