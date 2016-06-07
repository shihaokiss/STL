#pragma once
#include"Configer.h"
namespace TRACE
{
	//获取文件名
	string _GetFileName(string path)
	{
		char ch = '/';
#ifdef __WIN32__
		ch = '\\';
#endif
		size_t pos = path.rfind(ch);
		if (pos == string::npos)
			return path;
		else
			return path.substr(pos + 1);
	}

	void _ShowDebugMessage(char* File, char* Fun, int Line, char* Format ...)
	{
#ifdef __DEBUG__
		string Filename = _GetFileName(File);
		printf("【%s ：%d 行】 - %s\n", Filename.c_str(), Line, Fun);

		va_list args;
		va_start(args, Format);
		vfprintf(stdout, Format, args);
		va_end(args);
		cout << endl;
#endif
	}
#define __TRECE__(...) _ShowDebugMessage(__FILE__, __FUNCTION__, __LINE__,__VA_ARGS__)
}