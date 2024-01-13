import LensCtrl
import DefVal as DV

def ZoomSpeedChange():
    retval, speedMin = LensCtrl.ZoomSpeedMinRead()
    retval, speedMax = LensCtrl.ZoomSpeedMaxRead()
    print("\nPlease input PPS between {} to {}" .format(speedMin,speedMax) )
    speedVal = input(">>")
    speedPPS = int(speedVal)
    LensCtrl.ZoomSpeedWrite(speedPPS)

def FocusSpeedChange():
    retval, speedMin = LensCtrl.FocusSpeedMinRead()
    retval, speedMax = LensCtrl.FocusSpeedMaxRead()
    print("\nPlease input PPS between {} to {}" .format(speedMin, speedMax))
    speedVal = input(">>")
    speedPPS = int(speedVal)
    LensCtrl.FocusSpeedWrite(speedPPS)

def IrisSpeedChange():
    retval, speedMin = LensCtrl.IrisSpeedMinRead()
    retval, speedMax = LensCtrl.IrisSpeedMaxRead()
    print("\nPlease input PPS between {} to {}" .format(speedMin, speedMax))
    speedVal = input(">>")
    speedPPS = int(speedVal)
    LensCtrl.IrisSpeedWrite(speedPPS)

def ZoomBacklashToggleCtl():
    print("\nZoom backlash correction ", end="")
    retval, flag = LensCtrl.ZoomBacklashRead()
    if (flag == DV.ON):
        LensCtrl.ZoomBacklashWrite(DV.OFF)
        print("OFF")
    else:
        LensCtrl.ZoomBacklashWrite(DV.ON)
        print("ON")

def FocusBacklashToggleCtl():
    print("\nFocus backlash correction ", end="")
    retval, flag = LensCtrl.FocusBacklashRead()
    if (flag == DV.ON):
        LensCtrl.FocusBacklashWrite(DV.OFF)
        print("OFF")
    else:
        LensCtrl.FocusBacklashWrite(DV.ON)
        print("ON")

def IrisBacklashToggleCtl():
    print("\nIris backlash correction ", end="")
    retval, flag = LensCtrl.IrisBacklashRead()
    if (flag == DV.ON):
        LensCtrl.IrisBacklashWrite(DV.OFF)
        print("OFF")
    else:
        LensCtrl.IrisBacklashWrite(DV.ON)
        print("ON")
