#ifndef DMCDRC_H
	#define DMCDRC_H

// IMPORTANT: Constant values for data record item offsets can change between
// firmware revisions. Use the QZ command or the function DMCGetDataRecordRevision
// to determine what revision of data record access you have.
//
// The DMCGetDataRecordByItemId function retrieves a data record item by unique
// Id while the DMCGetDataRecord function retrieves a data record item by offset.
// While data record item offsets can change with the firmware revision, the data
// record item Ids always remain the same.

// Old data record access constants for backwards
// compatibility are located in the file DMCDRCO.H
#include "dmcdrco.h"

// Constant values for data record data types
enum DMCDataRecordTypes
{
	DRTypeUnknown = 0,
	DRTypeCHAR = 1,
	DRTypeUCHAR = 2,
	DRTypeSHORT = 3,
	DRTypeUSHORT = 4,
	DRTypeLONG = 5,
	DRTypeULONG = 6
};

// Constant values for data record item Ids to be used with the function
// DMCGetDataRecordByItemId
enum DMCDataRecordItemIds
{
   DRIdSampleNumber = 1,
	DRIdGeneralInput0,
	DRIdGeneralInput1,
	DRIdGeneralInput2,
	DRIdGeneralInput3,
	DRIdGeneralInput4,
	DRIdGeneralInput5,
	DRIdGeneralInput6,
	DRIdGeneralInput7,
	DRIdGeneralInput8,
	DRIdGeneralInput9,
	DRIdGeneralOutput0,
	DRIdGeneralOutput1,
	DRIdGeneralOutput2,
	DRIdGeneralOutput3,
	DRIdGeneralOutput4,
	DRIdGeneralOutput5,
	DRIdGeneralOutput6,
	DRIdGeneralOutput7,
	DRIdGeneralOutput8,
	DRIdGeneralOutput9,
	DRIdErrorCode,
	DRIdGeneralStatus,
	DRIdSegmentCountS,
	DRIdCoordinatedMoveStatusS,
	DRIdCoordinatedMoveDistanceS,
	DRIdSegmentCountT,
	DRIdCoordinatedMoveStatusT,
	DRIdCoordinatedMoveDistanceT,
	DRIdAnalogInput1,
	DRIdAnalogInput2,
	DRIdAnalogInput3,
	DRIdAnalogInput4,
	DRIdAnalogInput5,
	DRIdAnalogInput6,
	DRIdAnalogInput7,
	DRIdAnalogInput8,
	DRIdAxisStatus,
	DRIdAxisSwitches,
	DRIdAxisStopCode,
	DRIdAxisReferencePosition,
	DRIdAxisMotorPosition,
	DRIdAxisPositionError,
	DRIdAxisAuxillaryPosition,
	DRIdAxisVelocity,
	DRIdAxisTorque
};

// Constant values for axis Ids to be used with the function
// DMCGetDataRecordByItemId
enum DMCDataRecordAxisIds
{
	DRIdAxis1 = 1,
	DRIdAxis2,
	DRIdAxis3,
	DRIdAxis4,
	DRIdAxis5,
	DRIdAxis6,
	DRIdAxis7,
	DRIdAxis8
};

// Data record offsets

// Rev 1 constants
//    QZ command returns <#axes>,12,6,26

// Rev 2 constants
//    QZ command returns <#axes>,26,6,26
//    This rev added items to the general section for extended I/O.

// Rev 3 constants
//    QZ command returns <#axes>,24,16,26
//    This rev added items to the general section for the coordinated motion T axis.

// Rev 4 constants
//    QZ command returns <#axes>,24,16,28
//    This rev added 1 item to the axis section for analog inputs.
//    Note: each axis will now include the current value for 1 analog input.
//    X axis - analog 1, Y axis - analog 2, and so on. You must have an 8 axis
//    controller to get data for all 8 analog inputs.

