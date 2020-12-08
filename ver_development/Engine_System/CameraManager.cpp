#include "../BaseHeader.h"

// 생성자에서는 초기화만을 담당한다.
CCameraManager::CCameraManager(){
	_camera = new CCamera(CCamera::TWODEMENTION);
	_camera->SetVelocity(300.0f);
	_mode = RELAX;

	_origin = NULL;

	CameraDefault();
}

CCameraManager::~CCameraManager(){

}

void CCameraManager::CameraUpdate(){

}

void CCameraManager::CameraInit(float p_fx, float p_fy, float p_fz){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	_vDestination.x = t_vPos.x = p_fx;
	_vDestination.y = t_vPos.y = p_fy;
	_vDestination.z = t_vPos.z = p_fz;

	GetCamera()->SetZoom(t_vPos.z);

	GetCamera()->SetPosition(&t_vPos);
}

void CCameraManager::CameraDefault(){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	_vDestination.x = t_vPos.x = 0.0f;
	_vDestination.y = t_vPos.y = 0.0f;
	_vDestination.z = t_vPos.z = -700.0f;

	GetCamera()->SetZoom(t_vPos.z);

	GetCamera()->SetPosition(&t_vPos);
}

void CCameraManager::CameraMode(){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();

	if(_mode == MAP){
		SetDestinationByMouse();
		return;
	}
	else if(_mode == EVENT){
		FaceToDestination();
		return;
	}

	switch(StageMgr->GetStageType()){
		case CStageManager::GOODHOPE:
			_mode = RELAX;
			if(t_pHeroBody->GetRow() == CBaseObject::RIGHT)
				SetDestinationX(t_pHeroBody->GetPriPos()->x + 150.0f);
			else
				SetDestinationX(t_pHeroBody->GetPriPos()->x - 150.0f);

			CameraMgr->CameraUp(-300.0f);
			break;
		case CStageManager::CHIMNEY:
			_mode = RELAX;
			if(t_pHeroBody->GetRow() == CBaseObject::RIGHT)
				SetDestinationX(t_pHeroBody->GetPriPos()->x + 150.0f);
			else
				SetDestinationX(t_pHeroBody->GetPriPos()->x - 150.0f);

			CameraMgr->CameraUp(-200.0f);
			break;
		case CStageManager::HOME:
			_mode = RELAX;
			if(t_pHeroBody->GetRow() == CBaseObject::RIGHT)
				SetDestinationX(t_pHeroBody->GetPriPos()->x + 150.0f);
			else
				SetDestinationX(t_pHeroBody->GetPriPos()->x - 150.0f);

			CameraMgr->CameraUp(-130.0f);
			break;
		case CStageManager::SCRAPMOUNTAIN:
			switch(StageMgr->GetAreaNumber()){
				case 0:
					switch(_mode){
						case RELAX:
							if(t_pHeroBody->GetRow() == CBaseObject::RIGHT)
								SetDestinationX(t_pHeroBody->GetPriPos()->x + 150.0f);
							else
								SetDestinationX(t_pHeroBody->GetPriPos()->x - 150.0f);

							if(t_pHeroBody->GetPriPos()->x > AIMgr->GetDustKid()->GetDestination()->x - AIMgr->GetAttackRange()->_max.x){
								_mode = COMBAT;
							}
							break;
						case COMBAT:	
							if(t_pHeroBody->GetPriPos()->x < AIMgr->GetDustKid()->GetDestination()->x - AIMgr->GetAttackRange()->_max.x){
								_mode = RELAX;
								break;
							}

							if(AIMgr->GetDustKid()->GetLive() == true){
								switch(AIMgr->GetDustKid()->GetHealthState()){
									case CCharacterEntity::NONE:
										_mode = RELAX;
										break;
									case CCharacterEntity::HEALTHFUL:
										SetDestinationX(-StageMgr->GetStage()->GetWidthHalf() * (1.0f/2.0f));
										AIMgr->GetDustKid()->SetDestinationX(GetDestination()->x);
										break;
									case CCharacterEntity::NORMAL:
										SetDestinationX(0);
										AIMgr->GetDustKid()->SetDestinationX(GetDestination()->x);
										break;
									case CCharacterEntity::WEAK:
										SetDestinationX(StageMgr->GetStage()->GetWidthHalf() * (1.0f/2.0f));
										AIMgr->GetDustKid()->SetDestinationX(GetDestination()->x);
										break;
									default:
										_mode = RELAX;
										break;
								}
							}
							else
								_mode = RELAX;
							break;
						default:
							break;
					}
					break;
				case 1:
					switch(_mode){
						case RELAX:
							if(t_pHeroBody->GetRow() == CBaseObject::RIGHT)
								SetDestinationX(t_pHeroBody->GetPriPos()->x + 150.0f);
							else
								SetDestinationX(t_pHeroBody->GetPriPos()->x - 150.0f);

							if(t_pHeroBody->GetPriPos()->x > AIMgr->GetMiniWorker()->GetDestination()->x - AIMgr->GetAttackRange()->_max.x){
								_mode = COMBAT;
							}
							break;
						case COMBAT:	
							if(t_pHeroBody->GetPriPos()->x < AIMgr->GetMiniWorker()->GetDestination()->x - AIMgr->GetAttackRange()->_max.x){
								_mode = RELAX;
								break;
							}

							if(AIMgr->GetMiniWorker()->GetLive() == true){
								switch(AIMgr->GetMiniWorker()->GetHealthState()){
									case CCharacterEntity::NONE:
										_mode = RELAX;
										break;
									case CCharacterEntity::HEALTHFUL:
										SetDestinationX(-StageMgr->GetStage()->GetWidthHalf() * (1.0f/2.0f));
										AIMgr->GetMiniWorker()->SetDestinationX(GetDestination()->x);
										break;
									case CCharacterEntity::NORMAL:
										SetDestinationX(0);
										AIMgr->GetMiniWorker()->SetDestinationX(GetDestination()->x);
										break;
									case CCharacterEntity::WEAK:
										SetDestinationX(StageMgr->GetStage()->GetWidthHalf() * (1.0f/2.0f));
										AIMgr->GetMiniWorker()->SetDestinationX(GetDestination()->x);
										break;
									default:
										_mode = RELAX;
										break;
								}
							}
							else
								_mode = RELAX;
							break;
					}
					break;
				case 2:
					switch(_mode){
						case RELAX:
							if(t_pHeroBody->GetRow() == CBaseObject::RIGHT)
								SetDestinationX(t_pHeroBody->GetPriPos()->x + 150.0f);
							else
								SetDestinationX(t_pHeroBody->GetPriPos()->x - 150.0f);

							if(t_pHeroBody->GetPriPos()->x > AIMgr->GetWorker()->GetDestination()->x - AIMgr->GetAttackRange()->_max.x){
								_mode = COMBAT;
							}
							break;
						case COMBAT:	
							if(t_pHeroBody->GetPriPos()->x < AIMgr->GetWorker()->GetDestination()->x - AIMgr->GetAttackRange()->_max.x){
								_mode = RELAX;
								break;
							}

							if(AIMgr->GetWorker()->GetLive() == true){
								switch(AIMgr->GetWorker()->GetHealthState()){
									case CCharacterEntity::NONE:
										_mode = RELAX;
										break;
									case CCharacterEntity::HEALTHFUL:
										SetDestinationX(-StageMgr->GetStage()->GetWidthHalf() * (1.0f/2.0f));
										AIMgr->GetWorker()->SetDestinationX(GetDestination()->x);
										break;
									case CCharacterEntity::NORMAL:
										SetDestinationX(0);
										AIMgr->GetWorker()->SetDestinationX(GetDestination()->x);
										break;
									case CCharacterEntity::WEAK:
										SetDestinationX(StageMgr->GetStage()->GetWidthHalf() * (1.0f/2.0f));
										AIMgr->GetWorker()->SetDestinationX(GetDestination()->x);
										break;
									default:
										_mode = RELAX;
										break;
								}
							}
							else
								_mode = RELAX;
							break;
					}
					break;
			}
			CameraMgr->CameraUp(-100.0f);
			break;
		case CStageManager::FURNACE:
				switch(_mode){
					case RELAX:
						if(t_pHeroBody->GetRow() == CBaseObject::RIGHT)
							SetDestinationX(t_pHeroBody->GetPriPos()->x + 150.0f);
						else
							SetDestinationX(t_pHeroBody->GetPriPos()->x - 150.0f);

						if(t_pHeroBody->GetPriPos()->x > AIMgr->GetGateKeeper()->GetDestination()->x - AIMgr->GetAttackRange()->_max.x){
							_mode = COMBAT;
						}
						break;
					case COMBAT:	
						if(t_pHeroBody->GetPriPos()->x < AIMgr->GetGateKeeper()->GetDestination()->x - AIMgr->GetAttackRange()->_max.x){
							_mode = RELAX;
							break;
						}

						if(AIMgr->GetGateKeeper()->GetLive() == true){
							switch(AIMgr->GetGateKeeper()->GetHealthState()){
								case CCharacterEntity::NONE:
									_mode = RELAX;
									break;
								case CCharacterEntity::HEALTHFUL:
									SetDestinationX(-StageMgr->GetStage()->GetWidthHalf() * (1.0f/6.0f));
									AIMgr->GetGateKeeper()->SetDestinationX(GetDestination()->x);
									break;
								case CCharacterEntity::NORMAL:
								case CCharacterEntity::WEAK:
									SetDestinationX(StageMgr->GetStage()->GetWidthHalf() * (1.0f/3.0f));
									AIMgr->GetGateKeeper()->SetDestinationX(GetDestination()->x);
									break;
								default:
									_mode = RELAX;
									break;
							}
						}
						else
							_mode = RELAX;
						break;
				}
				break;
		case CStageManager::DUSTBRIDGE:
			switch(_mode){
					case RELAX:
						if(t_pHeroBody->GetRow() == CBaseObject::RIGHT)
							SetDestinationX(t_pHeroBody->GetPriPos()->x + 150.0f);
						else
							SetDestinationX(t_pHeroBody->GetPriPos()->x - 150.0f);

						if(t_pHeroBody->GetPriPos()->x < AIMgr->GetDustKing()->GetDestination()->x + AIMgr->GetAttackRange()->_max.x){
							_mode = COMBAT;
						}
						break;
					case COMBAT:	
						if(t_pHeroBody->GetPriPos()->x > AIMgr->GetDustKing()->GetDestination()->x + AIMgr->GetAttackRange()->_max.x){
							_mode = RELAX;
							break;
						}

						if(AIMgr->GetDustKing()->GetLive() == true){
							switch(AIMgr->GetDustKing()->GetHealthState()){
								case CCharacterEntity::NONE:
									_mode = RELAX;
									break;
								case CCharacterEntity::HEALTHFUL:
									SetDestinationX(StageMgr->GetStage()->GetWidthHalf() * (1.0f/2.0f));
									AIMgr->GetDustKing()->SetDestinationX(GetDestination()->x);
									break;
								case CCharacterEntity::NORMAL:
									SetDestinationX(0.0f);
									AIMgr->GetDustKing()->SetDestinationX(GetDestination()->x);
									break;
								case CCharacterEntity::WEAK:
									SetDestinationX(-StageMgr->GetStage()->GetWidthHalf() * (1.0f/2.0f));
									AIMgr->GetDustKing()->SetDestinationX(GetDestination()->x);
									break;
								default:
									_mode = RELAX;
									break;
							}
						}
						else
							_mode = RELAX;
						break;
				}
				break;
		case CStageManager::WORLDMAP:
			CameraMgr->SetDestinationByMouse();
			break;
		default:
			break;
	}
}

