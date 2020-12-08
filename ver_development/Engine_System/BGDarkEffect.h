////////////////////////////////////////////////////////////////////////////////
// BGDarkEffect Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _BGDarkEffect_H_
#define _BGDarkEffect_H_

class CBGDarkEffect : public CAttachment{
public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CBGDarkEffect>* m_pStateMachine;

public:
	CBGDarkEffect();
	~CBGDarkEffect();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CBGDarkEffect>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
};

#endif