#include "../BaseHeader.h"

// Belt의 끝에 도달했는지의 여부를 물음
bool CAttachment::bIsBeltEnd = false;

CAttachment::CAttachment(int id, OWNER p_owner, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen, int p_nAttType):COrgan(id){
	SetOwner(p_owner);

	// 방향을 바꾸면 x 축 대칭이 일어난다.
	_vPrimitivePos = p_vPos;
	_vPrimitiveSca = p_vSca;
	_vPrimitiveRot = p_vRot;

	_vPrimitiveCen = p_vCen;

	// 부속품 타입 설정
	AttType = p_nAttType;
}

CAttachment::~CAttachment(){

}

void CAttachment::TransformInStageHome(int p_nAttType, float timeDelta){
	switch(p_nAttType){
		case CStageHome::OUTSIDE:
			if(StageMgr->GetbIsHomeInOut() == true){
				if(_Mtrl.Get(0, GetCol()).Diffuse.a > 0.0f){
					_Mtrl.Get(0, GetCol()).Diffuse.a -= 0.01f;	// 어두워지고
					_Mtrl.Get(0, GetCol()).Diffuse.a -= 0.01f;	// 어두워지고
				}
			}
			else{
				if(_Mtrl.Get(GetRow(), GetCol()).Diffuse.a < 1.0f){
					_Mtrl.Get(0, GetCol()).Diffuse.a += 0.01f;	// 밝아지고
					_Mtrl.Get(0, GetCol()).Diffuse.a += 0.01f;	// 밝아지고
				}
			}
			break;
		default:
			break;
	}
}

void CAttachment::TransformInStageFurnace(int p_nAttType, float timeDelta){
	switch(p_nAttType){
		case CStageFurnace::DOOR:
			switch(_angleState){
				case true:
					// Max라면
					_vPrimitiveRot.z += 0.001f;
					if(_vPrimitiveRot.z >= D3DX_PI/120)
						_angleState = false;
					break;
					// case true: End
				case false:
					// Min라면
					_vPrimitiveRot.z -= 0.0015f;
					if(_vPrimitiveRot.z <= -D3DX_PI/80)
						_angleState = true;
					break;
			}
			break;
		default:
			break;
	}
}

void CAttachment::TransformInMainMenu(int p_nAttType, float timeDelta){
	static float fDeltaX = 0.0f;
	static float fDeltaXForIron = 0.0f;

	switch(p_nAttType){
		case CMainMenu::START:
		case CMainMenu::INTRO:
		case CMainMenu::EXIT:
			if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f){
				if(fDeltaXForIron > -1200.0f){
					fDeltaXForIron -= 6.0f;
					_vPrimitivePos.x += 6.0f;						
					_vPrimitiveRot.y += 0.02f;
				}
			}
			
			if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f){
				if(fDeltaXForIron < 1200.0f){
					fDeltaXForIron += 6.0f;
					_vPrimitivePos.x -= 6.0f;
					_vPrimitiveRot.y -= 0.02f;
				}
			}
			break;
			// case CMainMenu::BELT_START~EXIT: End
		case CMainMenu::LEFT:
			if(fDeltaXForIron <= -1200.0f){					
				if(_vPrimitiveRot.z <= D3DX_PI * 0.5f)
					_vPrimitiveRot.z += 0.04f;
			}
			else{
				if(_vPrimitiveRot.z >= 0.0f)
					_vPrimitiveRot.z -= 0.04f;
			}
			break;
		case CMainMenu::RIGHT:
			if(fDeltaXForIron >= 1200.0f){					
				if(_vPrimitiveRot.z >= -D3DX_PI * 0.5f)
					_vPrimitiveRot.z -= 0.04f;
			}
			else{
				if(_vPrimitiveRot.z <= 0.0f)
					_vPrimitiveRot.z += 0.04f;
			}
			break;
		case CMainMenu::ENTER:
			if(ObjectMgr->ComputeBoundMenu() != -1){
				GetMtrlArray()->Get(0, 0).Diffuse.a = 1.0f;
			}
			else
				GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
			break;
		case CMainMenu::TITLE:
			switch(_moveState){
				case true:
					// Max라면
					_vPrimitivePos.x += 0.05f;
					fDeltaX += 0.05f;
					if(fDeltaX >= 7.0f)
						_moveState = false;
					break;
					// case true: End
				case false:
					// Min라면
					_vPrimitivePos.x -= 0.05f;
					fDeltaX -= 0.05f;
					if(fDeltaX <= -7.0f)
						_moveState = true;
					break;
					// case false: End
			}
			// switch(_moveState) End
			switch(_angleState){
				case true:
					// Max라면
					_vPrimitiveRot.z += 0.0005f;
					if(_vPrimitiveRot.z >= D3DX_PI/40)
						_angleState = false;
					break;
					// case true: End
				case false:
					// Min라면
					_vPrimitiveRot.z -= 0.0005f;
					if(_vPrimitiveRot.z <= -D3DX_PI/40)
						_angleState = true;
					break;
					// case false: End
			}
			// switch(_angleState) End
			break;
			// case CMainMenu::TITLE: End
		default:
			break;
	}
	// switch p_nAttType End
}