void CCameraManager::LimitDestination(){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	// 우
	if((StageMgr->GetStage()->GetWidthHalf()*0.5f) < GetDestination()->x)
		SetDestinationX(StageMgr->GetStage()->GetWidthHalf()*0.5f);
	// 좌
	else if((StageMgr->GetStage()->GetWidthHalf()*-0.5f) > GetDestination()->x)
		SetDestinationX(StageMgr->GetStage()->GetWidthHalf()*-0.5f);

	// 상
	if((StageMgr->GetStage()->GetHeightHalf()*0.5f) < GetDestination()->y)
		SetDestinationY(StageMgr->GetStage()->GetHeightHalf()*0.5f);
	// 하
	else if((StageMgr->GetStage()->GetHeightHalf()*-0.5f) > GetDestination()->y)
		SetDestinationY(StageMgr->GetStage()->GetHeightHalf()*-0.5f);
}

void CCameraManager::SetDestinationByMouse(){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	if(GetOrigin()){
		if(EngineMgr->GetpInformation()->GetAbsolutedX() > SYSTEMWIDTH || EngineMgr->GetpInformation()->GetAbsolutedY() > SYSTEMHEIGHT)
			return;

		// 좌, 우
		if((GetOrigin()->GetWidthHalf()*0.5f) > EngineMgr->GetpInformation()->GetAdjustedX() && 
			-(GetOrigin()->GetWidthHalf()*0.5f) < EngineMgr->GetpInformation()->GetAdjustedX())
			SetDestinationX(EngineMgr->GetpInformation()->GetAdjustedX());

		// 상, 하		
		if(-(GetOrigin()->GetHeightHalf()*0.5f) < EngineMgr->GetpInformation()->GetAdjustedY() &&
			(GetOrigin()->GetHeightHalf()*0.5f) > EngineMgr->GetpInformation()->GetAdjustedY())
			SetDestinationY(EngineMgr->GetpInformation()->GetAdjustedY());

		if((GetOrigin()->GetWidthHalf()*0.5f) < GetDestination()->x || -(GetOrigin()->GetWidthHalf()*0.5f) > GetDestination()->x ||
			-(GetOrigin()->GetHeightHalf()*0.5f) > GetDestination()->y || (GetOrigin()->GetHeightHalf()*0.5f) < GetDestination()->y){
			SetDestinationX(0.0f);
			SetDestinationY(0.0f);
		}
	}
}

