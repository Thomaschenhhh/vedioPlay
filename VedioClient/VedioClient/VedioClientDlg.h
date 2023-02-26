
// VedioClientDlg.h : header file
//

#pragma once
class VideoClientController;

// CVedioClientDlg dialog
class CVedioClientDlg : public CDialogEx
{
// Construction
public:
	CVedioClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VEDIOCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	bool m_status;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	VideoClientController* m_controller;
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnDestroy();

	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnTRBNThumbPosChangingSliderPos(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTRBNThumbPosChangingSliderVolume(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
protected:

	CEdit m_vedio;
	CSliderCtrl m_pos;
	CSliderCtrl m_volume;
	CEdit m_url;
	CButton m_btnPlay;
	float m_length;
};
