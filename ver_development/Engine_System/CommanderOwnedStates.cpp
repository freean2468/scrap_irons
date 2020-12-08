#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
void CCommanderMinimize::Enter(CCommander* pCommander){
	
}

void CCommanderMinimize::Execute(CCommander* pCommander){
	// 바디 계산

	// 부속물 계산
	
}

void CCommanderMinimize::Exit(CCommander* pCommander){

}

bool CCommanderMinimize::OnMessage(CCommander* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Activate:
			agent->GetFSM()->ChangeState(CommanderActive->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
void CCommanderActive::Enter(CCommander* pCommander){
	
}

void CCommanderActive::Execute(CCommander* pCommander){
	CBody* t_pBody = pCommander->GetBody();
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);
	
	switch(StageMgr->GetStageType()){
		case CStageManager::DUSTBRIDGE:
			t_pBody->GetPriPos()->x = t_vPos.x + (SYSTEMWIDTH * 0.5f) - 90.0f;
			t_pBody->SetRow(CBaseObject::LEFT);
			break;
		default:
			t_pBody->GetPriPos()->x = t_vPos.x - (SYSTEMWIDTH * 0.5f) + 90.0f;
			t_pBody->SetRow(CBaseObject::RIGHT);
			break;
	}

	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.1f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.1f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	t_pBody->GetPriPos()->y = t_vPos.y + (SYSTEMHEIGHT * 0.5f) - 180.0f;
	t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;

	DWORD t_dwTime;

	static int t_nCount = 0;

	// 부속품 계산
	for(int i = 0; i < pCommander->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pCommander->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CCommander::GAGEBAR:
				if(AIMgr->GetCommandTime()->IsElapseTimer() == false){
					t_dwTime = AIMgr->GetCommandTime()->GetElapseTime();

					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.b = -1.0f;
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.g = -1.0f;
					if(t_dwTime == 0){
						t_Att->GetPriSca()->x = 0.0f;
					}
					else{
						t_Att->GetPriSca()->x = (float)((float)t_dwTime * (1.0f/(float)AIMgr->GetCommandTimeGap()));
					}
					t_nCount = 0;
				}
				else{
					t_Att->GetPriSca()->x = 1.0f;
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.b = 0.0f;
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.g = 0.0f;

					if(t_nCount <= 0){
						CDListIterator<CCharacterEntity*> itr;
		
						// 초기화
						itr = AIMgr->GetOurForceList()->GetIterator();
						
						for(itr.Start(); itr.Valid(); itr.Forth()){
							AIMgr->SetCommandType(CAIManager::NONE);
							Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pCommander->ID(), itr.Item()->ID(), Msg_Usual, NO_ADDITIONAL_INFO);
						}
						t_nCount++;
					}
				}
				break;
			case CCommander::GAGEBODY:
				break;
			default:
				break;
		}
	}

	pCommander->RenderOrgan();
}

void CCommanderActive::Exit(CCommander* pCommander){

}

bool CCommanderActive::OnMessage(CCommander* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(CommanderMinimize->Instance());
			return true;
		default:
			return false;
	}
}