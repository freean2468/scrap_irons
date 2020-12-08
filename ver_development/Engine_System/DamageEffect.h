////////////////////////////////////////////////////////////////////////////////
// DamageEffect 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _DamageEffect_H_
#define _DamageEffect_H_

#include "./Engine_System/BaseManager.h"

class CDamageEffect : public CBaseEffect{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CDamageEffect>* m_pStateMachine;
	int _damage;
	ID3DXFont*	_pFont;							// 폰트 인터페이스 변수

public:
	CDamageEffect(D3DXVECTOR3* p_pPos, int p_nDamage);
	~CDamageEffect();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CDamageEffect>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CDamageEffect>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	int GetDamage(){return _damage;}
	ID3DXFont* GetFont(){return _pFont;}
};

#endif