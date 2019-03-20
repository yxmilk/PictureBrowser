#include<stdio.h>
#include<io.h>
#include<stdlib.h>

int main(){
	
	FILE* file = _wfopen(L"./path.txt", L"w, ccs=UNICODE");
	fwprintf(file, L"%s", L"G:\\PictureBrowser\\PictureBrowser\\Debug\\0.PNG");
	fclose(file);
	
	wchar_t lastPath[MAX_PATH] = { 0 };
	FILE*pf = _wfopen(L"./path.txt", L"rb");
	if (pf)
	{
		wprintf(L"aaaaa");
		fseek(pf,2,0);
		if (fgetws(lastPath, MAX_PATH, pf) != NULL) {
		
			wprintf(L"%s\n", lastPath);
			wprintf(L"yuanyuan");

		}

	}
	
}