////////////////////////////////////////////////////////////////////////////////
// DiggyEffect 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _DiggyEffect_H_
#define _DiggyEffect_H_

#include "./Engine_System/BaseManager.h"

class CDiggyEffect : public CBaseEffect{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CDiggyEffect>* m_pStateMachine;
	CTimer* _timer;
	COrgan* _organ;

public:
	CDiggyEffect(COrgan* p_pOrgan, float _fTime);
	~CDiggyEffect();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CDiggyEffect>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CDiggyEffect>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
	CTimer* GetTimer(){return _timer;}
	D3DXVECTOR3* GetOrigin(){return _organ->GetPriPos();}
};

#endif