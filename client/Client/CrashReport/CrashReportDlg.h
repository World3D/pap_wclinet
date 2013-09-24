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
	HWND CreateOtherMoreTip( HWND hDlg, HINSTANCE hInst, RECT rect ) ;
	afx_msg void OnNMClickFixSuggestion(NMHDR *pNMHDR, LRESULT *pResult);
	void InitDialog( CString strFileName, CString strDumpInfo, CString strDumpFilePath, bool bDebug ) ;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

protected:
	CHyperLink m_clWinDebug;
	CHyperLink m_clFixSuggestion;
	CHyperLink m_clFullInfo;
    CString m_strFileTitle ; 
	CString m_strDumpInfo ; 
	CString m_strDumpFilePath ;
	HWND m_hOtherMoreTipWnd ;
	bool m_bDebug;
public:
	afx_msg void OnEnChangeAppendInfo();
};
