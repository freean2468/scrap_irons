////////////////////////////////////////////////////////////////////////////////
// Intro 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Intro_H_
#define _Intro_H_

class CIntro : public COrganEntity{
public:
	typedef enum IntroAttType {GAGEBODY, BLUE, RED} IntroATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CIntro>* m_pStateMachine;

	CCharacterEntity* _origin;

public:
	CIntro(int _id);
	~CIntro();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CIntro>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	CCharacterEntity* GetOrigin(){return _origin;}
};

#endif