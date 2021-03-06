////////////////////////////////////////////////////////////////////////////////
// DustEffect 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _DustEffect_H_
#define _DustEffect_H_

#include "./Engine_System/BaseManager.h"

class CDustEffect : public CBaseEffect{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CDustEffect>* m_pStateMachine;
	float _aceX;
	float _aceY;

public:
	CDustEffect(D3DXVECTOR3* p_pPos);
	~CDustEffect();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CDustEffect>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CDustEffect>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	float GetAceX(){return _aceX;}
	float GetAceY(){return _aceY;}
};

#endif