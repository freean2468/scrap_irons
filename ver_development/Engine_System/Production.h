////////////////////////////////////////////////////////////////////////////////
// Iron 생산 창 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Production_H_
#define _Production_H_

class CProduction : public COrganEntity{
public:
	typedef enum ProductionAttType {CLOSE = 0, BUTTON} PRODUCTIONATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CProduction>* m_pStateMachine;
	ID3DXFont*	_pFont;		// 폰트 인터페이스 변수
	bool _completeState;	// true는 완료버튼을 눌러야 하는 상황

public:
	CProduction(int id);
	~CProduction();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CProduction>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	ID3DXFont* GetFont(){return _pFont;}
	bool GetCompleteState(){return _completeState;}
	void SetCompleteState(bool p_bool){_completeState = p_bool;}
};

#endif