////////////////////////////////////////////
// ���� Ŭ����
////////////////////////////////////////////
#ifndef _BaseSound_H_
#define _BaseSound_H_

class CBaseSound{
private:
	// SoundManager ����
	CSoundManager* _sound;

	// Effect
	CSound* _effect;

public:
	CBaseSound();
	~CBaseSound();

	// �ʱ�ȭ �Լ�
	HRESULT InitSound(HWND hWnd);

	// ���� ���� Get�Լ�
	CSound* GetEffect(){return _effect;}
};

#endif