void CCameraManager::FaceToDestination(){
	// deltaS = v * deltaT
	// 벡터를 이용, 방향을 알아내야 한다.
	// 방향 = 벡터의 정규화
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	_camera->GetPosition(&t_vPos);

	float t_fDeltaX = _vDestination.x - t_vPos.x;
	float t_fDeltaY = _vDestination.y - t_vPos.y;
	float t_fDeltaZ = _vDestination.z - t_vPos.z;

	// 거리 == 벡터의 크기 == 힘
	float t_fDistance = 0.0f;
	D3DXVECTOR3 t_vHeading = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	t_fDistance = sqrt((t_fDeltaX * t_fDeltaX) + (t_fDeltaY * t_fDeltaY) + (t_fDeltaZ * t_fDeltaZ));

	if(t_fDistance > 0.0f){
		// a = f / m;
		float t_fAce = t_fDistance * 300.0f;

		float t_fVel = t_fAce * SYSTEM_FRAME_INTERVAL_VER_60;

		if(t_fVel >= 600.0f) t_fVel = 600.0f;

		t_vHeading.x = t_fDeltaX / t_fDistance;
		t_vHeading.y = t_fDeltaY / t_fDistance;
		t_vHeading.z = t_fDeltaZ / t_fDistance;

		t_vPos.x += (t_vHeading.x * t_fVel) * SYSTEM_FRAME_INTERVAL_VER_60;
		t_vPos.y += (t_vHeading.y * t_fVel) * SYSTEM_FRAME_INTERVAL_VER_60;
		t_vPos.z += (t_vHeading.z * t_fVel) * SYSTEM_FRAME_INTERVAL_VER_60;
		
		_camera->SetPosition(&t_vPos);
	}	
}

