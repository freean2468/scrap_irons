#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// EventWorldMapStageClear
///////////////////////////////////////////////////////////
void CEventWorldMapStageClear::Enter(CEventWorldMap* p_pEvent){
	
}

void CEventWorldMapStageClear::Execute(CEventWorldMap* p_pEvent){
	if(StageMgr->_scrapMountainClear == true && p_pEvent->GetAttachmentFromType(CEventWorldMap::SCRAPMOUNTAIN)->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.0f){

	}

	p_pEvent->RenderOrgan();
}

void CEventWorldMapStageClear::Exit(CEventWorldMap* p_pEvent){
	
}