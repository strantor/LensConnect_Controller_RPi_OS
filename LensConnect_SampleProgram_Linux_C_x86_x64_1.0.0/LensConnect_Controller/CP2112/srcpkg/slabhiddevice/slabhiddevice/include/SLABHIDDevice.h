////////////////////////////////////////////////////////////////////////////////
// SLABHIDDevice.h
////////////////////////////////////////////////////////////////////////////////

#ifndef HOST_LIB_SLABHIDDEVICE_INCLUDE_SLABHIDDEVICE_H_INCLUDED_MJWYLEYUPA
#define HOST_LIB_SLABHIDDEVICE_INCLUDE_SLABHIDDEVICE_H_INCLUDED_MJWYLEYUPA

/// @addtogroup slabhiddevice CP211x HID-based interface Library
///
/// The Silicon Labs CP211x USB-to-HID bridges are devices that communicate over
/// the Universal Serial Bus (USB) to perform Universal Asynchronous Receiver / Transmitter
/// (UART) data transfers. These devices have many programmable options that can
/// be configured via USB. These devices also often include flexible GPIO functions that
/// can be configured and accessed via USB during runtime. Silicon Labs provides libraries
/// that can be used to configure these devices and access their GPIOs.
///
/// Two interface library files can be used to interface with CP211x devices, CP210xManufacturing.DLL and .LIB, which is responsible for reading and writing
/// the device settings, and CP210xRuntime.DLL and .LIB, which is responsible for interfacing with the device's GPIOs. The APIs for CP210xManufacturing are
/// described below.
///
/// This document supercedes, obsoletes and takes precedences over AN532.
///
/// The CP211x SLABHIDDevice Host API is provided as a means to facilitate production of customized CP211x devices. This API allows access to the
/// CP211x device for retrieving and setting the VID, PID, product string, serial number, self - power attribute, maximum power consumption,
/// and device version.
///
/// The CP211x SLABHIDDevice Host API is provided in the form of a Windows Dynamic Link Library (DLL), SLABHIDDevice.DLL and as a Windows
/// static link library (SLABHIDDevice.static.LIB). The host interface
/// library communicates with the bridge controller device via the provided device driver and the operating system's USB stack.
///
/// Custom applications can use the CP211x SLABHIDDevice API implemented in SLABHIDDevice.DLL. To use functions implemented in SLABHIDDevice.DLL link SLABHIDDevice.LIB
/// include SLABHIDDevice.h into any source code files that call any functions implemented in SLABHIDDevice.DLL and include the PATH to the location of SLABHIDDevice.DLL
/// in your custom application Visual Studio .VCXPROJ Profile File's Properties->Linker->General->Additional Library Directories property.
///
/// Typically, the user initiates communication with the target CP211x device by making a call to @ref HidDevice_GetNumHidDevices(). This call
/// returns the number of CP211x target devices. This number is used as a range when calling @ref HidDevice_GetHidString() to build a list
/// of devices connected to the host machine.
/// A handle to the device must first be opened by a call to @ref HidDevice_Open() using an index determined from the call to @ref HidDevice_GetNumHidDevices().
/// The handle will be used for all subsequent accesses. When I/O operations are complete, the device handle is closed by a call to
/// @ref HidDevice_Close().
///
/// @{
/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////


#include	"silabs_defs.h"
#include	"silabs_sal.h"
#ifdef _WIN32
#include <windows.h>
#else // !_WIN32
#endif // !_WIN32
#include "Types.h"

#ifdef _WIN32
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CP210xDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CP210xDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SLAB_HID_DEVICE_EXPORTS
#define SLAB_HID_DEVICE_API
#elif defined(SLAB_HID_DEVICE_BUILD_SOURCE)
#define SLAB_HID_DEVICE_API
#else
#if defined(SILABS_STATIC_LINK)
#define SLAB_HID_DEVICE_API extern
#pragma comment (lib, "SLABHIDDevice.static.lib")
#else // defined(SILABS_STATIC_LINK)
#define SLAB_HID_DEVICE_API __declspec(dllimport)
#pragma comment (lib, "SLABHIDDevice.lib")
#endif // defined(SILABS_STATIC_LINK)
#endif
#else // !_WIN32
#define SLAB_HID_DEVICE_API ///< SLAB_HID_DEVICE_API definition
#define WINAPI ///< WINAPI definition
#endif // !_WIN32


/////////////////////////////////////////////////////////////////////////////
// Definitions
/////////////////////////////////////////////////////////////////////////////

