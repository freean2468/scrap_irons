////////////////////////////////////////////////////////////////////////////////
// ��ȣ�ۿ� ���� ǥ�� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Commander_H_
#define _Commander_H_

class CCommander : public COrganEntity{
public:
	typedef enum CommanderAttType {GAGEBODY, GAGEBAR} COMMANDERATTTYPE;

public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CCommander>* m_pStateMachine;

public:
	CCommander(int id);
	~CCommander();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CCommander>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
};

#endif