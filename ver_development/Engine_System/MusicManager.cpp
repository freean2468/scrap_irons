#include "../BaseHeader.h"

CMusicManager::CMusicManager(){
	wDeviceID = 0;

	// 사운드 매니저 생성
	_sound = new CSoundManager();

	// 사운드 매니저 초기화 및 설정
	_sound->Initialize(AppMgr->GetpWnd()->GetSafeHwnd(), DSSCL_PRIORITY);
	_sound->SetPrimaryBufferFormat(2, 45100, 16);
}

CMusicManager::~CMusicManager(){
	if(wDeviceID)
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, (DWORD)NULL);

	CDListIterator<CSound*> itr;

	itr = GetEffectList()->GetIterator();

	for(itr.Start(); itr.Valid();){
		itr.Item()->Stop();
		_effectList.Remove(itr);
	}
}

bool CMusicManager::PlayMP3FileForBGM(char* parm_path){
	DWORD Result;

	_bgmOpen.lpstrElementName = parm_path;

	Result = mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)((LPVOID)&_bgmOpen));

	if(Result)
		return Result;

	wDeviceID = _bgmOpen.wDeviceID;

	_bgmPlay.dwCallback = (DWORD)AppMgr->GetpWnd()->GetSafeHwnd();

	Result = mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)((LPVOID)&_bgmPlay));

	if(Result){
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, (DWORD)NULL);
		return Result;
	}

	return 0;
}

bool CMusicManager::PlayMP3FileForEffect(char* parm_path){
	DWORD Result;

	UINT t_wDeviceID = NULL;

	_effectsOpen.Append(new MCI_OPEN_PARMS());
	_effectsPlay.Append(new MCI_PLAY_PARMS());

	CDListIterator<MCI_OPEN_PARMS*> itrOpen = _effectsOpen.GetIterator();
	CDListIterator<MCI_PLAY_PARMS*> itrPlay = _effectsPlay.GetIterator();

	itrOpen.Item()->lpstrElementName = parm_path;
	itrOpen.Item()->lpstrDeviceType = "mpegvideo";
	itrOpen.Item()->dwCallback = (DWORD)AppMgr->GetpWnd()->GetSafeHwnd();

	Result = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)itrOpen.Item());

	if(Result)
		return Result;

	t_wDeviceID = itrOpen.Item()->wDeviceID;

	itrPlay.Item()->dwCallback = (DWORD)AppMgr->GetpWnd()->GetSafeHwnd();

	Result = mciSendCommand(t_wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)itrPlay.Item());

	if(Result){
		mciSendCommand(t_wDeviceID, MCI_CLOSE, 0, (DWORD)NULL);
		return Result;
	}

	return 0;
}

void CMusicManager::Close(){
	if(wDeviceID)
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, (DWORD)NULL);
}

void CMusicManager::InsertEffect(char* p_pStr){
	CSound* t_pEffect = 0;

	_sound->Create(&t_pEffect, p_pStr, 0, GUID_NULL);
	t_pEffect->Play(0, NULL);

	_effectList.Append(t_pEffect);
}

void CMusicManager::CheckEffectPlaying(){
	CDListIterator<CSound*> itr = _effectList.GetIterator();

	for(itr.Start(); itr.Valid();){
		itr.Item()->Stop();
		_effectList.Remove(itr);
	}
}