#pragma once

#define GRAB_MAIN_VERSION 3
#define GRAB_SUB_VERSION 1

#define GRAB_VERSION ((GRAB_MAIN_VERSION << 16) + GRAB_SUB_VERSION)
#define BUFFQUEUE_SIZE 24

enum GRAB_PARAM_INDEX_CONST
{
	GRAB_NONE = 0,
	GRAB_SHUTTER,
	GRAB_GAIN,
	GRAB_OFFSET,
	GRAB_SOFT_TRIG,
};


struct GRAB_FORMAT
{
	int width , height , bit;
	int cameraCount;
};

class __declspec(novtable) CCardGrabHook
{
public:
	
	virtual int _stdcall OnFrameGrabbed(int frameIndex , BYTE ** imageDataTab , float time) = 0;
	virtual int _stdcall OnFrameGrabbedEx(int frameIndex, BYTE * imageDataTab, float time) = 0;
	virtual void _stdcall OnGrabStop() = 0;
};

class __declspec(novtable) CCardGrab
{
public:
	
//	virtual int EnumDevices(MV_CC_DEVICE_INFO_LIST* pstDevList) = 0;
	virtual int _stdcall Open() = 0;
	virtual int Close() = 0;
	virtual int StartGrabbing() = 0;
// 	virtual int StartGrabbing() = 0;
// 	virtual void _stdcall Free() = 0;
// 	virtual int _stdcall Start(int grabCount = -1) = 0;
// 	virtual void _stdcall Stop() = 0;
// 	virtual int _stdcall SetPara(int paraIndex , void * para) = 0;
// 	virtual int _stdcall GetPara(int paraIndex , void * para) = 0;

};

extern "C" CCardGrab * _stdcall CreateCCardGrabInstance(int version = GRAB_VERSION);