
// Amplification.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#include <map>
#include <vector>

// CAmplificationApp:
// 有关此类的实现，请参阅 Amplification.cpp
//
struct DATA_Stock
{
	float Code;
	float Rate;
};
typedef std::vector<DATA_Stock> STOCK;

struct Stock_Price
{
	float Code;
	float Price;
};
typedef std::vector<Stock_Price> SPrice;


class CAmplificationApp : public CWinApp
{
public:
	CAmplificationApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CAmplificationApp theApp;
extern STOCK RATE_CODE;
extern SPrice STOCK_PRICE;
