#include "../BaseHeader.h"

CBackFog::CBackFog(int id):CBaseObject(id){

}

CBackFog::~CBackFog(){

}

void CBackFog::preRender(){
	CBaseObject::preRender();

	_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}

void CBackFog::postRender(){
	CBaseObject::postRender();

	_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}