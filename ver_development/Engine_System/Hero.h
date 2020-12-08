////////////////////////////////////////////////////////////////////////////////
// 주인공 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Hero_H_
#define _Hero_H_

class CHero : public CCharacterEntity{
public:
	typedef enum HeroAttType {ARM = 0, PUPIL} HEROATTTYPE;

private:
	float _bodyRotVelocity;
	float _armRotVelocity;
	float _pupilRotVelocity;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CHero>* m_pStateMachine;

	// 타이머
	CTimer* _timer;
public:
	CHero(int id);
	~CHero();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CHero>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void BoundUpdate();

	void SetTimer(DWORD dwDelayTime){_timer = new CTimer(dwDelayTime);}

	CTimer* GetTimer(){return _timer;}

	virtual void CalculationOrgan(float timeDelta){}

	float GetBodyRotVelocity(){return _bodyRotVelocity;}
	float GetArmRotVelocity(){return _armRotVelocity;}
	float GetPupilRotVelocity(){return _pupilRotVelocity;}
};

#endif