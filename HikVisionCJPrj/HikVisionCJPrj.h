#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HikVisionCJPrj.h"
#include "HikVisionPrj.h"
#include <QMessageBox>
class HikVisionCJPrj : public QMainWindow
{
	Q_OBJECT

public:
	HikVisionCJPrj(QWidget *parent = Q_NULLPTR);
	public slots:
	void on_pushButton_Init_clicked();
	void on_pushButton_softTrigger_clicked();
private:
	Ui::HikVisionCJPrjClass ui;
	HikVisionPrj* m_Hik;
};

class CHook : public CallBackEx
{
public:
	void __stdcall ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
	void __stdcall  ExceptionCallBack(unsigned int nMsgType, void* pUser);
protected:
private:
};