/// API Status return codes
#define	USE_LEGACY_SLAB_HID_DEVICE_STATUS
#if !defined(USE_LEGACY_SLAB_HID_DEVICE_STATUS)	// TODO: Enstone: These defines are a exact duplicate values of HID_DEVICE_STATUS enums in HIDDevice.h.
typedef enum _SLAB_HID_DEVICE_STATUS {
	HID_DEVICE_SUCCESS = 0x00		///< @ref SILABS_STATUS no error
	, HID_DEVICE_NOT_FOUND = 0x01					///< the specified device was not found
	, HID_DEVICE_NOT_OPENED = 0x02
	, HID_DEVICE_ALREADY_OPENED = 0x03
	, HID_DEVICE_TRANSFER_TIMEOUT = 0x04
	, HID_DEVICE_TRANSFER_FAILED = 0x05
	, HID_DEVICE_CANNOT_GET_HID_INFO = 0x06
	, HID_DEVICE_HANDLE_ERROR = 0x07
	, HID_DEVICE_INVALID_BUFFER_SIZE = 0x08
	, HID_DEVICE_SYSTEM_CODE = 0x09
	, HID_DEVICE_UNSUPPORTED_FUNCTION = 0x0A
	, HID_DEVICE_UNKNOWN_ERROR = SILABS_STATUS_UNKNOWN_ERROR
} SLAB_HID_DEVICE_STATUS, *PSLAB_HID_DEVICE_STATUS;
#else // defined(NOT_YET)
/// @defgroup SLAB_HID_DEVICE_STATUS HID Device Status Codes
/// @{
typedef BYTE SLAB_HID_DEVICE_STATUS;	///< SLAB HID Device Status Codes
#if !defined(HID_DEVICE_H)
#define HID_DEVICE_SUCCESS					0x00	///< @ref _SILABS_STATUS "SILABS_STATUS" no error
#define HID_DEVICE_NOT_FOUND				0x01					///< Indicates that the specified device index was invalid or the device does not exist or is inaccessible.
#define HID_DEVICE_NOT_OPENED				0x02					///< Indicates that the device must be opened prior to calling the function.
#define HID_DEVICE_ALREADY_OPENED			0x03					///< Indicates that the device is already opened and cannot be re-opened.
#define	HID_DEVICE_TRANSFER_TIMEOUT			0x04					///< Indicates that a get or set report function returned due to a timeout. @ref HidDevice_GetInputReport_Interrupt() and/or @ref HidDevice_GetInputReport_Interrupt_WithTimeout() returned with less bytes than requested.
#define HID_DEVICE_TRANSFER_FAILED			0x05					///< The host failed to communicate with the device or function parameters are incorrect.
#define HID_DEVICE_CANNOT_GET_HID_INFO		0x06					///< Cannot retrieve device path or hidStringType is invalid.
#define HID_DEVICE_HANDLE_ERROR				0x07					///< HID CreateFile() handle is invalid.
#define HID_DEVICE_INVALID_BUFFER_SIZE		0x08					///< Specified buffer is not large enough to return requested data.
#define HID_DEVICE_SYSTEM_CODE				0x09					///< Indicates that a system error occurred. Call Windows GetLastError() to retrieve the system error code.
#define	HID_DEVICE_INVALID_PARAMETER		0x0B					///< Specified (typically non-buffer related) parameter is wrong or unexpected
#define HID_DEVICE_UNKNOWN_ERROR			SILABS_STATUS_UNKNOWN_ERROR ///< This is the default return code value. This value should never be returned.
#endif
#define HID_DEVICE_UNSUPPORTED_FUNCTION		0x0A					///< The function is only supported on certain (newer?) Windows versions.
/// @}
#endif // defined(NOT_YET)


/// Max number of USB Devices allowed
#define MAX_USB_DEVICES					64

/// @defgroup SLABHIDDEVICE_MAX_REPORT_REQUESTS Max number of reports that can be requested at time
/// @{
#define MAX_REPORT_REQUEST_XP			512	///< Maximum number of input report buffers for Windows XP and later.
#define MAX_REPORT_REQUEST_2K			200	///< Maximum number of input report buffers for Windows 2000.

#define DEFAULT_REPORT_INPUT_BUFFERS	0	///< Use OS-dependent HID driver default.
/// @}

/// String Types	// TODO: Enstone: These defines are a exact duplicate values of HID_DEVICE_STRING_ID enums in HIDDevice.h.
#if !defined(HID_DEVICE_H)
#define HID_VID_STRING					0x01	///< VID string, derived from @ref HID_PATH_STRING
#define HID_PID_STRING					0x02	///< PID string, derived from @ref HID_PATH_STRING
#define HID_PATH_STRING					0x03	///< Full Path string 
#define HID_SERIAL_STRING				0x04	///< iSerial Number string retrieved from device
#define HID_MANUFACTURER_STRING			0x05	///< Manufacturer Description string retrieved from device
#define HID_PRODUCT_STRING				0x06	///< Product Description string retrieved from device
#endif
/// @defgroup SLABHIDDEVICE_MAX_STRING_LENGTHS String Lengths in ASCII character lengths not including NULL-terminator
/// @{
#if !defined(MAX_STRING_LENGTH)
#define MAX_VID_LENGTH					5	///< Maximum Length of VID string
#define MAX_PID_LENGTH					5	///< Maximum Length of PID string
#define MAX_PATH_LENGTH                 260	///< Maximum Length of Path string
#define MAX_SERIAL_STRING_LENGTH		256	///< Maximum Length of Serial Number string
#define MAX_MANUFACTURER_STRING_LENGTH	256	///< Maximum Length of Manufacturer string
#define MAX_PRODUCT_STRING_LENGTH		256	///< Maximum Length of Product string
#define MAX_INDEXED_STRING_LENGTH		256	///< Maximum Length of a USB String Descriptor string, in characters, not including null-terminator
#define MAX_STRING_LENGTH				260	///< maximum length of any string, in characters
#endif
/// @}

/////////////////////////////////////////////////////////////////////////////
// Typedefs
/////////////////////////////////////////////////////////////////////////////

typedef void* HID_DEVICE;		///< an opaque handle object

/////////////////////////////////////////////////////////////////////////////
// Exported Functions
/////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/// @brief Determines the number of devices connected to the system with matching VID/PID
///
/// @details This function returns the number of connected devices. This does not imply that a device is
/// available for use. Users must call @ref HidDevice_GetNumHidDevices() before calling any function that
/// takes a device index as a parameter in order to build an up - to - date device list. If a device is
/// installed or removed after calling @ref HidDevice_GetNumHidDevices(), then the device list will be out
/// of date, and the results may be unpredictable. Currently, @ref HidDevice_GetHidString(),
/// @ref HidDevice_GetHidIndexedString(), @ref HidDevice_GetHidAttributes(), and @ref HidDevice_Open() all 
/// take a device index parameter.
///
/// @param[in] Vid - Filter device results by the 2-byte Vendor ID value.
/// @param[in] Pid - Filter device results by the 2-byte Product ID value.
///
/// @note If both @p Vid and @p Pid are zero (0x0000), devices will NOT be filtered by @p Vid/@p Pid.
///
/// @returns Returns the number of devices connected to the system which have VID/PID of @p Vid/@p Pid.
/// A return value of 0 indicates that no devices are available. Otherwise returns the number of
/// connected devices. When referring to a device by dwDeviceIndex, the index may range from 0 to
/// (@ref HidDevice_GetNumHidDevices() � 1).
_Check_return_
_Ret_range_(0, MAX_USB_DEVICES-1)
SLAB_HID_DEVICE_API	DWORD WINAPI
HidDevice_GetNumHidDevices(_In_ _Pre_defensive_ const WORD Vid, _In_ _Pre_defensive_ const WORD Pid);

