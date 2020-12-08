////////////////////////////////////////////////////////////////////////////////
// SparksEffect Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _SparksEffect_H_
#define _SparksEffect_H_

#include "./Engine_System/BaseManager.h"

class CSparksEffect : public CBaseEffect{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CSparksEffect>* m_pStateMachine;

	float _scaAceX;
	float _scaAceY;

public:
	CSparksEffect(D3DXVECTOR3* p_pPos);
	~CSparksEffect();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
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