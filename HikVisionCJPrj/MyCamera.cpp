#include "MyCamera.h"
#include <string.h>

CMyCamera::CMyCamera()
{
	m_hook = NULL;
	m_hDevHandle = NULL;
}

CMyCamera::~CMyCamera()
{
	if (m_hDevHandle)
	{
		MV_CC_DestroyHandle(m_hDevHandle);
		m_hDevHandle = NULL;
	}
}
void __stdcall MyImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
{
	m_hook->ImageCallBackEx(pData, pFrameInfo, pUser);
}
std::string CMyCamera::GetLastErr()
{
	std::string errorMsg;
	switch (m_errType)
	{
	case MV_E_HANDLE:           errorMsg += "Error or invalid handle ";                                         break;
	case MV_E_SUPPORT:          errorMsg += "Not supported function ";                                          break;
	case MV_E_BUFOVER:          errorMsg += "Cache is full ";                                                   break;
	case MV_E_CALLORDER:        errorMsg += "Function calling order error ";                                    break;
	case MV_E_PARAMETER:        errorMsg += "Incorrect parameter ";                                             break;
	case MV_E_RESOURCE:         errorMsg += "Applying resource failed ";                                        break;
	case MV_E_NODATA:           errorMsg += "No data ";                                                         break;
	case MV_E_PRECONDITION:     errorMsg += "Precondition error, or running environment changed ";              break;
	case MV_E_VERSION:          errorMsg += "Version mismatches ";                                              break;
	case MV_E_NOENOUGH_BUF:     errorMsg += "Insufficient memory ";                                             break;
	case MV_E_ABNORMAL_IMAGE:   errorMsg += "Abnormal image, maybe incomplete image because of lost packet ";   break;
	case MV_E_UNKNOW:           errorMsg += "Unknown error ";                                                   break;
	case MV_E_GC_GENERIC:       errorMsg += "General error ";                                                   break;
	case MV_E_GC_ACCESS:        errorMsg += "Node accessing condition error ";                                  break;
	case MV_E_ACCESS_DENIED:	errorMsg += "No permission ";                                                   break;
	case MV_E_BUSY:             errorMsg += "Device is busy, or network disconnected ";                         break;
	case MV_E_NETER:            errorMsg += "Network error ";                                                   break;
	}
	return errorMsg;
}


int CMyCamera::Init(CallBackEx* hook)
{
	int eRet = MV_OK;
	m_hook = hook;
	MV_CC_DEVICE_INFO_LIST pstDevList;
	memset(&pstDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	eRet = EnumDevices(&pstDevList);
	if (MV_OK != eRet)
	{
		m_errType = eRet;
		return eRet;
	}
	MV_CC_DEVICE_INFO* pDeviceInfo;

	if (pstDevList.nDeviceNum > 0)
	{
		pDeviceInfo = pstDevList.pDeviceInfo[0]; //相机个数指定为一个
	}
	else
	{
		m_errType = MV_E_HANDLE;
		return MV_E_HANDLE;
	}
	if (pDeviceInfo == NULL)
	{
		m_errType = MV_E_HANDLE;
		return MV_E_HANDLE;
	}
	int oRet = MV_OK;
	oRet = Open(pDeviceInfo);
	if (MV_OK != oRet)
	{
		m_errType = oRet;
		return oRet;
	}
	int tRet = MV_OK;
	tRet = SetEnumValue("TriggerMode", MV_TRIGGER_MODE_ON);//触发模式
	if (MV_OK != tRet)
	{
		m_errType = tRet;
		return tRet;
	}
	int rRet = MV_OK;
	rRet = MV_CC_RegisterImageCallBackEx(m_hDevHandle, MyImageCallBackEx, m_hDevHandle);
	if (MV_OK != rRet)
	{
		m_errType = rRet;
		return rRet;
	}
// 	int reRet = MV_OK;
// 	reRet = MV_CC_RegisterExceptionCallBack(m_hDevHandle, ExceptionCallBack, m_hDevHandle);
// 	if (MV_OK != reRet)
// 	{
// 		printf("fail! rRet [0x%x]\n", reRet);
// 		return reRet;
// 	}
	int sRet = MV_OK;
	sRet = StartGrabbing();
	if (MV_OK != sRet)
	{
		m_errType = sRet;
		return sRet;
	}
	int stRet = MV_OK;
	stRet = SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_SOFTWARE);//软触发模式
	if (MV_OK != stRet)
	{
		m_errType = stRet;
		return stRet;
	}
	return MV_OK;
}

