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
	
	//ʱ�䴦��
	virtual void    Notify(TNotifyUI& msg);

private:
	//����¼�
	void clickEvent(TNotifyUI&);
	//���ڼ�������¼�
	void wndInitEvent(TNotifyUI &);
	
	//�����¼�
	virtual LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);

	//��һ��
	void prePicture();
	//��һ��
	void nextPicture();

	//Ŀ¼ѡ��Ի���
	wstring selectFile();

	//���浱ǰ�ļ�·��
	void savePath();

	//��ʾ��ǰ�ļ����µ�ͼƬ
	void showCur();

	int curPic = -1;
	//ͼƬ����
	PictureManager *pm;

	//��������Ŀ¼
	wstring cPath;

};