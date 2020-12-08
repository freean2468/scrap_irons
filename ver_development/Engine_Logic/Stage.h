#ifndef _Stage_H_
#define _Stage_H_

class CStage : public CBaseSection{
private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CStage>* m_pStateMachine;

public:
	CStage::CStage(int id):CBaseSection(id){
		// 상태기계를 설정한다.
		m_pStateMachine = new CStateMachine<CStage>(this);

		m_pStateMachine->SetCurrentState(NULL);

		m_pStateMachine->SetGlobalState(NULL);
	}
	~CStage(){}

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CStage>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}
};

#endif