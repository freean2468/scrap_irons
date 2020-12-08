////////////////////////////////////////////////////////////////////////////////
// LightEffect 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _LightEffect_H_
#define _LightEffect_H_

#include "./Engine_System/BaseManager.h"

class COrgan;

class CLightEffect : public CBaseEffect{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CLightEffect>* m_pStateMachine;
	COrgan* _organ;

public:
	CLightEffect(COrgan* t_pOrgan);
	~CLightEffect();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CLightEffect>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CLightEffect>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	COrgan* GetOrgan(){return _organ;}
	D3DXVECTOR3* GetOrigin(){return _organ->GetPriPos();}
};

#endif