#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// 로고 보여주기 상태
///////////////////////////////////////////////////////////
void CLogoShow::Enter(CSection* pSection){
	EffectMgr->SetPlaneType(CEffectManager::BLACK);
	EffectMgr->SetPlaneUse(true);

	StageMgr->SetbIsFadeInOut(false);
}

void CLogoShow::Execute(CSection* pSection){
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	EngineMgr->GetpDevice()->SetTransform(D3DTS_WORLD, &I);

	ObjectMgr->GetEntity(ID_LOGO)->Update();
	
	if(ObjectMgr->GetEntity(CBaseObject::LOGO)->GetBody()->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.4f &&
		ObjectMgr->GetEntity(CBaseObject::LOGO)->GetBody()->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4004f){
		MusicMgr->PlayMP3FileForBGM("./Sound/Logo.mp3");
	}

	if(ObjectMgr->GetEntity(CBaseObject::LOGO)->GetBody()->GetMtrlArray()->Get(0,0).Diffuse.a >= 1.0f){
		EffectMgr->SetPlaneType(CEffectManager::BLACK);
		EffectMgr->SetPlaneUse(true);
		StageMgr->SetbIsFadeInOut(true);
	}
	
	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f){
		pSection->GetFSM()->ChangeState(MainMenu->Instance());
	}
}

void CLogoShow::Exit(CSection* pSection){
	MusicMgr->Close();
	EffectMgr->SetBGDarkUse(false);
}

///////////////////////////////////////////////////////////
// 메인메뉴 상태
///////////////////////////////////////////////////////////
void CMainMenuPart::Enter(CSection* pSection){
	MusicMgr->PlayMP3FileForBGM("./Sound/MainMenu.mp3");
	EffectMgr->SetPlaneType(CEffectManager::BLACK);
	EffectMgr->SetPlaneUse(true);

	StageMgr->SetbIsFadeInOut(false);
}

void CMainMenuPart::Execute(CSection* pSection){
	// 오브젝트 그리기
	ObjectMgr->GetEntity(ID_MAINMENU)->Update();

	static int t_type = -1;

	if(::GetAsyncKeyState(VK_RETURN) == 0xffff8001){
		t_type = ObjectMgr->ComputeBoundMenu();		

		if(t_type != -1){
			EffectMgr->SetPlaneType(CEffectManager::BLACK);
			EffectMgr->SetPlaneUse(true);
			StageMgr->SetbIsFadeInOut(true);
			MusicMgr->PlayMP3FileForEffect("./Sound/MenuSelect.mp3");
		}
	}

	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f){
		switch(t_type){
			// 게임 시작
			case CMainMenu::START:
				StageMgr->SetStage(CStageManager::HOME);
				pSection->GetFSM()->ChangeState(AreaSelection->Instance());
				break;
			case CMainMenu::INTRO:
				pSection->GetFSM()->ChangeState(IntroShow->Instance());
				break;
			// 게임 끝
			case CMainMenu::EXIT:
				pSection->GetFSM()->ChangeState(GameEnd->Instance());
				break;
			default:
				break;
		}
	}
}

void CMainMenuPart::Exit(CSection* pSection){
	MusicMgr->Close();
	EffectMgr->SetBGDarkUse(false);
}

///////////////////////////////////////////////////////////
// Intro 상태
///////////////////////////////////////////////////////////
void CIntroShow::Enter(CSection* pSection){
	MusicMgr->PlayMP3FileForBGM("./Sound/MainMenu.mp3");
	EffectMgr->SetPlaneType(CEffectManager::BLACK);
	EffectMgr->SetPlaneUse(true);

	StageMgr->SetbIsFadeInOut(false);
}

void CIntroShow::Execute(CSection* pSection){
	// 오브젝트 그리기
	ObjectMgr->GetEntity(ID_INTRO)->Update();

	if(GetAsyncKeyState(VK_ESCAPE) && 0x8000f){
		EffectMgr->SetPlaneType(CEffectManager::BLACK);
		EffectMgr->SetPlaneUse(true);
		StageMgr->SetbIsFadeInOut(true);
	}

	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f){
		pSection->GetFSM()->ChangeState(MainMenu->Instance());
	}
}

