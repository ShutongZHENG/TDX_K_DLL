#include "pch.h"
#include "TCalcFuncSets.h"
#include <vector>
#include<iostream>
#pragma comment(lib,"./Amplification_DLL.lib")
using namespace std;
struct DATA_Stock
{
	float Code;
	float Rate;
};
typedef std::vector<DATA_Stock> STOCK;
static STOCK RES;
static int T=0;
static bool once = false;



//���ɵ�dll���������dll�뿽����ͨ���Ű�װĿ¼��T0002/dlls/����,���ڹ�ʽ���������а�
_declspec(dllimport) void Func_Search(STOCK S);
 /*
 ���� code , �������̼� , �������̼�
 
 */
void TestPlugin1(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	//CString CODE;
	//CString RATE;
	//CString Res;
		RES.push_back({ pfINa[DataLen - 1],((pfINb[DataLen - 1] - pfINc[DataLen -1]) / pfINc[DataLen - 1]) });
	//	CODE.Format(_T("%f"),RES[T].Code);
	//	RATE.Format(_T("%f"), RES[T].Rate);
	// Res = CODE + " " + RATE+"\n";
	//	fun_Save_One_Year_DATA(Res, wcslen(Res) * sizeof(wchar_t));
	//	T++;
		once = true;

}
void TestPlugin2(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	//��mfcִֻ��һ��

	if (once)
	{

		Func_Search(RES);
		once = false;

	}





	}
	






//���صĺ���
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	{1,(pPluginFUNC)&TestPlugin1},
	{2,(pPluginFUNC)&TestPlugin2},
	{0,NULL},
};

//������TCalc��ע�ắ��
BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun)
{
	if(*pFun==NULL)
	{
		(*pFun)=g_CalcFuncSets;
		return TRUE;
	}
	return FALSE;
}

BOOL fun_Save_One_Year_DATA(LPCTSTR SaveDATA, DWORD dword_param_BufferSize) {
	HANDLE handle_File = NULL;
	DWORD dword_NumberOfBytesToWrite = 0;
	handle_File = CreateFile(L"D:\DATA.txt",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (handle_File == INVALID_HANDLE_VALUE)
	{
		handle_File = CreateFile(L"D:\DATA.txt",
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (handle_File == INVALID_HANDLE_VALUE)
		{

			return false;
		}
		else
		{

			WORD dword_UnicodeFlag = 0xFEFF;
			WriteFile(handle_File,
				&dword_UnicodeFlag,
				sizeof(WORD),
				&dword_NumberOfBytesToWrite,
				NULL);

		}
	}
	else
	{

		SetFilePointer(handle_File, 0, NULL, FILE_END);
	}
	WriteFile(handle_File,
		SaveDATA,
		dword_param_BufferSize,
		&dword_NumberOfBytesToWrite,
		NULL);

	CloseHandle(handle_File);

	return true;

}



