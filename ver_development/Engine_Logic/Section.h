////////////////////////////////////////////////////
// ID�� ���� Entity�� ��� ���� Section �κ� Ŭ����
////////////////////////////////////////////////////
#ifndef _Section_H_
#define _Section_H_

class CSection : public CBaseGameEntity{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CSection>* m_pStateMachine;

	// Ÿ�̸�
	CTimer* _timer;

public:
	CSection::CSection(int id):CBaseGameEntity(id), _timer(NULL){
		// ���±�踦 �����Ѵ�.
		m_pStateMachine = new CStateMachine<CSection>(this);

		// ó�� ���¸� �ʱ�ȭ
		m_pStateMachine->SetCurrentState(LogoShow->Instance());

		m_pStateMachine->CurrentState()->Enter(this);

		m_pStateMachine->SetGlobalState(NULL);
	}
	~CSection(){
		d3d::Delete< CStateMachine<CSection>* >(m_pStateMachine);
		d3d::Delete<CTimer*>(_timer);
	}

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CSection>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	void SetTimer(DWORD dwDelayTime){_timer = new CTimer(dwDelayTime);}

	CTimer* GetTimer(){return _timer;}
};

#endif