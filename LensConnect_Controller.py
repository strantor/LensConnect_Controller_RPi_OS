import UsbCtrl
import LensCtrl
import ConfigVal as CV

import LensAccess as LA
import LensInfo as LI
import DefVal as DV
import LensSetup as LS

PROGRAM_VERSION ="1.0.0"

ItemNum = 0
detaliSelect = 0

usbOpen_flag = False
withZoom = False
withFocus = False
withIris = False
withOptFil = False

def OnOff(flag):
	if (flag == 1):
		return "ON"
	else:
		return "OFF"

def ScanUsbWithLensInfo():
	retval, numDevice = UsbCtrl.UsbGetNumDevices()
	if(numDevice >= 1):
		print("No.: S/N")
		for i in range(0, numDevice):
			retval = UsbCtrl.UsbOpen(i)
			if (retval == 0):
				retval, SnSrting = UsbCtrl.UsbGetOpenedSnDevice(i)
				retval, model = LensCtrl.ModelName()
				retval, userName = LensCtrl.UserAreaRead()
				print("{:2d} : {} , {} {}" .format(i, SnSrting, model, userName))
			else:
				print("{:2d} : {:35s} {}" .format(i,"Device access error.", "The device may alreadey be runing."))
			UsbCtrl.UsbClose()
	else:
		print("No LensConnect is connnected.")
	print("")

def UsbConnect(deviceNumber):
	global usbOpen_flag
	global withZoom
	global withFocus
	global withIris
	global withOptFil
	retval = UsbCtrl.UsbOpen(deviceNumber)
	if (retval != DV.RET_SUCCESS):
		print(retval)
		return retval
	
	retval = UsbCtrl.UsbSetConfig()
	if (retval != DV.RET_SUCCESS):
		print(retval)
		return retval

	retval, capabilities = LensCtrl.CapabilitiesRead()
	LensCtrl.Status2ReadSet()

	if (capabilities & CV.ZOOM_MASK):
		LensCtrl.ZoomParameterReadSet()
		if (LensCtrl.status2 & CV.ZOOM_MASK == DV.INIT_COMPLETED):
			LensCtrl.ZoomCurrentAddrReadSet()
		withZoom = True

	if (capabilities & CV.FOCUS_MASK):
		LensCtrl.FocusParameterReadSet()
		if (LensCtrl.status2 & CV.FOCUS_MASK == DV.INIT_COMPLETED):
			LensCtrl.FocusCurrentAddrReadSet()
		withFocus = True

	if (capabilities & CV.IRIS_MASK):
		LensCtrl.IrisParameterReadSet()
		if (LensCtrl.status2 & CV.IRIS_MASK == DV.INIT_COMPLETED):
			LensCtrl.IrisCurrentAddrReadSet()
		withIris = True

	if (capabilities & CV.OPT_FILTER_MASK):
		LensCtrl.OptFilterParameterReadSet()
		if (LensCtrl.status2 & CV.OPT_FILTER_MASK == DV.INIT_COMPLETED):
			LensCtrl.OptFilterCurrentAddrReadSet()
		withOptFil = True
	usbOpen_flag = True
	retval = 0
	return retval

def UsbDisconnect():
	global usbOpen_flag
	global withZoom
	global withFocus
	global withIris
	global withOptFil

	UsbCtrl.UsbClose()
	usbOpen_flag = False
	withZoom = False
	withFocus = False
	withIris = False
	withOptFil = False

