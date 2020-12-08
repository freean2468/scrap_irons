////////////////////////////////////////////////////////////////////////////////
// DustEffect Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _DustEffect_H_
#define _DustEffect_H_

#include "./Engine_System/BaseManager.h"

class CDustEffect : public CBaseEffect{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CDustEffect>* m_pStateMachine;
	float _aceX;
	float _aceY;

public:
	CDustEffect(D3DXVECTOR3* p_pPos);
	~CDustEffect();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
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