void CIntroShow::Exit(CSection* pSection){
	MusicMgr->Close();
	EffectMgr->SetBGDarkUse(false);
}

///////////////////////////////////////////////////////////
// 세계 지도 상태
///////////////////////////////////////////////////////////
void CWorldMapShow::Enter(CSection* pSection){
	MusicMgr->PlayMP3FileForBGM("./Sound/WorldMap.mp3");

	CameraMgr->SetOrigin(ObjectMgr->GetEntity(CBaseObject::WORLDMAP)->GetBody());
	CameraMgr->SetMode(CCameraManager::MAP);

	EngineMgr->SetExhaust(D3DXVECTOR3(-700.0f, -218.0f, 0.0f), -740.0f, -223.0f, 0.0f, -550.0f, -173.0f, 5.0f, 50);
	EngineMgr->SetExhaust(D3DXVECTOR3(-705.0f, -326.0f, 0.0f), -768.0f, -330.0f, 0.0f, -570.0f, -120.0f, 5.0f, 60);
	EngineMgr->SetExhaust(D3DXVECTOR3(-643.0f, -266.0f, 0.0f), -705.0f, -275.0f, 0.0f, -550.0f, -105.0f, 5.0f, 80);
	EngineMgr->SetExhaust(D3DXVECTOR3(-594.0f, -258.0f, 0.0f), -650.0f, -266.0f, 0.0f, -560.0f, -165.0f, 5.0f, 30);
	EngineMgr->SetExhaust(D3DXVECTOR3(-546.0f, -324.0f, 0.0f), -587.0f, -326.0f, 0.0f, -487.0f, -206.0f, 5.0f, 40);
	EngineMgr->SetExhaust(D3DXVECTOR3(-524.0f, -267.0f, 0.0f), -565.0f, -273.0f, 0.0f, -450.0f, -240.0f, 5.0f, 10);
	EngineMgr->SetExhaust(D3DXVECTOR3(-448.0f, -237.0f, 0.0f), -502.0f, -237.0f, 0.0f, -440.0f, -230.0f, 5.0f, 10);
	EngineMgr->SetExhaust(D3DXVECTOR3(-391.0f, -209.0f, 0.0f), -433.0f, -214.0f, 0.0f, -300.0f, -130.0f, 5.0f, 60);
	EngineMgr->SetExhaust(D3DXVECTOR3(-187.0f, -327.0f, 0.0f), -224.0f, -329.0f, 0.0f, -100.0f, -180.0f, 5.0f, 30);
	EngineMgr->SetExhaust(D3DXVECTOR3(-102.0f, -324.0f, 0.0f), -240.0f, -330.0f, 0.0f, 20.0f, -50.0f, 5.0f, 170);
	EngineMgr->SetExhaust(D3DXVECTOR3(336.0f, -367.0f, 0.0f), 286.0f, -376.0f, 0.0f, 390.0f, -190.0f, 5.0f, 150);
	EngineMgr->SetExhaust(D3DXVECTOR3(333.0f, -547.0f, 0.0f), 230.0f, -552.0f, 0.0f, 460.0f, -270.0f, 5.0f, 70);
	EngineMgr->SetExhaust(D3DXVECTOR3(652.0f, -159.0f, 0.0f), 622.0f, -162.0f, 0.0f, 820.0f, 10.0f, 5.0f, 70);
	EngineMgr->SetExhaust(D3DXVECTOR3(702.0f, -236.0f, 0.0f), 672.0f, -252.0f, 0.0f, 820.0f, -50.0f, 5.0f, 50);
//	EngineMgr->SetExhaust(D3DXVECTOR3(502.0f, 360.0f, 0.0f), 300.0f, 350.0f, 0.0f, 740.0f, 610.0f, 5.0f, 100);
//	EngineMgr->SetExhaust(D3DXVECTOR3(552.0f, 355.0f, 0.0f), 330.0f, 350.0f, 0.0f, 790.0f, 610.0f, 5.0f, 350);
//	EngineMgr->SetExhaust(D3DXVECTOR3(452.0f, 375.0f, 0.0f), 330.0f, 350.0f, 0.0f, 770.0f, 610.0f, 5.0f, 250);

	for(int i = 0; i < 100; i++)
		EngineMgr->UpdateExhaust();	

	EffectMgr->SetPlaneType(CEffectManager::BLACK);
	EffectMgr->SetPlaneUse(true);

	StageMgr->SetbIsFadeInOut(false);
	StageMgr->SetStage(CStageManager::WORLDMAP);

	// 아군 초기화
	AIMgr->InitOurForce();

	MouseMgr->SetUseCursor(true);
}

