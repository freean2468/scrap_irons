////////////////////////////////////////////////////////////////////////////////
// DustKing 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _DustKing_H_
#define _DustKing_H_

class CDustKing : public CCharacterEntity{
public:
	typedef enum DustKingAttType {SUB = 0, CORE, EYE, PUPIL, TIARA, HAND} DUSTKIDATTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CDustKing>* m_pStateMachine;

public:
	CDustKing(int id);
	~CDustKing();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CDustKing>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	virtual void RenderOrgan();

	// 충돌체크 관련
	void BoundUpdate();
};

#endif