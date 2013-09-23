// CrashReportDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CrashReport.h"
#include "CrashReportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCrashReportDlg �Ի���



CCrashReportDlg::CCrashReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCrashReportDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCrashReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FIX_SUGGESTION, m_fix_suggestion);
	DDX_Control(pDX, ID_FULL_INFO, m_full_info);
	DDX_Control(pDX, ID_DEBUG, m_win_debug);
}

BEGIN_MESSAGE_MAP(CCrashReportDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_DUMP_INFO, &CCrashReportDlg::OnEnChangeDumpInfo)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCrashReportDlg ��Ϣ�������

BOOL CCrashReportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	COLORREF blue_color = RGB( 0, 0, 238 ) ;

	// �޸�����
	m_fix_suggestion.SetURL( "#" ) ;
	m_fix_suggestion.SetUnderline( CHyperLink::ulAlways ) ;
	m_fix_suggestion.SetColours( -1, blue_color, blue_color ) ;
	m_fix_suggestion.SetTipText( "���ǽ����´�������Ϸʱʹ��\"ϵͳ�޸�\"�����޸����ܱ��𻵵���Դ�ļ�" ) ;
	m_fix_suggestion.SetTipDelayTime( 0 ) ;
	m_fix_suggestion.SetTipMaxWidth( 200 ) ;

	// �鿴��ϸ��Ϣ��������
	m_full_info.SetURL( m_dump_file_path ) ;
    m_full_info.SetUnderline( CHyperLink::ulAlways ) ;
    m_full_info.SetColours( -1, blue_color, blue_color ) ;
	m_full_info.SetTipText( "" ) ; //��Ҫ��ʾ

	SetDlgItemText( IDC_DUMP_INFO, m_dump_info) ;
	SetDlgItemText( IDC_FILE_TITLE, m_file_title ) ;
    
	if ( !m_debug ) GetDlgItem( ID_DEBUG )->EnableWindow( FALSE ) ;

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CCrashReportDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCrashReportDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CCrashReportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCrashReportDlg::OnEnChangeDumpInfo()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CCrashReportDlg::InitDialog( CString file_name, CString dump_info, CString dump_file_path, bool debug )
{
    m_file_title = file_name ;
	m_dump_info = dump_info ;
	m_dump_file_path = dump_file_path ;
	m_debug = debug ;
}

HBRUSH CCrashReportDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
    if ( ID_DEBUG == pWnd->GetDlgCtrlID() )
	{
		//pDC->SetTextColor( RGB( 172, 168, 153 ) );      //������ɫ
		//pDC->SetBkColor(RGB(0, 0, 255));       //���屳��ɫ 
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
