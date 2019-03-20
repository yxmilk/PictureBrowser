#include"MainWnd.h"

void CMainWindow::Notify(TNotifyUI& msg) {

	if (msg.sType == _T("click")) {

		clickEvent(msg);

	}
	else if (msg.sType == _T("windowinit")) {
	
		wndInitEvent(msg);
	}

}

void CMainWindow::clickEvent(TNotifyUI &msg) {

	if (msg.pSender->GetName() == _T("minBtn")) {

		::ShowWindow(GetActiveWindow(), SW_MINIMIZE);

	}
	else if (msg.pSender->GetName() == _T("closeBtn")) {

		savePath();

		exit(0);

	}
	else if (msg.pSender->GetName() == _T("maxBtn")) {

		::ShowWindow(GetActiveWindow(), SW_MAXIMIZE);

	}
	else if (msg.pSender->GetName() == _T("preBtn")) {
	
		prePicture();
	}
	else if (msg.pSender->GetName() == _T("nextBtn")) {

		nextPicture();
	}
	else if (msg.pSender->GetName() == _T("pathBtn")) {

		wstring path = selectFile();
		wstring filePath = path.substr(0, path.find_last_of(L"\\"));
		wstring fileName = path.substr(path.find_last_of(L"\\") + 1);

		if (filePath == pm->getPath()) {
		
			//Ŀ¼δ��
			//��ʾͼƬ
			CControlUI *imgLabel = m_PaintManager.FindControl(_T("labelImg"));
			imgLabel->SetBkImage(path.c_str());

			//ͼƬ�ı��ı��
			curPic = pm->getIndex(path);

		}
		else {
		
			//�ı�Ŀ¼
			if (pm->setFolder(filePath)) {

				//��ʾͼƬ
				CControlUI *imgLabel = m_PaintManager.FindControl(_T("labelImg"));
				imgLabel->SetBkImage(path.c_str());

				curPic = pm->getIndex(path);
			
				MessageBox(NULL, (_T("��ǰĿ¼���л���") + filePath + _T("!")).c_str(), _T("��Ϣ"), MB_OK | MB_TASKMODAL);
				
			}
			else {
			
				MessageBox(NULL, _T("��Ŀ¼û��PNGͼƬ��"), _T("��Ϣ"), MB_OK | MB_TASKMODAL);

			}
		}
		
		CControlUI *pathEd = m_PaintManager.FindControl(_T("pathEdit"));
		pathEd->SetText(path.c_str());
	}
}

void CMainWindow::wndInitEvent(TNotifyUI &msg) {

	pm = new PictureManager(Utility::getPwd());
	curPic = -1;
	cPath = Utility::getPwd();

	if (_waccess(L"./path.txt", 0) == -1) {
	
		//��ʾ����ǰĿ¼�µ�ͼƬ
		showCur();
	}
	else {
	
		wchar_t lastPath[MAX_PATH] = { 0 };
		FILE*pf = _wfopen(L"./path.txt", L"rb");

		wprintf(L"aaaaa");
		fseek(pf, 2, 0);
		if (fgetws(lastPath, MAX_PATH, pf) != NULL) {

			//��ʾ�ر�ʱĿ¼�µ�ͼƬ

			//��ʾ·��
			CEditUI *pathEd = (CEditUI *)m_PaintManager.FindControl(_T("pathEdit"));
			pathEd->SetText(lastPath);
			pathEd->SetReadOnly(TRUE);

			wstring path(lastPath);
			wstring filePath = path.substr(0, path.find_last_of(L"\\"));
			wstring fileName = path.substr(path.find_last_of(L"\\") + 1);
			
			//�ı�Ŀ¼
			if (pm->setFolder(filePath)) {

				//��ʾ�ϴε�ͼƬ������ϴε�ͼƬ�������ˣ�����ʾ�ϴιر�ʱĿ¼�µĵ�һ��ͼƬ��
				curPic = pm->getIndex(path);
				CControlUI *imgLabel = m_PaintManager.FindControl(_T("labelImg"));
				imgLabel->SetBkImage(pm->getPic(curPic).c_str());

			}
			else {

				//MessageBox(NULL, _T("�ϴ�Ŀ¼û��PNGͼƬ��"), _T("��Ϣ"), MB_OK | MB_TASKMODAL);
				//�ϴ�Ŀ¼��û��ͼƬ�ˣ�����ʾ��ǰĿ¼��ͼƬ
				showCur();

			}

		}
		else {
			//�ϴε�·��Ϊ��
			//MessageBox(NULL, _T("�ϴ�Ϊ�գ�"), _T("��Ϣ"), MB_OK | MB_TASKMODAL);
			showCur();
		}
	}


}

