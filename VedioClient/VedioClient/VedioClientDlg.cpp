
// VedioClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "VedioClient.h"
#include "VedioClientDlg.h"
#include "afxdialogex.h"
#include "VideoClientController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVedioClientDlg dialog



CVedioClientDlg::CVedioClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VEDIOCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_status = false;
	m_length = 0.0f;
}

void CVedioClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PLAY, m_vedio);
	DDX_Control(pDX, IDC_SLIDER_POS, m_pos);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_volume);
	DDX_Control(pDX, IDC_EDIT_URL, m_url);
	DDX_Control(pDX, IDC_BTN_PLAY, m_btnPlay);
}

BEGIN_MESSAGE_MAP(CVedioClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PLAY, &CVedioClientDlg::OnBnClickedBtnPlay)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_STOP, &CVedioClientDlg::OnBnClickedBtnStop)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_POS, &CVedioClientDlg::OnTRBNThumbPosChangingSliderPos)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_VOLUME, &CVedioClientDlg::OnTRBNThumbPosChangingSliderVolume)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CVedioClientDlg message handlers

BOOL CVedioClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetTimer(0, 500, NULL);
	m_pos.SetRange(0, 1);
	m_volume.SetRange(0, 100);
	m_volume.SetTicFreq(20);
	SetDlgItemText(IDC_STATIC_VOLUME, _T("100%"));
	SetDlgItemText(IDC_STATIC_TIME, _T("--:--:--/--:--:--"));
	m_controller->SetWnd(m_vedio.GetSafeHwnd());
	m_url.SetWindowText(_T("file:///F:\\c++学习记录\\Thomas\\vedioPlay\\VedioClient\\VedioClient\\1.mp4"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVedioClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVedioClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVedioClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 0)
	{
		//Controller,get play status and process information
		//refresh IDC_STATIC_TIME,IDC_STATIC_VOLUME
		float pos = m_controller->VideoCtrl(EVLC_GET_POSITION);
		if (pos != -1.0f)
		{
			if(m_length<=0.0f) m_length = m_controller->VideoCtrl(EVLC_GET_LENGTH);
			if (m_pos.GetRangeMax()<=1)
			{
				m_pos.SetRange(0, int(m_length));
			}
			
			CString strPos;
			strPos.Format(_T("%f/%f"), pos* m_length, m_length);
			SetDlgItemText(IDC_STATIC_TIME, strPos);
			m_pos.SetPos(int(pos * m_length));
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CVedioClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(0);
}

void CVedioClientDlg::OnBnClickedBtnPlay()
{
	// TODO: Add your control notification handler code here

	if (m_status ==false)
	{
		CString url;
		m_url.GetWindowText(url);
		m_controller->SetMedia(m_controller->Unicode2Utf8((LPCTSTR)url));
		m_btnPlay.SetWindowText(_T("Pause"));
		m_status = true;
		//TODO: Controller play interface
		m_controller->VideoCtrl(EVLC_PLAY);
	}
	else
	{
		m_btnPlay.SetWindowText(_T("Play"));
		m_status = false;
		//TODO: Controller stop interface
		m_controller->VideoCtrl(EVLC_PAUSE);
	}

}

void CVedioClientDlg::OnBnClickedBtnStop()
{
	// TODO: Add your control notification handler code here
	m_btnPlay.SetWindowText(_T("Play"));
	m_status = false;
	//TODO: Controller stop interface
	m_controller->VideoCtrl(EVLC_STOP);
}


void CVedioClientDlg::OnTRBNThumbPosChangingSliderPos(NMHDR* pNMHDR, LRESULT* pResult)
{
	// This feature requires Windows Vista or greater.
	// The symbol _WIN32_WINNT must be >= 0x0600.
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: Add your control notification handler code here
	TRACE("pos %d reason %d\r\n", pNMTPC->dwPos, pNMTPC->nReason);
	*pResult = 0;
}


void CVedioClientDlg::OnTRBNThumbPosChangingSliderVolume(NMHDR* pNMHDR, LRESULT* pResult)
{
	// This feature requires Windows Vista or greater.
	// The symbol _WIN32_WINNT must be >= 0x0600.
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: Add your control notification handler code here
	TRACE("pos %d reason %d\r\n", pNMTPC->dwPos, pNMTPC->nReason);
	*pResult = 0;
}


void CVedioClientDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (nSBCode == 5)
	{
		TRACE("pos %p volume %p cur %p pos %d cod %d\r\n", &m_pos, &m_volume, pScrollBar, nPos, nSBCode);
		CString strPos;
		strPos.Format(_T("%d%%"), nPos);
		SetDlgItemText(IDC_STATIC_TIME, strPos);
		m_controller->SetPosition(float(nPos)/ m_length);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CVedioClientDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//voice
	// TODO: Add your message handler code here and/or call default
	if (nSBCode==5)
	{
		TRACE("pos %p volume %p cur %p pos %d cod %d\r\n", &m_pos, &m_volume, pScrollBar, nPos, nSBCode);
		CString strVolume;
		strVolume.Format(_T("%d%%"), 100 - nPos);
		SetDlgItemText(IDC_STATIC_VOLUME, strVolume);
		m_controller->SetVolume(100 - nPos);
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
