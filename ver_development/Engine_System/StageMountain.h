////////////////////////////////////////////////////////////////////////////////
// Mt.Scrap 스테이지 담당 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _StageMountain_H_
#define _StageMountain_H_

#include "./Engine_System/BaseManager.h"

class CStageMountain : public COrganEntity{
public:
	typedef enum StageMountainAttType {SMOKE = 0} STAGEMOUNTAINTTTYPE;

private:
	// 상태기계 클래스의 한 인스턴스
	CStateMachine<CStageMountain>* m_pStateMachine;

	// Area
	CArea* _area[3];

public:
	CStageMountain(int id);
	~CStageMountain();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CStageMountain>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
	virtual void RenderOrgan();

	CArea* GetArea(int p_index){return _area[p_index];}
};

#endif