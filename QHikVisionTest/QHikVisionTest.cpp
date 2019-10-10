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
	int nRet = m_Hik->Init(this);
	if (nRet != MV_OK)
	{
		std::string errMsg = m_Hik->GetLastErr();
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "相机初始化成功");
	}
}

void QHikVisionTest::on_pushButton_softTrigger_clicked()
{
	int sRet=m_Hik->SoftwareTrigger();
	if (sRet != MV_OK)
	{
		std::string errMsg= m_Hik->GetLastErr();
    }
}

void QHikVisionTest::on_pushButton_close_clicked()
{
	m_Hik->Close();
}


void __stdcall QHikVisionTest::ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
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
