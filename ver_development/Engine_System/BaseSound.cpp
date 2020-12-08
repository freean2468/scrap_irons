#include "../BaseHeader.h"

CBaseSound::CBaseSound(){
	_sound = 0;
	_effect = 0;
}

CBaseSound::~CBaseSound(){

}

HRESULT CBaseSound::InitSound(HWND hWnd){
	if(FAILED(_sound->Create(&_effect, "./Sound/Effect.wav", 0, GUID_NULL))) return E_FAIL;

	return S_OK;
}