// Rev 1 General data item offsets
enum REV1DMCDataRecordGeneralOffsets
{
   DRREV1GenOffSampleNumber = 0,
	DRREV1GenOffGeneralInput1 = 2,
	DRREV1GenOffGeneralInput2 = 3,
	DRREV1GenOffGeneralInput3 = 4,
	DRREV1GenOffSpare = 5,
	DRREV1GenOffGeneralOutput1 = 6,
	DRREV1GenOffGeneralOutput2 = 7,
	DRREV1GenOffErrorCode = 8,
	DRREV1GenOffGeneralStatus = 9,
	DRREV1GenOffSegmentCount = 10,
	DRREV1GenOffCoordinatedMoveStatus = 12,
	DRREV1GenOffCoordinatedMoveDistance = 14,
	DRREV1GenOffAxis1 = 18,
	DRREV1GenOffAxis2 = 44,
	DRREV1GenOffAxis3 = 70,
	DRREV1GenOffAxis4 = 96,
	DRREV1GenOffAxis5 = 122,
	DRREV1GenOffAxis6 = 148,
	DRREV1GenOffAxis7 = 174,
	DRREV1GenOffAxis8 = 200,
	DRREV1GenOffEnd = 226
};

// Rev 1 axis data item offsets
enum REV1DMCDataRecordAxisOffsets
{
	DRREV1AxisOffNoAxis = 0,
	DRREV1AxisOffAxisStatus = 0,
	DRREV1AxisOffAxisSwitches = 2,
	DRREV1AxisOffAxisStopCode = 3,
	DRREV1AxisOffAxisReferencePosition = 4,
	DRREV1AxisOffAxisMotorPosition = 8,
	DRREV1AxisOffAxisPositionError = 12,
	DRREV1AxisOffAxisAuxillaryPosition = 16,
	DRREV1AxisOffAxisVelocity = 20,
	DRREV1AxisOffAxisTorque = 24,
	DRREV1AxisOffEnd = 26
};

// Rev 2 General data item offsets
enum REV2DMCDataRecordGeneralOffsets
{
   DRREV2GenOffSampleNumber = 0,
	DRREV2GenOffGeneralInput0 = 2,
	DRREV2GenOffGeneralInput1 = 3,
	DRREV2GenOffGeneralInput2 = 4,
	DRREV2GenOffGeneralInput3 = 5,
	DRREV2GenOffGeneralInput4 = 6,
	DRREV2GenOffGeneralInput5 = 7,
	DRREV2GenOffGeneralInput6 = 8,
	DRREV2GenOffGeneralInput7 = 9,
	DRREV2GenOffGeneralInput8 = 10,
	DRREV2GenOffGeneralInput9 = 11,
	DRREV2GenOffGeneralOutput0 = 12,
	DRREV2GenOffGeneralOutput1 = 13,
	DRREV2GenOffGeneralOutput2 = 14,
	DRREV2GenOffGeneralOutput3 = 15,
	DRREV2GenOffGeneralOutput4 = 16,
	DRREV2GenOffGeneralOutput5 = 17,
	DRREV2GenOffGeneralOutput6 = 18,
	DRREV2GenOffGeneralOutput7 = 19,
	DRREV2GenOffGeneralOutput8 = 20,
	DRREV2GenOffGeneralOutput9 = 21,
	DRREV2GenOffErrorCode = 22,
	DRREV2GenOffGeneralStatus = 23,
	DRREV2GenOffSegmentCount = 24,
	DRREV2GenOffCoordinatedMoveStatus = 26,
	DRREV2GenOffCoordinatedMoveDistance = 28,
	DRREV2GenOffAxis1 = 32,
	DRREV2GenOffAxis2 = 58,
	DRREV2GenOffAxis3 = 84,
	DRREV2GenOffAxis4 = 110,
	DRREV2GenOffAxis5 = 136,
	DRREV2GenOffAxis6 = 162,
	DRREV2GenOffAxis7 = 188,
	DRREV2GenOffAxis8 = 214,
	DRREV2GenOffEnd = 240
};

