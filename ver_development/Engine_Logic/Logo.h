#ifndef _Logo_H_
#define _Logo_H_

template <class entity_type> class CState;

class CLogo : public CBaseSection{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CLogo>* m_pStateMachine;

public:
	CLogo::CLogo(int id):CBaseSection(id){
		// 상태기계를 설정한다.
		m_pStateMachine = new CStateMachine<CLogo>(this);

		m_pStateMachine->SetCurrentState(LogoShow->Instance());

		m_pStateMachine->SetGlobalState(NULL);
	}
	~CLogo(){}

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CLogo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}
};

#endif