def CommandList():
	print("\n----- LensConnect Control -----")
	print(" 0 : Command list ")
	if (withZoom == True):
		print("----- ZOOM -----")
		print(" 1 : Initialize zoom")
		if ((LensCtrl.status2 & CV.ZOOM_MASK) == DV.INIT_COMPLETED):
			print("11 : Move zoom {} - {}" .format(LensCtrl.zoomMinAddr, LensCtrl.zoomMaxAddr))
			print("12 : Displays the current zoom address\n")

	if (withFocus == True):
		print("----- FOCUS -----")
		print(" 2 : Initialize focus")
		if ((LensCtrl.status2 & CV.FOCUS_MASK) == DV.INIT_COMPLETED):
			print("21 : Move focus {} - {}" .format(LensCtrl.focusMinAddr, LensCtrl.focusMaxAddr))
			print("22 : Displays the current focus address")
			print("23 : Fine move focus control")
			print("24 : Fine step number setting\n")

	if (withIris == True):
		print("----- IRIS -----")
		print(" 3 : Initialize iris")
		if ((LensCtrl.status2 & CV.IRIS_MASK) == DV.INIT_COMPLETED):
			print("31 : Move iris {} - {}" .format(LensCtrl.irisMinAddr, LensCtrl.irisMaxAddr))
			print("32 : Displays the current iris address\n")

	if (withOptFil == True):
		print("----- Optical Filter -----")
		print(" 4 : Initialize optical filter")
		if ((LensCtrl.status2 & CV.OPT_FILTER_MASK) == DV.INIT_COMPLETED):
			print("41 : Move optical filter 0 - {}" .format(LensCtrl.optFilMaxAddr))
			print("42 : Displays the current optical filter address\n")

	print("----- Ohter -----")
	print(" 5 : Parameter setup")
	print(" 6 : Displays the information")
	print(" 7 : Displays the user name")
	print("71 : Write the user area")
	print(" 8 : Close USB (other lens)")
	print(" 9 :  Exit appliction\n")

def CommandSetupList():
	print("")
	if (withZoom == True):
		print(" 1: Zoom")
	if (withFocus == True):
		print(" 2: Focus")
	if (withIris == True):
		print(" 3: Iris")
	print(" 5: Return to main\n")

def DetailSetupList(motorNumber):
	print(" 1: Speed change. ", end="")
	if (motorNumber == DV.ZOOM):
		print("Current zoom speed is ", LensCtrl.zoomSpeedPPS)
	elif (motorNumber == DV.FOCUS):
		print("Current focus speed is ", LensCtrl.focusSpeedPPS)
	elif (motorNumber == DV.IRIS):
		print("Current iris speed is ", LensCtrl.irisSpeedPPS)

	print(" 2: Backlash correnction change. Currently ", end="")
	if (motorNumber == DV.ZOOM):
		retval, flag = LensCtrl.ZoomBacklashRead()
		print(OnOff(flag))
	if (motorNumber == DV.FOCUS):
		retval, flag = LensCtrl.FocusBacklashRead()
		print(OnOff(flag))
	if (motorNumber == DV.IRIS):
		retval, flag = LensCtrl.IrisBacklashRead()
		print(OnOff(flag))

	print(" 5: Back (Cancel)\n")

def CommandLensInfoList():
	print("\n----- Information -----")
	print(" 0: Displays General")
	if (withZoom == True):
		print(" 1: Displays Zoom")
	if (withFocus == True):
		print(" 2: Displays Focus")
	if (withIris == True):
		print(" 3: Displays Iris")
	if (withOptFil == True):
		print(" 4: Displays Optical filter")
	print(" 5: Return to main\n")

def MainExe(number):
	global ItemNum
	if (number == 0):
		print("",end="")
	elif ((number == 1) & (withZoom == True)):
		print("Initializing")
		LensCtrl.ZoomInit()
	elif ((number == 11) & (withZoom == True)):
		LA.MoveLens(DV.ZOOM)
	elif ((number == 12) & (withFocus == True)):
		print("\nZoom current address %d\n" % LensCtrl.zoomCurrentAddr)

	elif ((number == 2) & (withFocus == True)):
		print("Initializing")
		LensCtrl.FocusInit()
	elif ((number == 21) & (withFocus == True)):
		LA.MoveLens(DV.FOCUS)
	elif ((number == 22) & (withFocus == True)):
		print("\nFocus current address %d\n" % LensCtrl.focusCurrentAddr)
	elif ((number == 23) & (withFocus == True)):
		LA.FineFocusMove()
	elif ((number == 24) & (withFocus ==True)):
		LA.FineNumSet()

	elif ((number == 3) & (withIris == True)):
		print("Initializing")
		LensCtrl.IrisInit()
	elif ((number == 31) & (withIris == True)):
		LA.MoveLens(DV.IRIS)
	elif ((number ==32) & (withIris == True)):
		print("\nIris current address %d\n" % LensCtrl.irisCurrentAddr)
	
	elif ((number == 4) & (withOptFil == True)):
		print("Initializing")
		LensCtrl.OptFilterInit()
	elif ((number == 41) & (withOptFil == True)):
		LA.MoveLens(DV.OPT)
	elif ((number ==42) & (withOptFil == True)):
		print("\nOptical filter current address %d\n" %  LensCtrl.optCurrentAddr)

	elif (number == 5):
		CommandSetupList()
		ItemNum = DV.SETUP
	elif (number == 6):
		CommandLensInfoList()
		ItemNum = DV.INFO
	elif (number == 7):
		retval, userName = LensCtrl.UserAreaRead()
		print(userName)
	elif (number == 71):
		LA.UserIDWrite()
	elif(number == 8):
		UsbDisconnect()
	else:
		print("\nWrong number entered.\n")
	
	if ((number <= 4) or (number == 23)):
		CommandList()

