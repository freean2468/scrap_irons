#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
void CInteractMinimize::Enter(CInteract* pInteract){
	
}

void CInteractMinimize::Execute(CInteract* pInteract){
	// 바디 계산

	// 부속물 계산
	
}

void CInteractMinimize::Exit(CInteract* pInteract){

}

bool CInteractMinimize::OnMessage(CInteract* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Activate:
			agent->GetFSM()->ChangeState(InteractActive->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
void CInteractActive::Enter(CInteract* pInteract){
	
}

void CInteractActive::Execute(CInteract* pInteract){
	// 각종 계산

	// 바디 계산
	CBody* t_pBody = pInteract->GetBody();

	static bool t_bMoveLimit = false;
	static float fDeltaY = 25.0f;

	switch(t_bMoveLimit){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			t_pBody->GetPriSca()->y += 0.01f;
			t_pBody->GetPriSca()->x -= 0.002f;

			fDeltaY += 2.0f;
			if(fDeltaY >= 50.0f){
				t_bMoveLimit = false;
			}
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			t_pBody->GetPriSca()->y -= 0.01f;
			t_pBody->GetPriSca()->x += 0.002f;
			
			fDeltaY -= 2.0f;
			if(fDeltaY <= -50.0f){
				t_bMoveLimit = true;
			}
			break;
	}

	// 부속물 계산
	
	pInteract->RenderOrgan();
}

void CInteractActive::Exit(CInteract* pInteract){

}

bool CInteractActive::OnMessage(CInteract* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(InteractMinimize->Instance());
			return true;
		default:
			return false;
	}
}