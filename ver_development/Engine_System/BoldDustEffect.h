////////////////////////////////////////////////////////////////////////////////
// BoldDustEffect Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _BoldDustEffect_H_
#define _BoldDustEffect_H_

#include "./Engine_System/BaseManager.h"

class CBoldDustEffect : public CBaseEffect{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CBoldDustEffect>* m_pStateMachine;
	float _aceX;
	float _aceY;

public:
	CBoldDustEffect(D3DXVECTOR3* p_pPos);
	~CBoldDustEffect();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
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