////////////////////////////////////////////////////
// ID를 가진 Entity를 상속 받은 Section 부분 클래스
////////////////////////////////////////////////////
#ifndef _Section_H_
#define _Section_H_

class CSection : public CBaseGameEntity{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CSection>* m_pStateMachine;

	// 타이머
	CTimer* _timer;

public:
	CSection::CSection(int id):CBaseGameEntity(id), _timer(NULL){
		// 상태기계를 설정한다.
		m_pStateMachine = new CStateMachine<CSection>(this);

		// 처음 상태를 초기화
		m_pStateMachine->SetCurrentState(LogoShow->Instance());

		m_pStateMachine->CurrentState()->Enter(this);

		m_pStateMachine->SetGlobalState(NULL);
	}
	~CSection(){
		d3d::Delete< CStateMachine<CSection>* >(m_pStateMachine);
		d3d::Delete<CTimer*>(_timer);
	}

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CSection>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	void SetTimer(DWORD dwDelayTime){_timer = new CTimer(dwDelayTime);}

	CTimer* GetTimer(){return _timer;}
};

#endif