#include "../BaseHeader.h"

CEffectManager::CEffectManager(){
	_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 위치 벡터
	_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 크기 벡터
	_vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 회전 벡터

	_bgDarkUse = false;

	SetBGEffectRange(CBaseObject::WORLDMAP);

	// bgDarkEffects
	_bgDarkEffect.Resize(5);

	_vScale.x = 12.0f; _vScale.y = 12.0f; _vScale.z = 1.0f;

	_bgDarkEffect.Get(0) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_bgDarkEffect.Get(0)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/BGDarkEffects/1.dds", 100, 100, 0.05f, 0);

	_bgDarkEffect.Get(1) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_bgDarkEffect.Get(1)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/BGDarkEffects/2.dds", 100, 100, 0.05f, 0);

	_bgDarkEffect.Get(2) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_bgDarkEffect.Get(2)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/BGDarkEffects/3.dds", 100, 100, 0.05f, 0);

	_bgDarkEffect.Get(3) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_bgDarkEffect.Get(3)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/BGDarkEffects/4.dds", 100, 100, 0.05f, 0);

	_bgDarkEffect.Get(4) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_bgDarkEffect.Get(4)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/BGDarkEffects/5.dds", 100, 100, 0.05f, 0);

	for(int i = 0; i < _bgDarkEffect.GetSize(); i++)
		SetBGEffectInfoOnRandom(_bgDarkEffect.Get(i));

	SetBGEffectRange(CBaseObject::STAGEFURNACE);

	// bgStreamEffect
	_bgSteamUse = false;
	_bgSteamEffect.Resize(4);

	_vScale.x = 1.0f; _vScale.y = 1.0f; _vScale.z = 1.0f;

	_bgSteamEffect.Get(0) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_bgSteamEffect.Get(0)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/SteamEffect/1.dds", 1000, 600, 0.7f, 0);

	_bgSteamEffect.Get(1) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_bgSteamEffect.Get(1)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/SteamEffect/2.dds", 1000, 600, 0.7f, 0);

	_bgSteamEffect.Get(2) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_bgSteamEffect.Get(2)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/SteamEffect/3.dds", 1000, 600, 0.7f, 0);

	_bgSteamEffect.Get(3) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_bgSteamEffect.Get(3)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/SteamEffect/4.dds", 1000, 600, 0.7f, 0);

	for(int i = 0; i < _bgSteamEffect.GetSize(); i++)
		SetBGEffectInfoOnRandom(_bgSteamEffect.Get(i));

	// Plane
	_ePlaneType = BLACK;
	_planeUse = true;

	_plane.Resize(2);

	_vScale.x = 1.2f; _vScale.y = 1.2f; _vScale.z = 1.2f;

	_plane.Get(0) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_plane.Get(0)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/Plane/BlackPlane.dds", 800, 600, 0.0f, 0);

	_plane.Get(1) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_plane.Get(1)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/Plane/WhitePlane.dds", 800, 600, 0.0f, 0);	

	// Command
	_commandUse = false;
	_eCommandType = CAIManager::RUNAWAY;
	
	_command.Resize(3);

	_vScale.x = 0.1f; _vScale.y = 0.1f; _vScale.z = 0.1f;
	_vPos.x = 0.0f;

	_command.Get(0) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_command.Get(0)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/CommandEffect/Attack.dds", 460, 330, 1.0f, 0);

	_command.Get(1) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_command.Get(1)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/CommandEffect/Runaway.dds", 460, 330, 1.0f, 0);

	_command.Get(2) = new CAttachment(ID_ATTACHMENT, CBaseObject::BASE, _vPos, _vScale, _vRotate, _vPos, 0);
	_command.Get(2)->InitObject(EngineMgr->GetpDevice(), "./Image/Effects/CommandEffect/Defense.dds", 460, 330, 1.0f, 0);
}

CEffectManager::~CEffectManager(){
	// 반복자 생성
	CDListIterator<CBaseEffect*> itr;
	
	// _damageEffect로부터 반복자 초기화
	itr = _baseEffect.GetIterator();
	
	// _damageEffect를 훑으며
	for(itr.Start(); itr.Valid();){
		_baseEffect.Remove(itr);
	}

	CDListIterator<CLightEffect*> itrLight;

	itrLight = _lightEffect.GetIterator();

	for(itrLight.Start(); itrLight.Valid();){
		_lightEffect.Remove(itrLight);
	}
}

void CEffectManager::EffectUpdate(){
	BGDarkEffectUpdate();
	BGStreamEffectUpdate();

	EffectMgr->CommandEffectUpdate();

	SmallScaleEffectUpdate();
	SmallScaleEffectDelete();

	if(AIMgr->BuffCharacterCheck())
		LightEffectUpdate();
}

