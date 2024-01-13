/////////////////////////////////////////////////////////////////////////////
// SLABCP2112.h
// For SLABHIDtoSMBus.dll
// and Silicon Labs CP2112 HID to SMBus
/////////////////////////////////////////////////////////////////////////////
#ifndef HOST_LIB_SLABHIDSMBUS_INCLUDE_SLABCP2112_H_INCLUDED_QU4N7WC20W
#define HOST_LIB_SLABHIDSMBUS_INCLUDE_SLABCP2112_H_INCLUDED_QU4N7WC20W

/// @addtogroup slabhidsmbus CP2112 SMBus over HID interface Library
///
/// @{
/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "Types.h"
#include	"silabs_defs.h"
#include	"silabs_sal.h"

/////////////////////////////////////////////////////////////////////////////
// Tool-chain-dependent hacks
/////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HID_TO_SMBUS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HID_TO_SMBUS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#if defined(HID_TO_SMBUS_EXPORTS)
#define HID_TO_SMBUS_API
#else
#define HID_TO_SMBUS_API __declspec(dllimport)
#pragma comment(lib, "SLABHIDtoSMBus.lib")
#endif // defined(HID_TO_SMBUS_EXPORTS)
#else // !_WIN32
#define HID_TO_SMBUS_API
#define WINAPI
#endif // !_WIN32


/////////////////////////////////////////////////////////////////////////////
// Return Code Definitions
/////////////////////////////////////////////////////////////////////////////

// HID_SMBUS_STATUS
#if defined(NOT_YET)
typedef enum _HID_SMBUS_STATUS {
	HID_SMBUS_SUCCESS = SILABS_STATUS_SUCCESS			///< @ref SILABS_STATUS no error
	, HID_SMBUS_DEVICE_NOT_FOUND = 0x01					///< the specified device was not found
	, HID_SMBUS_INVALID_HANDLE = 0x02					///< an handle parameter was not valid
	, HID_SMBUS_INVALID_DEVICE_OBJECT = 0x03
	, HID_SMBUS_INVALID_PARAMETER = 0x04				///< a parameter was not valid
	, HID_SMBUS_INVALID_REQUEST_LENGTH = 0x05

	, HID_SMBUS_DEVICE_ALREADY_OPENED = SILABS_STATUS_DEVICE_ALREADY_OPENED	///< the specified device is already (exclusively) opened

	, HID_SMBUS_READ_ERROR = 0x10
	, HID_SMBUS_WRITE_ERROR = 0x11
	, HID_SMBUS_READ_TIMED_OUT = 0x12
	, HID_SMBUS_WRITE_TIMED_OUT = 0x13
	, HID_SMBUS_DEVICE_IO_FAILED = 0x14
	, HID_SMBUS_DEVICE_ACCESS_ERROR = 0x15
	, HID_SMBUS_DEVICE_NOT_SUPPORTED = 0x16

	, HID_SMBUS_UNKNOWN_ERROR = SILABS_STATUS_UNKNOWN_ERROR	///< an otherwise unclassified error occurred
} HID_SMBUS_STATUS, *PHID_SMBUS_STATUS;
#else // defined(NOT_YET)
typedef int HID_SMBUS_STATUS;

// HID_SMBUS_STATUS Return Codes
/// @defgroup  HID_SMBUS_STATUSReturnCodes  HID_SMBUS_STATUS Return Codes definitions
/// @{
#define HID_SMBUS_SUCCESS							SILABS_STATUS_SUCCESS	///< Success
#define	HID_SMBUS_DEVICE_NOT_FOUND					0x01					///< the specified device was not found
#define HID_SMBUS_INVALID_HANDLE					0x02					///< an handle parameter was not valid
#define	HID_SMBUS_INVALID_DEVICE_OBJECT				0x03					///< the device object pointer does not match the address of a valid HID - to - UART device
#define	HID_SMBUS_INVALID_PARAMETER					0x04					///< a parameter was not valid
#define	HID_SMBUS_INVALID_REQUEST_LENGTH			0x05					///< the specified number of bytes to read or write is invalid.

#define	HID_SMBUS_DEVICE_ALREADY_OPENED				SILABS_STATUS_DEVICE_ALREADY_OPENED	///< the specified device is already (exclusively) opened

#define	HID_SMBUS_READ_ERROR						0x10					///< the read was not successful and did not time out.
#define	HID_SMBUS_WRITE_ERROR						0x11					///< the write was not successful.
#define	HID_SMBUS_READ_TIMED_OUT					0x12					///< a read failed to return the number of bytes requested before the read timeout elapsed.
#define	HID_SMBUS_WRITE_TIMED_OUT					0x13					///< a write failed to complete sending the number of bytes requested before the write timeout elapsed.
#define	HID_SMBUS_DEVICE_IO_FAILED					0x14					///< host was unable to get or set a feature report.
#define HID_SMBUS_DEVICE_ACCESS_ERROR				0x15					///< the device or device property could not be accessed.Either the device is not opened, already opened when trying to open, or an error occurred when trying to get HID information.
#define HID_SMBUS_DEVICE_NOT_SUPPORTED				0x16					///< the current device does not support the corresponding action

#define HID_SMBUS_UNKNOWN_ERROR						SILABS_STATUS_UNKNOWN_ERROR					///< This value should never be returned.
/// @}
#endif // defined(NOT_YET)

// HID_SMBUS_TRANSFER_S0
typedef BYTE HID_SMBUS_S0;

/// @defgroup  HID_SMBUS_S0  HID_SMBUS_S0 definitions
/// @{
#define HID_SMBUS_S0_IDLE							0x00	///< No transfers are currently active on the bus.
#define HID_SMBUS_S0_BUSY							0x01	///< A read or write transfer is in progress.
#define HID_SMBUS_S0_COMPLETE						0x02	///< A read or write transfer completed without error and without retry.
#define HID_SMBUS_S0_ERROR							0x03	///< A read or write transfer completed with an error.
/// @}

// HID_SMBUS_TRANSFER_S1
typedef BYTE HID_SMBUS_S1;

// HID_SMBUS_TRANSFER_S0 = HID_SMBUS_S0_BUSY
/// @defgroup  HID_SMBUS_S1_BUSY  HID_SMBUS_S1_BUSY definitions
/// @{
#define HID_SMBUS_S1_BUSY_ADDRESS_ACKED				0x00	///< The slave address was acknowledged.
#define HID_SMBUS_S1_BUSY_ADDRESS_NACKED			0x01	///< The slave address has not been acknowledged.
#define HID_SMBUS_S1_BUSY_READING					0x02	///< Read data phase in progress.
#define HID_SMBUS_S1_BUSY_WRITING					0x03	///< Write data phase in progress.
/// @}

// HID_SMBUS_TRANSFER_S0 = HID_SMBUS_S0_ERROR
/// @defgroup  HID_SMBUS_S1_ERRORS  HID_SMBUS_S1_ERROR definitions
/// @{
#define HID_SMBUS_S1_ERROR_TIMEOUT_NACK				0x00	///< Tranfer timeout: SMBus slave address was NACKed
#define HID_SMBUS_S1_ERROR_TIMEOUT_BUS_NOT_FREE		0x01	///< Tranfser timeout: SMBus not free (or SCL low timeout occurred)
#define HID_SMBUS_S1_ERROR_ARB_LOST					0x02	///< Bus arbitration was lost
#define HID_SMBUS_S1_ERROR_READ_INCOMPLETE			0x03	///< Read was incomplete
#define HID_SMBUS_S1_ERROR_WRITE_INCOMPLETE			0x04	///< Write was incomplete
#define HID_SMBUS_S1_ERROR_SUCCESS_AFTER_RETRY		0x05	///< Transfer completed after numRetries number of retries
/// @}

