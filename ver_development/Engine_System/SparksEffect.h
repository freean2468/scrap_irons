////////////////////////////////////////////////////////////////////////////////
// SparksEffect 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _SparksEffect_H_
#define _SparksEffect_H_

#include "./Engine_System/BaseManager.h"

class CSparksEffect : public CBaseEffect{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CSparksEffect>* m_pStateMachine;

	float _scaAceX;
	float _scaAceY;

public:
	CSparksEffect(D3DXVECTOR3* p_pPos);
	~CSparksEffect();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CSparksEffect>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CSparksEffect>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	float GetScaAceX(){return _scaAceX;}
	float GetScaAceY(){return _scaAceY;}
};

#endif