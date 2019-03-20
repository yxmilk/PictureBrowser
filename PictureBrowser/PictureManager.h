#pragma once
#include<vector>
#include<string>

using namespace std;

class PictureManager {

public:
	PictureManager(wstring);
	~PictureManager();

	//当前目录
	wstring getPath();

	bool setFolder(wstring);

	//按照编号取图片地址
	wstring getPic(int);
	//按照图片地址取编号
	int getIndex(wstring picPath);

	//图片数量
	int getPicNum();

private:
	wstring picFolder;
	vector<wstring> picNames;
	bool getPicNames(wstring, vector<wstring>&);
	bool isPng(const wchar_t *);//判断是否为png文件
};