/////////////////////////////////////////////////////////////////////////////
// String Definitions
/////////////////////////////////////////////////////////////////////////////

// Product String Types
/// @ref HidSmbus_GetString() and @ref HidSmbus_GetOpenedString() options values
typedef enum _HID_SMBUS_GETSTRING {
	HID_SMBUS_GET_VID_STR = 0x01	///< Vendor ID string
	, HID_SMBUS_GET_PID_STR = 0x02	///< Product ID string
	, HID_SMBUS_GET_PATH_STR = 0x03	///< Path string
	, HID_SMBUS_GET_SERIAL_STR = 0x04	///< Serial Number string
	, HID_SMBUS_GET_MANUFACTURER_STR = 0x05	///< Manufacturer string
	, HID_SMBUS_GET_PRODUCT_STR = 0x06	///< Product string
} HID_SMBUS_GETSTRING, *PHID_SMBUS_GETSTRING;
_Check_return_
_Success_(return == TRUE)
__inline static bool IsValidHID_SMBUS_GETSTRING(_In_ const HID_SMBUS_GETSTRING _s) { return (HID_SMBUS_GET_VID_STR == _s) || (HID_SMBUS_GET_PID_STR == _s) || (HID_SMBUS_GET_PATH_STR == _s) || (HID_SMBUS_GET_SERIAL_STR == _s) || (HID_SMBUS_GET_MANUFACTURER_STR == _s) || (HID_SMBUS_GET_PRODUCT_STR == _s); }

// String Lengths
#define HID_SMBUS_DEVICE_STRLEN						260

// HID_SMBUS_DEVICE_STR
typedef char HID_SMBUS_DEVICE_STR[HID_SMBUS_DEVICE_STRLEN];

/////////////////////////////////////////////////////////////////////////////
// SMBUS Definitions
/////////////////////////////////////////////////////////////////////////////

// SMbus Configuration Limits
/// @defgroup  SMbusConfigurationLimits  SMbus Configuration Limits definitions
/// @{
#define HID_SMBUS_MIN_BIT_RATE						1
#define HID_SMBUS_MIN_TIMEOUT						0
#define HID_SMBUS_MAX_TIMEOUT						1000
#define HID_SMBUS_MAX_RETRIES						1000
#define HID_SMBUS_MIN_ADDRESS						0x02
#define HID_SMBUS_MAX_ADDRESS						0xFE
/// @}

// Read/Write Limits
/// @defgroup  ReadWriteLimits  Read/Write Limits definitions
/// @{
#define HID_SMBUS_MIN_READ_REQUEST_SIZE				1
#define HID_SMBUS_MAX_READ_REQUEST_SIZE				512
#define HID_SMBUS_MIN_TARGET_ADDRESS_SIZE			1
#define HID_SMBUS_MAX_TARGET_ADDRESS_SIZE			16
#define HID_SMBUS_MAX_READ_RESPONSE_SIZE			61
#define HID_SMBUS_MIN_WRITE_REQUEST_SIZE			1
#define HID_SMBUS_MAX_WRITE_REQUEST_SIZE			61
/// @}

/////////////////////////////////////////////////////////////////////////////
// GPIO Definitions
/////////////////////////////////////////////////////////////////////////////

// GPIO Pin Direction Bit Value
/// @defgroup  GPIOPinDirectionBitValue  GPIO Pin Direction Bit Value definitions
/// @{
#define HID_SMBUS_DIRECTION_INPUT					0	///< 
#define HID_SMBUS_DIRECTION_OUTPUT					1	///< 
/// @}

// GPIO Pin Mode Bit Value
/// @defgroup  GPIOPinModeBitValue  GPIO Pin Mode Bit Value definitions
/// @{
#define HID_SMBUS_MODE_OPEN_DRAIN					0	///< Open-Drain
#define HID_SMBUS_MODE_PUSH_PULL					1	///< Push-Pull
/// @}

// GPIO Function Bitmask
/// @defgroup  GPIOFunctionBitmask  GPIO Function Bitmask definitions
/// @{
#define HID_SMBUS_MASK_FUNCTION_GPIO_7_CLK			0x01	///< Enables or disables the clock output function of GPIO.7
#define HID_SMBUS_MASK_FUNCTION_GPIO_0_TXT			0x02	///< Enables or disables the TX toggle function of GPIO.0
#define HID_SMBUS_MASK_FUNCTION_GPIO_1_RXT			0x04	///< Enables or disables the RX toggle function of GPIO.1
/// @}

// GPIO Function Bit Value
/// @defgroup  GPIOFunctionBitValue  GPIO Function Bit Value definitions
/// @{
#define HID_SMBUS_GPIO_FUNCTION						0	///< GPIO function as configured using direction and mode.
#define HID_SMBUS_SPECIAL_FUNCTION					1	///< Special function: GPIO.0 - TX Toggle (push - pull output) GPIO.1 - RX Toggle (push - pull output) GPIO.7 - Clock Output (push - pull output)
/// @}

// GPIO Pin Bitmask
/// @defgroup  GPIOPinBitmask  GPIO Pin Bitmask definitions
/// @{
#define HID_SMBUS_MASK_GPIO_0						0x01
#define HID_SMBUS_MASK_GPIO_1						0x02
#define HID_SMBUS_MASK_GPIO_2						0x04
#define HID_SMBUS_MASK_GPIO_3						0x08
#define HID_SMBUS_MASK_GPIO_4						0x10
#define HID_SMBUS_MASK_GPIO_5						0x20
#define HID_SMBUS_MASK_GPIO_6						0x40
#define HID_SMBUS_MASK_GPIO_7						0x80
/// @}

/////////////////////////////////////////////////////////////////////////////
// Part Number Definitions
/////////////////////////////////////////////////////////////////////////////

// Part Numbers
#define HID_SMBUS_PART_CP2112						CP210x_PARTNUM_CP2112

/////////////////////////////////////////////////////////////////////////////
// User Customization Definitions
/////////////////////////////////////////////////////////////////////////////

// User-Customizable Field Lock Bitmasks
/// @ref HidSmbus_SetLock() and @ref HidSmbus_GetLock() options values
typedef enum _HID_SMBUS_LOCKBITS {
	HID_SMBUS_LOCK_VID = ((BYTE)(0xFF & 0x01))					///< VID
	, HID_SMBUS_LOCK_PID = ((BYTE)(0xFF & 0x02))				///< PID
	, HID_SMBUS_LOCK_POWER = ((BYTE)(0xFF & 0x04))				///< Power
	, HID_SMBUS_LOCK_POWER_MODE = ((BYTE)(0xFF & 0x08))			///< Power Mode
	, HID_SMBUS_LOCK_RELEASE_VERSION = ((BYTE)(0xFF & 0x10))	///< Release Version
	, HID_SMBUS_LOCK_MFG_STR = ((BYTE)(0xFF & 0x20))			///< Manufacturing String
	, HID_SMBUS_LOCK_PRODUCT_STR = ((BYTE)(0xFF & 0x40))		///< Product String
	, HID_SMBUS_LOCK_SERIAL_STR = ((BYTE)(0xFF & 0x80))			///< Serial String
} HID_SMBUS_LOCKBITS, *PHID_SMBUS_LOCKBITS;
_Check_return_
_Success_(return == TRUE)
__inline static bool IsValidHID_SMBUS_HID_SMBUS_LOCKBITS(_In_ const HID_SMBUS_LOCKBITS _s)
{
	return (HID_SMBUS_LOCK_VID == _s) || (HID_SMBUS_LOCK_PID == _s)
		|| (HID_SMBUS_LOCK_POWER == _s) || (HID_SMBUS_LOCK_POWER_MODE == _s)
		|| (HID_SMBUS_LOCK_RELEASE_VERSION == _s)
		|| (HID_SMBUS_LOCK_MFG_STR == _s) || (HID_SMBUS_LOCK_PRODUCT_STR == _s) || (HID_SMBUS_LOCK_SERIAL_STR == _s);
}