void CWorldMapShow::Execute(CSection* pSection){
	ObjectMgr->ComputeBoundStagePointAndMouse(pSection);
	ObjectMgr->GetEntity(ID_WORLDMAP)->Update();

	EventMgr->GetEventWorldMap()->Update();

	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f){
		pSection->GetFSM()->ChangeState(AreaSelection->Instance());
	}
}

void CWorldMapShow::Exit(CSection* pSection){
	MouseMgr->SetUseCursor(false);

	MusicMgr->Close();
	CameraMgr->SetMode(CCameraManager::RELAX);

	EffectMgr->SetBGDarkUse(false);
	EngineMgr->DeleteExhaust();
}

///////////////////////////////////////////////////////////
// Area Selection 상태
///////////////////////////////////////////////////////////
void CAreaSelection::Enter(CSection* pSection){
	StageMgr->SetbIsFadeInOut(false);
	MouseMgr->SetUseCursor(true);
	CameraMgr->CameraDefault();
	ObjectMgr->SetItemCount(0);
}

void CAreaSelection::Execute(CSection* pSection){	
	CameraMgr->CameraDefault();

	switch(StageMgr->GetStageType()){
		case CStageManager::SCRAPMOUNTAIN:
			ObjectMgr->GetEntity(CBaseObject::STAGEMOUNTAIN)->Update();

			if(StageMgr->GetAreaNumber() != -1){
				EffectMgr->SetPlaneType(CEffectManager::BLACK);
				EffectMgr->SetPlaneUse(true);
				StageMgr->SetbIsFadeInOut(true);
				
				if(EffectMgr->AlphaPlaneUpdate() >= 1.0f){
					switch(StageMgr->GetAreaNumber()){
						case 0:
							Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_SECTION, ID_STAGEMOUNTAIN, Msg_Area1, NO_ADDITIONAL_INFO);
							break;
						case 1:
							Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_SECTION, ID_STAGEMOUNTAIN, Msg_Area2, NO_ADDITIONAL_INFO);
							break;
						case 2:
							Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_SECTION, ID_STAGEMOUNTAIN, Msg_Area3, NO_ADDITIONAL_INFO);
							break;	
						default:
							break;
					}
					StageMgr->Update(pSection);
				}				
			}
			else
				EffectMgr->AlphaPlaneUpdate();
			break;		
		default:
			StageMgr->Update(pSection);
			break;
	}

	EffectMgr->EffectUpdate();
}

void CAreaSelection::Exit(CSection* pSection){
	MouseMgr->SetUseCursor(false);
}

///////////////////////////////////////////////////////////
// Stage::Home Show
///////////////////////////////////////////////////////////
void CStageHomeShow::Enter(CSection* pSection){
	MusicMgr->PlayMP3FileForBGM("./Sound/Home.mp3");

	StageMgr->SetbIsFadeInOut(false);
	StageMgr->SetStage(CStageManager::HOME);

	COrgan* t_pBody = StageMgr->GetStage();

	EngineMgr->SetDirt(t_pBody->GetPriPos()->x - t_pBody->GetWidthHalf() - 100.0f, t_pBody->GetPriPos()->y - t_pBody->GetHeightHalf() - 100.0f, 0.0f,
		t_pBody->GetPriPos()->x + t_pBody->GetWidthHalf() + 100.0f, t_pBody->GetPriPos()->y + t_pBody->GetHeightHalf() + 100.0f, 5.0f, 50);

	for(int i = 0; i < 100; i++){
		EngineMgr->GetpDirt()->update(EngineMgr->GetTimeDelta());
	}

	EngineMgr->GetpDirt()->render();

	CameraMgr->CameraInit(0.0f, -130.0f, -700.0f);
}

