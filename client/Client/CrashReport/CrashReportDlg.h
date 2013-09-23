// CrashReportDlg.h : ͷ�ļ�
//

#pragma once

#include "HyperLink.h"
#include "afxwin.h"

// CCrashReportDlg �Ի���
class CCrashReportDlg : public CDialog
{
// ����
public:
	CCrashReportDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CRASHREPORT_DIALOG };

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
	afx_msg void OnEnChangeDumpInfo();
	HWND CreateSysLink( HWND hDlg, HINSTANCE hInst, RECT rect ) ;
	afx_msg void OnNMClickFixSuggestion(NMHDR *pNMHDR, LRESULT *pResult);
	void InitDialog( CString file_name, CString dump_info, CString dump_file_path, bool debug ) ;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	CHyperLink m_win_debug;
	CHyperLink m_fix_suggestion;
	CHyperLink m_full_info;
    CString m_file_title ; 
	CString m_dump_info ; 
	CString m_dump_file_path ;
	bool m_debug;
};
