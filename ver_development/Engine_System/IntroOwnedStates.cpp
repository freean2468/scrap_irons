#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CIntroUsual::Enter(CIntro* pIntro){
	
}

void CIntroUsual::Execute(CIntro* pIntro){
	pIntro->RenderOrgan();
}

void CIntroUsual::Exit(CIntro* pIntro){

}

bool CIntroUsual::OnMessage(CIntro* agent, const Telegram& msg){
	return false;
}