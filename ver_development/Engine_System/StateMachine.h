////////////////////////////////////////////////////
// ���� ���� ��� Ŭ����
// ���µ��� ����
////////////////////////////////////////////////////
#ifndef _StateMachine_H_
#define _StateMachine_H_

template <class entity_type>
class CStateMachine{
private:
	// �� �ν��Ͻ��� �����ϴ� ������Ʈ�� ����Ű�� ������
	entity_type* m_pOwner;

	CState<entity_type>* m_pCurrentState;

	// ������Ʈ�� ���� �־��� ������ ������ ���
	CState<entity_type>* m_pPreviousState;

	// �� ���� ���� FSM�� ���ŵ� ������ ȣ��ȴ�.
	CState<entity_type>* m_pGlobalState;
public:
	CStateMachine(entity_type* owner):m_pOwner(owner),
									m_pCurrentState(NULL),
									m_pPreviousState(NULL),
									m_pGlobalState(NULL)
	{}

	// FSM�� �ʱ�ȭ�ϱ� ���� ���� �޼ҵ���� ����Ѵ�.
	void SetCurrentState(CState<entity_type>* s){m_pCurrentState = s;}
	void SetGlobalState(CState<entity_type>* s){m_pGlobalState = s;}
	void SetPreviousState(CState<entity_type>* s){m_pPreviousState = s;}

	// FSM�� �����ϱ� ���� �̰��� ȣ���Ѵ�.
	void Update()const{
		// ���� ���°� �����ϸ�, �װ��� execute �޼ҵ带 ȣ���Ѵ�.
		if(m_pGlobalState) m_pGlobalState->Execute(m_pOwner);

		// ���� ���¿� ���ؼ� �����ϰ�
		if(m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}

	// ���ο� ���·� ��ȭ��Ų��.
	void ChangeState(CState<entity_type>* pNewState){
		assert(pNewState && "<CStateMachine::ChangeState>: trying to change to a null state");

		// ���� ������ ����� �����Ѵ�.
		m_pPreviousState = m_pCurrentState;

		// ���� ������ exit �޼ҵ带 ȣ���Ѵ�.
		m_pCurrentState->Exit(m_pOwner);

		// ���¸� ���ο� ���·� ��ȭ��Ų��.
		m_pCurrentState = pNewState;

		// ���ο� ������ enter �޼ҵ带 ȣ���Ѵ�.
		m_pCurrentState->Enter(m_pOwner);
	}

	// ���¸� ���� ���·� �ٽ� ��ȭ��Ų��.
	void RevertToPreviousState(){
		ChangeState(m_pPreviousState);
	}

	bool HandleMessage(const Telegram& msg)const{
		// �켱 ���� ���°� ��ȿ�ϰ� �޽����� ó���� �� �ִ����� �˾ƺ���.
		if(m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg)){
			return true;
		}

		// ó���� �� ���� ���� ���°� ��ġ�Ǿ� �ִٸ� �޽����� ���� ���·� ������.
		if(m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg)){
			return false;
		}

		return false;
	}

	// ������(accessor)
	CState<entity_type>* CurrentState() const{return m_pCurrentState;}
	CState<entity_type>* GlobalState() const{return m_pGlobalState;}
	CState<entity_type>* PreviousState() const{return m_pPreviousState;}

	// ���� ���� ������ ������ �Ű������� �Ѱܹ��� Ŭ������ ���İ� ���ٸ�
	// ������ ��ȯ
	bool isInState(const CState<entity_type>& st)const;
};

#endif