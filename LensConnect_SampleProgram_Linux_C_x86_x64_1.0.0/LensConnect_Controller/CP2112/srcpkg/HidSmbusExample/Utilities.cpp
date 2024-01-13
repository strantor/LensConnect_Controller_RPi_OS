/////////////////////////////////////////////////////////////////////////////
// Utilities.m
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////

#include "Utilities.h"
#include <cstring>
#include "mainwindow.h"
/////////////////////////////////////////////////////////////////////////////
// Public Functions
/////////////////////////////////////////////////////////////////////////////
const char * HidSmbus_DecodeErrorStatus(HID_SMBUS_STATUS status)
{
	const char * str;

	switch (status)
	{
	case HID_SMBUS_SUCCESS:					str = "HID_SMBUS_SUCCESS";					break;
	case HID_SMBUS_DEVICE_NOT_FOUND:		str = "HID_SMBUS_DEVICE_NOT_FOUND";		break;
	case HID_SMBUS_INVALID_HANDLE:			str = "HID_SMBUS_INVALID_HANDLE";			break;
	case HID_SMBUS_INVALID_DEVICE_OBJECT:	str = "HID_SMBUS_INVALID_DEVICE_OBJECT";	break;
	case HID_SMBUS_INVALID_PARAMETER:		str = "HID_SMBUS_INVALID_PARAMETER";		break;
	case HID_SMBUS_INVALID_REQUEST_LENGTH:	str = "HID_SMBUS_INVALID_REQUEST_LENGTH";	break;
	case HID_SMBUS_READ_ERROR:				str = "HID_SMBUS_READ_ERROR";				break;
	case HID_SMBUS_WRITE_ERROR:				str = "HID_SMBUS_WRITE_ERROR";				break;
	case HID_SMBUS_READ_TIMED_OUT:			str = "HID_SMBUS_READ_TIMED_OUT";			break;
	case HID_SMBUS_WRITE_TIMED_OUT:			str = "HID_SMBUS_WRITE_TIMED_OUT";			break;
	case HID_SMBUS_DEVICE_IO_FAILED:		str = "HID_SMBUS_DEVICE_IO_FAILED";		break;
	case HID_SMBUS_DEVICE_ACCESS_ERROR:		str = "HID_SMBUS_DEVICE_ACCESS_ERROR";		break;
	case HID_SMBUS_DEVICE_NOT_SUPPORTED:	str = "HID_SMBUS_DEVICE_NOT_SUPPORTED";	break;
	case HID_SMBUS_UNKNOWN_ERROR:			str = "HID_SMBUS_UNKNOWN_ERROR";			break;
	default:								str = "Unknown Status";
	}

	return str;
}

const char * HidSmbus_DecodeGPIOStatus(HID_SMBUS_STATUS status)
{
    const char * str;

    switch (status)
    {
    case GPIO_INPUT_OPEN_DRAIN:			str = "GPIO_INPUT_OPEN_DRAIN";		break;
    case GPIO_OUTPUT_OPEN_DRAIN:		str = "GPIO_OUTPUT_OPEN_DRAIN";		break;
    case GPIO_OUTPUT_PUSH_PULL:			str = "GPIO_OUTPUT_PUSH_PULL";		break;
    case GPIO_SPECIAL_PUSH_PULL:        str = "GPIO_SPECIAL_PUSH_PULL";     break;
    default:							str = "Unknown Status";
    }

    return str;
}

const char * HidSmbus_DecodePower(HID_SMBUS_STATUS status)
{
    const char * str;

    switch (status)
    {
    case HID_SMBUS_BUS_POWER:			    str = "HID_SMBUS_BUS_POWER";		break;
    case HID_SMBUS_SELF_POWER_VREG_DIS:		str = "HID_SMBUS_SELF_POWER_VREG_DIS";		break;
    case HID_SMBUS_SELF_POWER_VREG_EN:		str = "HID_SMBUS_SELF_POWER_VREG_EN";		break;
    default:							    str = "Unknown Status";
    }

    return str;
}

const char * HidSmbus_DecodeTransferStatus(HID_SMBUS_S0 status0)
{
	const char * str;

	switch (status0)
	{
	case HID_SMBUS_S0_IDLE:			str = "Idle";				break;
	case HID_SMBUS_S0_BUSY:			str = "Busy";				break;
	case HID_SMBUS_S0_COMPLETE:		str = "Complete";			break;
	case HID_SMBUS_S0_ERROR:		str = "Error";				break;
	default:						str = "Unknown Status";	break;
	}

	return str;
}

char gStatusString[256];

const char * HidSmbus_DecodeTransferStatuses(HID_SMBUS_S0 status0, HID_SMBUS_S1 status1)
{


    memset(gStatusString, 0, sizeof(gStatusString));

	switch (status0)
	{
	case HID_SMBUS_S0_IDLE:			strcat(gStatusString, "Idle");			break;
	case HID_SMBUS_S0_BUSY:			strcat(gStatusString, "Busy - ");		break;
	case HID_SMBUS_S0_COMPLETE:		strcat(gStatusString, "Complete");		break;
	case HID_SMBUS_S0_ERROR:		strcat(gStatusString, "Error - ");		break;
	default:						strcat(gStatusString, "Unknown Status");	break;
	}

	if (status0 == HID_SMBUS_S0_BUSY)
	{
		switch (status1)
		{
		case HID_SMBUS_S1_BUSY_ADDRESS_ACKED:	strcat(gStatusString, "Address Acked");		break;
		case HID_SMBUS_S1_BUSY_ADDRESS_NACKED:	strcat(gStatusString, "Address Nacked");		break;
		case HID_SMBUS_S1_BUSY_READING:			strcat(gStatusString, "Read in Progress");	break;
		case HID_SMBUS_S1_BUSY_WRITING:			strcat(gStatusString, "Write in Progress");	break;
		default:								strcat(gStatusString, "Unknown Status");		break;
		}
	}
	else if (status0 == HID_SMBUS_S0_ERROR)
	{
		switch (status1)
		{
		case HID_SMBUS_S1_ERROR_TIMEOUT_NACK:			strcat(gStatusString, "Timeout (Address Nacked)");	break;
		case HID_SMBUS_S1_ERROR_TIMEOUT_BUS_NOT_FREE:	strcat(gStatusString, "Timeout (Bus Not Free)");		break;
		case HID_SMBUS_S1_ERROR_ARB_LOST:				strcat(gStatusString, "Arbitration Lost");			break;
		case HID_SMBUS_S1_ERROR_READ_INCOMPLETE:		strcat(gStatusString, "Read Incomplete");				break;
		case HID_SMBUS_S1_ERROR_WRITE_INCOMPLETE:		strcat(gStatusString, "Write Incomplete");			break;
		case HID_SMBUS_S1_ERROR_SUCCESS_AFTER_RETRY:	strcat(gStatusString, "Success After Retries");		break;
		default:										strcat(gStatusString, "Unknown Status");				break;
		}
	}

	return gStatusString;
}
