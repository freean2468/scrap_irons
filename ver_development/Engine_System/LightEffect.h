////////////////////////////////////////////////////////////////////////////////
// LightEffect Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _LightEffect_H_
#define _LightEffect_H_

#include "./Engine_System/BaseManager.h"

class COrgan;

class CLightEffect : public CBaseEffect{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CLightEffect>* m_pStateMachine;
	COrgan* _organ;

public:
	CLightEffect(COrgan* t_pOrgan);
	~CLightEffect();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
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