void CStageHomeShow::Execute(CSection* pSection){
	// 배경 그리기
	ObjectMgr->GetEntity(ID_STAGEHOME)->Update();

	// 계산
	ObjectMgr->ComputeBoundStageHomeAndHero();
	ObjectMgr->ComputeGetOutStage(CBaseObject::STAGEHOME, AIMgr->GetHero()->GetBody());
	UIMgr->ActivateProduction();

	// 주인공 기관 계산 & 그리기
	AIMgr->HeroUpdate();

	if(!StageMgr->GetbIsHomeInOut()){
		// 수레 그리기
		AIMgr->CartUpdate();

		// 꽃 그리기
		AIMgr->FlowerUpdate();

		// AI 그리기
		AIMgr->AIUpdate();

		EffectMgr->EffectUpdate();
	}	

	// UI 그리기
	UIMgr->UIUpdate();

	EngineMgr->GetpDirt()->update(EngineMgr->GetTimeDelta());

	if(!StageMgr->GetbIsHomeInOut()){
		EngineMgr->GetpDirt()->render(); // 하늘위에서 떨어지는 Dirt Particle 그리기
	}

	// 이벤트
	EventMgr->GetEventStage()->Update();

	// Effect
	EffectMgr->AlphaPlaneUpdate();

	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f)
		if(StageMgr->GetbIsGetOutStage())
			pSection->GetFSM()->ChangeState(WorldMapShow->Instance());
}

void CStageHomeShow::Exit(CSection* pSection){
	MusicMgr->Close();

	d3d::Delete<CParticle*>( EngineMgr->GetpDirt() );
	StageMgr->SetbIsGetOutStage(false);
	StageMgr->SetbIsFadeInOut(false);
	CameraMgr->CameraDefault();
}

///////////////////////////////////////////////////////////
// Stage::Mountain Show
///////////////////////////////////////////////////////////
void CStageMountainShow::Enter(CSection* pSection){
	UIMgr->ActiveCommander();

	StageMgr->SetbIsFadeInOut(false);
	StageMgr->SetStage(CStageManager::SCRAPMOUNTAIN);

	COrgan* t_pBody = StageMgr->GetStage();

	EngineMgr->SetDirt(-t_pBody->GetWidthHalf() - 100.0f, -t_pBody->GetHeightHalf() - 100.0f, 0.0f,
		t_pBody->GetWidthHalf() + 100.0f, t_pBody->GetHeightHalf() + 100.0f, 5.0f, 600);

	for(int i = 0; i < 200; i++){
		EngineMgr->GetpDirt()->update(EngineMgr->GetTimeDelta());
		EngineMgr->GetpDirt()->render();
	}

	CameraMgr->CameraInit(-600.0f, -100.0f, -950.0f);

	EffectMgr->SetBGEffectRange(CBaseObject::STAGEMOUNTAIN);
	EffectMgr->SetBGDarkUse(true);
	EffectMgr->ResetBGDarkEffect();
}