// Field Lock Bit Values
/// @defgroup  FieldLockBitValues  Field Lock Bit Values definitions
/// @{
#define HID_SMBUS_LOCK_UNLOCKED						1	///< Field can be customized. If the bit is set to 1, the corresponding field HAS NOT been customized
#define HID_SMBUS_LOCK_LOCKED						0	///< Field has already been customized, or has been locked. If the bit is set to 0, the corresponding field HAS been customized or locked, and can no longer be changed for this device
/// @}

// Power Max Value (500 mA)
#define HID_SMBUS_BUS_POWER_MAX						0xFA	///< maximum power of 500mA, represented as a milliamps/2, I.e. 250 IFF bus-powered

// Power Modes
/// @defgroup  PowerModes  Power Modes definitions
/// @{
#define HID_SMBUS_BUS_POWER							0x00	///< Device is bus powered
#define HID_SMBUS_SELF_POWER_VREG_DIS				0x01	///< Device is self powered (voltage regulator disabled)
#define HID_SMBUS_SELF_POWER_VREG_EN				0x02	///< Device is self powered (voltage regulator enabled)
/// @}

// USB Config Bitmasks
/// @defgroup USBConfigBitmasks USB Config Bitmasks definitions
/// @{
#define HID_SMBUS_SET_VID							0x01	///< VID
#define HID_SMBUS_SET_PID							0x02	///< PID
#define HID_SMBUS_SET_POWER							0x04	///< Power
#define HID_SMBUS_SET_POWER_MODE					0x08	///< Power Mode
#define HID_SMBUS_SET_RELEASE_VERSION				0x10	///< Release Version
/// @}

// USB Config Bit Values
/// @defgroup USBConfigBitValues USB Config Bit Values definitions
/// @{
#define HID_SMBUS_SET_IGNORE						0
#define HID_SMBUS_SET_PROGRAM						1
/// @}

// String Lengths
/// @defgroup CP2112StringLengths String Lengths definitions
/// @{
#define HID_SMBUS_CP2112_MFG_STRLEN					30
#define HID_SMBUS_CP2112_PRODUCT_STRLEN				30
#define HID_SMBUS_CP2112_SERIAL_STRLEN				30
/// @}

// HID_SMBUS_MFG_STR
typedef char HID_SMBUS_CP2112_MFG_STR[HID_SMBUS_CP2112_MFG_STRLEN];

// HID_SMBUS_PRODUCT_STR
typedef char HID_SMBUS_CP2112_PRODUCT_STR[HID_SMBUS_CP2112_PRODUCT_STRLEN];

// HID_SMBUS_SERIAL_STR
typedef char HID_SMBUS_CP2112_SERIAL_STR[HID_SMBUS_CP2112_SERIAL_STRLEN];

/////////////////////////////////////////////////////////////////////////////
// Typedefs
/////////////////////////////////////////////////////////////////////////////

typedef void* HID_SMBUS_DEVICE;

/////////////////////////////////////////////////////////////////////////////
// Exported Library Functions
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// HidSmbus_GetNumDevices
/// @brief Determines the number of devices connected to the system with matching VID/PID
///
/// @param[out] lpdwNumDevices a pointer to a DWORD/4-byte location to hold the returned device count
/// @param[in] vid is the 2-byte Vendor ID value, filter device results by this Vendor ID.
/// @param[in] pid is the 2-byte Product ID value, filter device results by this Product ID.
///
/// @note If both vid and pid are set to 0x0000, then HID devices will not be filtered by VID/PID.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- lpdwNumDevices was not specified, or is an unexpected value
	HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetNumDevices(_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ DWORD* lpdwNumDevices, _In_ _Pre_defensive_ const WORD vid, _In_ _Pre_defensive_ const WORD pid);

// HidSmbus_GetString
/// @brief This function returns a null-terminated vendor ID string, product ID string, serial number string, device path
/// string, manufacturer string, or product string for the device specified by an index passed in deviceNum.
/// 
/// @detail The index for the first device is 0 and the last device is the value returned by @ref HidUart_GetNumDevices() - 1.
///
/// @param[in] deviceNum Index of the device for which the string is desired.
/// @param[in] vid is the 2-byte Vendor ID value, filter device results by this Vendor ID.
/// @param[in] pid is the 2-byte Product ID value, filter device results by this Product ID.
/// @param[out] deviceString - Variable of type @ref HID_SMBUS_DEVICE_STR which will contain a NULL terminated
/// ASCII device string on return. The string is 260 bytes on Windows and 512 bytes on macos and Linux.
/// @param[in] options - Determines if deviceString contains a vendor ID string, product ID string, serial number string,
/// device path string, manufacturer string, or product string. See @ref HID_SMBUS_GETSTRING
///
/// @note If both @ref vid and @ref pid are set to 0x0000, then HID devices will not be filtered by VID/PID.
///
/// @note BUG: This is an string-UNSAFE function, not defensive against a "too small" buffer provided as the @ref deviceString parameter.
///
/// @note Intended for use pre- @ref HidSmbus_Open() or post- @ref HidSmbus_Close(). Fails with #HID_SMBUS_DEVICE_ALREADY_OPENED otherwise.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- deviceString was not specified, and/or options is an unexpected value
///	@retval	#HID_SMBUS_DEVICE_NOT_FOUND -- the specified device was not found
///	@retval	#HID_SMBUS_DEVICE_ALREADY_OPENED -- the specified device is already (exclusively) opened
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetString(_In_ _Pre_defensive_ const DWORD deviceNum, _In_ _Pre_defensive_ const WORD vid, _In_ _Pre_defensive_ const WORD pid, _Out_ _Pre_defensive_ char* deviceString, _In_ _Pre_defensive_ const HID_SMBUS_GETSTRING options);

// HidSmbus_GetOpenedString
/// @brief This function returns a null-terminated vendor ID string, product ID string, serial number string, device path
/// string, manufacturer string, or product string for the device specified by device.
///
/// @param[in] device is the Device object pointer as returned by @ref HidSmbus_Open().
/// @param[out] deviceString - Variable of type @ref HID_SMBUS_DEVICE_STR which will contain a NULL terminated
/// ASCII device string on return. The string is 260 bytes on Windows and 512 bytes on macos
/// and Linux.
/// @param[in] options - Determines if deviceString contains a vendor ID string, product ID string, serial number string,
/// device path string, manufacturer string, or product string. See @ref HID_SMBUS_GETSTRING
///
/// @note BUG: This is an string-UNSAFE function, not defensive against a "too small" buffer provided as the @ref deviceString parameter.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- deviceString was not specified, and/or options is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetOpenedString(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, char* deviceString, _In_ _Pre_defensive_ const HID_SMBUS_GETSTRING options);