void CEffectManager::BGDarkEffectUpdate(){
	D3DXVECTOR3 t_vTemp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	static float fCount = 0;

	if(_bgDarkUse){
		for(int i = 0; i < 5; i++){
			CAttachment* t_pAtt = _bgDarkEffect.Get(i);

			if(t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a < 0.7f)
				t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.005f;

			t_pAtt->GetPriPos()->x += 1.0f;
			t_pAtt->GetPriPos()->y += 0.5f * sin(fCount);

			fCount += 0.0001f;

			if(sin(fCount) > D3DX_PI)
				fCount = 0;

			t_pAtt->Render(&t_vTemp, &t_vTemp, &t_vTemp, &t_vTemp);

			if(CheckOverRange(t_pAtt))
				t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;

			if(t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a < -0.01f)
				SetBGEffectInfoOnRandom(t_pAtt);
		}
	}
}

void CEffectManager::ResetBGDarkEffect(){
	for(int i = 0; i < 5; i++){
		CAttachment* t_pAtt = _bgDarkEffect.Get(i);

		SetBGEffectInfoOnRandom(t_pAtt);
	}
}

void CEffectManager::BGStreamEffectUpdate(){
	D3DXVECTOR3 t_vTemp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	static float fCount = 0;

	if(_bgSteamUse){
		for(int i = 0; i < 4; i++){
			CAttachment* t_pAtt = _bgSteamEffect.Get(i);

			if(t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a < 0.7f)
				t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.005f;

			t_pAtt->GetPriPos()->x += 1.0f;
			t_pAtt->GetPriPos()->y += 0.5f * sin(0.5f*fCount);

			fCount += 0.0001f;

			if(sin(fCount) > D3DX_PI)
				fCount = 0;

			t_pAtt->Render(&t_vTemp, &t_vTemp, &t_vTemp, &t_vTemp);

			if(CheckOverRange(t_pAtt))
				t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;

			if(t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a < -0.01f)
				SetBGEffectInfoOnRandom(t_pAtt);
		}
	}
}

void CEffectManager::ResetBGStreamEffect(){
	for(int i = 0; i < 4; i++){
		CAttachment* t_pAtt = _bgSteamEffect.Get(i);

		SetBGEffectInfoOnRandom(t_pAtt);
	}
}

float CEffectManager::AlphaPlaneUpdate(){
	D3DXVECTOR3 t_vTemp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CAttachment* t_pAtt;

	if(_planeUse){
		CameraMgr->GetCamera()->GetPosition(&t_vPos);

		switch(_ePlaneType){
			case BLACK:	
				t_pAtt = _plane.Get(0);				
				break;
			case WHITE:	
				t_pAtt = _plane.Get(1);
				break;
		}

		t_pAtt->GetPriPos()->x = t_vPos.x;
		t_pAtt->GetPriPos()->y = t_vPos.y;
		t_pAtt->GetPriPos()->z = 700.0f + t_vPos.z;

		t_pAtt->Render(&t_vTemp, &t_vTemp, &t_vTemp, &t_vTemp);

		switch(_planeState){
			case true:
				t_pAtt->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;

				if(t_pAtt->GetMtrlArray()->Get(0,0).Diffuse.a > 1.0f)
					_planeState = false;
				return t_pAtt->GetMtrlArray()->Get(0,0).Diffuse.a;
			case false:
				t_pAtt->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;

				if(t_pAtt->GetMtrlArray()->Get(0,0).Diffuse.a < 0.0f){
					_planeUse = false;
					_planeState = true;
				}
				return t_pAtt->GetMtrlArray()->Get(0,0).Diffuse.a;
		}
	}

	return -1.0f;
}