/// @brief Gets a "Product string"
///
/// @details This function returns an ASCII NULL-terminated Vendor ID string, Product ID string, serial number string, manufacturer string,
/// product description string, or full
/// path string for the device specified by an index passed in the @p dwDeviceIndex parameter. The index of the
/// first device is 0, and the index of the last device is the value(NumDevices) returned by @ref HidDevice_GetNumHidDevices() - 1.
///
/// The @ref HID_VID_STRING "Vendor ID" string is derived from the "full path" string.
/// deviceString must point to a buffer at least @ref MAX_VID_LENGTH bytes long.
///
/// The @ref HID_PID_STRING "Product ID" string is derived from the "full path" string.
/// deviceString must point to a buffer at least @ref MAX_PID_LENGTH bytes long.
///
/// The @ref HID_PATH_STRING "full path" string is the "device interface path" or "Device Path". This path can be passed to Win32 functions such as CreateFile().
/// deviceString must point to a buffer at least @ref MAX_PATH_LENGTH bytes long.
///
/// The @ref HID_SERIAL_STRING "Serial Number" string is the Serial Number string from the specified Hid device's USB Device Descriptor's iSerialNumber Serial Number String Descriptor.
/// deviceString must point to a buffer at least @ref MAX_SERIAL_STRING_LENGTH bytes long.
///
/// The @ref HID_MANUFACTURER_STRING "Manufacturer Description" string is the Manufacturer string from the specified Hid device's USB Device Descriptor's iManufacturer Manufacturer String Descriptor.
/// deviceString must point to a buffer at least @ref MAX_MANUFACTURER_STRING_LENGTH bytes long.
///
/// The @ref HID_PRODUCT_STRING "Product" string is the product string from the specified Hid device's USB Device Descriptor's iProduct Product String Descriptor.
/// deviceString must point to a buffer at least @ref MAX_PRODUCT_STRING_LENGTH bytes long.
///
/// Returned strings are UCS-1?/ASCII and NULL-terminated. (verified)
///
///
/// @param[in] dwDeviceIndex is the desired device's index into the device list used to determine @ref HidDevice_GetNumHidDevices()
/// @param[in] Vid - Filter device results by the 2-byte Vendor ID value.
/// @param[in] Pid - Filter device results by the 2-byte Product ID value.
/// @param[in] WhichHidStringToReturn is the indication of which string to return, one of HID_DEVICE_STRING_ID
/// @param[out] deviceString points at a buffer into which the string will be copied and returned
/// @param[in] deviceStringLengthInBytes is the size, in bytes/octets, of the buffer into which the the string will be copied and returned I.e. sizeof deviceString buffer
///
/// @note If both @p Vid and @p Pid are zero (0x0000), devices will NOT be filtered by @p Vid/@p Pid.
///
/// @note Once a device is opened dwDeviceIndex is no longer valid, and @ref HidDevice_GetString() must be used rather than @ref HidDevice_GetHidString()
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_NOT_FOUND -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- failed, @p deviceStringLengthInBytes indicated a buffer that is too small
///	@retval	#HID_DEVICE_ALREADY_OPENED -- failed to open the device, it is already exclusively open elsewhere
///	@retval	#HID_DEVICE_SYSTEM_CODE -- failed
///	@retval	#HID_DEVICE_CANNOT_GET_HID_INFO -- failed
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetHidString(_In_ _Pre_defensive_ const DWORD dwDeviceIndex, _In_ _Pre_defensive_ const WORD Vid, _In_ _Pre_defensive_ const WORD Pid, _In_ _Pre_defensive_ const BYTE WhichHidStringToReturn, char* deviceString, _In_ _Pre_defensive_ const DWORD deviceStringLengthInBytes);

/// @brief Gets an indexed string from the device
///
/// Returned strings are UCS-1?/ASCII and NULL-terminated. (verified)
///
/// @param[in] dwDeviceIndex is the desired device's index into the device list used to determine @ref HidDevice_GetNumHidDevices()
/// @param[in] Vid - Filter device results by the 2-byte Vendor ID value.
/// @param[in] Pid - Filter device results by the 2-byte Product ID value.
/// @param[in] stringIndex is the one-based index of which USB String Descriptor string to return.
/// @param[out] deviceString points at a buffer into which the string will be copied and returned
/// @param[in] deviceStringLengthInBytes is the size, in bytes/octets, of the buffer into which the the string will be copied and returned I.e. sizeof deviceString buffer
///
/// @note If both Vid and Pid are zero (0x0000), devices will NOT be filtered by Vid/Pid.
///
/// @note String descriptors are referenced by their one-based index number. Specifically, a stringIndex
/// of 0 successfully does NOT return the list of supported languages.
///
/// @note Once a device is opened dwDeviceIndex is no longer valid, and @ref HidDevice_GetIndexedString() must be used rather than @ref HidDevice_GetHidIndexedString()
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_NOT_FOUND -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- failed, @p deviceStringLengthInBytes indicated a buffer that is too small
///	@retval	#HID_DEVICE_ALREADY_OPENED -- failed to open the device, it is already exclusively open elsewhere
///	@retval	#HID_DEVICE_SYSTEM_CODE -- failed, including when @p stringIndex is "too high" (I.e. there aren't this many strings on the device to index)
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetHidIndexedString(_In_ _Pre_defensive_ const DWORD dwDeviceIndex, _In_ _Pre_defensive_ const WORD Vid, _In_ _Pre_defensive_ const WORD Pid, _In_ _Pre_defensive_ const DWORD stringIndex, char* deviceString, _In_ _Pre_defensive_ const DWORD deviceStringLengthInBytes);

