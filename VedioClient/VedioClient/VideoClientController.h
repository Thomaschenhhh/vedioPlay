#pragma once
#include "EVlc.h"
#include "VedioClientDlg.h"
enum EVlcCommand {
	EVLC_PLAY,
	EVLC_PAUSE,
	EVLC_STOP,
	EVLC_GET_VOLUME,
	EVLC_GET_POSITION,
	EVLC_GET_LENGTH
};
class VideoClientController
{
public:
	VideoClientController();
	~VideoClientController();
	int Init(CWnd*& pWnd);
	int Invoke();
	//���strUrl�а������ķ��Ż��ַ�����ʹ��utf-8����
	int SetMedia(const std::string& strUrl);
	//����-1.0��ʾ����
	float VideoCtrl(EVlcCommand cmd);
	void SetPosition(float pos);
	int SetWnd(HWND hWnd);
	int SetVolume(int volume);
	VlcSize GetMediaInfo();
	std::string Unicode2Utf8(const std::wstring& strIn);
protected:
	EVlc m_vlc;
	CVedioClientDlg m_dlg;
};
