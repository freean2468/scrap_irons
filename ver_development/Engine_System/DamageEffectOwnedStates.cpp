#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CDamageEffectUsual::Enter(CDamageEffect* pDamageEffect){
	_deltaY = 0.1f;
}

void CDamageEffectUsual::Execute(CDamageEffect* pDamageEffect){
	CBody* t_pBody = pDamageEffect->GetBody();

	t_pBody->GetPriPos()->y += _deltaY;

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a > 0.0f)
		t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.02f;

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.0f)
		pDamageEffect->SetIsDie(true);

	_deltaY+=0.005f;

	pDamageEffect->RenderOrgan();

	char line[8];

	itoa(pDamageEffect->GetDamage(), line, 10);

	EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D ������ �ؽ�Ʈ ���

	D3DXVECTOR3 _vPos;			// ��ġ ����
	D3DXMATRIXA16 _pos;			// ��ġ ��ȯ ���
	D3DXMATRIXA16 _rotation;	// ȸ�� ��ȯ ���
	D3DXVECTOR3 _vRotate;		// ȸ�� ����

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, t_pBody->GetPriPos()->x, t_pBody->GetPriPos()->y + 5.0f, t_pBody->GetPriPos()->z);

	D3DXMATRIXA16 rX;
	D3DXMatrixIdentity(&rX);
	D3DXMatrixRotationX(&rX, D3DX_PI);
	_rotation = rX;

	mtMatrix *= _rotation * _pos;

	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

	RECT rect;

	rect.right = (long)20.0f;
	rect.left = (long)-20.0f;
	rect.top = (long)-20.0f;
	rect.bottom = (long)20.0f;

	// Text ���      
	pDamageEffect->GetFont()->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_CENTER | DT_VCENTER , 0xffff5500);      

	EngineMgr->GetpSprite()->End();

	// ���� ��ǥ�� �������� �ǵ�����.
	D3DXMatrixIdentity(&mtMatrix);
	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

	pDamageEffect->InitChainVector();
}

void CDamageEffectUsual::Exit(CDamageEffect* pDamageEffect){

}

bool CDamageEffectUsual::OnMessage(CDamageEffect* agent, const Telegram& msg){
	return false;
}