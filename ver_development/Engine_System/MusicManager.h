#ifndef _MusicManager_H_
#define _MusicManager_H_

class CMusicManager{
private:
	MCI_OPEN_PARMS _bgmOpen;
	MCI_PLAY_PARMS _bgmPlay;

	CDLinkedList<MCI_OPEN_PARMS*> _effectsOpen;
	CDLinkedList<MCI_PLAY_PARMS*> _effectsPlay;

	UINT wDeviceID;

	// Direct Sound
	// SoundManager º¯¼ö
	CSoundManager* _sound;

	// Effect
	CDLinkedList<CSound*> _effectList;

private:
	CMusicManager();	// standard constructor
	CMusicManager(const CMusicManager&);
	CMusicManager& operator =(const CMusicManager&);

public:
	~CMusicManager();
	static CMusicManager* Instance(){
		static CMusicManager instance;

		return &instance;
	}

	bool PlayMP3FileForBGM(char* parm_path);
	bool PlayMP3FileForEffect(char* parm_path);
	void Close();

	MCI_OPEN_PARMS* GetBGMOpenParam(){return &_bgmOpen;}
	MCI_PLAY_PARMS* GetBGMPlayParam(){return &_bgmPlay;}

	CDLinkedList<MCI_OPEN_PARMS*>* GetEffectOpenParam(){return &_effectsOpen;}
	CDLinkedList<MCI_PLAY_PARMS*>* GetEffectPlayParam(){return &_effectsPlay;}

	CSoundManager* GetDirectSoundManager(){return _sound;}

	void InsertEffect(char* p_pStr);
	void CheckEffectPlaying();
	CDLinkedList<CSound*>* GetEffectList(){return &_effectList;}
	UINT GetDeviceID(){return wDeviceID;}
};

#define MusicMgr CMusicManager::Instance()

#endif