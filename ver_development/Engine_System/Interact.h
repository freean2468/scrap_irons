////////////////////////////////////////////////////////////////////////////////
// ��ȣ�ۿ� ���� ǥ�� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Interact_H_
#define _Interact_H_

class CInteract : public COrganEntity{
public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CInteract>* m_pStateMachine;

public:
	CInteract(int id);
	~CInteract();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CInteract>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
};

#endif