////////////////////////////////////////////////////
// Stage와 관련된 정보를 담당 관리 클래스
////////////////////////////////////////////////////
#ifndef _StageManager_H_
#define _StageManager_H_

class CStageManager{
public:
	typedef enum StageType {WORLDMAP = -10, NOTHING = -1, HOME, SCRAPMOUNTAIN, FURNACE, CHIMNEY, DUSTBRIDGE, GOODHOPE} STAGETYPE;

	// IsStageClear
	bool _homeClear;
	bool _scrapMountainClear;
	bool _furnaceClear;
	bool _chimneyClear;
	bool _dustBridgeClear;

private:
	/////////////////////////////////
	// All Stage related
	COrgan* _stage;
	int _nStageType;
	int _nArea;
	float _fStageHeight;
	D3DXVECTOR3 _vHeroStartPos;
	bool _bIsGetOutStage; // true 이면 나갔고 false 이면 아니다.
	bool _bIsFadeInOut;	  // true이면 Fade out false이면 Fade in

	/////////////////////////////////
	// Home
	bool _bIsHomeInOut;	// 안이면 true 밖이면 false

private:
	CStageManager();
	CStageManager(const CStageManager&);
	CStageManager& operator =(const CStageManager&);

public:
	~CStageManager();
	static CStageManager* Instance(){
		static CStageManager instance;

		return &instance;
	}

	void Update(CSection* pSection);

	/////////////////////////////////
	// All Stage related
	D3DXVECTOR3 GetStartPos(){return _vHeroStartPos;}
	void SetStartPos(D3DXVECTOR3 p_vPos){_vHeroStartPos = p_vPos;}

	COrgan* GetStage(){return _stage;}
	int GetStageType(){return _nStageType;}
	void SetStage(int p_nType);
	float GetStageHeight(){return _fStageHeight;}
	void SetStageHeight(float p_fTemp){_fStageHeight = p_fTemp;}

	int GetAreaNumber(){return _nArea;}
	void SetAreaNumber(int p_nArea){_nArea = p_nArea;}	
	
	bool GetbIsGetOutStage(){return _bIsGetOutStage;}
	void SetbIsGetOutStage(bool p_bGetOut){_bIsGetOutStage = p_bGetOut;}

	bool GetbIsFadeInOut(){return _bIsFadeInOut;}
	void SetbIsFadeInOut(bool p_bInOut){_bIsFadeInOut = p_bInOut;}

	void ComputeMoveLimitStage();

	/////////////////////////////////
	// Home
	void SetbIsHomeInOut(bool p_bTemp){_bIsHomeInOut = p_bTemp;}
	bool GetbIsHomeInOut(){return _bIsHomeInOut;}	
};

#define StageMgr CStageManager::Instance()

#endif