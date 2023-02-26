#include "pch.h"
#include "VideoClientController.h"

VideoClientController::VideoClientController()
{
	m_dlg.m_controller = this;
}

VideoClientController::~VideoClientController()
{
}

int VideoClientController::Init(CWnd*& pWnd)
{
	pWnd = &m_dlg;
	return 0;
}

int VideoClientController::Invoke()
{
	INT_PTR nResponse = m_dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
	return nResponse;
}

int VideoClientController::SetMedia(const std::string& strUrl)
{
	return m_vlc.SetMedia(strUrl);
}

float VideoClientController::VideoCtrl(EVlcCommand cmd)
{
	switch (cmd)
	{
	case EVLC_PLAY:
		return float(m_vlc.Play());
	case EVLC_PAUSE:
		return float(m_vlc.Pause());
	case EVLC_STOP:
		return float(m_vlc.Stop());
	case EVLC_GET_VOLUME:
		return float(m_vlc.GetVolume());
	case EVLC_GET_POSITION:
		return m_vlc.GetPostion();
	case EVLC_GET_LENGTH:
		return m_vlc.GetLength();
	default:
		break;
	}
	return -1.0f;
}

void VideoClientController::SetPosition(float pos)
{
	m_vlc.SetPostion(pos);
}

int VideoClientController::SetWnd(HWND hWnd)
{
	return m_vlc.SetHwnd(hWnd);
}

int VideoClientController::SetVolume(int volume)
{
	return m_vlc.SetVolume(volume);
}

VlcSize VideoClientController::GetMediaInfo()
{
	return m_vlc.GetMediaInfo();
}

std::string VideoClientController::Unicode2Utf8(const std::wstring& strIn)
{
	return m_vlc.Unicode2Utf8(strIn);
}