// Rev 2 axis data item offsets
enum REV2DMCDataRecordAxisOffsets
{
	DRREV2AxisOffNoAxis = 0,
	DRREV2AxisOffAxisStatus = 0,
	DRREV2AxisOffAxisSwitches = 2,
	DRREV2AxisOffAxisStopCode = 3,
	DRREV2AxisOffAxisReferencePosition = 4,
	DRREV2AxisOffAxisMotorPosition = 8,
	DRREV2AxisOffAxisPositionError = 12,
	DRREV2AxisOffAxisAuxillaryPosition = 16,
	DRREV2AxisOffAxisVelocity = 20,
	DRREV2AxisOffAxisTorque = 24,
	DRREV2AxisOffEnd = 26
};

// Rev 3 General data item offsets
enum REV3DMCDataRecordGeneralOffsets
{
   DRREV3GenOffSampleNumber = 0,
	DRREV3GenOffGeneralInput0 = 2,
	DRREV3GenOffGeneralInput1 = 3,
	DRREV3GenOffGeneralInput2 = 4,
	DRREV3GenOffGeneralInput3 = 5,
	DRREV3GenOffGeneralInput4 = 6,
	DRREV3GenOffGeneralInput5 = 7,
	DRREV3GenOffGeneralInput6 = 8,
	DRREV3GenOffGeneralInput7 = 9,
	DRREV3GenOffGeneralInput8 = 10,
	DRREV3GenOffGeneralInput9 = 11,
	DRREV3GenOffGeneralOutput0 = 12,
	DRREV3GenOffGeneralOutput1 = 13,
	DRREV3GenOffGeneralOutput2 = 14,
	DRREV3GenOffGeneralOutput3 = 15,
	DRREV3GenOffGeneralOutput4 = 16,
	DRREV3GenOffGeneralOutput5 = 17,
	DRREV3GenOffGeneralOutput6 = 18,
	DRREV3GenOffGeneralOutput7 = 19,
	DRREV3GenOffGeneralOutput8 = 20,
	DRREV3GenOffGeneralOutput9 = 21,
	DRREV3GenOffErrorCode = 22,
	DRREV3GenOffGeneralStatus = 23,
	DRREV3GenOffSegmentCountS = 24,
	DRREV3GenOffCoordinatedMoveStatusS = 26,
	DRREV3GenOffCoordinatedMoveDistanceS = 28,
	DRREV3GenOffSegmentCountT = 32,
	DRREV3GenOffCoordinatedMoveStatusT = 34,
	DRREV3GenOffCoordinatedMoveDistanceT = 36,
	DRREV3GenOffAxis1 = 40,
	DRREV3GenOffAxis2 = 66,
	DRREV3GenOffAxis3 = 92,
	DRREV3GenOffAxis4 = 118,
	DRREV3GenOffAxis5 = 144,
	DRREV3GenOffAxis6 = 170,
	DRREV3GenOffAxis7 = 196,
	DRREV3GenOffAxis8 = 222,
	DRREV3GenOffEnd = 248
};

// Rev 3 axis data item offsets
enum REV3DMCDataRecordAxisOffsets
{
	DRREV3AxisOffNoAxis = 0,
	DRREV3AxisOffAxisStatus = 0,
	DRREV3AxisOffAxisSwitches = 2,
	DRREV3AxisOffAxisStopCode = 3,
	DRREV3AxisOffAxisReferencePosition = 4,
	DRREV3AxisOffAxisMotorPosition = 8,
	DRREV3AxisOffAxisPositionError = 12,
	DRREV3AxisOffAxisAuxillaryPosition = 16,
	DRREV3AxisOffAxisVelocity = 20,
	DRREV3AxisOffAxisTorque = 24,
	DRREV3AxisOffEnd = 26
};

