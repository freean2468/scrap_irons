////////////////////////////////////////////////////////////////////////////////
// 꽃(민들레) 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Tinkle_H_
#define _Tinkle_H_

class CTinkle : public CCharacterEntity{
public:
	typedef enum TinkleAttType {EYE = 0, EFFECT} TINKLEATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CTinkle>* m_pStateMachine;

public:
	CTinkle(int id);
	~CTinkle();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CTinkle>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void BoundUpdate(){}
};

#endif