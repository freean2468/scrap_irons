////////////////////////////////////////////////////////////////////////////////
// 꽃(민들레) 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Flower_H_
#define _Flower_H_

class CFlower : public CCharacterEntity{
public:
	typedef enum FlowerAttType {ONE = 0, TWO, THREE} FLOWERATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CFlower>* m_pStateMachine;

	float _rotVelocity;

public:
	CFlower(int id);
	~CFlower();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	virtual void BoundUpdate();

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CFlower>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	float GetRotVelocity(){return _rotVelocity;}
};

#endif