void CStageMountainShow::Execute(CSection* pSection){
	// 계산
	ObjectMgr->ComputeGetOutStage(CBaseObject::STAGEMOUNTAIN, AIMgr->GetHero()->GetBody());

	// 배경 그리기
	ObjectMgr->GetEntity(ID_STAGEMOUNTAIN)->Update();

	// 주인공 기관 계산 & 그리기
	AIMgr->HeroUpdate();
	
	// 수레 그리기
	AIMgr->CartUpdate();

	// 꽃 그리기
	AIMgr->FlowerUpdate();

	// Item 그리기
	ObjectMgr->CreatItem();
	ObjectMgr->UpdateItem();	

	// AI 그리기
	AIMgr->AIUpdate();

	// 하늘위에서 떨어지는 Dirt Particle 그리기
	EngineMgr->GetpDirt()->update(EngineMgr->GetTimeDelta());
	EngineMgr->GetpDirt()->render(); 

	EffectMgr->EffectUpdate();

	// UI 그리기
	UIMgr->UIUpdate();

	// 이벤트
	EventMgr->GetEventStage()->Update();

	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f)
		if(StageMgr->GetbIsGetOutStage())
			pSection->GetFSM()->ChangeState(WorldMapShow->Instance());
}

void CStageMountainShow::Exit(CSection* pSection){
	MusicMgr->Close();

	EffectMgr->SetBGDarkUse(false);
	d3d::Delete<CParticle*>( EngineMgr->GetpDirt() );
	StageMgr->SetbIsGetOutStage(false);
	StageMgr->SetbIsFadeInOut(false);
	CameraMgr->CameraDefault();
	StageMgr->SetAreaNumber(-1);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_SECTION, ID_STAGEMOUNTAIN, Msg_Selection, NO_ADDITIONAL_INFO);
	UIMgr->MinimizeCommander();
}

///////////////////////////////////////////////////////////
// Stage::Furnace Show
///////////////////////////////////////////////////////////
void CStageFurnaceShow::Enter(CSection* pSection){
	MusicMgr->PlayMP3FileForBGM("./Sound/Furnace.mp3");

	UIMgr->ActiveCommander();

	StageMgr->SetbIsFadeInOut(false);
	StageMgr->SetStage(CStageManager::FURNACE);

	COrgan* t_pBody = StageMgr->GetStage();

	EngineMgr->SetKindling(-t_pBody->GetWidthHalf() - 100.0f, -t_pBody->GetHeightHalf() - 100.0f, 0.0f,
		t_pBody->GetWidthHalf() + 100.0f, t_pBody->GetPriPos()->y - 300.0f, 1.0f, 100);

	for(int i = 0; i < 100; i++){
		EngineMgr->GetpKindling()->update(EngineMgr->GetTimeDelta());
		EngineMgr->GetpKindling()->render();
	}

	CameraMgr->CameraInit(-300.0f, -140.0f, -900.0f);

	EffectMgr->SetBGEffectRange(CBaseObject::STAGEFURNACE);
	EffectMgr->SetBGStreamUse(true);
	EffectMgr->ResetBGStreamEffect();
}

void CStageFurnaceShow::Execute(CSection* pSection){	
	// 배경 그리기
	ObjectMgr->GetEntity(ID_STAGEFURNACE)->Update();

	AIMgr->GateKeeperUpdate();

	if(AIMgr->GetGateKeeper()->GetLive() == false && EventMgr->GetEventStage()->_gatekeeperDie == false){
		EventMgr->GetEventStage()->GetFSM()->ChangeState(EventStageGateKeeperDie->Instance());
		EventMgr->GetEventStage()->_gatekeeperDie = true;
		StageMgr->_furnaceClear = true;
	}

	// 계산
	ObjectMgr->ComputeGetOutStage(CBaseObject::STAGEFURNACE, AIMgr->GetHero()->GetBody());
	CameraMgr->CameraUp(-300.0f);
	StageMgr->ComputeMoveLimitStage();

	// 주인공 기관 계산 & 그리기
	AIMgr->HeroUpdate();

	if(!StageMgr->GetbIsHomeInOut()){
		// 수레 그리기
		AIMgr->CartUpdate();

		// 꽃 그리기
		AIMgr->FlowerUpdate();

		// AI 그리기
		AIMgr->AIUpdate();
	}

	EffectMgr->EffectUpdate();

	// UI 그리기
	UIMgr->UIUpdate();

	EngineMgr->GetpKindling()->update(EngineMgr->GetTimeDelta());
	EngineMgr->GetpKindling()->render();

	// 이벤트
	EventMgr->GetEventStage()->Update();

	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f)
		if(StageMgr->GetbIsGetOutStage())
			pSection->GetFSM()->ChangeState(WorldMapShow->Instance());
}