void CEffectManager::CommandEffectUpdate(){
	D3DXVECTOR3 t_vTemp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CAttachment* t_pAtt;
	CBody* t_pBody = UIMgr->GetCommander()->GetBody();

	if(_commandUse){
		switch(_eCommandType){
			case CAIManager::ATTACK:
				t_pAtt = _command.Get(0);
				break;
			case CAIManager::RUNAWAY:
				t_pAtt = _command.Get(1);
				break;
			case CAIManager::DEFENSE:
				t_pAtt = _command.Get(2);
				break;
		}

		t_pAtt->RenderApplyScale(t_pBody->GetPriPos(), t_pBody->GetPriSca(), t_pBody->GetPriCen());

		static float t_fDeltaX = 0.0f;

		t_fDeltaX += 5.0f;

		switch(StageMgr->GetStageType()){
			case CStageManager::DUSTBRIDGE:
				if(t_fDeltaX <= (float)SYSTEMWIDTH * 0.5f){
					t_pAtt->GetPriPos()->x -= 8.0f;
					t_pAtt->GetPriSca()->x += 0.006f;
					t_pAtt->GetPriSca()->y += 0.006f;
				}
				else if(t_fDeltaX >= (float)SYSTEMWIDTH * 0.5f && t_fDeltaX <= (float)SYSTEMWIDTH){
					t_pAtt->GetPriPos()->x += 8.0f;
					t_pAtt->GetPriSca()->x -= 0.006f;
					t_pAtt->GetPriSca()->y -= 0.006f;
				}
				else{
					t_pAtt->GetPriPos()->x = 000.0f;
					t_pAtt->GetPriSca()->x = 0.1f;
					t_pAtt->GetPriSca()->y = 0.1f;

					_commandUse = false;
					t_fDeltaX = 0.0f;
				}
				break;
			default:
				if(t_fDeltaX <= (float)SYSTEMWIDTH * 0.5f){
					t_pAtt->GetPriPos()->x += 8.0f;
					t_pAtt->GetPriSca()->x += 0.006f;
					t_pAtt->GetPriSca()->y += 0.006f;
				}
				else if(t_fDeltaX >= (float)SYSTEMWIDTH * 0.5f && t_fDeltaX <= (float)SYSTEMWIDTH){
					t_pAtt->GetPriPos()->x -= 8.0f;
					t_pAtt->GetPriSca()->x -= 0.006f;
					t_pAtt->GetPriSca()->y -= 0.006f;
				}
				else{
					t_pAtt->GetPriPos()->x = 0.0f;
					t_pAtt->GetPriSca()->x = 0.1f;
					t_pAtt->GetPriSca()->y = 0.1f;

					_commandUse = false;
					t_fDeltaX = 0.0f;
				}
				break;
		}		
	}
}

void CEffectManager::LightEffectUpdate(){
	CDListIterator<CLightEffect*> itr;

	itr = _lightEffect.GetIterator();

	for(itr.Start(); itr.Valid(); itr.Forth()){
		itr.Item()->Update();
	}
}

void CEffectManager::SmallScaleEffectUpdate(){
	CDListIterator<CBaseEffect*> itr;
	
	itr = _baseEffect.GetIterator();
	
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(itr.Item()->GetEffectType() != DAMAGE)
			itr.Item()->Update();
	}

	// Damaged를 나중에 렌더
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(itr.Item()->GetEffectType() == DAMAGE)
			itr.Item()->Update();
	}
}
	
void CEffectManager::SmallScaleEffectDelete(){
	// 반복자 생성
	CDListIterator<CBaseEffect*> itr;
	
	itr = _baseEffect.GetIterator();
	
	for(itr.Start(); itr.Valid();){
		if(itr.Item()->GetIsDie()){
			d3d::Delete<CBaseEffect*>(itr.Item());
			_baseEffect.Remove(itr);
		}
		else{
			itr.Forth();
		}
	}
}

void CEffectManager::SetCommandEffect(CAIManager::COMMANDTYPE p_eType){	
	_commandUse = true;
	_eCommandType = p_eType;
}

void CEffectManager::SetBGEffectInfoOnRandom(CAttachment* p_pAtt){
	float t_fTemp = (rand() % 7 + 1) * 0.1f;
	float fAlpha = 0.0f;

	p_pAtt->GetPriPos()->x = (float)(abs(_box._max.x - _box._min.x) * t_fTemp) - abs(_box._min.x);
	p_pAtt->GetPriPos()->y = (float)(abs(_box._max.y - _box._min.y) * t_fTemp) - abs(_box._min.y);
	p_pAtt->GetPriPos()->z = (float)_box._min.z - 50.0f;
		
	p_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a = fAlpha;
}

void CEffectManager::SetBGEffectRange(CBaseObject::OWNER p_eStage){
	CBody* t_pBody = ObjectMgr->GetEntity(p_eStage)->GetBody();

	switch(p_eStage){
		case CBaseObject::STAGEFURNACE:
			_box._min = D3DXVECTOR3((float)(-t_pBody->GetWidthHalf() - 100.0f),
				(float)(-t_pBody->GetHeightHalf() - 50.0f), -100.0f);
			_box._max = D3DXVECTOR3((float)(t_pBody->GetWidthHalf()),
				-300.0f, 0.0f);
			break;
		default:
			_box._min = D3DXVECTOR3((float)(-t_pBody->GetWidthHalf() - 200.0f),
				(float)(-t_pBody->GetHeightHalf() - 100.0f), -100.0f);
			_box._max = D3DXVECTOR3((float)(t_pBody->GetWidthHalf()) + 200.0f,
				(float)(t_pBody->GetHeightHalf() + 100.0f), 0.0f);
			break;
	}
}

bool CEffectManager::CheckOverRange(CAttachment* t_pAtt){
	if(t_pAtt->GetPriPos()->x > _box._max.x)
		return true;

	return false;
}