#include "../BaseHeader.h"

CBaseEffect::CBaseEffect(SMALLSCALEEFFECTTYPE p_Type):COrganEntity(ID_EFFECT){
	_effectType = p_Type;
	_bIsDie = false;
}

CBaseEffect::~CBaseEffect(){
	
}