void CStageFurnaceShow::Exit(CSection* pSection){
	MusicMgr->Close();

	d3d::Delete<CParticle*>( EngineMgr->GetpKindling() );
	UIMgr->MinimizeCommander();

	EffectMgr->SetBGStreamUse(false);
	StageMgr->SetbIsGetOutStage(false);
	StageMgr->SetbIsFadeInOut(false);
	CameraMgr->CameraDefault();
}

///////////////////////////////////////////////////////////
// Stage::Chimney Show
///////////////////////////////////////////////////////////
void CStageChimneyShow::Enter(CSection* pSection){
	MusicMgr->PlayMP3FileForBGM("./Sound/Chimney.mp3");

	StageMgr->SetbIsFadeInOut(false);
	StageMgr->SetStage(CStageManager::CHIMNEY);

	COrgan* t_pBody = StageMgr->GetStage();

	EngineMgr->SetDirt(t_pBody->GetPriPos()->x - t_pBody->GetWidthHalf() - 100.0f, t_pBody->GetPriPos()->y - t_pBody->GetHeightHalf() - 100.0f, 0.0f,
		t_pBody->GetPriPos()->x + t_pBody->GetWidthHalf() + 100.0f, t_pBody->GetPriPos()->y + t_pBody->GetHeightHalf() + 100.0f, 5.0f, 50);

	for(int i = 0; i < 200; i++){
		EngineMgr->GetpDirt()->update(EngineMgr->GetTimeDelta());
		EngineMgr->GetpDirt()->render();
	}

	CameraMgr->CameraInit(0.0f, -140.0f, -900.0f);
}

void CStageChimneyShow::Execute(CSection* pSection){
	// 배경 그리기
	ObjectMgr->GetEntity(ID_STAGECHIMNEY)->Update();

	// 계산
	ObjectMgr->ComputeGetOutStage(CBaseObject::STAGECHIMNEY, AIMgr->GetHero()->GetBody());
	CameraMgr->CameraUp(-300.0f);
	StageMgr->ComputeMoveLimitStage();

	// 주인공 기관 계산 & 그리기
	AIMgr->HeroUpdate();

	// 수레 그리기
	AIMgr->CartUpdate();

	// 꽃 그리기
	AIMgr->FlowerUpdate();

	// AI 그리기
	AIMgr->AIUpdate();

	EngineMgr->GetpDirt()->update(EngineMgr->GetTimeDelta());
	EngineMgr->GetpDirt()->render(); // 하늘위에서 떨어지는 Dirt Particle 그리기

	EffectMgr->EffectUpdate();

	// UI 그리기
	UIMgr->UIUpdate();

	// 이벤트
	EventMgr->GetEventStage()->Update();

	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f)
		if(StageMgr->GetbIsGetOutStage())
			pSection->GetFSM()->ChangeState(WorldMapShow->Instance());
}

void CStageChimneyShow::Exit(CSection* pSection){
	MusicMgr->Close();

	d3d::Delete<CParticle*>( EngineMgr->GetpDirt() );
	StageMgr->SetbIsGetOutStage(false);
	StageMgr->SetbIsFadeInOut(false);
	CameraMgr->CameraDefault();
}