int CMyCamera::SoftwareTrigger()
{
	int nRet = MV_OK;
	nRet = CommandExecute("TriggerSoftware");
	if (MV_OK != nRet)
	{
		m_errType = nRet;
	}
	return nRet;
}

int CMyCamera::EnumDevices(MV_CC_DEVICE_INFO_LIST* pstDevList)
{
	int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, pstDevList);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	return MV_OK;
}

// ch:打开设备 | en:Open Device
int     CMyCamera::Open(MV_CC_DEVICE_INFO* pstDeviceInfo)
{
	if (NULL == pstDeviceInfo)
	{
		return MV_E_PARAMETER;
	}

	int nRet = MV_OK;
	if (m_hDevHandle == NULL)
	{
		nRet = MV_CC_CreateHandle(&m_hDevHandle, pstDeviceInfo);
		if (MV_OK != nRet)
		{
			return nRet;
		}
	}

	nRet = MV_CC_OpenDevice(m_hDevHandle);
	if (MV_OK != nRet)
	{
		MV_CC_DestroyHandle(m_hDevHandle);
		m_hDevHandle = NULL;

		return nRet;
	}

	return MV_OK;
}
// ch:关闭设备 | en:Close Device
int     CMyCamera::Close()
{
	int nRet = MV_OK;

	if (NULL == m_hDevHandle)
	{
		return MV_E_PARAMETER;
	}

	nRet =MV_CC_CloseDevice(m_hDevHandle);
	if (MV_OK != nRet)
	{
		m_errType = nRet;
		return nRet;
	}
	nRet = MV_CC_DestroyHandle(m_hDevHandle);
	if (MV_OK != nRet)
	{
		m_errType = nRet;
		return nRet;
	}
	m_hDevHandle = NULL;

	return nRet;
}


// ch:开启抓图 | en:Start Grabbing
int     CMyCamera::StartGrabbing()
{
	return MV_CC_StartGrabbing(m_hDevHandle);
}


// ch:停止抓图 | en:Stop Grabbing
int     CMyCamera::StopGrabbing()
{
	return MV_CC_StopGrabbing(m_hDevHandle);
}

int     CMyCamera::GetOneFrameTimeout(unsigned char* pData, unsigned int* pnDataLen, unsigned int nDataSize, MV_FRAME_OUT_INFO_EX* pFrameInfo, int nMsec)
{
	if (NULL == pnDataLen)
	{
		return MV_E_PARAMETER;
	}

	int nRet = MV_OK;

	*pnDataLen = 0;

	nRet = MV_CC_GetOneFrameTimeout(m_hDevHandle, pData, nDataSize, pFrameInfo, nMsec);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	*pnDataLen = pFrameInfo->nFrameLen;

	return nRet;
}


// ch:设置显示窗口句柄 | en:Set Display Window Handle
int     CMyCamera::Display(void* hWnd)
{
	return MV_CC_Display(m_hDevHandle, hWnd);
}


int CMyCamera::SaveImage(MV_SAVE_IMAGE_PARAM_EX* pstParam)
{
	if (NULL == pstParam)
	{
		return MV_E_PARAMETER;
	}

	return MV_CC_SaveImageEx2(m_hDevHandle, pstParam);
}

// ch:注册图像数据回调 | en:Register Image Data CallBack
int CMyCamera::RegisterImageCallBack(void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo,
	void* pUser), void* pUser)
{
	return MV_CC_RegisterImageCallBackEx(m_hDevHandle, cbOutput, pUser);
}


// ch:注册消息异常回调 | en:Register Message Exception CallBack
int     CMyCamera::RegisterExceptionCallBack(void(__stdcall* cbException)(unsigned int nMsgType, void* pUser), void* pUser)
{
	return MV_CC_RegisterExceptionCallBack(m_hDevHandle, cbException, pUser);
}


