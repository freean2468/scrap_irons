#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CWorldMapUsual::Enter(CWorldMap* pWorldMap){
	
}

void CWorldMapUsual::Execute(CWorldMap* pWorldMap){
	for(int i = 0; i < pWorldMap->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWorldMap->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWorldMap::LIGHT:
				if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.1f){
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.003f;
					if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.1f)
						t_Att->GetMtrlArray()->Get(0,0).Diffuse.a = 0.1f;
				}
				break;
			case CWorldMap::TEXT:
				if(t_Att->GetPriSca()->x > 0.0f && t_Att->GetPriSca()->y > 0.0f){
					t_Att->GetPriSca()->x-=0.01f;
					t_Att->GetPriSca()->y-=0.01f;
				}
				break;
			default:
				break;
		}
	}	

	pWorldMap->RenderOrgan();	
}

void CWorldMapUsual::Exit(CWorldMap* pWorldMap){

}

bool CWorldMapUsual::OnMessage(CWorldMap* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ending:
			agent->GetFSM()->ChangeState(WorldMapEnding->Instance());
			return true;
	}
	return false;
}

///////////////////////////////////////////////////////////
// Ending State
///////////////////////////////////////////////////////////
void CWorldMapEnding::Enter(CWorldMap* pWorldMap){
	
}

void CWorldMapEnding::Execute(CWorldMap* pWorldMap){
	if(pWorldMap->GetBody()->GetMtrlArray()->Get(0, 0).Diffuse.a > 0.0f)
		pWorldMap->GetBody()->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.001f;

	if(pWorldMap->GetBody()->GetPriSca()->x >= 0.5f){
		pWorldMap->GetBody()->GetPriSca()->x -= 0.0025f;
		pWorldMap->GetBody()->GetPriSca()->y -= 0.0025f;
	}

	for(int i = 0; i < pWorldMap->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWorldMap->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWorldMap::LIGHT:
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.a = 0.0f;
				break;
			case CWorldMap::TEXT:
				t_Att->GetPriSca()->x=0.0f;
				t_Att->GetPriSca()->y=0.0f;
				break;
			default:
				break;
		}
	}	

	pWorldMap->RenderOrgan();	
}

void CWorldMapEnding::Exit(CWorldMap* pWorldMap){

}

bool CWorldMapEnding::OnMessage(CWorldMap* agent, const Telegram& msg){
	return false;
}