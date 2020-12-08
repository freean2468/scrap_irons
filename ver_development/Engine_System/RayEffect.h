////////////////////////////////////////////////////////////////////////////////
// RayEffect Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _RayEffect_H_
#define _RayEffect_H_

#include "./Engine_System/BaseManager.h"

class CRayEffect : public CBaseEffect{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CRayEffect>* m_pStateMachine;

public:
	CRayEffect(D3DXVECTOR3* p_pPos, float p_fDistance);
	~CRayEffect();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CRayEffect>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CRayEffect>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
};

#endif