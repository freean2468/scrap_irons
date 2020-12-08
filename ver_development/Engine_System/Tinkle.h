////////////////////////////////////////////////////////////////////////////////
// ��(�ε鷹) Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Tinkle_H_
#define _Tinkle_H_

class CTinkle : public CCharacterEntity{
public:
	typedef enum TinkleAttType {EYE = 0, EFFECT} TINKLEATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CTinkle>* m_pStateMachine;

public:
	CTinkle(int id);
	~CTinkle();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CTinkle>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void BoundUpdate(){}
};

#endif