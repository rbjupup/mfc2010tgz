
// tgzMfcDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CtgzMfcDlg �Ի���




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


// CtgzMfcDlg ��Ϣ�������

BOOL CtgzMfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtgzMfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