// 올려다보기 함수
void CCameraManager::CameraUp(float p_fDownLimit){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	static float t_fCount = 0.0f;

	if( ::GetAsyncKeyState('W') & 0x8000f ){
		t_fCount+=5.0f;
		if((StageMgr->GetStage()->GetHeightHalf()*0.5f) > t_fCount)
			SetDestinationY(t_fCount);
	}
	else{
		SetDestinationY(p_fDownLimit);
		t_fCount = 0.0f;
	}
}

// 카메라 진동
void CCameraManager::CameraVibration(){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	int t_x = rand() % 3;
	int t_y = rand() % 10;
	int t_z = rand() % 3;

	if(rand() % 2 == 0)
		t_vPos.x += t_x;
	else
		t_vPos.x -= t_x;

	if(rand() % 2 == 0)
		t_vPos.y += t_y;
	else
		t_vPos.y -= t_y;
	
	if(rand() % 2 == 0)
		t_vPos.z += t_z;
	else
		t_vPos.z -= t_z;

	GetCamera()->SetPosition(&t_vPos);
}

// 키체크 함수
void CCameraManager::CheckKey(float timeDelta, CBaseObject::OWNER Owner){
	////////////////////
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GetCamera()->GetPosition(&t_vPos);

	// 카메라 좌우이동
	if( ::GetAsyncKeyState('A') & 0x8000f ){
		GetCamera()->CallKeyDown();

		if(t_vPos.x <= (-0.5*ObjectMgr->GetEntity(Owner)->GetBody()->GetWidthHalf()))
			return;
		else
			GetCamera()->strafe(-_camera->GetVelocity());
	}

	if( ::GetAsyncKeyState('D') & 0x8000f ){
		GetCamera()->CallKeyDown();

		if(t_vPos.x >= (0.5*ObjectMgr->GetEntity(Owner)->GetBody()->GetWidthHalf()))
			return;
		else
			GetCamera()->strafe(_camera->GetVelocity());
	}

	// 카메라 상하이동
	if( ::GetAsyncKeyState('W') & 0x8000f ){
		GetCamera()->CallKeyDown();	

		if(t_vPos.y >= (0.5*ObjectMgr->GetEntity(Owner)->GetBody()->GetHeightHalf()))
			return;
		else
			GetCamera()->fly(_camera->GetVelocity());
	}

	if( ::GetAsyncKeyState('S') & 0x8000f ){
		GetCamera()->CallKeyDown();	

		if(t_vPos.y <= (-0.5*ObjectMgr->GetEntity(Owner)->GetBody()->GetHeightHalf()))
			return;
		else
			GetCamera()->fly(-_camera->GetVelocity());
	}
}