/// @brief Reads and returns the Vendor ID, Product ID and device Release Number
///
/// @details This function returns the USB vendor ID, product ID, and device release number for the device
/// specified by dwDeviceIndex.
///
/// @param[in] dwDeviceIndex is the desired device's index into the device list used to determine @ref HidDevice_GetNumHidDevices()
/// @param[in] Vid - Filter device results by the 2-byte Vendor ID value.
/// @param[in] Pid - Filter device results by the 2-byte Product ID value.
/// @param[out] pDeviceVid points at a 2-byte buffer into which the USB device vendor ID value will be written
/// @param[out] pDevicePid points at a 2-byte buffer into which the USB device product ID value will be written
/// @param[out] pDeviceReleaseNumber points at a 2-byte buffer into which the USB device bcdVersion, or device release number, value will be written
///
/// @note If both @p Vid and @p Pid are zero (0x0000), devices will NOT be filtered by @p Vid/@p Pid.
///
/// @note A successfully returned @p pDeviceReleaseNumber is in binary-coded decimal (BCD).
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_PARAMETER -- pDeviceVid, pDevicePid and/or pDeviceReleaseNumber is an unexpected value
///	@retval	#HID_DEVICE_NOT_FOUND -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_ALREADY_OPENED -- failed to open the device, it is already exclusively open elsewhere
///	@retval	#HID_DEVICE_SYSTEM_CODE -- failed, see Windows GetLastError()
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetHidAttributes(_In_ _Pre_defensive_ const DWORD dwDeviceIndex, _In_ _Pre_defensive_ const WORD Vid, _In_ _Pre_defensive_ const WORD Pid, _Out_writes_bytes_(2) _Pre_defensive_ WORD* pDeviceVid, _Out_writes_bytes_(2) _Pre_defensive_ WORD* pDevicePid, _Out_writes_bytes_(2) _Pre_defensive_ WORD* pDeviceReleaseNumber);

/// @brief Return the GUID for HIDClass devices ("return the HID GUID")
///
/// @param[out] pHIDGuid points at a caller-allocated GUID buffer into which the HID GUID value will be written
///
SLAB_HID_DEVICE_API void WINAPI
HidDevice_GetHidGuid(_Out_ void *pHIDGuid);

/// @brief tbd
///
/// @param[out] pMajor points at a 1-byte buffer into which the library major version number value will be written
/// @param[out] pMinor points at a 1-byte buffer into which the  library minor version number value will be written
/// @param[out] pbIsReleaseBuild points at a 4-byte buffer into which a non-zero/TRUE value will be written IFF the library was built as Release mode, else into which a zero/0 value will be written if the library was built as Debug mode.
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- pMajor, pMinor and/or pbIsReleaseBuild is an unexpected value
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetHidLibraryVersion(_Out_writes_bytes_(1) _Pre_defensive_ BYTE* pMajor, _Out_writes_bytes_(1) _Pre_defensive_ BYTE* pMinor, _Out_writes_bytes_(4) BOOL* pbIsReleaseBuild);

/// @brief tbd
///
/// @details For Windows 2000, the maximum number of queued input reports is 200/@ref MAX_REPORT_REQUEST_2K.
/// For Windows XP and later, the maximum number of queued input reports is 512/@ref MAX_REPORT_REQUEST_XP.
/// For Windows XP and later, the OS default number of queued input reports is 32.
/// In most cases, call this function with numInputBuffers set to @ref MAX_REPORT_REQUEST_XP to
/// achieve the best input report throughput.
/// If numInputBuffers is set to a value higher than the OS maximum, then the OS maximum value will
/// be used.
/// It is very common to list all connected devices by serial string. After calling
/// @ref HidDevice_GetNumHidDevices(), call @ref HidDevice_GetHidString() to get each device's serial string,
/// making sure to check the return code. Since @ref HidDevice_GetHidString() may fail (indicating that the
/// device is unavailable) it is not appropriate to simply add each device's serial string to a list and use
/// the list index to open. Similarly, a device index may have changed since the last time the device
/// list was updated. In this case, the user should select a device solely by serial string and query all
/// devices for a matching serial string.
/// This function allocates the dynamic report buffers, sets timeouts to their default values, and clears
/// the report queue.
///
/// @param[out] device is a pointer to an @ref HID_DEVICE opaque object location to hold the returned open handle to the device
/// @param[in] dwDeviceIndex is the desired device's index into the device list used to determine @ref HidDevice_GetNumHidDevices()
/// @param[in] Vid is the 2-byte Vendor ID value.
/// @param[in] Pid is the 2-byte Product ID value.
/// @param[in] numInputBuffers is the number of input report buffers to queue in the HID class driver.
///
/// @note If both @p Vid and @p Pid are zero (0x0000), devices will NOT be filtered by @p Vid/@p Pid.
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_PARAMETER -- device is an unexpected value
///	@retval	#HID_DEVICE_NOT_FOUND -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_ALREADY_OPENED -- failed to open the device, it is already exclusively open elsewhere
///	@retval	#HID_DEVICE_SYSTEM_CODE -- failed
///	@retval	#HID_DEVICE_CANNOT_GET_HID_INFO -- failed
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_Open(_Out_ HID_DEVICE* device, _In_ _Pre_defensive_ const DWORD dwDeviceIndex, _In_ _Pre_defensive_ const WORD Vid, _In_ _Pre_defensive_ const WORD Pid, _In_ _Pre_defensive_ const DWORD numInputBuffers);

/// @brief This function returns the device opened state.
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open(), or not
///
/// @returns Returns TRUE if a device is opened. Returns FALSE if the device is invalid or if a device is not opened.
_Ret_range_(FALSE, TRUE)
_Success_(return)
SLAB_HID_DEVICE_API	BOOL WINAPI
HidDevice_IsOpened(_In_ _Pre_defensive_ const HID_DEVICE device);

