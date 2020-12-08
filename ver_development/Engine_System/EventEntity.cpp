#include "../BaseHeader.h"

CEventEntity::CEventEntity(int id):COrganEntity(id){
	
}

CEventEntity::~CEventEntity(){

}

void CEventEntity::CalculationOrgan(float timeDelta){
	if(GetBody()){
		BodySetting();
		GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
		
		InitChainVector();

		BodySetting();
		if(GetMessage()){
			if(GetMessage()->GetUse()){
				GetMessage()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
				GetMessage()->RenderLine();
			}
		}

		InitChainVector();
	}
}