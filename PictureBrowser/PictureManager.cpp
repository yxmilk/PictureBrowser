#include"PictureManager.h"
#include<io.h>
#include<iostream>
#include<algorithm>

PictureManager::PictureManager(wstring picFolder) {

	this->picFolder = picFolder;

	// 获取文件夹下所有的png文件名
	getPicNames(this->picFolder, picNames);
}

bool PictureManager::setFolder(wstring newF) {
		
	if (getPicNames(newF, picNames)) {
	
		this->picFolder = newF;
		return true;
	}
	else return false;
}

bool PictureManager::getPicNames(wstring picF, vector<wstring> &picV) {

	vector<wstring> nV;

	_wfinddata_t fileInfo;
	int fHandle = _wfindfirst((picF + L"\\*").c_str(), &fileInfo);

	do {

		if (fileInfo.attrib != _A_SUBDIR) {

			if (isPng(fileInfo.name)) {

				nV.push_back(picF + L"\\" + wstring(fileInfo.name));
			}

		}

	} while (!_wfindnext(fHandle, &fileInfo));

	if (nV.size() > 0) {
	
		picV = nV;
		return true;
	}
	else return false;
}

bool PictureManager::isPng(const wchar_t * name) {

	wstring nameS(name);
	wstring s = nameS.substr(nameS.length() - 4, nameS.length());

	transform(s.begin(), s.end(), s.begin(), ::tolower);

	return s == wstring(L".png");
}

wstring PictureManager::getPic(int index) {

	return picNames[index];
}

int PictureManager::getPicNum() {

	return picNames.size();
}

wstring PictureManager::getPath() {

	return picFolder;
}

int PictureManager::getIndex(wstring picName) {

	for (int i = 0; i < picNames.size(); ++i) {
	
		if (picNames[i] == picName) return i;
	}

	return 0;
}