#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
void CSmallInfoMinimize::Enter(CSmallInfo* pSmallInfo){
	
}

void CSmallInfoMinimize::Execute(CSmallInfo* pSmallInfo){
	
}

void CSmallInfoMinimize::Exit(CSmallInfo* pSmallInfo){

}

bool CSmallInfoMinimize::OnMessage(CSmallInfo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(SmallInfoMinimize->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
void CSmallInfoActive::Enter(CSmallInfo* pSmallInfo){
	
}

void CSmallInfoActive::Execute(CSmallInfo* pSmallInfo){
	CCharacterEntity* t_pEntity = pSmallInfo->GetOrigin();
	CBody* t_pBody = pSmallInfo->GetBody();

	DWORD t_dwTime;

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

	// 부속품 계산
	for(int i = 0; i < pSmallInfo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pSmallInfo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){			
			case CSmallInfo::RED:
				if(t_pEntity->GetAttackTime()->IsElapseTimer() == false){
					t_dwTime = t_pEntity->GetAttackTime()->GetElapseTime();

					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.b = -1.0f;
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.g = -1.0f;
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.r = -0.5f;
					if(t_dwTime == 0){
						t_Att->GetPriSca()->x = 0.0f;
					}
					else{
						t_Att->GetPriSca()->x = (float)((float)t_dwTime * (1.0f/(float)t_pEntity->GetAttackTimeGap()));
					}
				}
				else{
					t_Att->GetPriSca()->x = 1.0f;
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.r = 0.0f;
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.b = 0.0f;
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.g = 0.0f;
				}
				break;
			case CSmallInfo::BLUE:
				if(t_pEntity->GetNowHealthy() == 0)
					t_Att->GetPriSca()->x = 0.0f;
				else{
					t_Att->GetPriSca()->x = (float)((float)t_pEntity->GetNowHealthy()/(float)t_pEntity->GetMaxHealthy());
				}
				break;
			default:
				break;
		}
	}

	pSmallInfo->RenderOrgan();
}

void CSmallInfoActive::Exit(CSmallInfo* pSmallInfo){

}

bool CSmallInfoActive::OnMessage(CSmallInfo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(SmallInfoMinimize->Instance());
			return true;
		default:
			return false;
	}
}