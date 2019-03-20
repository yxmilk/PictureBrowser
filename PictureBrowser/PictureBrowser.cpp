// PictureBrowser.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PictureBrowser.h"

#include "MainWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)

{

	CPaintManagerUI::SetInstance(hInstance);// 加载XML的时候，需要使用该句柄去定位EXE的路径，才能加载XML的路径
											//设置XML的路径
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath()); //此处设置为和exe在同一目录

	CMainWindow mainWnd;
	mainWnd.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainWnd.CenterWindow();
	mainWnd.ShowModal();

	//CPaintManagerUI::MessageLoop();

	delete mainWnd;

	return 0;


}
