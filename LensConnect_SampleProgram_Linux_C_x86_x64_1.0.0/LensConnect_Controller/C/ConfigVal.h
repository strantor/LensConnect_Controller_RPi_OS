#ifndef _ConfigVal_h
#define _ConfigVal_h 1

// LensConnect Parameters //
// for USB
#define VID 0x10C4	// USB VID
#define PID 0x8D08	// USB PID
#define I2CSLAVEADDR 0x20	// I2C SleveAddress(7bitAddress)

// for LensConnect Register bit
#define INIT_RUN_BIT    0x0001
#define NEED_INIT_BIT   0x0001
#define ZOOM_MASK       0x0002
#define FOCUS_MASK      0x0004
#define IRIS_MASK       0x0008
#define OPT_FILTER_MASK 0x0010

// for WaitCalc
#define OPT_FILTER_SPEED 1

// for Usb Add Error
#define LOWHI_ERROR 0x50 // Status Bit 0 -> 1 Error
#define HILOW_ERROR 0x51 // Status Bit 1 -> 0 Error

// for USB Read Length
#define LENSMODEL_LENGTH 24
#define USERAREA_LENGTH  32
#define LENSADDRESS_LENGTH 4
#define LENSCOUNT_LENGTH 4
#define SEGMENTOFFSET_LENGTH 2
#define DATA_LENGTH 2

// Status wait Time
#define LOW_HIGH_WAIT  20
#define WAIT_MAG     1100	// [ms]:1[s]=1000[ms]*1.1times :Status wait magnification
#define MINIMUM_WAIT 2000

// HidSmbus_SetTimeouts
#define RESPONSETIMEOUT 0 // 0 is Clock stretching

// for HidSmnus_ssetSmbusConfig
#define BITRATE 100000		// Default value 100KHz
#define AUTOREADRESPOND 0 	// 0 is false.
#define WRITETIMEOUT 1000	// [ms]
#define READTIMEOUT  1000	// [ms]
#define SCLLOWTIMEOUT 0		// [ms]
#define TRANSFARRETRIES 0	// [ms]

// for HidSmbus_SetGpioConfig
#define DIRECTION 0xFF	//HID_SMBUS_GPIO All Output(1) set
#define MODE 0x00	//HID_SMBUS_MODE All OpenDrain(0) set
#define SPECIAL 0x00	// GPIO7 Special function OFF(0)
#define CLKDIV 0xFF	// Not Use <if GPIO7 is ClkOut, 48MHz/(2*255)>

#endif // _ConfigVal_h