/// @brief This function returns the HID handle for the currently-opened device.
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
///
/// @returns Returns a Windows HANDLE created by Windows CreateFile() in @ref HidDevice_Open(). Returns
/// INVALID_HANDLE_VALUE if a device is not open or if there was an error opening a device.
_Check_return_
SLAB_HID_DEVICE_API	HANDLE WINAPI
HidDevice_GetHandle(_In_ _Pre_defensive_ const HID_DEVICE device);

/// @brief Gets a "Product string"
///
/// @details This function returns an ASCII NULL-terminated Vendor ID string, Product ID string, serial number string, manufacturer string,
/// product description string, or full
/// path string for the device specified by @p device parameter.
///
/// The @ref HID_VID_STRING "Vendor ID" string is derived from the "full path" string.
/// deviceString must point to a buffer at least @ref MAX_VID_LENGTH bytes long.
///
/// The @ref HID_PID_STRING "Product ID" string is derived from the "full path" string.
/// deviceString must point to a buffer at least @ref MAX_PID_LENGTH bytes long.
///
/// The @ref HID_PATH_STRING "full path" string is the "device interface path" or "Device Path". This path can be passed to Win32 functions such as CreateFile().
/// deviceString must point to a buffer at least @ref MAX_PATH_LENGTH bytes long.
///
/// The @ref HID_SERIAL_STRING "Serial Number" string is the Serial Number string from the specified Hid device's USB Device Descriptor's iSerialNumber Serial Number String Descriptor.
/// deviceString must point to a buffer at least @ref MAX_SERIAL_STRING_LENGTH bytes long.
///
/// The @ref HID_MANUFACTURER_STRING "Manufacturer Description" string is the Manufacturer string from the specified Hid device's USB Device Descriptor's iManufacturer Manufacturer String Descriptor.
/// deviceString must point to a buffer at least @ref MAX_MANUFACTURER_STRING_LENGTH bytes long.
///
/// The @ref HID_PRODUCT_STRING "Product" string is the product string from the specified Hid device's USB Device Descriptor's iProduct Product String Descriptor.
/// deviceString must point to a buffer at least @ref MAX_PRODUCT_STRING_LENGTH bytes long.
///
/// Returned strings are UCS-1?/ASCII and NULL-terminated. (verified)
///
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[in] WhichHidStringToReturn is the indication of which string to return, one of HID_DEVICE_STRING_ID
/// @param[out] deviceString points at a buffer into which the string will be copied and returned
/// @param[in] deviceStringLengthInBytes is the size, in bytes/octets, of the buffer into which the the string will be copied and returned I.e. sizeof deviceString buffer
///
/// @note Once a device is opened dwDeviceIndex is no longer valid, and @ref HidDevice_GetString() must be used rather than @ref HidDevice_GetHidString()
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_NOT_FOUND -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- failed, @p deviceStringLengthInBytes indicated a buffer that is too small
///	@retval	#HID_DEVICE_SYSTEM_CODE -- failed
///	@retval	#HID_DEVICE_CANNOT_GET_HID_INFO -- failed_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetString(_In_ _Pre_defensive_ const HID_DEVICE device, _In_ _Pre_defensive_ const BYTE WhichHidStringToReturn, char* deviceString, _In_ _Pre_defensive_ const DWORD deviceStringLengthInBytes);

/// @brief Gets an indexed string from the device
///
/// Returned strings are UCS-1?/ASCII and NULL-terminated. (verified)
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[in] stringIndex is the one-based index of which USB String Descriptor string to return.
/// @param[out] deviceString points at a buffer into which the string will be copied and returned
/// @param[in] deviceStringLengthInBytes is the size, in bytes/octets, of the buffer into which the the string will be copied and returned I.e. sizeof deviceString buffer
///
/// @note String descriptors are referenced by their one-based index number. Specifically, a @p stringIndex
/// of 0 successfully does NOT return the list of supported languages.
///
/// @note Once a device is opened dwDeviceIndex is no longer valid, and @ref HidDevice_GetIndexedString() must be used rather than @ref HidDevice_GetHidIndexedString()
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- failed, @p deviceStringLengthInBytes indicated a buffer that is too small
///	@retval	#HID_DEVICE_SYSTEM_CODE -- failed, including when @p stringIndex is "too high" (I.e. there aren't this many strings on the device to index)
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetIndexedString(_In_ _Pre_defensive_ const HID_DEVICE device, _In_ _Pre_defensive_ const DWORD stringIndex, char* deviceString, _In_ _Pre_defensive_ const DWORD deviceStringLengthInBytes);

/// @brief Reads and returns the Vendor ID, Product ID and device Release Number
///
/// @details This function returns the USB vendor ID, product ID, and device release number for the device
/// specified by device.
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[out] pDeviceVid points at a 2-byte buffer into which the USB device vendor ID value will be written
/// @param[out] pDevicePid points at a 2-byte buffer into which the USB device product ID value will be written
/// @param[out] pDeviceReleaseNumber points at a 2-byte buffer into which the USB device bcdVersion, or device release number, value will be written
///
/// @note A successfully returned @p pDeviceReleaseNumber is in binary-coded decimal (BCD).
///
/// @note Once a device is opened dwDeviceIndex is no longer valid, and @ref HidDevice_GetAttributes() must be used rather than @ref HidDevice_GetHidAttributes()
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_PARAMETER -- pDeviceVid, pDevicePid and/or pDeviceReleaseNumber is an unexpected value
///	@retval	#HID_DEVICE_SYSTEM_CODE -- failed, system error see Windows' GetLastError()
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetAttributes(_In_ _Pre_defensive_ const HID_DEVICE device, _Out_writes_bytes_(2) _Pre_defensive_ WORD* pDeviceVid, _Out_writes_bytes_(2) _Pre_defensive_ WORD* pDevicePid, _Out_writes_bytes_(2) _Pre_defensive_ WORD* pDeviceReleaseNumber);

