#include "../BaseHeader.h"

// Belt�� ���� �����ߴ����� ���θ� ����
bool CAttachment::bIsBeltEnd = false;

CAttachment::CAttachment(int id, OWNER p_owner, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen, int p_nAttType):COrgan(id){
	SetOwner(p_owner);

	// ������ �ٲٸ� x �� ��Ī�� �Ͼ��.
	_vPrimitivePos = p_vPos;
	_vPrimitiveSca = p_vSca;
	_vPrimitiveRot = p_vRot;

	_vPrimitiveCen = p_vCen;

	// �μ�ǰ Ÿ�� ����
	AttType = p_nAttType;
}

CAttachment::~CAttachment(){

}

void CAttachment::TransformInStageHome(int p_nAttType, float timeDelta){
	switch(p_nAttType){
		case CStageHome::OUTSIDE:
			if(StageMgr->GetbIsHomeInOut() == true){
				if(_Mtrl.Get(0, GetCol()).Diffuse.a > 0.0f){
					_Mtrl.Get(0, GetCol()).Diffuse.a -= 0.01f;	// ��ο�����
					_Mtrl.Get(0, GetCol()).Diffuse.a -= 0.01f;	// ��ο�����
				}
			}
			else{
				if(_Mtrl.Get(GetRow(), GetCol()).Diffuse.a < 1.0f){
					_Mtrl.Get(0, GetCol()).Diffuse.a += 0.01f;	// �������
					_Mtrl.Get(0, GetCol()).Diffuse.a += 0.01f;	// �������
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
					// Max���
					_vPrimitiveRot.z += 0.001f;
					if(_vPrimitiveRot.z >= D3DX_PI/120)
						_angleState = false;
					break;
					// case true: End
				case false:
					// Min���
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
					// Max���
					_vPrimitivePos.x += 0.05f;
					fDeltaX += 0.05f;
					if(fDeltaX >= 7.0f)
						_moveState = false;
					break;
					// case true: End
				case false:
					// Min���
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
					// Max���
					_vPrimitiveRot.z += 0.0005f;
					if(_vPrimitiveRot.z >= D3DX_PI/40)
						_angleState = false;
					break;
					// case true: End
				case false:
					// Min���
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