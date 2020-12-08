////////////////////////////////////////////////////////////////////////////////
// BGDarkEffect 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _BGDarkEffect_H_
#define _BGDarkEffect_H_

class CBGDarkEffect : public CAttachment{
public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CBGDarkEffect>* m_pStateMachine;

public:
	CBGDarkEffect();
	~CBGDarkEffect();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CBGDarkEffect>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
};

#endif