// HidSmbus_GetIndexedString
/// @brief This function returns a null-terminated USB string descriptor for the device specified by an index
/// passed in deviceNum. (Windows/Linux only)
///
/// @param[in] deviceNum Index of the device for which the string is desired.
/// @param[in] vid is the 2-byte Vendor ID value, filter device results by this Vendor ID.
/// @param[in] pid is the 2-byte Product ID value, filter device results by this Product ID.
/// @param[in] stringIndex - Specifies the device-specific index of the USB string descriptor to return.
/// @param[out] deviceString - Variable of type @ref HID_SMBUS_DEVICE_STR which will contain a NULL terminated
/// device descriptor string on return. The string is 260 bytes on Windows and 512 bytes on Linux.
///
/// @note If both vid and pid are set to 0x0000, then HID devices will not be filtered by VID/PID.
///
/// @note BUG: This is an string-UNSAFE function, not defensive against a "too small" buffer provided as the @ref deviceString parameter.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- deviceString was not specified, and/or options is an unexpected value
///	@retval	#HID_SMBUS_DEVICE_NOT_FOUND -- the specified device was not found
///	@retval	#HID_SMBUS_DEVICE_ALREADY_OPENED -- the specified device is already (exclusively) opened
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetIndexedString(_In_ _Pre_defensive_ const DWORD deviceNum, _In_ _Pre_defensive_ const WORD vid, _In_ _Pre_defensive_ const WORD pid, _In_ _Pre_defensive_ const DWORD stringIndex, char* deviceString);

// HidSmbus_GetOpenedIndexedString
/// @brief This function returns a null-terminated USB string descriptor for the device specified by device. (Windows/Linux only)
///
/// @param[in] device is the Device object pointer as returned by @ref HidSmbus_Open().
/// @param[in] stringIndex - Specifies the device-specific index of the USB string descriptor to return.
/// @param[out] deviceString - Variable of type @ref HID_SMBUS_DEVICE_STR which will contain a NULL terminated
/// device descriptor string on return. The string is 260 bytes on Windows and 512 bytes on Linux.
///
/// @note BUG: This is an string-UNSAFE function, not defensive against a "too small" buffer provided as the @ref deviceString parameter.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- deviceString is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetOpenedIndexedString(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _In_ _Pre_defensive_ const DWORD stringIndex, char* deviceString);

// HidSmbus_GetAttributes
/// @brief This function returns the device vendor ID, product ID, and device release number for the device specified
/// by an index passed in deviceNum.
///
/// @param[in] deviceNum Index of the device for which the string is desired.
/// @param[in] vid is the 2-byte Vendor ID value, filter device results by this Vendor ID.
/// @param[in] pid is the 2-byte Product ID value, filter device results by this Product ID.
/// @param[out] deviceVid - returns the 2-byte Vendor ID value from the device.
/// @param[out] devicePid - returns the 2-byte Product ID value from the device.
/// @param[out] pDeviceReleaseNumber points at a 2-byte buffer into which the USB device bcdVersion, or device release number, value will be written
///
/// @note If both vid and pid are zero (0x0000), devices will NOT be filtered by vid/pid.
///
/// @note A successfully returned pDeviceReleaseNumber is in binary-coded decimal (BCD).
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- -- deviceVid, devicePid and/or pDeviceReleaseNumber is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetAttributes(_In_ _Pre_defensive_ const DWORD deviceNum, _In_ _Pre_defensive_ const WORD vid, _In_ _Pre_defensive_ const WORD pid, _Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* deviceVid, _Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* devicePid, _Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* deviceReleaseNumber);

// HidSmbus_GetOpenedAttributes
/// @brief This function returns the device vendor ID, product ID, and device release number for the opened device.
///
/// @param[in] device is the Device object pointer as returned by @ref HidSmbus_Open().
/// @param[out] pDeviceVid - returns the 2-byte Vendor ID value from the device.
/// @param[out] pDevicePid - returns the 2-byte Product ID value from the device.
/// @param[out] pDeviceReleaseNumber points at a 2-byte buffer into which the USB device bcdVersion, or device release number, value will be written
///
/// @note A successfully returned @ref pDeviceReleaseNumber is in binary-coded decimal (BCD).
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- deviceString was not specified, and/or options is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetOpenedAttributes(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* deviceVid, _Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* devicePid, _Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* deviceReleaseNumber);

// HidSmbus_Open
/// @brief Opens a device using a device number between 0 and @ref HidSmbus_GetNumDevices() - 1, enables the
/// UART, and returns a device object pointer which will be used for subsequent accesses.
///
/// @param[out] pdevice - Returns a pointer to a HID-to-SMBUS device object for subsequent accesses to the device.
/// @param[in] deviceNum - Zero-based device index, between 0 and (@ref HidSmbus_GetNumDevices() - 1).
/// @param[in] vid is the 2-byte Vendor ID value, filter device results by this Vendor ID.
/// @param[in] pid is the 2-byte Product ID value, filter device results by this Product ID.
///
/// @note If both @ref vid and @ref pid are zero (0x0000), devices will NOT be filtered by @ref vid/@ref pid.
///
/// @note Be careful when opening a device. Any HID device may be opened by this library. However, if the
/// device is not actually a CP211x, use of this library will cause undesirable results. The best course of
/// action would be to designate a unique VID/PID for CP211x devices only. The application should then
/// filter devices using this VID/PID.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_DEVICE_NOT_FOUND -- deviceNum is an unexpected value
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- Could not access device (i.e. already opened?)
///	@retval	#HID_SMBUS_DEVICE_NOT_SUPPORTED -- Per device's PartNum only support CP2110 and CP2114 devices
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- pdevice is an unexpected value
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_Open(_Out_writes_bytes_(sizeof(HID_SMBUS_DEVICE*)) _Pre_defensive_ HID_SMBUS_DEVICE* pdevice, _In_ _Pre_defensive_ const DWORD deviceNum, _In_ _Pre_defensive_ const WORD vid, _In_ _Pre_defensive_ const WORD pid);

// HidSmbus_Close
/// @brief Closes an opened device using the device object pointer provided by @ref HidUart_Open().
///
/// @param[in] device is the Device object pointer as returned by @ref HidSmbus_Open().
///
/// @note The device parameter is invalid after calling @ref HidSmbus_Close(). Set device to NULL after calling @ref HidSmbus_Close().
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- device is not a valid, recognized Device object
///	@retval	#HID_SMBUS_INVALID_HANDLE -- failed, the device specified by device does not have a valid handle
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_Close(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device);

// HidSmbus_IsOpened
/// @brief Returns the device opened status.
///
/// @param[in] device is the Device object pointer as returned by @ref HidSmbus_Open().
/// @param[out] pbIsOpened points to a buffer into which a Boolean flag where TRUE means the device object pointer is valid and the device has been opened using @ref HidSmbus_Open(), and FALSE means it has not will be written
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- device is not a valid, recognized Device object
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- pbIsOpened is an unexpected value
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_IsOpened(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _Out_writes_bytes_(sizeof(BOOL)) _Pre_defensive_ BOOL* bIsOpened);

// HidSmbus_ReadRequest
/// @brief intiates a read transfer to the specified slave device address.
///
/// Read and write timeouts as well as transfer retries can be set using @ref HidSmbus_SetSmbusConfig().
///
/// HidSmbus_ReadRequest() initiates a read transfer. SMBus is a half-duplex bus, which means that
/// only one read, address read, or write transfer can be active at a time.The device will attempt to read
/// up to transferRetries number of times and for readTimeout milliseconds before timing out.
/// See HidSmbus_SetSmbusConfig() for more information on configuring read timeouts. If the autoReadRespond
/// setting is enabled, then call @ref HidSmbus_GetReadResponse() to return the results of the read transfer.
/// 
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in] slaveAddress the address of the slave device to read from. This value must be between
/// 0x02–0xFE. The least significant bit is the read / write bit for the SMBus transaction and must be 0.
/// @param[in]  numBytesToRead is the number of bytes to read from the device (1–512).
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- slaveAddress and/or numBytesToRead is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_ReadRequest(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _In_range_(0x02,0xFE) _Pre_defensive_ const BYTE slaveAddress, _In_range_(1, 512) _Pre_defensive_ const WORD numBytesToRead);

