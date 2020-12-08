////////////////////////////////////////////////////////////////////////////////
// KiritKirit Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Kirit_H_
#define _Kirit_H_

class CKirit : public CCharacterEntity{
public:
	typedef enum KiritAttType {EFFECTONE, EFFECTTWO, EFFECTTHREE} KIRITATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CKirit>* m_pStateMachine;

public:
	CKirit(int id);
	~CKirit();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CKirit>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	virtual void BoundUpdate();
};

#endif