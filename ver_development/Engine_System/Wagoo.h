////////////////////////////////////////////////////////////////////////////////
// WagooWagoo 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Wagoo_H_
#define _Wagoo_H_

class CWagoo : public CCharacterEntity{
public:
	typedef enum WagooAttType {HEAD = 0, EYE, LEFT, RIGHT} HEROATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CWagoo>* m_pStateMachine;

public:
	CWagoo(int id);
	~CWagoo();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CWagoo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	virtual void BoundUpdate();
};

#endif