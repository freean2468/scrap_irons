////////////////////////////////////////////////////////////////////////////////
// DiggyEffect Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _DiggyEffect_H_
#define _DiggyEffect_H_

#include "./Engine_System/BaseManager.h"

class CDiggyEffect : public CBaseEffect{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CDiggyEffect>* m_pStateMachine;
	CTimer* _timer;
	COrgan* _organ;

public:
	CDiggyEffect(COrgan* p_pOrgan, float _fTime);
	~CDiggyEffect();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
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