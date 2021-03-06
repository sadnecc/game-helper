// HelperStart.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "inject.h"
using namespace std;

MyClass Typewriting;

void Inject(LPCWSTR dllpath)
{
	if (Typewriting.ImeInstall(dllpath))
		cout << "输入法安装成功" << endl;
	else
		cout << "输入法安装失败" << endl;
	HWND dnf = ::FindWindow(NULL, L"地下城与勇士");
	if (dnf == NULL)
	{
		cout << "游戏未启动" << endl;
		return;
	}
	Sleep(1000);
	Typewriting.IMEActiv(dnf);
	//Typewriting.Stop_AND_UnInstall();
}

void NotWrite()
{
	char cmd[512];
	sprintf_s(cmd, "cacls C:\\Users\\Administrator\\AppData\\LocalLow\\DNF /e /p everyone:N");
	system(cmd);
	sprintf_s(cmd, "cacls F:\\Game\\地下城与勇士 /e /p everyone:N");
	system(cmd);
	sprintf_s(cmd, "cacls F:\\Game\\地下城与勇士 /e /p everyone:R");
	system(cmd);
}

void Reset()
{
	char cmd[512];
	sprintf_s(cmd, "cacls C:\\Users\\Administrator\\AppData\\LocalLow\\DNF /e /p everyone:F");
	system(cmd);
	sprintf_s(cmd, "cacls F:\\Game\\地下城与勇士 /e /p everyone:F");
	system(cmd);
}

int main()
{
	Reset();
	cout << "开始注入模块" << endl; 
	Inject(L"C:\\Users\\Administrator\\Desktop\\cscapi.dll");
	cout << "禁止写入数据" << endl;
	NotWrite();
	int a;
	cout << "INPUT a(0表示卸载模块，1表示安装模块)" << endl;
	cin >> a;
	if (a == 0)
	{
		cout << "还原初始化状态" << endl;
		Typewriting.Stop_AND_UnInstall();
		Reset();
		return 0;
	}
	while (true)
	{
		HWND dnf = ::FindWindow(NULL, L"地下城与勇士");
		if (dnf == NULL)
			break;
		Sleep(1000);
	}
	cout << "还原初始化状态" << endl;
	Typewriting.Stop_AND_UnInstall();
	Reset();
}