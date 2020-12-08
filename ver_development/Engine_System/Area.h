////////////////////////////////////////////////////////////////////////////////
// Area 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Area_H_
#define _Area_H_

#include "./Engine_System/BaseManager.h"

class CArea : public COrganEntity{
public:
	typedef enum AreaAttType {CLEAR = 0, QM} AREAATTTYPE;

private:
// 상태기계 클래스의 한 인스턴스
	CStateMachine<CArea>* m_pStateMachine;

	int _areaNumber;
	bool _clear;

public:
	CArea(int p_nNum, char* p_pStr);
	~CArea();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CArea>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
	virtual void RenderOrgan();
	
	void SetAreaNumber(int p_nNum){_areaNumber = p_nNum;}
	int GetAreaNumber(){return _areaNumber;}

	void SetClear(bool p_bool){_clear = p_bool;}
	bool GetClear(){return _clear;}
};

#endif