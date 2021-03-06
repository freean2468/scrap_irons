////////////////////////////////////////////////////////////////////////////////
// 상호작용 가능 표시 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _SmallInfo_H_
#define _SmallInfo_H_

class CSmallInfo : public COrganEntity{
public:
	typedef enum SmallInfoAttType {GAGEBODY, BLUE, RED} SmallInfoATTTYPE;

public:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CSmallInfo>* m_pStateMachine;

	CCharacterEntity* _origin;

public:
	CSmallInfo(CCharacterEntity* p_pEntity);
	~CSmallInfo();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CSmallInfo>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	CCharacterEntity* GetOrigin(){return _origin;}
};

#endif