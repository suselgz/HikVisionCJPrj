#include "QHikVisionTest.h"
#pragma execution_character_set("utf-8")
QHikVisionTest::QHikVisionTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_Hik = (HikVisionPrj *)HikVisionPrjInstance();
}

QHikVisionTest::~QHikVisionTest()
{
	m_Hik->StopGrabbing();
	m_Hik->Close();
	delete m_Hik;
}

void QHikVisionTest::on_pushButton_Init_clicked()
{
	CHook * hook = new CHook;
	int nRet = m_Hik->Init(hook);
	if (nRet != 0)
	{
		showErrMsg(nRet, this);
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "相机初始化成功");
	}
}

void QHikVisionTest::on_pushButton_softTrigger_clicked()
{
	int sRet=m_Hik->SoftwareTrigger();
	if (sRet != 0)
	{
		showErrMsg(sRet, this);
    }
}

void QHikVisionTest::on_pushButton_close_clicked()
{
	m_Hik->Close();
}

void QHikVisionTest::showErrMsg(unsigned int nMsgType, void* pUser)
{
	QString errorMsg;
	switch (nMsgType)
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
	QMessageBox::information(NULL, "INFO", errorMsg);
}

void __stdcall CHook::ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
{
	cv::Mat rltImg;
	int type = 0;
	if (pFrameInfo->enPixelType == PixelType_Gvsp_RGB8_Packed)
	{
		type = 3;
	}
	int bufSize = pFrameInfo->nFrameLen;
	if (bufSize > m_nResizeBufSizeEx)
	{
		if (m_imageRealdata)
		{
			delete[] m_imageRealdata;
		}
		m_imageRealdata = new BYTE[bufSize];
		m_nResizeBufSizeEx = bufSize;
	}
	memcpy(m_imageRealdata, pData, bufSize);
	rltImg = cv::Mat::zeros(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);
	memcpy(rltImg.data, m_imageRealdata, bufSize);
	cv::imwrite("D:/123.bmp", rltImg);
}

void __stdcall CHook::ExceptionCallBack(unsigned int nMsgType, void* pUser)
{
	QHikVisionTest* hik = new QHikVisionTest();
	hik->showErrMsg(nMsgType, pUser);
}
