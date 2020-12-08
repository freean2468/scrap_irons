#include "../BaseHeader.h"

CInformation::CInformation(){	
	FrameCntForNon    = 0;
	TimeElapsedForNon = 0;
	FrameCntForAdjusted = 0;
	TimeElapsedForAdjusted = 0;

	FPS         = 0;
	FPSAdjusted = 0;
	_rect.left = 0;
	_rect.top = 0;
	_rect.right = SYSTEMWIDTH;
	_rect.bottom = SYSTEMHEIGHT;

	_crdAdjusted = 0;
	_crdAbsoluted = 0;
	_nowPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_disPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_firstPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	_space = CInformation::DOWN;
}

CInformation::~CInformation(){

}

void CInformation::CalcInformation(float timeDelta){
	// FPS계산
	FPSCalculation(timeDelta);

	// 마우스 좌표 갱신
	sprintf(_crdString, "AdX : %.2f, AdY : %.2f AbX : %.2f, AbY : %.2f", _crdAdjusted.GetX(), _crdAdjusted.GetY(),_crdAbsoluted.GetX(), _crdAbsoluted.GetY());
	_crdString[59] = '\0'; // mark end of string

	// 카메라 계산
	sprintf(_cameraString, "CX : %.2f, CY : %.2f, CZ : %.2f", _nowPos.x, _nowPos.y, _nowPos.z);
	_cameraString[59] = '\0'; // mark end of string

	// 왼쪽 Shift키 입력
	if(GetAsyncKeyState(VK_LSHIFT) & 0x8000f){
		switch(_space){
			case DOWN:
				_space = CInformation::DOWN;
				_lastPos = *(this->GetCameraPos());
				break;
			case UP:
				_space = CInformation::UP;
				_firstPos = *(this->GetCameraPos());
				break;
		}
		if(_firstPos != 0 && _lastPos != 0){
			_disPos = _firstPos - _lastPos;
			sprintf(_distanceString, "DX : %.2f, DY : %.2f", _disPos.x, _disPos.y);
			_crdString[59] = '\0'; // mark end of string
			_firstPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			_lastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}
}

void CInformation::FPSCalculation(float timeDelta){
	FrameCntForNon++;
	TimeElapsedForNon += timeDelta;

	if(TimeElapsedForNon >= 1.0f){
		FPS = (float)FrameCntForNon / TimeElapsedForNon;

		sprintf(_FPSString, "FPS : %.2f", FPS);
		_FPSString[29] = '\0'; // mark end of string

		TimeElapsedForNon = 0.0f;
		FrameCntForNon = 0;
	}
}

void CInformation::FPSAdjustedCalculation(float timeDelta){
	FrameCntForAdjusted++;
	TimeElapsedForAdjusted += timeDelta;

	if(TimeElapsedForAdjusted >= 1.0f){
		FPSAdjusted = (float)FrameCntForAdjusted / TimeElapsedForAdjusted;

		sprintf(_FPSAdjustedString, "FPSAdjusted : %.2f", FPSAdjusted);
		_FPSAdjustedString[29] = '\0'; // mark end of string

		TimeElapsedForAdjusted = 0.0f;
		FrameCntForAdjusted = 0;
	}
}

void CInformation::DrawInformation(ID3DXFont* font, ID3DXSprite* sprite){
	sprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE );

	RECT rect;

	rect = _rect;
      
	// FPS 출력
	font->DrawText(sprite, _FPSString, -1, &rect, DT_TOP | DT_LEFT | DT_WORDBREAK, 0xffff0000);      
	font->DrawText(sprite, _FPSAdjustedString, -1, &rect, DT_BOTTOM | DT_LEFT | DT_WORDBREAK, 0xffff0000);

	// 마우스 좌표 출력
	font->DrawText(sprite, _crdString, -1, &rect, DT_TOP | DT_RIGHT | DT_WORDBREAK, 0xffff0000);

	// 카메라 좌표 출력
	font->DrawText(sprite, _cameraString, -1, &rect, DT_BOTTOM | DT_RIGHT | DT_WORDBREAK, 0xffff0000);

	// 카메라상의 좌표 간격 출력
//	font->DrawText(sprite, _distanceString, -1, &rect, DT_BOTTOM | DT_LEFT, 0xffff0000);

	sprite->End();
}