// ch:获取Int型参数，如 Width和Height，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
// en:Get Int type parameters, such as Width and Height, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::GetIntValue(IN const char* strKey, OUT unsigned int *pnValue)
{
	if (NULL == strKey || NULL == pnValue)
	{
		return MV_E_PARAMETER;
	}

	MVCC_INTVALUE stParam;
	memset(&stParam, 0, sizeof(MVCC_INTVALUE));
	int nRet = MV_CC_GetIntValue(m_hDevHandle, strKey, &stParam);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	*pnValue = stParam.nCurValue;

	return MV_OK;
}


// ch:设置Int型参数，如 Width和Height，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
// en:Set Int type parameters, such as Width and Height, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::SetIntValue(IN const char* strKey, IN unsigned int nValue)
{
	if (NULL == strKey)
	{
		return MV_E_PARAMETER;
	}

	return MV_CC_SetIntValue(m_hDevHandle, strKey, nValue);
}


// ch:获取Float型参数，如 ExposureTime和Gain，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
// en:Get Float type parameters, such as ExposureTime and Gain, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::GetFloatValue(IN const char* strKey, OUT float *pfValue)
{
	if (NULL == strKey || NULL == pfValue)
	{
		return MV_E_PARAMETER;
	}

	MVCC_FLOATVALUE stParam;
	memset(&stParam, 0, sizeof(MVCC_FLOATVALUE));
	int nRet = MV_CC_GetFloatValue(m_hDevHandle, strKey, &stParam);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	*pfValue = stParam.fCurValue;

	return MV_OK;
}


// ch:设置Float型参数，如 ExposureTime和Gain，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
// en:Set Float type parameters, such as ExposureTime and Gain, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::SetFloatValue(IN const char* strKey, IN float fValue)
{
	if (NULL == strKey)
	{
		return MV_E_PARAMETER;
	}

	return MV_CC_SetFloatValue(m_hDevHandle, strKey, fValue);
}


// ch:获取Enum型参数，如 PixelFormat，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
// en:Get Enum type parameters, such as PixelFormat, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::GetEnumValue(IN const char* strKey, OUT unsigned int *pnValue)
{
	if (NULL == strKey || NULL == pnValue)
	{
		return MV_E_PARAMETER;
	}

	MVCC_ENUMVALUE stParam;
	memset(&stParam, 0, sizeof(MVCC_ENUMVALUE));
	int nRet = MV_CC_GetEnumValue(m_hDevHandle, strKey, &stParam);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	*pnValue = stParam.nCurValue;

	return MV_OK;
}


// ch:设置Enum型参数，如 PixelFormat，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
// en:Set Enum type parameters, such as PixelFormat, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::SetEnumValue(IN const char* strKey, IN unsigned int nValue)
{
	if (NULL == strKey)
	{
		return MV_E_PARAMETER;
	}

	return MV_CC_SetEnumValue(m_hDevHandle, strKey, nValue);
}


// ch:获取Bool型参数，如 ReverseX，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
// en:Get Bool type parameters, such as ReverseX, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::GetBoolValue(IN const char* strKey, OUT bool *pbValue)
{
	if (NULL == strKey || NULL == pbValue)
	{
		return MV_E_PARAMETER;
	}

	return MV_CC_GetBoolValue(m_hDevHandle, strKey, pbValue);
}


// ch:设置Bool型参数，如 ReverseX，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
// en:Set Bool type parameters, such as ReverseX, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::SetBoolValue(IN const char* strKey, IN bool bValue)
{
	if (NULL == strKey)
	{
		return MV_E_PARAMETER;
	}

	return MV_CC_SetBoolValue(m_hDevHandle, strKey, bValue);
}


// ch:获取String型参数，如 DeviceUserID，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件UserSetSave
// en:Get String type parameters, such as DeviceUserID, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::GetStringValue(IN const char* strKey, IN OUT char* strValue, IN unsigned int nSize)
{
	if (NULL == strKey || NULL == strValue)
	{
		return MV_E_PARAMETER;
	}

	MVCC_STRINGVALUE stParam;
	memset(&stParam, 0, sizeof(MVCC_STRINGVALUE));
	int nRet = MV_CC_GetStringValue(m_hDevHandle, strKey, &stParam);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	strcpy_s(strValue, nSize, stParam.chCurValue);

	return MV_OK;
}