// HidSmbus_AddressReadRequest
/// @brief intiates a read transfer to the specified slave device address and specifies the address
/// to read from on the device. Read and write timeouts as well as transfer retries can be set using
/// @ref HidSmbus_SetSmbusConfig()
///
/// HidSmbus_AddressReadRequest() initiates a read transfer. SMBus is a half-duplex bus which
/// means that only one read, address read, or write transfer can be active at a time. The device will attempt
/// to read up to transferRetries number of times and for readTimeout milliseconds before timing
/// out. See @ref HidSmbus_SetSmbusConfig() for more information on configuring read timeouts. If the
/// autoReadRespond setting is enabled, then call @ref HidSmbus_GetReadResponse() to return the results of
/// the read transfer. The device will transmit the target address on the bus after the slave device has
/// acknowledged its address. This function is designed to read from EEPROMs with an SMBus interface.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in] slaveAddress the address of the slave device to read from. This value must be between
/// 0x02–0xFE. The least significant bit is the read / write bit for the SMBus transaction and must be 0.
/// @param[in]  numBytesToRead is the number of bytes to read from the device (1–512).
/// @param[in]  targetAddressSize is the size of the target address in bytes (1-16).
/// @param[in]  targetAddress is the address to read from the slave device.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- slaveAddress and/or numBytesToRead and/or targetAddressSize and/or targetAddress is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_AddressReadRequest(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _In_range_(0x02, 0xFE)  _Pre_defensive_ const BYTE slaveAddress, _In_range_(1, 512) _Pre_defensive_ const WORD numBytesToRead, _In_range_(1, 16) _Pre_defensive_ const BYTE targetAddressSize, BYTE targetAddress[16]);

// HidSmbus_ForceReadResponse
/// @brief cause the device to send a read response to the host after a read transfer has been issued.
///
/// HidSmbus_ForceReadResponse() should only be called if autoReadRespond is disabled using
/// @ref HidSmbus_SetSmbusConfig(). This allows the user to read data in a polled mode. Call
/// @ref HidSmbus_ReadRequest() or @ref HidSmbus_AddressReadRequest() first. Next, call @ref HidSmbus_TransferStatusRequest()
/// and @ref HidSmbus_TransferStatusResponse() to check if the device has received data. Next, call HidSmbus_ForceReadResponse().
/// Finally, call @ref HidSmbus_GetReadResponse() repeatedly until all read
/// data is returned.
///
/// @note Typically, this procedure is not necessary as users should enable the autoReadRespond setting.
/// 
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in]  numBytesToRead is the number of bytes to read from the device (1–512).
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- numBytesToRead is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_ForceReadResponse(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _In_range_(1, 512) _Pre_defensive_ const WORD numBytesToRead);

// HidSmbus_GetReadResponse
/// @brief returns the read response to a read request. Read and write timeouts as well as transfer
/// retries can be set using HidSmbus_SetSmbusConfig()
///
/// HidSmbus_GetReadResponse() waits for up to readTimeout milliseconds for the device to send a
/// read response interrupt report to the host. This function should be called repeatedly until all read data
/// has been received or an error occurs. Call @ref HidSmbus_ReadRequest() or @ref HidSmbus_AddressReadRequest()
/// followed by HidSmbus_GetReadResponse() to read data when autoReadResponse is enabled
/// using @ref HidSmbus_SetSmbusConfig(). HidSmbus_GetReadResponse() will wait for up to
/// responseTimeout milliseconds before returning @ref HID_SMBUS_READ_TIMED_OUT.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out] status  points at a 1-byte buffer into which the status of the read request will be copied and returned. See @ref HID_SMBUS_S0.
/// @param[out] buffer - returns up to 61 read data bytes.
/// @param[in] bufferSize—is the size of buffer and must be at least 61 bytes.
/// @param[out] numBytesRead—returns the number of valid data bytes returned in buffer.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- status and/or buffer and/or buffersize and/or numBytesRead is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetReadResponse(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_Out_writes_bytes_(sizeof(HID_SMBUS_S0)) _Pre_defensive_ HID_SMBUS_S0* status,
	_Out_writes_bytes_(sizeof(bufferSize)) _Pre_defensive_ BYTE* buffer,
	_In_ _Pre_defensive_ const BYTE bufferSize,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* numBytesRead
);

// HidSmbus_WriteRequest
/// @brief writes the specified number of bytes from the supplied buffer to the specified slave device
/// and returns immediately after sending the request to the CP2112.
///
/// Read and write timeouts can be set using @ref HidSmbus_SetTimeouts().
///
/// Call @ref HidSmbus_TransferStatusRequest() / @ref HidSmbus_GetTransferStatusResponse() to wait for
/// the write transfer to complete before issuing another transfer request. The device waits for up to
/// transferRetries number of retries and writeTimeout number of milliseconds before timing out.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in] slaveAddress the address of the slave device to write to. This value must be between
/// 0x02–0xFE. The least significant bit is the read / write bit for the SMBus transaction and must be 0.
/// @param[in]  buffer—is the address of a buffer to be sent to the device.
/// @param[in]  numBytesToWrite is the number of bytes to write to the device (1–61). This value must be less
/// than or equal to the size of buffer.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- slaveAddress and/or buffer and/or numBytesToWrite is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_WriteRequest(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_In_range_(0x02, 0xFE) _Pre_defensive_ const BYTE slaveAddress,
	_In_reads_bytes_(numBytesToWrite) _Pre_defensive_ BYTE* buffer,
	_In_range_(1, 61)   _Pre_defensive_ const BYTE numBytesToWrite
);

// HidSmbus_TransferStatusRequest
/// @brief requests the status of the current read or write transfer.
///
/// Call HidSmbus_TransferStatusRequest() followed by @ref HidSmbus_GetTransferStatusResponse()
/// to get the status of the current read or write transfer.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_TransferStatusRequest(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device);

// HidSmbus_GetTransferStatusResponse
/// @brief returns the status of the current read or write transfer.
///
/// Call @ref HidSmbus_TransferStatusRequest() followed by HidSmbus_GetTransferStatusResponse()
/// to get the status of the current read or write transfer. HidSmbus_GetTransferStatusResponse() will
/// wait for up to responseTimeout milliseconds before returning @ref HID_SMBUS_READ_TIMED_OUT.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out] status  points at a 1-byte buffer into which the status of the read or write request will be copied and returned. See @ref HID_SMBUS_S0.
/// @param[out] detailedStatus  points at a 1-byte buffer into which the extended status of the read or write request will be copied and returned. See @ref HID_SMBUS_S1.
/// @param[out]  numRetries points at a 2-byte buffer into which the tbd will be copied and returned.
/// @param[out]  bytesRead points at a 2-byte buffer into which the tbd will be copied and returned.
///
/// When status of @ref HID_SMBUS_S0_IDLE is returned, for detailedStatus see @ref TBD.
/// When status of @ref HID_SMBUS_S0_BUSY is returned, for detailedStatus see @ref HID_SMBUS_S1_BUSY.
/// When status of @ref HID_SMBUS_S0_ERROR is returned, for detailedStatus see @ref HID_SMBUS_S1_ERRORS.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- status and/or detailedStatus and/or numRetries and/or bytesRead is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetTransferStatusResponse(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_Out_writes_bytes_(sizeof(HID_SMBUS_S0)) _Pre_defensive_ HID_SMBUS_S0* status,
	_Out_writes_bytes_(sizeof(HID_SMBUS_S1)) _Pre_defensive_ HID_SMBUS_S1* detailedStatus,
	_Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* numRetries,
	_Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* bytesRead
);

