#pragma once
#include<vector>
#include<string>

using namespace std;

class PictureManager {

public:
	PictureManager(wstring);
	~PictureManager();

	//��ǰĿ¼
	wstring getPath();

	bool setFolder(wstring);

	//���ձ��ȡͼƬ��ַ
	wstring getPic(int);
	//����ͼƬ��ַȡ���
	int getIndex(wstring picPath);

	//ͼƬ����
	int getPicNum();

private:
	wstring picFolder;
	vector<wstring> picNames;
	bool getPicNames(wstring, vector<wstring>&);
	bool isPng(const wchar_t *);//�ж��Ƿ�Ϊpng�ļ�
};