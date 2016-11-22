
// tgzMfcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "tgzMfc.h"
#include "tgzMfcDlg.h"
#include "afxdialogex.h"
#include "zlib.h"
#include "zconf.h"

#pragma comment( lib, "zdll.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern int rbjtar(int argc,char **argv);


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtgzMfcDlg 对话框




CtgzMfcDlg::CtgzMfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtgzMfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtgzMfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtgzMfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GZBUTTON, &CtgzMfcDlg::OnBnClickedGzbutton)
END_MESSAGE_MAP()


// CtgzMfcDlg 消息处理程序

BOOL CtgzMfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtgzMfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtgzMfcDlg::OnPaint()
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
HCURSOR CtgzMfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtgzMfcDlg::OnBnClickedGzbutton()
{
	CString path;
	GetFilePath(path);

//	DecompressAll(path);

	char * str[2] = {
		"untgz",
		path.GetBuffer(),
	};

	rbjtar(2,str);
}

void CtgzMfcDlg::GetFilePath(CString &path)
{
	CFileDialog OpenDialog(TRUE,NULL,"",OFN_ALLOWMULTISELECT|OFN_ENABLESIZING|OFN_HIDEREADONLY);
	if (OpenDialog.DoModal())
	{

		IShellItemArray *pResult=OpenDialog.GetResults();
		OpenDialog.m_ofn.nMaxFile = 500 * MAX_PATH;
		DWORD dwCount=0;
		IShellItem *pItem;
		WCHAR *pFilePath;
		pResult->GetCount(&dwCount);
		for (DWORD i=0;i<dwCount;i++)
		{
			pResult->GetItemAt(i,&pItem);
			pItem->GetDisplayName(SIGDN_FILESYSPATH,&pFilePath);
			path+=pFilePath;
			path+="\n";
		}
	}
	path.TrimLeft();
	path.TrimRight();
}

void CtgzMfcDlg::DecompressAll(CString &path)
{
	char * str[2] = {
		"untgz",
		path.GetBuffer(),
	};

	rbjtar(2,str);
}