// HidSmbus_CancelTransfer
/// @brief cancels the current read or write transfer.
///
/// This function will clear any read responses received.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_CancelTransfer(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device);

// HidSmbus_CancelIo
/// @brief This function cancels any pending HID reads and writes (Windows Only).
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_CancelIo(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device);

// HidSmbus_SetTimeouts
/// @brief Sets the response timeouts.
///
/// Response timeouts are used by @ref HidSmbus_GetReadResponse() and @ref HidSmbus_GetTransferStatusResponse().
/// The default value for response timeouts is 1000ms, but timeouts can be set to wait for any number of
/// milliseconds between 1 and 0xFFFFFFFF. Specifying a response timeout of 0, will wait indefinitely.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in]  responseTimeout is the 4-byte response timeout.
///
/// @note If timeouts are set to a large value and no data is received, the application may appear unresponsive.
/// It is recommended to set timeouts appropriately before using the device. Typically, users will want to
/// specify a response timeout that is greater than the read and write timeouts.
///
/// @note Timeouts are maintained for each device but are not persistent across @ref HidSmbus_Open()/@ref HidSmbus_Close().
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_SetTimeouts(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _In_ _Pre_defensive_ const DWORD responseTimeout);

// HidSmbus_GetTimeouts
/// @brief returns the current response timeouts specified in milliseconds.
///
/// A response timeout value of 0 indicates an infinite timeout.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out]  responseTimeout points at a 4-byte buffer into which the response timeout will be copied and returned.
///
/// @note Timeouts are maintained for each device but are not persistent across @ref HidSmbus_Open()/@ref HidSmbus_Close().
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- responseTimeout is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetTimeouts(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ DWORD* responseTimeout);

// HidSmbus_SetSmbusConfig
/// @brief sets the SMBus bit rate, address, and transfer settings such as timeouts and retries.
/// 
/// Refer to the device data sheet for a list of supported configuration settings.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in]  bitRate is the 4-byte bit rate for SMBus communication. The default is 100 kHz. This value must be non-zero.
/// @param[in]  address is the 1-byte device’s slave address (0x02–0xFE) address. The device will only acknowledge
/// this address. The default is 0x02. The least significant bit is the read/write bit for the SMBus
/// transaction and must be 0.
/// @param[in]  autoReadRespond is the 4-byte boolean value that controls the read response behavior of the device. If enabled, the device will
/// automatically send read response interrupt reports to the device after initiating a read transfer. If
/// disabled, the user must call @ref HidSmbus_ForceReadResponse() before read response interrupt reports
/// will be sent to the host. The default is FALSE(0).
/// @param[in]  writeTimeout is the 2-byte time limit in milliseconds (0–1000) before the device will automatically
/// cancel a write transfer. A value of 0 indicates an infinite timeout. In this case, a write transfer will
/// wait indefinitely for a write to complete or until @ref HidSmbus_CancelTransfer() is called. The default
/// is 0.
/// @param[in]  readTimeout is the 2-byte time limit in milliseconds (0 - 1000) before the device will automatically
/// cancel a read transfer. A value of 0 indicates an infinite timeout. In this case, a read transfer will
/// wait indefinitely for a read to complete or until @ref HidSmbus_CancelTransfer() is called. The default
/// is 0.
/// @param[in]  sclLowTimeout is the 4-byte timeout that will reset the SMBus if the SCL line is held low for more than
/// 25ms. If enabled and an SCL Low Timeout occurs, the status byte of the Transfer Status Response
/// command will be set appropriately. The default is FALSE(0).
/// @param[in]  transferRetries is the 2-byte number of times to retry (0 - 1000) a failed read or write transfer. A
/// value of 0 indicates an infinite number of retries until the specified read or write timeout has
/// elapsed. The default is 0.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- bitRate and/or address and/or autoReadRespond and/or writeTimeout and/or readTimeout and/or sclLowTimeout and/or transferRetries is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_SetSmbusConfig(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_In_ _Pre_defensive_ const DWORD bitRate,
	_In_range_(HID_SMBUS_MIN_ADDRESS, HID_SMBUS_MAX_ADDRESS) _Pre_defensive_ const BYTE address,
	_In_ _Pre_defensive_ const BOOL autoReadRespond,
	_In_range_(HID_SMBUS_MIN_TIMEOUT, HID_SMBUS_MAX_TIMEOUT) _Pre_defensive_ const WORD writeTimeout,
	_In_range_(HID_SMBUS_MIN_TIMEOUT, HID_SMBUS_MAX_TIMEOUT) _Pre_defensive_ const WORD readTimeout,
	_In_ _Pre_defensive_ const BOOL sclLowTimeout,
	_In_range_(0, HID_SMBUS_MAX_RETRIES) _Pre_defensive_ const WORD transferRetries
);

// HidSmbus_GetSmbusConfig
/// @brief gets the SMBus bit rate, address, and transfer settings such as timeouts and retries.
///
/// Refer to the device data sheet for a list of supported configuration settings.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out]  bitRate returns the 4-byte bit rate for SMBus communication. The default is 100 kHz. This value must be non-zero.
/// @param[out]  address returns the 1-byte device’s slave address (0x02–0xFE) address. The device will only acknowledge
/// this address. The default is 0x02. The least significant bit is the read/write bit for the SMBus
/// transaction and must be 0.
/// @param[out]  autoReadRespond returns the 4-byte boolean value that controls the read response behavior of the device. If enabled, the device will
/// automatically send read response interrupt reports to the device after initiating a read transfer. If
/// disabled, the user must call @ref HidSmbus_ForceReadResponse() before read response interrupt reports
/// will be sent to the host. The default is FALSE(0).
/// @param[out]  writeTimeout returns the 2-byte time limit in milliseconds (0–1000) before the device will automatically
/// cancel a write transfer. A value of 0 indicates an infinite timeout. In this case, a write transfer will
/// wait indefinitely for a write to complete or until @ref HidSmbus_CancelTransfer() is called. The default
/// is 0.
/// @param[out]  readTimeout returns the 2-byte time limit in milliseconds (0 - 1000) before the device will automatically
/// cancel a read transfer. A value of 0 indicates an infinite timeout. In this case, a read transfer will
/// wait indefinitely for a read to complete or until @ref HidSmbus_CancelTransfer() is called. The default
/// is 0.
/// @param[out]  sclLowTimeout returns the 4-byte timeout that will reset the SMBus if the SCL line is held low for more than
/// 25ms. If enabled and an SCL Low Timeout occurs, the status byte of the Transfer Status Response
/// command will be set appropriately. The default is FALSE(0).
/// @param[out]  transferRetries returns the 2-byte number of times to retry (0 - 1000) a failed read or write transfer. A
/// value of 0 indicates an infinite number of retries until the specified read or write timeout has
/// elapsed. The default is 0.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- bitRate and/or address and/or autoReadRespond and/or writeTimeout and/or readTimeout and/or sclLowTimeout and/or transferRetries is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetSmbusConfig(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ DWORD* bitRate,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* address,
	_Out_writes_bytes_(sizeof(BOOL)) _Pre_defensive_ BOOL* autoReadRespond,
	_Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* writeTimeout,
	_Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* readTimeout,
	_Out_writes_bytes_(sizeof(BOOL)) _Pre_defensive_ BOOL* sclLowtimeout,
	_Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* transferRetries
);

