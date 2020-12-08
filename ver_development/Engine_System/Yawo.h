////////////////////////////////////////////////////////////////////////////////
// YawoYawo 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Yawo_H_
#define _Yawo_H_

class CYawo : public CCharacterEntity{
public:
	typedef enum YawoAttType {BODY = 0, HEAD, LEGONE, LEGTWO, LEGTHREE, LEGFOUR, LEGFIVE} YAWOATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CYawo>* m_pStateMachine;

public:
	CYawo(int id);
	~CYawo();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CYawo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	virtual void BoundUpdate();

	virtual void ApplyDamageOurForceToEnemy();
};

#endif