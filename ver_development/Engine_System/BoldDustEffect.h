////////////////////////////////////////////////////////////////////////////////
// BoldDustEffect 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _BoldDustEffect_H_
#define _BoldDustEffect_H_

#include "./Engine_System/BaseManager.h"

class CBoldDustEffect : public CBaseEffect{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CBoldDustEffect>* m_pStateMachine;
	float _aceX;
	float _aceY;

public:
	CBoldDustEffect(D3DXVECTOR3* p_pPos);
	~CBoldDustEffect();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CBoldDustEffect>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CBoldDustEffect>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	float GetAceX(){return _aceX;}
	float GetAceY(){return _aceY;}
};

#endif