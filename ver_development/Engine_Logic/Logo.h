#ifndef _Logo_H_
#define _Logo_H_

template <class entity_type> class CState;

class CLogo : public CBaseSection{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CLogo>* m_pStateMachine;

public:
	CLogo::CLogo(int id):CBaseSection(id){
		// ���±�踦 �����Ѵ�.
		m_pStateMachine = new CStateMachine<CLogo>(this);

		m_pStateMachine->SetCurrentState(LogoShow->Instance());

		m_pStateMachine->SetGlobalState(NULL);
	}
	~CLogo(){}

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CLogo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}
};

#endif