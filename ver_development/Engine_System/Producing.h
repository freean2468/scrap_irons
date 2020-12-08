////////////////////////////////////////////////////////////////////////////////
// Iron 생산 완료 창 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Producing_H_
#define _Producing_H_

class CProducing : public COrganEntity{
public:
	typedef enum ProducingAttType {DOORLEFT = 0, DOORRIGHT, NEEDLE} PRODUCINGATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CProducing>* m_pStateMachine;

public:
	CProducing(int id);
	~CProducing();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CProducing>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();
};

#endif