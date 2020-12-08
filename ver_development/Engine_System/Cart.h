////////////////////////////////////////////////////////////////////////////////
// 수레 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Cart_H_
#define _Cart_H_

class CCart : public CCharacterEntity{
public:
	typedef enum CartAttType {PLANTER = 0, PIPE, LUMBER, NAIL, BODYFRONT, PUPIL, MOUSEOVER, MOUSEUNDER, WHEELLEFT, WHEELRIGHT} CARTATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CCart>* m_pStateMachine;

	float _rotVelocity;
public:
	CCart(int id);
	~CCart();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CCart>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void BoundUpdate();

	float GetRotVelocity(){return _rotVelocity;}
};

#endif