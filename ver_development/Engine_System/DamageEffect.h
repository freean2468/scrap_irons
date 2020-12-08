////////////////////////////////////////////////////////////////////////////////
// DamageEffect Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _DamageEffect_H_
#define _DamageEffect_H_

#include "./Engine_System/BaseManager.h"

class CDamageEffect : public CBaseEffect{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CDamageEffect>* m_pStateMachine;
	int _damage;
	ID3DXFont*	_pFont;							// ��Ʈ �������̽� ����

public:
	CDamageEffect(D3DXVECTOR3* p_pPos, int p_nDamage);
	~CDamageEffect();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CDamageEffect>* GetFSM()const{return m_pStateMachine;}
	void SetFSM(CStateMachine<CDamageEffect>* p_pMachine){m_pStateMachine = p_pMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	int GetDamage(){return _damage;}
	ID3DXFont* GetFont(){return _pFont;}
};

#endif