void CMainWindow::prePicture() {

	if (curPic <= 0) {
	
		MessageBox(NULL, _T("�Ѿ��ǵ�һ��ͼƬ��"), _T("��Ϣ"), MB_OK | MB_TASKMODAL);
	}
	else {
	
		--curPic;
		CControlUI *imgLabel = m_PaintManager.FindControl(_T("labelImg"));
		imgLabel->SetBkImage(pm->getPic(curPic).c_str());

		//��ʾ·��
		CEditUI *pathEd = (CEditUI *)m_PaintManager.FindControl(_T("pathEdit"));
		pathEd->SetText(pm->getPic(curPic).c_str());

	}
}

void CMainWindow::nextPicture() {

	if (curPic >= pm->getPicNum() - 1) {

		MessageBox(NULL, _T("�Ѿ������һ��ͼƬ��"), _T("��Ϣ"), MB_OK | MB_TASKMODAL);
	}
	else {
	
		++curPic;
		CControlUI *imgLabel = m_PaintManager.FindControl(_T("labelImg"));
		imgLabel->SetBkImage(pm->getPic(curPic).c_str());

		//��ʾ·��
		CEditUI *pathEd = (CEditUI *)m_PaintManager.FindControl(_T("pathEdit"));
		pathEd->SetText(pm->getPic(curPic).c_str());
	}

}

wstring CMainWindow::selectFile() {

	TCHAR szBuffer[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = _T("png Files(*.png)\0*.png\0");//Ҫѡ����ļ���׺   
	ofn.lpstrInitialDir = Utility::getPwd().c_str();//Ĭ�ϵ��ļ�·��   
	ofn.lpstrFile = szBuffer;//����ļ��Ļ�����   
	ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
	ofn.nFilterIndex = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//��־����Ƕ�ѡҪ����OFN_ALLOWMULTISELECT  
	BOOL bSel = GetOpenFileName(&ofn);

	return wstring(szBuffer);

}

void CMainWindow::savePath() {

	FILE* file = _wfopen((cPath + L"\\path.txt").c_str(), L"w, ccs=UNICODE");
	if (curPic != -1) {
		
		fwprintf(file, L"%s", pm->getPic(curPic).c_str());
	}
	fclose(file);

}

LRESULT CMainWindow::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {

	switch (wParam) {
	
	case VK_UP:
	case VK_LEFT:
		prePicture();
		break;
	case VK_DOWN:
	case VK_RIGHT:
		nextPicture();
		break;

	}

	return 0;
}

void CMainWindow::showCur() {

	CControlUI *imgLabel = m_PaintManager.FindControl(_T("labelImg"));
	if (pm->getPicNum() > 0) {

		imgLabel->SetBkImage(pm->getPic(0).c_str());
		curPic = 0;

		//��ʾ·��
		CEditUI *pathEd = (CEditUI *)m_PaintManager.FindControl(_T("pathEdit"));
		pathEd->SetText(pm->getPic(0).c_str());
		pathEd->SetReadOnly(TRUE);
	}
	else {

		MessageBox(NULL, _T("��ǰĿ¼��δ�ҵ�PNGͼƬ��"), _T("��Ϣ"), MB_OK | MB_TASKMODAL);

	}

}