/// @brief This function sends an HID feature report from the host to the device over the control endpoint.
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[in] ReportBuffer is a byte array containing a feature report. The first byte specifies the report ID.
/// @param[in] ReportBufferLengthInBytes - The size of ReportBuffer in bytes I.e. the size of the feature report including the report ID.
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- ReportBuffer and/or ReportBufferLengthInBytes is an unexpected value
///	@retval	#HID_DEVICE_NOT_OPENED -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_TRANSFER_FAILED -- failed, interaction with the device failed
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_SetFeatureReport_Control(_In_ _Pre_defensive_ const HID_DEVICE device, _In_reads_bytes_(ReportBufferLengthInBytes) _Pre_defensive_ BYTE* ReportBuffer, _In_ _Pre_defensive_ const DWORD ReportBufferLengthInBytes);

/// @brief This function receives an HID feature report from the host to the device over the control endpoint.
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[in] ReportBuffer - The buffer into which the feature report should be placed. The first byte of the buffer should be set to the report ID of the desired report.
/// @param[in] ReportBufferLengthInBytes - The size of ReportBuffer in bytes
///
/// The user must call this
/// function with the first byte in @p ReportBuffer set to the report ID of the report to receive. @p ReportBuffer must be
/// large enough to hold the feature report including report ID and, in most cases, should be
/// allocated with a size equal to @ref HidDevice_GetFeatureReportBufferLength().
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- ReportBuffer and/or ReportBufferLengthInBytes is an unexpected value
///	@retval	#HID_DEVICE_NOT_OPENED -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_TRANSFER_FAILED -- failed, interaction with the device failed
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetFeatureReport_Control(_In_ _Pre_defensive_ const HID_DEVICE device, _Out_writes_bytes_(ReportBufferLengthInBytes) _Pre_defensive_ BYTE* ReportBuffer, _In_ _Pre_defensive_ const DWORD ReportBufferLengthInBytes);

/// @brief This function sends an HID output report from the host to the device over the interrupt endpoint.
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[in] ReportBuffer - A byte array containing an output report. The first byte specifies the report ID.
/// @param[in] ReportBufferLengthInBytes - The size of ReportBuffer in bytes
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- ReportBuffer and/or ReportBufferLengthInBytes is an unexpected value
///	@retval	#HID_DEVICE_NOT_OPENED -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_TRANSFER_FAILED -- failed, interaction with the device failed
///	@retval	#HID_DEVICE_TRANSFER_TIMEOUT -- failed, interaction with the device timed out
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_SetOutputReport_Interrupt(_In_ _Pre_defensive_ const HID_DEVICE device, _In_reads_bytes_(ReportBufferLengthInBytes) _Pre_defensive_ BYTE* ReportBuffer, _In_ _Pre_defensive_ const DWORD ReportBufferLengthInBytes);

/// @brief This function receives an HID input report from the host to the device over the interrupt endpoint.
///
/// Each input report returned in buffer is stored on boundaries set by the maximum input report buffer
/// size. For example, if the maximum input report buffer size as returned by
/// @ref HidDevice_GetInputReportBufferLength() is 64 and @ref HidDevice_GetInputReport_Interrupt() returns
/// 2 input reports, then bytesReturned will return with 128 bytes. The first input report starts at
/// buffer[0], and the second input report starts at buffer[64] regardless of the actual size of the report.
/// To retrieve the maximum number of input reports possible, call @ref HidDevice_GetInputReport_Interrupt()
/// with bufferSize set to(@ref HidDevice_GetInputReportBufferLength() * @ref HidDevice_GetMaxReportRequest())
/// and numReports set to @ref HidDevice_GetMaxReportRequest().
///
/// To get input report interrupt with timeouts see @ref HidDevice_GetInputReport_Interrupt_WithTimeout().
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[in] ReportBuffer - The buffer into which the tbd report should be placed.The first byte of the buffer should be set to the report ID of the desired report
/// @param[in] ReportBufferLengthInBytes - The size of ReportBuffer in bytes
/// @param[in] numReports - The maximum number of input reports to return
/// @param[out] bytesReturned points at a 1-byte buffer into which the number of bytes returned in @p ReportBuffer will be written
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- ReportBuffer and/or ReportBufferLengthInBytes is an unexpected value
///	@retval	#HID_DEVICE_NOT_OPENED -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_TRANSFER_FAILED -- failed, interaction with the device failed
///	@retval	#HID_DEVICE_TRANSFER_TIMEOUT -- failed, interaction with the device timed out
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetInputReport_Interrupt(_In_ _Pre_defensive_ const HID_DEVICE device, _Out_writes_bytes_(ReportBufferLengthInBytes) _Pre_defensive_ BYTE* ReportBuffer, _In_ _Pre_defensive_ const DWORD ReportBufferLengthInBytes, _In_ _Pre_defensive_ const DWORD numReports, _Out_writes_bytes_(sizeof(DWORD)) _Pre_defensive_ DWORD* bytesReturned);

