import DevAddr as DA
import DefVal as DV
import LensCtrl

def GeneralInfo():
    print("\n***** General Information *****")

    retval, version = LensCtrl.ProtocolVersion()
    if (retval == DV.RET_SUCCESS):
        print("Protocol version = ", version)
    else:
        print(retval)
    
    retval, version = LensCtrl.FWVersion()
    if (retval == DV.RET_SUCCESS):
        print("Firmware version = ", version)
    else:
        print(retval)
    
    retval, revision = LensCtrl.LensRevision()
    if (retval == DV.RET_SUCCESS):
        print("Lens revision = ", revision)
    else:
        print(retval)

    retval, i2cAddr = LensCtrl.LensAddress()
    if (retval == DV.RET_SUCCESS):
        print("Lens I2C address = {:#04x} (7bit)" .format(i2cAddr))
    else:
        print(retval)

    retval, model = LensCtrl.ModelName()
    if (retval == DV.RET_SUCCESS):
        print("Lens model name = ", model)
    else:
        print(retval)
    
    retval, capabilities = LensCtrl.CapabilitiesRead()
    if (retval == DV.RET_SUCCESS):
        print("Capabilities = {:#06x} : {:#016b}" .format(capabilities, capabilities))
    else:
        print(retval)

    retval, status1 = LensCtrl.Status1Read()
    if (retval == DV.RET_SUCCESS):
        print("Status1      = {:#06x} : {:#016b}" .format(status1, status1))
    else:
        print(retval)
    
    retval, status2 = LensCtrl.Status2ReadSet()
    if (retval == DV.RET_SUCCESS):
        print("Status2      = {:#06x} : {:#016b}" .format(status2, status2))
    else:
        print(retval)

    retval, kelvinValue = LensCtrl.TempKelvinVal()
    if (retval == DV.RET_SUCCESS):
        tempCels = round(kelvinValue - DV.KELVIN_TO_CELS)
        print("Temperature = ", tempCels, "degree Celsius")
    else:
        print(retval)

def ZoomInfo():
    print("\n***** ZOOM Information *****")
    print("Current postion = ", LensCtrl.zoomCurrentAddr)
    retval, flag = LensCtrl.ZoomBacklashRead()
    print("Backlash corrention = ", flag)
    pos = LensCtrl.NoErrChk2BytesIntRead(DA.ZOOM_INIT_POSITION)
    print("Initialize position = ", pos)
    min = LensCtrl.NoErrChk2BytesIntRead(DA.ZOOM_MECH_STEP_MIN)
    print("Mechanical min = ", min)
    max = LensCtrl.NoErrChk2BytesIntRead(DA.ZOOM_MECH_STEP_MAX)
    print("Mechanical max = ", max)
    print("Position min = ", LensCtrl.zoomMinAddr)
    print("Position max = ", LensCtrl.zoomMaxAddr)
    print("Speed value = ", LensCtrl.zoomSpeedPPS)
    retval, speedMin = LensCtrl.ZoomSpeedMinRead()
    print("Speed min = ", speedMin)
    retval, speedMax = LensCtrl.ZoomSpeedMaxRead()
    print("Speed max = ", speedMax)
    retval, count = LensCtrl.ZoomCountValRead()
    print("Count value = ", count)
    retval, countMax = LensCtrl.ZoomCountMaxRead()
    print("Count max = ", countMax)



def FocusInfo():
    print("\n***** FOCUS Information *****")
    print("Current position = ", LensCtrl.focusCurrentAddr)
    retval, flag = LensCtrl.FocusBacklashRead()
    print("Backlash correction = ", flag)
    pos = LensCtrl.NoErrChk2BytesIntRead(DA.FOCUS_INIT_POSITION)
    print("Initialize position = ", pos)
    print("Mechanical min = ", LensCtrl.focusMinAddr)
    print("Mechanical max = ", LensCtrl.focusMaxAddr)
    min = LensCtrl.NoErrChk2BytesIntRead(DA.FOCUS_POSITION_MIN)
    print("Position min = ", min)
    max = LensCtrl.NoErrChk2BytesIntRead(DA.FOCUS_POSITION_MAX)
    print("Position max = ", max)
    print("Speed value = ", LensCtrl.focusSpeedPPS)
    retval, speedMin = LensCtrl.FocusSpeedMinRead()
    print("Speed min = ", speedMin)
    retval, speedMax = LensCtrl.FocusSpeedMaxRead()
    print("Speed max = ", speedMax)
    retval, count = LensCtrl.FocusCountValRead()
    print("Count value = ", count)
    retval, countMax = LensCtrl.FocusCountMaxRead()
    print("Count max = ", countMax)

def IrisInfo():
    print("\n***** IRIS Information *****")
    print("Current position = ", LensCtrl.irisCurrentAddr)
    retval, flag = LensCtrl.IrisBacklashRead()
    print("Backlash correction = ", flag)
    pos = LensCtrl.NoErrChk2BytesIntRead(DA.IRIS_INIT_POSITION)
    print("Initialize position = ", pos)
    print("Mechanical min = ", LensCtrl.irisMinAddr)
    print("Mechanical max = ", LensCtrl.irisMaxAddr)
    min = LensCtrl.NoErrChk2BytesIntRead(DA.IRIS_POSITION_MIN)
    print("Position min = ", min)
    max = LensCtrl.NoErrChk2BytesIntRead(DA.IRIS_POSITION_MAX)
    print("Position max = ", max)
    print("Speed value = ", LensCtrl.irisSpeedPPS)
    retval, speedMin = LensCtrl.IrisSpeedMinRead()
    print("Speed min = ", speedMin)
    retval, speedMax = LensCtrl.IrisSpeedMaxRead()
    print("Speed max = ", speedMax)
    retval, count = LensCtrl.IrisCountValRead()
    print("Count value = ", count)
    retval, countMax = LensCtrl.IrisCountMaxRead()
    print("Count max = ", countMax)

def OptFilterInfo():
    print("\n***** OPTICAL FILTER Information *****")
    print("Current position = ", LensCtrl.optCurrentAddr)
    pos = LensCtrl.NoErrChk2BytesIntRead(DA.OPT_FILTER_INIT_POSITION)
    print("Initialize position = ", pos)
    print("Mechanical min = ", 0)
    print("Mechanical max = ", LensCtrl.optFilMaxAddr)
    print("Position min = ", 0)
    max = LensCtrl.NoErrChk2BytesIntRead(DA.OPT_FILTER_POSITION_MAX)
    print("Position max = ", max)
    retval, count = LensCtrl.OPtFilterCountValRead()
    print("Count value = ", count)
    retval, countMax = LensCtrl.OptFilterCountMaxRead()
    print("Count max = ", countMax)
