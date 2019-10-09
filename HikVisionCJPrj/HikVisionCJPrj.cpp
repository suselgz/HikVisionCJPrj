#include "HikVisionCJPrj.h"
#pragma execution_character_set("utf-8")
HikVisionCJPrj::HikVisionCJPrj(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_Hik = (HikVisionPrj *)HikVisionPrjInstance();
}

void HikVisionCJPrj::on_pushButton_Init_clicked()
{
	CHook * hook = new CHook;
	int nRet=m_Hik->Init(hook);
	if (nRet != 0)
	{
		QMessageBox::information(NULL,"INFO","相机初始化失败");
	}
	else
	{
		QMessageBox::information(NULL, "INFO", "相机初始化成功");
	}
}

void HikVisionCJPrj::on_pushButton_softTrigger_clicked()
{
	m_Hik->SoftwareTrigger();
}

void __stdcall CHook::ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
{
	if (pFrameInfo)
	{
		printf("Get One Frame: Width[%d], Height[%d], nFrameNum[%d]\n",
			pFrameInfo->nWidth, pFrameInfo->nHeight, pFrameInfo->nFrameNum);
	}
}

void __stdcall CHook::ExceptionCallBack(unsigned int nMsgType, void* pUser)
{

}

