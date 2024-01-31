
// AmplificationDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Amplification.h"
#include "AmplificationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAmplificationDlg 对话框



CAmplificationDlg::CAmplificationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AMPLIFICATION_DIALOG, pParent)
	, Code(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAmplificationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, Rate);
	DDX_Text(pDX, IDC_EDIT3, Code);
	DDX_Control(pDX, IDC_EDIT3, Edit_RATE_CODE);
	DDX_Control(pDX, IDC_LIST1, g_List);
}

BEGIN_MESSAGE_MAP(CAmplificationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Search, &CAmplificationDlg::OnBnClickedButtonSearch)
	ON_WM_NCPAINT()
	ON_WM_HOTKEY()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CAmplificationDlg 消息处理程序

BOOL CAmplificationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	RegisterHotKey(this->GetSafeHwnd(), KeyID, MOD_ALT, 'Q');


	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	g_List.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	g_List.SetExtendedStyle(g_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列   
	g_List.InsertColumn(0, _T("股票编码"), LVCFMT_LEFT, 2*rect.Width() / 3, 0);
	g_List.InsertColumn(1, _T("价格"), LVCFMT_LEFT,  rect.Width() / 3, 1);




	//隐藏对话框窗口 由于Oninitial是模态对话框 应该使用 RunModalLoop() 否则无法隐藏对话框
	ShowWindow(SW_HIDE);
	RunModalLoop();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAmplificationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAmplificationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAmplificationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAmplificationDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	AfxBeginThread(AFX_SEARCH_RATE, this);
}

STOCK CAmplificationDlg::TRUERATE()
{
	STOCK res;
	for (int i = 0; i < RATE_CODE.size(); i++)
	{
		if (RATE_CODE[i].Rate >= Rate*0.01)
		{
			res.push_back(RATE_CODE[i]);
		}
	}
	return res;
}


UINT CAmplificationDlg::AFX_SEARCH_RATE(LPVOID lpParam)
{

	CAmplificationDlg* CA = (CAmplificationDlg*)lpParam;


	float N_code;
	float N_Rate;
	wchar_t* stopstring = NULL;
	HANDLE hFile;
	hFile = CreateFile(
		_T("D:\DATA.txt"),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	DWORD dwNoByteToRead = GetFileSize(hFile, NULL);
	wchar_t* buffer = new wchar_t[dwNoByteToRead];
	DWORD dwNoByteRead = 0;
	ReadFile(
		hFile,
		buffer,
		dwNoByteToRead,
		&dwNoByteRead,
		NULL);
	CloseHandle(hFile);

	for (int i = 0; i < dwNoByteToRead; i++)
	{
		buffer[i] = buffer[i + 1];
	}


	do
	{
		N_code = wcstof(buffer, &stopstring);
		wcscpy_s(buffer, wcslen(stopstring) + 1, stopstring);
		N_Rate = wcstof(buffer, &stopstring);
		wcscpy_s(buffer, wcslen(stopstring) + 1, stopstring);
		RATE_CODE.push_back({ N_code,N_Rate });

	} while (N_code != (float)0.);
	RATE_CODE.pop_back();

	delete[] buffer;
	STOCK RATE = CA->TRUERATE();
	CString res;
	CString tran;
	for (size_t i = 0; i < RATE.size(); i++)
	{
		tran.Format(_T("%f"), RATE[i].Code);
		res = res + tran + _T(" \r\n");
	}
	tran.Format(_T("%d"), RATE.size());
	res = res + _T("合计:")+tran+ _T(" \r\n");
	CA->Edit_RATE_CODE.SetWindowTextW(res);
	return 0;
}



void CAmplificationDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nHotKeyId) {
	case 1001:
	{
		BOOL bVisible = IsWindowVisible();//查看消息是显示还是隐藏
		int nCmdShow = bVisible ? SW_HIDE : SW_SHOW;//?自动判断
		ShowWindow(nCmdShow);


	}

	default:
		break;
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CAmplificationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	UnregisterHotKey(this->GetSafeHwnd(), KeyID);
}

UINT CAmplificationDlg::AFX_SHOW_PRICE(LPVOID lpParam)
{

	CAmplificationDlg* CA = (CAmplificationDlg*)lpParam;

	CString NCODE;
	CString NPRICE;

	for (int i = 1; i < STOCK_PRICE.size(); i++)
	{
		NCODE.Format(_T("%f"), STOCK_PRICE[i].Code);
		CA->g_List.InsertItem(i - 1, NCODE);
		NPRICE.Format(_T("%f"), STOCK_PRICE[i].Price);
		CA->g_List.SetItemText(i - 1, 1, NPRICE);
	}


	return 0;
}