// ch:设置String型参数，如 DeviceUserID，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件UserSetSave
// en:Set String type parameters, such as DeviceUserID, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::SetStringValue(IN const char* strKey, IN const char* strValue)
{
	if (NULL == strKey)
	{
		return MV_E_PARAMETER;
	}

	return MV_CC_SetStringValue(m_hDevHandle, strKey, strValue);
}


// ch:执行一次Command型命令，如 UserSetSave，详细内容参考SDK安装目录下的 MvCameraNode.xlsx 文件
// en:Execute Command once, such as UserSetSave, for details please refer to MvCameraNode.xlsx file under SDK installation directory
int     CMyCamera::CommandExecute(IN const char* strKey)
{
	if (NULL == strKey)
	{
		return MV_E_PARAMETER;
	}

	return MV_CC_SetCommandValue(m_hDevHandle, strKey);
}

int CMyCamera::GetOptimalPacketSize()
{
	return MV_CC_GetOptimalPacketSize(m_hDevHandle);
}

int  CMyCamera::GetAllMatchInfo(OUT unsigned int *nLostFrame, OUT unsigned int *nFrameCount)
{
	MV_CC_DEVICE_INFO stDevInfo = { 0 };
	int nRet = MV_CC_GetDeviceInfo(m_hDevHandle, &stDevInfo); //该接口u3暂不支持，用此方式来判断u3还是GigE
	if (MV_E_SUPPORT == nRet)
	{
		stDevInfo.nTLayerType = MV_USB_DEVICE;
	}

	if (MV_GIGE_DEVICE == stDevInfo.nTLayerType)
	{
		MV_ALL_MATCH_INFO struMatchInfo = { 0 };
		MV_MATCH_INFO_NET_DETECT stMatchInfoNetDetect;
		struMatchInfo.pInfo = &stMatchInfoNetDetect;

		struMatchInfo.nType = MV_MATCH_TYPE_NET_DETECT; // ch:网络流量和丢包信息 | en:Net flow and lsot packet information
		memset(struMatchInfo.pInfo, 0, sizeof(MV_MATCH_INFO_NET_DETECT));
		struMatchInfo.nInfoSize = sizeof(MV_MATCH_INFO_NET_DETECT);

		nRet = MV_CC_GetAllMatchInfo(m_hDevHandle, &struMatchInfo);
		if (MV_OK != nRet)
		{
			return nRet;
		}

		MV_MATCH_INFO_NET_DETECT *pInfo = (MV_MATCH_INFO_NET_DETECT*)struMatchInfo.pInfo;
		*nFrameCount = pInfo->nNetRecvFrameCount;
		*nLostFrame = stMatchInfoNetDetect.nLostFrameCount;
	}
	else if (MV_USB_DEVICE == stDevInfo.nTLayerType)
	{
		MV_ALL_MATCH_INFO struMatchInfo = { 0 };
		MV_MATCH_INFO_USB_DETECT stMatchInfoNetDetect;
		struMatchInfo.pInfo = &stMatchInfoNetDetect;

		struMatchInfo.nType = MV_MATCH_TYPE_USB_DETECT; // ch:网络流量和丢包信息 | en:Net flow and lsot packet information
		memset(struMatchInfo.pInfo, 0, sizeof(MV_MATCH_INFO_USB_DETECT));
		struMatchInfo.nInfoSize = sizeof(MV_MATCH_INFO_USB_DETECT);

		nRet = MV_CC_GetAllMatchInfo(m_hDevHandle, &struMatchInfo);
		if (MV_OK != nRet)
		{
			return nRet;
		}

		MV_MATCH_INFO_NET_DETECT *pInfo = (MV_MATCH_INFO_NET_DETECT*)struMatchInfo.pInfo;
		*nFrameCount = pInfo->nNetRecvFrameCount;
		*nLostFrame = stMatchInfoNetDetect.nErrorFrameCount;
	}

	return MV_OK;
}
HikVisionPrj * _stdcall HikVisionPrjInstance(int version)
{
	if (version == KX_HIKVISION_VERSION)
	{
		HikVisionPrj *Hik;
		Hik = (HikVisionPrj *)new CMyCamera;
		return Hik;
	}
	else
	{
		return 0;
	}
}