def SetupExe(number):
	global ItemNum
	global detaliSelect
	global motorNumber
	if (detaliSelect == DV.OFF):
		if ((number == DV.ZOOM) & (withZoom == True)):
			motorNumber = DV.ZOOM
			detaliSelect = DV.ON

		elif ((number == DV.FOCUS) & (withFocus == True)):
			motorNumber = DV.FOCUS
			detaliSelect = DV.ON

		elif ((number == DV.IRIS) & (withIris == True)):
			motorNumber = DV.IRIS
			detaliSelect = DV.ON

		elif (number == DV.BACK_MAIN):
			ItemNum = DV.MAIN
			CommandList()

		else:
			print("\nWrong number entered.\n")
			CommandSetupList()

		if (detaliSelect == DV.ON):
			DetailSetupList(motorNumber)
	else:
		if (number == 1):
			if (motorNumber == DV.ZOOM):
				LS.ZoomSpeedChange()
			if (motorNumber == DV.FOCUS):
				LS.FocusSpeedChange()
			if (motorNumber == DV.IRIS):
				LS.IrisSpeedChange()

		elif (number == 2):
			if (motorNumber == DV.ZOOM):
				LS.ZoomBacklashToggleCtl()
			if (motorNumber == DV.FOCUS):
				LS.FocusBacklashToggleCtl()
			if (motorNumber == DV.IRIS):
				LS.IrisBacklashToggleCtl()

		elif (number == 5):
			print("")

		else:
			print("\nWrong number entered.\n")

		CommandSetupList()
		detaliSelect = DV.OFF

def InfoExe(number):
	global ItemNum
	if (number == DV.GENE):
		LI.GeneralInfo()

	elif ((number == DV.ZOOM) & (withZoom == True)):
		LI.ZoomInfo()

	elif ((number == DV.FOCUS) & (withFocus == True)):
		LI.FocusInfo()

	elif ((number == DV.IRIS) & (withIris == True)):
		LI.IrisInfo()

	elif ((number == DV.OPT) & (withOptFil ==True)):
		LI.OptFilterInfo()

	elif (number == DV.BACK_MAIN):
		ItemNum = DV.MAIN
		CommandList()

	else:
		print("\nWrong number entered.\n")
	
	if (number != DV.BACK_MAIN):
		CommandLensInfoList()

def main():
	global ItemNum
	global usbOpen_flag
	ItemNum = DV.MAIN
	usbOpen_flag = False
	print("LensConnect Control ", PROGRAM_VERSION)
	while(True):
		if (usbOpen_flag == False):
			ScanUsbWithLensInfo()
			print(" 8 : Scan lens")
			print(" 9 : Exit appliction\n")
			num = input("Please select connect lens No.")
			number = int(num)
			if (number == 9):
				UsbDisconnect()
				break
			if (number != 8):
				retval = UsbConnect(number)
				if (retval == DV.RET_SUCCESS):
					print("No. {} lens opened" .format(number))
					CommandList()
				else:
					print("error! = {}" .format(retval))
		else:
			num = input("Select number :")
			number = int(num)
			if (ItemNum == DV.MAIN):
				if (number == 9):
					UsbDisconnect()
					break
				if (number == 8):
					UsbDisconnect()
				MainExe(number)
			elif (ItemNum == DV.SETUP):
				SetupExe(number)
			elif (ItemNum == DV.INFO):
				InfoExe(number)



if __name__ == "__main__":
 	main()
