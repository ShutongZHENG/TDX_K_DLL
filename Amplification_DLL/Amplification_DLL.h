// Amplification_DLL.h: Amplification_DLL DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "Resource.h"		// 主符号
#include <map>
#include <vector>

// CAmplificationDLLApp
// 有关此类实现的信息，请参阅 Amplification_DLL.cpp
//
struct DATA_Stock
{
	float Code;
	float Rate;
};
typedef std::vector<DATA_Stock> STOCK;

class CAmplificationDLLApp : public CWinApp
{
public:
	CAmplificationDLLApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
extern CAmplificationDLLApp theApp;
extern STOCK RATE_CODE;
