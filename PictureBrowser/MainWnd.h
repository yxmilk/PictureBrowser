#pragma once
#include <UIlib.h>
#include"PictureManager.h"
#include"Utility.h"
#include<shlobj.h>

using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif

class CMainWindow :public WindowImplBase {

public:
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainWnd"); }
	virtual CDuiString GetSkinFile() { return _T("MainWnd.xml"); }
	virtual CDuiString GetSkinFolder() { return _T(""); }
	
	//时间处理
	virtual void    Notify(TNotifyUI& msg);

private:
	//点击事件
	void clickEvent(TNotifyUI&);
	//窗口加载完成事件
	void wndInitEvent(TNotifyUI &);
	
	//键盘事件
	virtual LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);

	//上一张
	void prePicture();
	//下一张
	void nextPicture();

	//目录选择对话框
	wstring selectFile();

	//保存当前文件路径
	void savePath();

	//显示当前文件夹下的图片
	void showCur();

	int curPic = -1;
	//图片管理
	PictureManager *pm;

	//程序所在目录
	wstring cPath;

};