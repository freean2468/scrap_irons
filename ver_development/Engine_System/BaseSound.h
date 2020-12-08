////////////////////////////////////////////
// 사운드 클래스
////////////////////////////////////////////
#ifndef _BaseSound_H_
#define _BaseSound_H_

class CBaseSound{
private:
	// SoundManager 변수
	CSoundManager* _sound;

	// Effect
	CSound* _effect;

public:
	CBaseSound();
	~CBaseSound();

	// 초기화 함수
	HRESULT InitSound(HWND hWnd);

	// 사운드 버퍼 Get함수
	CSound* GetEffect(){return _effect;}
};

#endif