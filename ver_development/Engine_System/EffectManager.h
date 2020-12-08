////////////////////////////////////////////////////
// Effect ��� ���� Ŭ����
////////////////////////////////////////////////////
#ifndef _EffectManager_H_
#define _EffectManager_H_

class CEffectManager{
public:
	typedef enum PlaneType{BLACK=0, WHITE} PLANETYPE;

private:
	// BG Effect
	CArray<CAttachment*> _plane;	    // ȯ�� ��ȯ ȿ��
	CArray<CAttachment*> _bgDarkEffect; // ���� �Ȱ� ȿ��
	CArray<CAttachment*> _bgSteamEffect; // ���� ȿ��

	// etc Effect
	CDLinkedList<CLightEffect*> _lightEffect;	// Tinkle Buff ȿ��
	CArray<CAttachment*> _command;		// ��� ȿ��	
	CDLinkedList<CQuestionMark*> _questionMark;	// ����ǥ ȿ��

	// Small scale Effect
	CDLinkedList<CBaseEffect*> _baseEffect; // ���̽� ����Ʈ Ŭ����

	d3d::BoundingBox _box;

	D3DXVECTOR3 _vPos;
	D3DXVECTOR3 _vScale; 
	D3DXVECTOR3 _vRotate;

	bool _bgDarkUse;
	bool _bgSteamUse;
	
	bool _planeUse;
	PLANETYPE _ePlaneType;
	bool _planeState;	// true�� ++, false�� --

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

	// Effect ������Ʈ
	void EffectUpdate();

	// BG ��� ȿ�� ���� ����
	void SetBGEffectRange(CBaseObject::OWNER p_eStage);
	bool CheckOverRange(CAttachment* t_pAtt);

	// ��� ȿ�� ���� ����
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