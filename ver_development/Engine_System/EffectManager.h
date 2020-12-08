////////////////////////////////////////////////////
// Effect 담당 관리 클래스
////////////////////////////////////////////////////
#ifndef _EffectManager_H_
#define _EffectManager_H_

class CEffectManager{
public:
	typedef enum PlaneType{BLACK=0, WHITE} PLANETYPE;

private:
	// BG Effect
	CArray<CAttachment*> _plane;	    // 환면 전환 효과
	CArray<CAttachment*> _bgDarkEffect; // 검은 안개 효과
	CArray<CAttachment*> _bgSteamEffect; // 증기 효과

	// etc Effect
	CDLinkedList<CLightEffect*> _lightEffect;	// Tinkle Buff 효과
	CArray<CAttachment*> _command;		// 명령 효과	
	CDLinkedList<CQuestionMark*> _questionMark;	// 물음표 효과

	// Small scale Effect
	CDLinkedList<CBaseEffect*> _baseEffect; // 베이스 이펙트 클래스

	d3d::BoundingBox _box;

	D3DXVECTOR3 _vPos;
	D3DXVECTOR3 _vScale; 
	D3DXVECTOR3 _vRotate;

	bool _bgDarkUse;
	bool _bgSteamUse;
	
	bool _planeUse;
	PLANETYPE _ePlaneType;
	bool _planeState;	// true는 ++, false는 --

	bool _commandUse;
	CAIManager::COMMANDTYPE _eCommandType;

private:
	CEffectManager();
	CEffectManager(const CEffectManager&);
	CEffectManager& operator =(const CEffectManager&);

public:
	~CEffectManager();
	static CEffectManager* Instance(){
		static CEffectManager instance;

		return &instance;
	}

	// Effect 업데이트
	void EffectUpdate();

	// BG 배경 효과 영역 설정
	void SetBGEffectRange(CBaseObject::OWNER p_eStage);
	bool CheckOverRange(CAttachment* t_pAtt);

	// 배경 효과 정보 셋팅
	void SetBGEffectInfoOnRandom(CAttachment* p_pAtt);

	// bgDarkEffect
	void BGDarkEffectUpdate();
	void ResetBGDarkEffect();
	void SetBGDarkUse(bool p_bool){_bgDarkUse = p_bool;}
	bool GetBGDarkUse(){return _bgDarkUse;}

	// bgStreamEffect
	void BGStreamEffectUpdate();
	void ResetBGStreamEffect();
	void SetBGStreamUse(bool p_bool){_bgSteamUse = p_bool;}
	bool GetBGStreamUse(){return _bgSteamUse;}

	// AlphaPlane
	float AlphaPlaneUpdate();
	void SetPlaneType(PLANETYPE p_eType){_ePlaneType = p_eType;}
	void SetPlaneUse(bool p_bool){_planeUse = p_bool;}

	// CommandEffect
	void CommandEffectUpdate();
	CAIManager::COMMANDTYPE GetCommandType(){return _eCommandType;}
	bool GetCommandUse(){return _commandUse;}
	void SetCommandEffect(CAIManager::COMMANDTYPE p_eType);
	CAttachment* GetCommand(int p_nIndex){return _command.Get(p_nIndex);}

	// TinkleBuffEffect
	CDLinkedList<CLightEffect*>* GetLightEffectList(){return &_lightEffect;}
	void LightEffectUpdate();
	void InsertLightEffect(COrgan* p_pOrgan){_lightEffect.Append(new CLightEffect(p_pOrgan));}

	// small Scale
	CDLinkedList<CBaseEffect*>* GetSmallEffectList(){return &_baseEffect;}
	void SmallScaleEffectUpdate();
	void SmallScaleEffectDelete();
	void InsertQuestionMark(COrgan* p_pOrgan){_baseEffect.Append(new CQuestionMark(p_pOrgan));}
	void InsertDamageEffect(D3DXVECTOR3* p_pPos, int p_nDamage){_baseEffect.Append(new CDamageEffect(p_pPos, p_nDamage));}
	void InsertSparksEffect(D3DXVECTOR3* p_pPos){_baseEffect.Append(new CSparksEffect(p_pPos));}
	void InsertRayEffect(D3DXVECTOR3* p_pPos, float p_fDistance){_baseEffect.Append(new CRayEffect(p_pPos, p_fDistance));}
	void InsertDiggyEffect(COrgan* p_pOrgan, float t_fTime){_baseEffect.Append(new CDiggyEffect(p_pOrgan, t_fTime));}
	void InsertDustEffect(D3DXVECTOR3* p_pPos){_baseEffect.Append(new CDustEffect(p_pPos));}
	void InsertBoldDustEffect(D3DXVECTOR3* p_pPos){_baseEffect.Append(new CBoldDustEffect(p_pPos));}
};

#define EffectMgr CEffectManager::Instance()

#endif