/// @brief This function receives an HID input report from the host to the device over the interrupt endpoint.
///
/// Set input report interrupt timeouts by settings getReportTimeout in @ref HidDevice_SetTimeouts().
///
/// Each input report returned in buffer is stored on boundaries set by the maximum input report buffer
/// size. For example, if the maximum input report buffer size as returned by
/// @ref HidDevice_GetInputReportBufferLength() is 64 and @ref HidDevice_GetInputReport_Interrupt() returns
/// 2 input reports, then bytesReturned will return with 128 bytes. The first input report starts at
/// buffer[0], and the second input report starts at buffer[64] regardless of the actual size of the report.
/// To retrieve the maximum number of input reports possible, call @ref HidDevice_GetInputReport_Interrupt()
/// with bufferSize set to(@ref HidDevice_GetInputReportBufferLength() * @ref HidDevice_GetMaxReportRequest())
/// and numReports set to @ref HidDevice_GetMaxReportRequest().
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[in] ReportBuffer - The buffer into which the tbd report should be placed.The first byte of the buffer should be set to the report ID of the desired report
/// @param[in] ReportBufferLengthInBytes - The size of ReportBuffer in bytes
/// @param[in] numReports - The maximum number of input reports to return
/// @param[out] bytesReturned points at a 1-byte buffer into which the number of bytes returned in @p ReportBuffer will be written
/// @param[in] TimeoutMSec is the timeout in Milliseconds
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- ReportBuffer and/or ReportBufferLengthInBytes is an unexpected value
///	@retval	#HID_DEVICE_NOT_OPENED -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_TRANSFER_FAILED -- failed, interaction with the device failed
///	@retval	#HID_DEVICE_TRANSFER_TIMEOUT -- failed, interaction with the device timed out
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetInputReport_Interrupt_WithTimeout(_In_ _Pre_defensive_ const HID_DEVICE device, _Out_writes_bytes_(ReportBufferLengthInBytes) _Pre_defensive_ BYTE* ReportBuffer, _In_ _Pre_defensive_ const DWORD ReportBufferLengthInBytes, _In_ _Pre_defensive_ const DWORD numReports, _Out_writes_bytes_(sizeof(BYTE)) _Pre_defensive_ DWORD* bytesReturned, _In_ _Pre_defensive_ const DWORD TimeoutMSec);

/// @brief Sends an HID output report from the host to the device over the control endpoint
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[in] ReportBuffer - A byte array containing an output report. The first byte specifies the report ID.
/// @param[in] ReportBufferLengthInBytes - The size of ReportBuffer in bytes
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- ReportBuffer and/or ReportBufferLengthInBytes is an unexpected value
///	@retval	#HID_DEVICE_NOT_OPENED -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_UNSUPPORTED_FUNCTION -- failed, this function is not supported on older Windows versions (Windows 2000)
///	@retval	#HID_DEVICE_TRANSFER_FAILED -- failed, interaction with the device failed
///	@retval	#HID_DEVICE_TRANSFER_TIMEOUT -- failed, interaction with the device timed out
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_SetOutputReport_Control(_In_ _Pre_defensive_ const HID_DEVICE device, _In_reads_bytes_(ReportBufferLengthInBytes) _Pre_defensive_ BYTE* ReportBuffer, _In_ _Pre_defensive_ const DWORD ReportBufferLengthInBytes);

/// @brief Receives an HID input report from the device to the host over the control endpoint
///
/// The user must call this
/// function with the first byte in @p ReportBuffer set to the report ID of the report to receive. @p ReportBuffer must be
/// large enough to hold the input report including report ID and, in most cases, should be
/// allocated with a size equal to @ref HidDevice_GetInputReportBufferLength().
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[in] ReportBuffer - The buffer into which the tbd report should be placed. The first byte of the buffer should be set to the report ID of the desired report
/// @param[in] ReportBufferLengthInBytes - The size of ReportBuffer in bytes
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_INVALID_BUFFER_SIZE -- ReportBuffer and/or ReportBufferLengthInBytes is an unexpected value
///	@retval	#HID_DEVICE_NOT_OPENED -- failed, the device specified by the dwDeviceIndex and filtered on by Vid and Pid, was not found
///	@retval	#HID_DEVICE_UNSUPPORTED_FUNCTION -- failed, this function is not supported on older Windows versions (Windows 2000)
///	@retval	#HID_DEVICE_TRANSFER_FAILED -- failed, interaction with the device failed
///	@retval	#HID_DEVICE_TRANSFER_TIMEOUT -- failed, interaction with the device timed out
_Check_return_
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_GetInputReport_Control(_In_ _Pre_defensive_ const HID_DEVICE device, _Out_writes_bytes_(ReportBufferLengthInBytes) _Pre_defensive_ BYTE* ReportBuffer, _In_ _Pre_defensive_ const DWORD ReportBufferLengthInBytes);


/// @brief Returns the maximum input report size including the report ID
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
///
/// @returns A return value of zero indicates that the specified device cannot be found. A non-zero value
/// specifies the maximum input report size including the report ID. This function should be called to
/// determine the appropriate buffer size for @ref HidDevice_GetInputReport_Interrupt() and
/// @ref HidDevice_GetInputReport_Control().
SLAB_HID_DEVICE_API	WORD WINAPI
HidDevice_GetInputReportBufferLength(_In_ _Pre_defensive_ const HID_DEVICE device);

/// @brief Returns the maximum output report size including the report ID
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
///
/// @returns A return value of zero indicates that the specified device cannot be found. A non-zero value
/// specifies the maximum output report size, including the report ID.
SLAB_HID_DEVICE_API	WORD WINAPI
HidDevice_GetOutputReportBufferLength(_In_ _Pre_defensive_ const HID_DEVICE device);

/// @brief Returns the maximum feature report size, including the report ID
///
/// @details This function should be called to determine the appropriate buffer size for @ref HidDevice_GetFeatureReport_Control().
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
///
/// @returns A return value of zero indicates that the specified device cannot be found. A non-zero value
/// specifies the maximum feature report size, including the report ID.
SLAB_HID_DEVICE_API	WORD WINAPI
HidDevice_GetFeatureReportBufferLength(_In_ _Pre_defensive_ const HID_DEVICE device);

/// @brief Returns the maximum number of input reports that can be queued in the HID driver
///
/// @details This function should be called to determine the appropriate buffer size for @ref HidDevice_GetInputReport_Interrupt().
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
///
/// @returns A return value of zero indicates that the specified device cannot be found. A non-zero return value
/// specifies the maximum number of reports in the HID driver input report queue.
SLAB_HID_DEVICE_API	DWORD WINAPI
HidDevice_GetMaxReportRequest(_In_ _Pre_defensive_ const HID_DEVICE device);

