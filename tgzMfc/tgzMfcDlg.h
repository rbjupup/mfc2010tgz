
// tgzMfcDlg.h : ͷ�ļ�
//

#pragma once
/* values used in typeflag field */

#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */

/* GNU tar extensions */

#define GNUTYPE_DUMPDIR  'D'    /* file names from dumped directory */
#define GNUTYPE_LONGLINK 'K'    /* long link name */
#define GNUTYPE_LONGNAME 'L'    /* long file name */
#define GNUTYPE_MULTIVOL 'M'    /* continuation of file from another volume */
#define GNUTYPE_NAMES    'N'    /* file name that does not fit into main hdr */
#define GNUTYPE_SPARSE   'S'    /* sparse file */
#define GNUTYPE_VOLHDR   'V'    /* tape/volume header */


/* tar header */

#define BLOCKSIZE     512
#define SHORTNAMESIZE 100

struct tar_header
{                               /* byte offset */
	char name[100];               /*   0 */
	char mode[8];                 /* 100 */
	char uid[8];                  /* 108 */
	char gid[8];                  /* 116 */
	char size[12];                /* 124 */
	char mtime[12];               /* 136 */
	char chksum[8];               /* 148 */
	char typeflag;                /* 156 */
	char linkname[100];           /* 157 */
	char magic[6];                /* 257 */
	char version[2];              /* 263 */
	char uname[32];               /* 265 */
	char gname[32];               /* 297 */
	char devmajor[8];             /* 329 */
	char devminor[8];             /* 337 */
	char prefix[155];             /* 345 */
	/* 500 */
};

union tar_buffer
{
	char               buffer[BLOCKSIZE];
	struct tar_header  header;
};

struct attr_item
{
	struct attr_item  *next;
	char              *fname;
	int                mode;
	time_t             time;
};

enum { TGZ_EXTRACT, TGZ_LIST, TGZ_INVALID };

// CtgzMfcDlg �Ի���
class CtgzMfcDlg : public CDialogEx
{
// ����
public:
	CtgzMfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TGZMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGzbutton();

	void DecompressAll(CString &path);

	void GetFilePath(CString &path);

};
