#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// EventWorldMapStageClear
///////////////////////////////////////////////////////////
void CEventWorldMapStageClear::Enter(CEventWorldMap* p_pEvent){
	
}

void CEventWorldMapStageClear::Execute(CEventWorldMap* p_pEvent){
	if(StageMgr->_homeClear == true){
		if(p_pEvent->GetAttachmentFromType(CEventWorldMap::SCRAPMOUNTAIN)->GetMtrlArray()->Get(0,0).Diffuse.a > 0.0f){
			EventMgr->SetEventing(true);
			CameraMgr->SetMode(CCameraManager::EVENT);
			CameraMgr->SetDestinationX(p_pEvent->GetAttachmentFromType(CEventWorldMap::SCRAPMOUNTAIN)->GetPriPos()->x);
			CameraMgr->SetDestinationY(p_pEvent->GetAttachmentFromType(CEventWorldMap::SCRAPMOUNTAIN)->GetPriPos()->y);
			p_pEvent->GetAttachmentFromType(CEventWorldMap::SCRAPMOUNTAIN)->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.005f;
			p_pEvent->GetAttachmentFromType(CEventWorldMap::SCRAPMOUNTAIN)->GetPriPos()->z -= 4.0f;
		}
		else{
			EventMgr->SetEventing(false);
			CameraMgr->SetMode(CCameraManager::MAP);
		}
	}

	if(StageMgr->_scrapMountainClear == true){
		if(p_pEvent->GetAttachmentFromType(CEventWorldMap::FURNACE)->GetMtrlArray()->Get(0,0).Diffuse.a > 0.0f){
			EventMgr->SetEventing(true);
			CameraMgr->SetMode(CCameraManager::EVENT);
			CameraMgr->SetDestinationX(p_pEvent->GetAttachmentFromType(CEventWorldMap::FURNACE)->GetPriPos()->x);
			CameraMgr->SetDestinationY(p_pEvent->GetAttachmentFromType(CEventWorldMap::FURNACE)->GetPriPos()->y);
			p_pEvent->GetAttachmentFromType(CEventWorldMap::FURNACE)->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.005f;
			p_pEvent->GetAttachmentFromType(CEventWorldMap::FURNACE)->GetPriPos()->z -= 4.0f;
		}
		else{
			EventMgr->SetEventing(false);
			CameraMgr->SetMode(CCameraManager::MAP);
		}
	}

	if(StageMgr->_furnaceClear == true){
		if(p_pEvent->GetAttachmentFromType(CEventWorldMap::CHIMNEY)->GetMtrlArray()->Get(0,0).Diffuse.a > 0.0f){
			EventMgr->SetEventing(true);
			CameraMgr->SetMode(CCameraManager::EVENT);
			CameraMgr->SetDestinationX(p_pEvent->GetAttachmentFromType(CEventWorldMap::CHIMNEY)->GetPriPos()->x);
			CameraMgr->SetDestinationY(p_pEvent->GetAttachmentFromType(CEventWorldMap::CHIMNEY)->GetPriPos()->y);
			p_pEvent->GetAttachmentFromType(CEventWorldMap::CHIMNEY)->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.005f;
			p_pEvent->GetAttachmentFromType(CEventWorldMap::CHIMNEY)->GetPriPos()->z -= 4.0f;
		}
		else{
			EventMgr->SetEventing(false);
			CameraMgr->SetMode(CCameraManager::MAP);
		}
	}

	if(StageMgr->_chimneyClear == true){
		if(p_pEvent->GetAttachmentFromType(CEventWorldMap::DUSTBRIDGE)->GetMtrlArray()->Get(0,0).Diffuse.a > 0.0f){
			EventMgr->SetEventing(true);
			CameraMgr->SetMode(CCameraManager::EVENT);
			CameraMgr->SetDestinationX(p_pEvent->GetAttachmentFromType(CEventWorldMap::DUSTBRIDGE)->GetPriPos()->x);
			CameraMgr->SetDestinationY(p_pEvent->GetAttachmentFromType(CEventWorldMap::DUSTBRIDGE)->GetPriPos()->y);
			p_pEvent->GetAttachmentFromType(CEventWorldMap::DUSTBRIDGE)->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.005f;
			p_pEvent->GetAttachmentFromType(CEventWorldMap::DUSTBRIDGE)->GetPriPos()->z -= 4.0f;
		}
		else{
			EventMgr->SetEventing(false);
			CameraMgr->SetMode(CCameraManager::MAP);
		}
	}

	if(StageMgr->_dustBridgeClear == true){
		if(p_pEvent->GetAttachmentFromType(CEventWorldMap::GOODHOPE)->GetMtrlArray()->Get(0,0).Diffuse.a > 0.0f){
			EventMgr->SetEventing(true);
			CameraMgr->SetMode(CCameraManager::EVENT);
			CameraMgr->SetDestinationX(p_pEvent->GetAttachmentFromType(CEventWorldMap::GOODHOPE)->GetPriPos()->x);
			CameraMgr->SetDestinationY(p_pEvent->GetAttachmentFromType(CEventWorldMap::GOODHOPE)->GetPriPos()->y);
			p_pEvent->GetAttachmentFromType(CEventWorldMap::GOODHOPE)->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.005f;
			p_pEvent->GetAttachmentFromType(CEventWorldMap::GOODHOPE)->GetPriPos()->z -= 4.0f;
		}
		else{
			EventMgr->SetEventing(false);
			CameraMgr->SetMode(CCameraManager::MAP);
		}
	}

	p_pEvent->RenderOrgan();
}

void CEventWorldMapStageClear::Exit(CEventWorldMap* p_pEvent){
	
}

///////////////////////////////////////////////////////////
// EventWorldMapEnding
///////////////////////////////////////////////////////////
void CEventWorldMapEnding::Enter(CEventWorldMap* p_pEvent){
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, p_pEvent->ID(), ID_WORLDMAP, Msg_Ending, NO_ADDITIONAL_INFO);

	EventMgr->ReadText("./script/Event/Ending.txt");
}

void CEventWorldMapEnding::Execute(CEventWorldMap* p_pEvent){
	if(p_pEvent->GetAttachmentFromType(CEventWorldMap::ENDING)->GetMtrlArray()->Get(0,0).Diffuse.a <= 1.0f){
		p_pEvent->GetAttachmentFromType(CEventWorldMap::ENDING)->GetMtrlArray()->Get(0,0).Diffuse.a += 0.001f;
	}

	if(p_pEvent->GetAttachmentFromType(CEventWorldMap::ENDING)->GetPriSca()->x > 0.5f){
		p_pEvent->GetAttachmentFromType(CEventWorldMap::ENDING)->GetPriSca()->x -= 0.005f;
		p_pEvent->GetAttachmentFromType(CEventWorldMap::ENDING)->GetPriSca()->y -= 0.005f;
	}

	if(EventMgr->NextText()){
		EffectMgr->SetPlaneUse(true);
		EffectMgr->SetPlaneType(CEffectManager::WHITE);
		StageMgr->SetbIsFadeInOut(true);
	}

	p_pEvent->RenderOrgan();
}

void CEventWorldMapEnding::Exit(CEventWorldMap* p_pEvent){
	
}

bool CEventWorldMapEnding::OnMessage(CEventWorldMap* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Senario:
			agent->GetMessage()->SetUse(true);
			agent->GetMessage()->SetLine((char*)msg.ExtraInfo);
			return true;
		case Msg_SenarioEnd:
			agent->GetMessage()->SetUse(false);
			agent->GetMessage()->SetLine(NULL);
			return true;
		default:
			return false;
	}
}