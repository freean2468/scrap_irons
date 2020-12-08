////////////////////////////////////////////////////
// 유한 상태 기계 클래스
// 상태들을 관리
////////////////////////////////////////////////////
#ifndef _StateMachine_H_
#define _StateMachine_H_

template <class entity_type>
class CStateMachine{
private:
	// 이 인스턴스를 소유하는 에이전트를 가리키는 포인터
	entity_type* m_pOwner;

	CState<entity_type>* m_pCurrentState;

	// 에이전트가 속해 있었던 마지막 상태의 기록
	CState<entity_type>* m_pPreviousState;

	// 이 상태 논리는 FSM이 갱신될 때마다 호출된다.
	CState<entity_type>* m_pGlobalState;
public:
	CStateMachine(entity_type* owner):m_pOwner(owner),
									m_pCurrentState(NULL),
									m_pPreviousState(NULL),
									m_pGlobalState(NULL)
	{}

	// FSM을 초기화하기 위해 다음 메소드들을 사용한다.
	void SetCurrentState(CState<entity_type>* s){m_pCurrentState = s;}
	void SetGlobalState(CState<entity_type>* s){m_pGlobalState = s;}
	void SetPreviousState(CState<entity_type>* s){m_pPreviousState = s;}

	// FSM을 갱신하기 위해 이것을 호출한다.
	void Update()const{
		// 전역 상태가 존재하면, 그것의 execute 메소드를 호출한다.
		if(m_pGlobalState) m_pGlobalState->Execute(m_pOwner);

		// 현재 상태에 대해서 동일하게
		if(m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}

	// 새로운 상태로 변화시킨다.
	void ChangeState(CState<entity_type>* pNewState){
		assert(pNewState && "<CStateMachine::ChangeState>: trying to change to a null state");

		// 이전 상태의 기록을 유지한다.
		m_pPreviousState = m_pCurrentState;

		// 기존 상태의 exit 메소드를 호출한다.
		m_pCurrentState->Exit(m_pOwner);

		// 상태를 새로운 상태로 변화시킨다.
		m_pCurrentState = pNewState;

		// 새로운 상태의 enter 메소드를 호출한다.
		m_pCurrentState->Enter(m_pOwner);
	}

	// 상태를 이전 상태로 다시 변화시킨다.
	void RevertToPreviousState(){
		ChangeState(m_pPreviousState);
	}

	bool HandleMessage(const Telegram& msg)const{
		// 우선 현재 상태가 유효하고 메시지를 처리할 수 있는지를 알아본다.
		if(m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg)){
			return true;
		}

		// 처리할 수 없고 전역 상태가 설치되어 있다면 메시지를 전역 상태로 보낸다.
		if(m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg)){
			return false;
		}

		return false;
	}

	// 접근자(accessor)
	CState<entity_type>* CurrentState() const{return m_pCurrentState;}
	CState<entity_type>* GlobalState() const{return m_pGlobalState;}
	CState<entity_type>* PreviousState() const{return m_pPreviousState;}

	// 만약 현재 상태의 형식이 매개변수로 넘겨받은 클래스의 형식과 같다면
	// 참값을 반환
	bool isInState(const CState<entity_type>& st)const;
};

#endif