// Rev 4 General data item offsets
enum REV4DMCDataRecordGeneralOffsets
{
   DRREV4GenOffSampleNumber = 0,
	DRREV4GenOffGeneralInput0 = 2,
	DRREV4GenOffGeneralInput1 = 3,
	DRREV4GenOffGeneralInput2 = 4,
	DRREV4GenOffGeneralInput3 = 5,
	DRREV4GenOffGeneralInput4 = 6,
	DRREV4GenOffGeneralInput5 = 7,
	DRREV4GenOffGeneralInput6 = 8,
	DRREV4GenOffGeneralInput7 = 9,
	DRREV4GenOffGeneralInput8 = 10,
	DRREV4GenOffGeneralInput9 = 11,
	DRREV4GenOffGeneralOutput0 = 12,
	DRREV4GenOffGeneralOutput1 = 13,
	DRREV4GenOffGeneralOutput2 = 14,
	DRREV4GenOffGeneralOutput3 = 15,
	DRREV4GenOffGeneralOutput4 = 16,
	DRREV4GenOffGeneralOutput5 = 17,
	DRREV4GenOffGeneralOutput6 = 18,
	DRREV4GenOffGeneralOutput7 = 19,
	DRREV4GenOffGeneralOutput8 = 20,
	DRREV4GenOffGeneralOutput9 = 21,
	DRREV4GenOffErrorCode = 22,
	DRREV4GenOffGeneralStatus = 23,
	DRREV4GenOffSegmentCountS = 24,
	DRREV4GenOffCoordinatedMoveStatusS = 26,
	DRREV4GenOffCoordinatedMoveDistanceS = 28,
	DRREV4GenOffSegmentCountT = 32,
	DRREV4GenOffCoordinatedMoveStatusT = 34,
	DRREV4GenOffCoordinatedMoveDistanceT = 36,
	DRREV4GenOffAxis1 = 40,
	DRREV4GenOffAxis2 = 68,
	DRREV4GenOffAxis3 = 96,
	DRREV4GenOffAxis4 = 124,
	DRREV4GenOffAxis5 = 152,
	DRREV4GenOffAxis6 = 180,
	DRREV4GenOffAxis7 = 208,
	DRREV4GenOffAxis8 = 236,
	DRREV4GenOffEnd = 264
};

// Rev 4 axis data item offsets
enum REV4DMCDataRecordAxisOffsets
{
	DRREV4AxisOffNoAxis = 0,
	DRREV4AxisOffAxisStatus = 0,
	DRREV4AxisOffAxisSwitches = 2,
	DRREV4AxisOffAxisStopCode = 3,
	DRREV4AxisOffAxisReferencePosition = 4,
	DRREV4AxisOffAxisMotorPosition = 8,
	DRREV4AxisOffAxisPositionError = 12,
	DRREV4AxisOffAxisAuxillaryPosition = 16,
	DRREV4AxisOffAxisVelocity = 20,
	DRREV4AxisOffAxisTorque = 24,
	DRREV4AxisOffAnalogInput = 26,
	DRREV4AxisOffEnd = 28
};

// Data record structures used with QR command and function DMCCopyDataRecord

// Some controllers such as the DMC-1802 and the DMC-2000 do not implement the
// data record access feature with a secondary channel. They do, however, support
// a form of data record access via the QR command.  This command returns, in binary
// format, a copy of the current data record on demand. Use the structure below to
// overlay the binary data returned. It can be used with the function DMCCommand in the
// following way:
//
//    LONG rc;
//    DMCDATARECORDQR MyDataRecordQR;
//    rc = DMCCommand(hdmc, "QR\r", &MyDataRecordQR, sizeof(MyDataRecordQR));
//
// The QR command can return a full copy of the data record or a subset depending on
// the arguments used with it. For more information, consult the Galil Command Reference.
//
// For controllers which implement data record access feature with a secondary channel,
// the function DMCCopyDataRecord can be used to retrieve a copy of the current data record
// (current as of the last call to the function DMCRefreshDataRecord). The structure
// DMCDATARECORD can be used as template for the data returned. The actual length of the data
// returned can be determined by using the function DMCGetDataRecordSize. You MUST allocate
// sufficient storage for the entire data record before calling the function DMCCopyDataRecord.
// An example follows:
//
//    LONG rc;
//    USHORT RecordSize;
//    DMCDATARECORD MyDataRecord;
//    rc = DMCGetDataRecordSize(hdmc, &RecordSize);
//    if (sizeof(MyDataRecord) >= RecordSize)
//       rc = DMCCopyDataRecord(hdmc, (PVOID)&MyDataRecord); // Safe to make call
//    else
//       ;                                                   // Must allocate more storage
//                                                           // by adjusting structure
//
// NOTE: You should change the AxisInfo array declaration in DMCDATARECORD to match the
// number of axes for your controller. You should also delete any members from the structure
// which are not included in the data record revision of your controller.
//
// NOTE: These structures can change between firmware revisions.