///////////////////////////////////////////////////////////
// Stage::DustBridge Show
///////////////////////////////////////////////////////////
void CStageDustBridgeShow::Enter(CSection* pSection){
	MusicMgr->PlayMP3FileForBGM("./Sound/DustBridge.mp3");

	UIMgr->ActiveCommander();

	StageMgr->SetbIsFadeInOut(false);
	StageMgr->SetStage(CStageManager::DUSTBRIDGE);

	COrgan* t_pBody = StageMgr->GetStage();

	EngineMgr->SetDirt(t_pBody->GetPriPos()->x - t_pBody->GetWidthHalf() - 100.0f, t_pBody->GetPriPos()->y - t_pBody->GetHeightHalf() - 100.0f, 0.0f,
		t_pBody->GetPriPos()->x + t_pBody->GetWidthHalf() + 100.0f, t_pBody->GetPriPos()->y + t_pBody->GetHeightHalf() + 100.0f, 5.0f, 50);

	for(int i = 0; i < 200; i++){
		EngineMgr->GetpDirt()->update(EngineMgr->GetTimeDelta());
		EngineMgr->GetpDirt()->render();
	}

	EffectMgr->SetBGEffectRange(CBaseObject::STAGEDUSTBRIDGE);
	EffectMgr->SetBGDarkUse(true);

	CameraMgr->CameraInit(0.0f, -140.0f, -950.0f);
}

void CStageDustBridgeShow::Execute(CSection* pSection){
	// 배경 그리기
	ObjectMgr->GetEntity(ID_STAGEDUSTBRIDGE)->Update();

	AIMgr->DustKingUpdate();

	if(AIMgr->GetDustKing()->GetLive() == false && EventMgr->GetEventStage()->_dustKingDie == false){
		EventMgr->GetEventStage()->GetFSM()->ChangeState(EventStageDustKingDie->Instance());
		EventMgr->GetEventStage()->_dustKingDie = true;
		StageMgr->_dustBridgeClear = true;
	}

	// 계산
	ObjectMgr->ComputeGetOutStage(CBaseObject::STAGEDUSTBRIDGE, AIMgr->GetHero()->GetBody());
	CameraMgr->CameraUp(150.0f);

	// 주인공 기관 계산 & 그리기
	AIMgr->HeroUpdate();

	// 수레 그리기
	AIMgr->CartUpdate();

	// 꽃 그리기
	AIMgr->FlowerUpdate();

	// AI 그리기
	AIMgr->AIUpdate();

	EngineMgr->GetpDirt()->update(EngineMgr->GetTimeDelta());
	EngineMgr->GetpDirt()->render(); // 하늘위에서 떨어지는 Dirt Particle 그리기

	EffectMgr->EffectUpdate();

	// UI 그리기
	UIMgr->UIUpdate();

	// 이벤트
	EventMgr->GetEventStage()->Update();

	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f)
		if(StageMgr->GetbIsGetOutStage())
			pSection->GetFSM()->ChangeState(WorldMapShow->Instance());
}

void CStageDustBridgeShow::Exit(CSection* pSection){
	MusicMgr->Close();

	UIMgr->MinimizeCommander();

	d3d::Delete<CParticle*>( EngineMgr->GetpDirt() );
	EffectMgr->SetBGDarkUse(false);
	StageMgr->SetbIsGetOutStage(false);
	StageMgr->SetbIsFadeInOut(false);
	CameraMgr->CameraDefault();
}

///////////////////////////////////////////////////////////
// Stage::GoodHope Show
///////////////////////////////////////////////////////////
void CStageGoodHopeShow::Enter(CSection* pSection){
	MusicMgr->PlayMP3FileForBGM("Sound/GoodHope.mp3");

	StageMgr->SetbIsFadeInOut(false);
	StageMgr->SetStage(CStageManager::GOODHOPE);

	COrgan* t_pBody = StageMgr->GetStage();

	EngineMgr->SetDirt(t_pBody->GetPriPos()->x - t_pBody->GetWidthHalf() - 100.0f, t_pBody->GetPriPos()->y - t_pBody->GetHeightHalf() - 100.0f, 0.0f,
		t_pBody->GetPriPos()->x + t_pBody->GetWidthHalf() + 100.0f, t_pBody->GetPriPos()->y + t_pBody->GetHeightHalf() + 100.0f, 5.0f, 50);

	for(int i = 0; i < 200; i++){
		EngineMgr->GetpDirt()->update(EngineMgr->GetTimeDelta());
		EngineMgr->GetpDirt()->render();
	}

	EffectMgr->SetBGEffectRange(CBaseObject::STAGEGOODHOPE);
	EffectMgr->SetBGDarkUse(true);

	CameraMgr->CameraInit(0.0f, -180.0f, -800.0f);
}

