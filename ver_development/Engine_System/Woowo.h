////////////////////////////////////////////////////////////////////////////////
// WoowoWoowo 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Woowo_H_
#define _Woowo_H_

class CWoowo : public CCharacterEntity{
public:
	typedef enum WoowoAttType {LEFT = 0, RIGHT, BODY, EYE} WOOWOATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CWoowo>* m_pStateMachine;

public:
	CWoowo(int id);
	~CWoowo();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CWoowo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	virtual void BoundUpdate();
};

#endif