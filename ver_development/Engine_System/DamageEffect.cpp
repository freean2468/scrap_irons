#include "../BaseHeader.h"

CDamageEffect::CDamageEffect(D3DXVECTOR3* p_pPos, int p_nDamage):CBaseEffect(DAMAGE){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CDamageEffect>(this);

	LoadEntityData("./script/Effect/DamageEffect.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(DamageEffectUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_body->GetPriPos()->x = p_pPos->x;
	_body->GetPriPos()->y = p_pPos->y;

	_pFont = d3d::IniFont(18, 9, 1000, false, "맑은 고딕");

	_damage = p_nDamage;
}

CDamageEffect::~CDamageEffect(){
	d3d::Delete<CStateMachine<CDamageEffect>*>(m_pStateMachine);
	d3d::Release<ID3DXFont*>(_pFont);
}	