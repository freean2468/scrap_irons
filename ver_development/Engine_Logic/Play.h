#ifndef _Play_H_
#define _Play_H_

class CPlay : public CBaseSection{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CPlay>* m_pStateMachine;

public:
	CPlay::CPlay(int id):CBaseSection(id){
		// ���±�踦 �����Ѵ�.
		m_pStateMachine = new CStateMachine<CPlay>(this);

		m_pStateMachine->SetCurrentState(NULL);

		m_pStateMachine->SetGlobalState(NULL);
	}
	~CPlay();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CPlay>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}
};

#endif