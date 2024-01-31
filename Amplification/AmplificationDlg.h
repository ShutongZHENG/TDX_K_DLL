
// AmplificationDlg.h: 头文件
//

#pragma once
#define KeyID 1001 
// CAmplificationDlg 对话框
class CAmplificationDlg : public CDialogEx
{
// 构造
public:
	CAmplificationDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AMPLIFICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 涨幅值
	 DOUBLE Rate;
	afx_msg void OnBnClickedButtonSearch();
	// 符合涨幅的股票代码
	CString Code;
	 STOCK TRUERATE();
	static UINT AFX_SEARCH_RATE(LPVOID lpParam);
	CEdit Edit_RATE_CODE;
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnDestroy();
	CListCtrl g_List;
	static UINT AFX_SHOW_PRICE(LPVOID lpParam);
};