// HidSmbus_Reset
/// @brief initiates a full device reset. All configuration settings will be reset to their default values
/// after the device re-enumerates.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
///
/// @note Resetting the device will make the device handle stale. Users must close the device using the old
/// handle before proceeding to reconnect to the device. See more information on surprise removal.
/// See @ref HidSmbus_SetSmbusConfig() and @ref HidSmbus_SetGpioConfig() for default configuration settings.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_Reset(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device);

// HidSmbus_SetGpioConfig
/// @brief configures the GPIO pins’ directions and modes.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in]  direction is the 1-byte bitmask that specifies each GPIO pin’s direction. See @ref GPIOPinDirectionBitValue.
/// @param[in]  mode is the 1-byte bitmask that specifies each GPIO pin’s mode. See @ref GPIOPinModeBitValue.
/// @param[in]  function is the 1-byte bitmask that specifies the special behavior of GPIO.0, GPIO.1, and GPIO.7. See @ref GPIOFunctionBitmask.
/// @param[in]  clkDiv is the 1-byte clock output divider value used for GPIO.7 when configured in clock output
/// mode. The frequency is equal to 48 MHz / (2 x clkDiv) when clkDiv is between 1 and 255 and
/// equal to 48 MHz when clkDiv is 0.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- direction and/or mode and/or function and/or clkDiv is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_SetGpioConfig(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_In_ _Pre_defensive_ const BYTE direction,
	_In_ _Pre_defensive_ const BYTE mode,
	_In_ _Pre_defensive_ const BYTE function,
	_In_ _Pre_defensive_ const BYTE clkDiv
);

// HidSmbus_GetGpioConfig
/// @brief returns the GPIO pins’ directions and modes.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out]  direction returns  the 1-byte bitmask that specifies each GPIO pin’s direction. See @ref GPIOPinDirectionBitValue.
/// @param[out]  mode returns the 1-byte bitmask that specifies each GPIO pin’s mode. See @ref GPIOPinModeBitValue.
/// @param[out]  function returns the 1-byte bitmask that specifies the special behavior of GPIO.0, GPIO.1, and GPIO.7. See @ref GPIOFunctionBitmask.
/// @param[out]  clkDiv returns the 1-byte clock output divider value used for GPIO.7 when configured in clock output
/// mode. The frequency is equal to 48 MHz / (2 x clkDiv) when clkDiv is between 1 and 255 and
/// equal to 48 MHz when clkDiv is 0.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- direction and/or mode and/or function and/or clkDiv is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetGpioConfig(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* direction,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* mode,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* function,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* clkDiv
);

// HidSmbus_ReadLatch
/// @brief returns the current GPIO latch value.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out] latchValue points at a buffer into which the current GPIO latch value will be copied and returned
///
/// If a pin is configured as an input, then the latchValue bit represents the logical voltage level received
/// on the pin. If a pin is configured as an output, then the latchValue bit represents the logical
/// voltage level driven on the pin.
/// 
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- latchValue is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_ReadLatch(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* latchValue);

// HidSmbus_WriteLatch
/// @brief sets the current GPIO latch value for the specified bits.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in]  options is the 1-byte output value to drive on GPIO pins configured as outputs. See @ref GPIOPinBitmask.
/// @param[in]  options is the 1-byte bitmask specifying which bits to modify.
///
/// @note Only GPIO pins configured as outputs with their corresponding latchMask bits set can be written to.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- deviceString was not specified, and/or options is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_WriteLatch(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_In_ _Pre_defensive_ const BYTE latchValue,
	_In_ _Pre_defensive_ const BYTE latchMask
);

// HidSmbus_GetPartNumber
/// @brief retrieves the part number and version of the CP2112 device.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out] partNumber points at a byte-sized buffer into which the Part Number value will be written. See @ref HID_SMBUS_PART_CP2112.
/// @param[out] version points at a byte-sized buffer into which the part's Version value will be written
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, another @ref HID_SMBUS_STATUS if there is an error:
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- device is invalid
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- partNumber or version is an unexpected value
///	@retval	#HID_SMBUS_DEVICE_IO_FAILED -- the device failed to respond to I/O in any expected manner
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetPartNumber(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* partNumber,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* version
);

// HidSmbus_GetLibraryVersion
/// @brief Reads and returns the HID USB-to-SMBus Interface Library version
///
/// @param[out] major points at a byte-sized buffer into which the major number part of the DLL Version will be written
/// @param[out] minor points at a byte-sized buffer into which the minor number part of the DLL Version will be written
/// @param[out] bIsRelease points at a BOOL-sized buffer into which a True/False indication of whether the DLL is a Release-build or not (Debug-build) will be written
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, another @ref HID_SMBUS_STATUS if there is an error:
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- major or minor or bIsRelease is an unexpected value
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetLibraryVersion(_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* major, _Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* minor, _Out_writes_bytes_(sizeof(BOOL)) _Pre_defensive_ BOOL* bIsRelease);

// HidSmbus_GetHidLibraryVersion
/// @brief Reads and returns the version of the HID Device Interface Library that is currently in use.
///
/// @param major points at a byte-sized buffer into which the major number part of the Firmware Version will be written
/// @param minor points at a byte-sized buffer into which the minor number part of the Firmware Version will be written
/// @param bIsRelease points at a BOOL-sized buffer into which a True/False indication of whether the Firmware is a Release-build or not (Debug-build) will be written
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, another @ref HID_SMBUS_STATUS if there is an error:
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- major or minor or bIsRelease is an unexpected value
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- the device failed to respond to I/O in any expected manner
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetHidLibraryVersion(_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* major, _Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* minor, _Out_writes_bytes_(sizeof(BOOL)) _Pre_defensive_ BOOL* bIsRelease);

