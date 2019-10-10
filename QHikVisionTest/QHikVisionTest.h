#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QHikVisionTest.h"
#include "HikVisionPrj.h"
#include <QMessageBox>
#include <windows.h>
#include "opencv2/opencv.hpp"
class QHikVisionTest : public QMainWindow ,public CallBackEx
{
	Q_OBJECT

public:
	QHikVisionTest(QWidget *parent = Q_NULLPTR);
	~QHikVisionTest();
	public slots:
	void on_pushButton_Init_clicked();
	void on_pushButton_softTrigger_clicked();
	void on_pushButton_close_clicked();
private:
	void __stdcall ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
	Ui::QHikVisionTestClass ui;
	HikVisionPrj* m_Hik;
	BYTE *m_imageRealdata = NULL;
	int m_nResizeBufSizeEx;
};
