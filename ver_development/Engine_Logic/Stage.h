#ifndef _Stage_H_
#define _Stage_H_

class CStage : public CBaseSection{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CStage>* m_pStateMachine;

public:
	CStage::CStage(int id):CBaseSection(id){
		// ���±�踦 �����Ѵ�.
		m_pStateMachine = new CStateMachine<CStage>(this);

		m_pStateMachine->SetCurrentState(NULL);

		m_pStateMachine->SetGlobalState(NULL);
	}
	~CStage(){}

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CStage>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}
};

#endif