// HidSmbus_GetHidGuid
/// @brief Return the GUID for HIDClass devices ("return the HID GUID") (Windows only)
///
/// The HID GUID can be used to register for surprise removal notifications. See @ref MSDNURL.
///
/// @param[out] pHIDGuid points at a caller-allocated GUID buffer into which the HID GUID value will be written
///
/// @note BUG: This is an buffer-UNSAFE function, not defensive against a "too small" buffer provided as the pHIDGuid parameter.
/// @deprecated please use @ref HidUart_GetHidGuidSafe()
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- pHIDGuid is an unexpected value
_Check_return_
_Ret_range_(HID_UART_SUCCESS, HID_UART_UNKNOWN_ERROR)
_Success_(return == HID_UART_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetHidGuid(_Out_ void* pHIDGuid);
// TODO: Enstone: Implement HidSmbus_GetHidGuidSafe(_Out_ GUID *pHIDGuid);

/////////////////////////////////////////////////////////////////////////////
// Exported Library Functions - Device Customization
/////////////////////////////////////////////////////////////////////////////

// HidSmbus_SetLock
/// @brief permanently locks/disables device customization.
///
/// @param[in]  device is an open handle to the device as returned from @ref HidSmbus_Open()
/// @param[in] lock is a 1-byte bitmask specifying which fields can be customized/programmed and which fields
/// are already customized.  See @ref HID_SMBUS_LOCKBITS and @ref FieldLockBitValues.
///
/// @note When this function is successfully called, the specified fields are fully locked and cannot be further
/// customized. The user customization functions can be called and may return HID_SMBUS_SUCCESS
/// even though the device was not programmed. Call @ref HidSmbus_GetLock() to verify
/// that customization was successful. Each field is stored in one time programmable memory(OTP) and
/// can only be customized once. After a field is customized, the corresponding lock bits are set to 0.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- lock was not specified, and/or is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_SetLock(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _In_ _Pre_defensive_ const BYTE lock);

// HidSmbus_GetLock
/// @brief Get and return the device customization lock status
///
/// @param[in]  device is an open handle to the device as returned from @ref HidSmbus_Open()
/// @param[out] lock points at a 1-byte buffer into which the @ref #HID_SMBUS_LOCKBITS bitmask specifying which fields are locked will be copied and returned
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- lock was not specified, and/or is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetLock(_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device, _Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* lock);

// HidSmbus_SetUsbConfig
/// @brief This function allows one-time customization of the USB configuration, which includes vendor ID,
/// product ID, power, power mode, and release version settings.Each field can be independently programmed
/// one time via the mask field.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in] vid is the 2-byte Vendor ID value.
/// @param[in] pid is the 2-byte Product ID value.
/// @param[in] power is the 1-byte power value which specifies the current requested by the device IFF the device is configured to be bus powered. See @ref HID_SMBUS_BUS_POWER_MAX.
/// @param[in] powerMode is the 1-byte Power Mode value to configure the device as bus powered or self powered. See @ref PowerModes.
/// @param[in] releaseVersion is the 2-byte user-programmable Major.Minor Release Version value.
/// @param[in] mask is the 1-byte bitmask value specifying which fields to customize.  See @ref USBConfigBitmasks.
///
/// @note releaseVersion version is not the same as the device release number described in the USB device descriptor.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- power and/or powerMode is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_SetUsbConfig(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_In_ _Pre_defensive_ const WORD vid,
	_In_ _Pre_defensive_ const WORD pid,
	_In_range_(0, HID_SMBUS_BUS_POWER_MAX) _Pre_defensive_ const BYTE power,
	_In_ _Pre_defensive_ const BYTE powerMode,
	_In_ _Pre_defensive_ const WORD releaseVersion,
	_In_ _Pre_defensive_ const BYTE mask
);

// HidSmbus_GetUsbConfig
/// @brief retrieves USB configuration, which includes vendor ID, product ID, power, power mode,
/// release version, and flush buffers settings.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out] pVid points to a 1-byte buffer into which the Vendor ID  is written and returned.
/// @param[out] pPid points to a 1-byte buffer into which the Product ID  is written and returned.
/// @param[out] pPower points to a 1-byte buffer into which the power value which specifies the current requested by the device IFF the device is configured to be bus powered  is written and returned. See @ref HID_SMBUS_BUS_POWER_MAX.
/// @param[out] pPowerMode points to a 1-byte buffer into which the Power Mode value to configure the device as bus powered or self powered  is written and returned. See @ref PowerModes.
/// @param[out] pReleaseVersion points to a 1-byte buffer into which the Major.Minor Release Version value is written and returned.
/// @param[out] pFlushBuffers is the 2-byte Flush Buffers value is written and returned.  See @ref USBConfigBitmasks.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- vid and/or pid and/or power and/or powerMode and/or releaseVersion is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetUsbConfig(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* vid,
	_Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* pid,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* power,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* powerMode,
	_Out_writes_bytes_(sizeof(WORD)) _Pre_defensive_ WORD* releaseVersion
);

// HidSmbus_SetManufacturingString
/// @brief Allows one-time customization of the USB manufacturing string.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in] manufacturingString is a variable of type HID_SMBUS_CP2112_MFG_STR, a 30-byte character
/// buffer containing the ASCII manufacturing string.
/// @param[in]  strlen is the 1-byte length of manufacturingString in bytes.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- manufacturingString and/or strlen is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_SetManufacturingString(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_In_reads_bytes_(strlen) _Pre_defensive_ char* manufacturingString,
	_In_range_(0, HID_SMBUS_CP2112_MFG_STRLEN) _Pre_defensive_ const BYTE strlen
);

// HidSmbus_GetManufacturingString
/// @brief retrieves the USB manufacturing string.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out] manufacturingString is a variable of type HID_SMBUS_CP2112_MFG_STR, a 30-byte character
/// buffer that will contain the ASCII manufacturing string.
/// @param[out]  strlen returns the length of the string in bytes.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- manufacturingString and/or strlen is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetManufacturingString(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	char* manufacturingString,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* strlen
);

// HidSmbus_SetProductString
/// @brief allows one-time customization of the USB product string.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in] productString is a variable of type HID_SMBUS_CP2112_PRODUCT_STR, a 30-byte character
/// buffer containing the ASCII product string.
/// @param[in]  strlen is the length of productString in bytes. The maximum string length is 30 bytes.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- productString and/or strlen is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_SetProductString(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_In_reads_bytes_(strlen) _Pre_defensive_ char* productString,
	_In_range_(0, HID_SMBUS_CP2112_PRODUCT_STRLEN) _Pre_defensive_ const BYTE strlen
);

// HidSmbus_GetProductString
/// @brief retrieves the USB product string.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out] productString is a variable of type HID_SMBUS_CP2112_PRODUCT_STR, a 30-byte character
/// buffer that will contain the ASCII product string.
/// @param[out]  strlen returns the length of the string in bytes.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- productString and/or strlen is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetProductString(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	char* productString,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* strlen
);

// HidSmbus_SetSerialString
/// @brief allows one-time customization of the USB serial string.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[in] serialString is a variable of type HID_SMBUS_CP2112_SERIAL_STR, a 30-byte character buffer
/// containing the ASCII serial string.
/// @param[in]  strlen is the length of serialString in bytes. The maximum string length is 30 bytes.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- serialString and/or strlen is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_SetSerialString(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	_In_reads_bytes_(strlen) _Pre_defensive_ char* serialString,
	_In_range_(0, HID_SMBUS_CP2112_SERIAL_STRLEN) _Pre_defensive_ const BYTE strlen
);

// HidSmbus_GetSerialString
/// @brief retrieves the USB product string.
///
/// @param[in]  device is an open handle to the device as returned by @ref HidSmbus_Open().
/// @param[out] serialString is a variable of type HID_SMBUS_CP2112_SERIAL_STR, a 30-byte character buffer
/// that will contain the ASCII product string.
/// @param[out]  strlen returns the length of the string in bytes.
///
/// @returns Returns #HID_SMBUS_SUCCESS on success, or another @ref HID_SMBUS_STATUS Return value if there is an error.
///	@retval	#HID_SMBUS_SUCCESS -- success
///	@retval	#HID_SMBUS_INVALID_PARAMETER -- serialString and/or strlen is an unexpected value
///	@retval	#HID_SMBUS_INVALID_DEVICE_OBJECT -- the specified device is invalid
///	@retval	#HID_SMBUS_DEVICE_ACCESS_ERROR -- tbd
_Check_return_
_Ret_range_(HID_SMBUS_SUCCESS, HID_SMBUS_UNKNOWN_ERROR)
_Success_(HID_SMBUS_SUCCESS)
HID_TO_SMBUS_API HID_SMBUS_STATUS WINAPI
HidSmbus_GetSerialString(
	_In_ _Pre_defensive_ const HID_SMBUS_DEVICE device,
	char* serialString,
	_Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ BYTE* strlen
);

#ifdef __cplusplus
}
#endif // __cplusplus

/// @}

#endif // HOST_LIB_SLABHIDSMBUS_INCLUDE_SLABCP2112_H_INCLUDED_QU4N7WC20W
