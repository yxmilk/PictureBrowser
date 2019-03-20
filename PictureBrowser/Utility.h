#pragma once

#include<windows.h>
#include<string>

using namespace std;

class Utility {

public:
	static wstring string2wstring(string s);
	static wstring getPwd();

};