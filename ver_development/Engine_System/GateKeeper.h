////////////////////////////////////////////////////////////////////////////////
// GateKeeper 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _GateKeeper_H_
#define _GateKeeper_H_

class CGateKeeper : public CCharacterEntity{
public:
	typedef enum GateKeeperAttType {FIRST = 0, SECOND, THIRD, ARM} GATEKEEPERATTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CGateKeeper>* m_pStateMachine;

	float _deltaY;	// 상하 운동

public:
	CGateKeeper(int id);
	~CGateKeeper();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CGateKeeper>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	// 충돌체크 관련
	void BoundUpdate();

	void SetDeltaY(float p_delta){_deltaY = p_delta;}
	float GetDeltaY(){return _deltaY;}
};

#endif