/// @brief Deletes all pending input reports in the HID driver queue and the HID library
///
/// This function first cancels pending overlapped input report reads (CancelIo()). Next, it flushes the
/// HID driver input report queue. Finally, it flushes the library's internal input report queue.
/// 
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
///
/// @returns Returns TRUE if the function completed successfully.
/// Returns FALSE if the function failed or if the device does not exist.
///	@retval	TRUE -- success
///	@retval	FALSE -- the function failed or the device does not exist.
_Check_return_
_Ret_range_(FALSE, TRUE)
_Success_(return)
SLAB_HID_DEVICE_API	BOOL WINAPI
HidDevice_FlushBuffers(_In_ _Pre_defensive_ const HID_DEVICE device);

/// @brief Cancels all pending input and output operations issued by the calling thread
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
///
/// @returns Returns TRUE if the function completed successfully.
/// Returns FALSE if the function failed or if the device does not exist.
///	@retval	TRUE -- success
///	@retval	FALSE -- the function failed or the device does not exist.
_Check_return_
_Ret_range_(FALSE, TRUE)
_Success_(return)
SLAB_HID_DEVICE_API	BOOL WINAPI
HidDevice_CancelIo(_In_ _Pre_defensive_ const HID_DEVICE device);

/// @brief Returns the input and output report timeouts over the interrupt endpoint
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[out] pGetReportTimeoutInMilliSeconds points at a 4-byte buffer into which the GetInputReport timeout value will be written
/// @param[out] pSetReportTimeoutInMilliSeconds points at a 4-byte buffer into which the SetOutputReport timeout value will be written
///
/// @p pGetReportTimeoutInMilliSeconds is the read timeout for @ref HidDevice_GetInputReport_Interrupt_WithTimeout() in
/// milliseconds. This timeout specifies the number of milliseconds that must elapse before
/// @ref HidDevice_GetInputReport_Interrupt_WithTimeout() will return with fewer bytes than requested with an
/// @ref HID_DEVICE_TRANSFER_TIMEOUT error. A timeout of 0 ms will return immediately with
/// any available data.
///
/// @p pSetReportTimeoutInMilliSeconds is the write timeout for HidDevice_SetOutputReport_Interrupt() in
/// milliseconds.This timeout specifies the number of milliseconds that must elapse for an output report
/// before @ref HidDevice_SetOutputReport_Interrupt() returns with an @ref HID_DEVICE_TRANSFER_TIMEOUT
/// error.
///
/// @note Read and write timeouts are maintained for each device but are not persistent across
/// @ref HidDevice_Open() / @ref HidDevice_Close().Allow for sufficient write timeouts to make sure that an
/// output report can be transmitted successfully.
///
/// The default get report and set report timeouts are both 1000 ms.
///
SLAB_HID_DEVICE_API	void WINAPI
HidDevice_GetTimeouts(_In_ _Pre_defensive_ const HID_DEVICE device, _Out_writes_bytes_(4) _Pre_defensive_ DWORD* pGetReportTimeoutInMilliSeconds, _Out_writes_bytes_(4) _Pre_defensive_ DWORD* pSetReportTimeoutInMilliSeconds);

/// @brief Sets the input and output report timeouts over the interrupt endpoint
///
/// @details Timeouts are used for @ref HidDevice_GetInputReport_Interrupt() and @ref HidDevice_SetOutputReport_Interrupt().
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
/// @param[in] getReportTimeoutInMilliSeconds - Sets the timeout used in @ref  HidDevice_GetInputReport_Interrupt() in
/// milliseconds. This timeout specifies the number of milliseconds that must elapse before
/// @ref HidDevice_GetInputReport_Interrupt() will return fewer bytes than requested with an
/// #HID_DEVICE_TRANSFER_TIMEOUT error. A timeout of 0 ms will return immediately with
/// any available data.
/// @param[in] setReportTimeoutInMilliSeconds - Sets the timeout used in @ref HidDevice_SetOutputReport_Interrupt() in
/// milliseconds.This timeout specifies the number of milliseconds that must elapse during an
/// output report before @ref HidDevice_SetOutputReport_Interrupt() will return with an
/// #HID_DEVICE_TRANSFER_TIMEOUT error.
///
/// @note If get report timeouts are set to a large value and no data is received, the application may appear
/// unresponsive.Therefore, it is recommended to set timeouts to an appropriate value before reading
/// from the device.
/// The default value for get report and set report timeouts is 1000 ms and can be set to any number
/// of milliseconds from 0 to 0xFFFFFFFF.
///
SLAB_HID_DEVICE_API	void WINAPI
HidDevice_SetTimeouts(_In_ _Pre_defensive_ const HID_DEVICE device, _In_ _Pre_defensive_ const DWORD getReportTimeoutInMilliSeconds, _In_ _Pre_defensive_ const DWORD setReportTimeoutInMilliSeconds);

/// @brief Closes an open handle to the device
///
/// This function deletes the internal library input report buffer and cancels any pending input report
/// reads via::CancelIo(). This function is responsible for deallocating the HID class object allocated
/// in @ref HidDevice_Open().
///
/// @param[in] device is an open handle to the device as returned by @ref HidDevice_Open()
///
/// @returns Returns #HID_DEVICE_SUCCESS on success, or another @ref SLAB_HID_DEVICE_STATUS Return value if there is an error.
///	@retval	#HID_DEVICE_SUCCESS -- success
///	@retval	#HID_DEVICE_HANDLE_ERROR -- failed, the device specified by device does not have a valid handle
///	@retval	#HID_DEVICE_NOT_FOUND -- failed, the device specified by device was not found
///	@retval	#HID_DEVICE_NOT_OPENED -- failed, the device specified by device is not open
_Ret_range_(HID_DEVICE_SUCCESS, HID_DEVICE_UNKNOWN_ERROR)
_Success_(HID_DEVICE_SUCCESS == return)
SLAB_HID_DEVICE_API	SLAB_HID_DEVICE_STATUS WINAPI
HidDevice_Close(_In_ _Pre_defensive_ const HID_DEVICE device);

#ifdef __cplusplus
}
#endif // __cplusplus

/// @}

#endif // HOST_LIB_SLABHIDDEVICE_INCLUDE_SLABHIDDEVICE_H_INCLUDED_MJWYLEYUPA