void CStageGoodHopeShow::Execute(CSection* pSection){	
	// 배경 그리기
	ObjectMgr->GetEntity(ID_STAGEGOODHOPE)->Update();

	// 계산
	ObjectMgr->ComputeGetOutStage(CBaseObject::STAGEGOODHOPE, AIMgr->GetHero()->GetBody());
	CameraMgr->CameraUp(-300.0f);

	// 주인공 기관 계산 & 그리기
	AIMgr->HeroUpdate();

	// 수레 그리기
	AIMgr->CartUpdate();

	// 꽃 그리기
	AIMgr->FlowerUpdate();

	// AI 그리기
	AIMgr->AIUpdate();

	EngineMgr->GetpDirt()->update(EngineMgr->GetTimeDelta());
	EngineMgr->GetpDirt()->render(); // 하늘위에서 떨어지는 Dirt Particle 그리기

	EffectMgr->EffectUpdate();

	// UI 그리기
	UIMgr->UIUpdate();

	// 이벤트
	EventMgr->GetEventStage()->Update();

	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f){
		if(StageMgr->GetbIsGetOutStage() && EventMgr->GetEventWorldMap()->_ending == false)
			pSection->GetFSM()->ChangeState(WorldMapShow->Instance());
		else if(EventMgr->GetEventWorldMap()->_ending)
			pSection->GetFSM()->ChangeState(EndingShow->Instance());
	}
}

void CStageGoodHopeShow::Exit(CSection* pSection){
	MusicMgr->Close();

	if(EventMgr->GetEventStage()->_goodHopeIntro == true && EventMgr->GetEventStage()->_goodHope == false)
		EventMgr->GetEventStage()->_goodHopeIntro = false;

	d3d::Delete<CParticle*>( EngineMgr->GetpDirt() );
	EffectMgr->SetBGDarkUse(false);
	StageMgr->SetbIsGetOutStage(false);
	StageMgr->SetbIsFadeInOut(false);
	CameraMgr->CameraDefault();
}

///////////////////////////////////////////////////////////
// 게임 끝 상태
///////////////////////////////////////////////////////////
void CGameEnd::Enter(CSection* pSection){
	
}

void CGameEnd::Execute(CSection* pSection){
	PostQuitMessage(0);
}

void CGameEnd::Exit(CSection* pSection){
	
}

///////////////////////////////////////////////////////////
// Ending
///////////////////////////////////////////////////////////
void CEndingShow::Enter(CSection* pSection){
	MusicMgr->PlayMP3FileForBGM("./Sound/Ending.mp3");

	CameraMgr->SetOrigin(ObjectMgr->GetEntity(CBaseObject::WORLDMAP)->GetBody());
	CameraMgr->SetMode(CCameraManager::EVENT);

	EffectMgr->SetPlaneType(CEffectManager::BLACK);
	EffectMgr->SetPlaneUse(true);

	StageMgr->SetbIsFadeInOut(false);
	StageMgr->SetStage(CStageManager::WORLDMAP);

	// 아군 초기화
	AIMgr->InitOurForce();
}

void CEndingShow::Execute(CSection* pSection){
	ObjectMgr->GetEntity(ID_WORLDMAP)->Update();

	EventMgr->GetEventWorldMap()->Update();

	if(EffectMgr->AlphaPlaneUpdate() >= 1.0f){
		pSection->GetFSM()->ChangeState(GameEnd->Instance());
		MusicMgr->Close();
	}
}

void CEndingShow::Exit(CSection* pSection){
	MusicMgr->Close();
	CameraMgr->SetMode(CCameraManager::RELAX);

	EffectMgr->SetBGDarkUse(false);
}