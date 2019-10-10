#define KX_HIKVISION_MAIN_VERSION 1
#define KX_HIKVISION_SUB_VERSION 1
#define KX_HIKVISION_VERSION ((KX_HIKVISION_MAIN_VERSION << 16) + KX_HIKVISION_SUB_VERSION)
#pragma once
#include <string>
#include "MvCameraControl.h"

#define CODE_LIB_SOLUTION
#ifdef  CODE_LIB_SOLUTION
#define CODE_LIB_EXPORT __declspec(dllexport)
#else
#define CODE_LIB_EXPORT __declspec(dllimport)
#endif

class  CallBackEx
{
public:
	/*ͼ��ص�*/
	virtual void __stdcall ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser) = 0;
};
class  HikVisionPrj 
{
public:
	/*���ش�����Ϣ*/
	virtual std::string GetLastErr()=0;
	/*��ʼ��*/
	virtual int Init(CallBackEx* hook) = 0;
	/*����ģʽ*/
	virtual int SoftwareTrigger()=0;
	/*ֹͣ�ɼ�*/
	virtual int StopGrabbing()=0;
	/*�رվ��*/
	virtual int Close()=0;
};
CODE_LIB_EXPORT HikVisionPrj * _stdcall HikVisionPrjInstance(int version = KX_HIKVISION_VERSION);