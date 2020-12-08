////////////////////////////////////////////////////////////////////////////////
// BoostEffect Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _BoostEffect_H_
#define _BoostEffect_H_

#include "./Engine_System/BaseManager.h"

class CBoostEffect : public CBaseEffect{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CBoostEffect>* m_pStateMachine;
	CBody* _origin;

public:
	CBoostEffect(CBody* p_pOrgan);
	~CBoostEffect();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CBoostEffect>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CBoostEffect>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	CBody* GetOrigin(){return _origin;}
};

#endif