// Structure must be aligned on 1 byte boundary
#pragma pack(1)

typedef struct _DMCAXISINFO
{
	USHORT	Status;
	UCHAR		Switches;
	UCHAR		StopCode;
	LONG		ReferencePosition;
	LONG		MotorPosition;
	LONG		PositionError;
	LONG		AuxillaryPosition;
	LONG		Velocity;
	SHORT		Torque;
	SHORT		AnalogInput;               // Rev 4 and above
} DMCAXISINFO, FAR* PDMCAXISINFO;

typedef struct _DMCDATARECORD
{
   USHORT	SampleNumber;
	UCHAR		Input0;
	UCHAR		Input1;
	UCHAR		Input2;
	UCHAR		Input3;
	UCHAR		Input4;
	UCHAR		Input5;                    // Rev 3 and above
	UCHAR		Input6;                    // Rev 3 and above
	UCHAR		Input7;                    // Rev 3 and above
	UCHAR		Input8;                    // Rev 3 and above
	UCHAR		Input9;                    // Rev 3 and above
	UCHAR		Output0;
	UCHAR		Output1;
	UCHAR		Output2;                   // Rev 3 and above
	UCHAR		Output3;                   // Rev 3 and above
	UCHAR		Output4;                   // Rev 3 and above
	UCHAR		Output5;                   // Rev 3 and above
	UCHAR		Output6;                   // Rev 3 and above
	UCHAR		Output7;                   // Rev 3 and above
	UCHAR		Output8;                   // Rev 3 and above
	UCHAR		Output9;                   // Rev 3 and above
	UCHAR		ErrorCode;
	UCHAR		GeneralStatus;
	USHORT	SegmentCountS;
	USHORT	CoordinatedMoveStatusS;
	LONG		CoordinatedMoveDistanceS;
	USHORT	SegmentCountT;             // Rev 3 and above
	USHORT	CoordinatedMoveStatusT;    // Rev 3 and above
	LONG		CoordinatedMoveDistanceT;  // Rev 3 and above
	DMCAXISINFO	AxisInfo[8];            // One DMCAXISINFO struct for each axis
} DMCDATARECORD, FAR* PDMCDATARECORD;

typedef struct _DMCDATARECORDQR
{
   USHORT fSAxis    :1;                // Contains Axis S info
   USHORT fTAxis    :1;                // Contains Axis T info
   USHORT fIO       :1;                // Contains I/O info
   USHORT fReserved :5;
   USHORT fAxis1    :1;                // Contains Axis 1 info
   USHORT fAxis2    :1;						// Contains Axis 2 info
   USHORT fAxis3    :1;                // Contains Axis 3 info
   USHORT fAxis4    :1;                // Contains Axis 4 info
   USHORT fAxis5    :1;                // Contains Axis 5 info
   USHORT fAxis6    :1;                // Contains Axis 6 info
   USHORT fAxis7    :1;                // Contains Axis 7 info
   USHORT fAxis8    :1;                // Contains Axis 8 info
	USHORT			usDataLength;        // Length of data returned from QR command
	DMCDATARECORD	DataRecord;
	UCHAR				Padding[4];          // Extra space to hold "\r\n:" added by QR command
} DMCDATARECORDQR, FAR* PDMCDATARECORDQR;

#pragma pack()

#endif // DMCDRC_H
