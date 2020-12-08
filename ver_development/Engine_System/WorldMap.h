////////////////////////////////////////////////////////////////////////////////
// 유동적인 스테이지
////////////////////////////////////////////////////////////////////////////////
#ifndef _WorldMap_H_
#define _WorldMap_H_

#include "./Engine_System/BaseManager.h"

class CWorldMap : public COrganEntity{
public:
	typedef enum WorldMapAttType {STAGEPOINT = 0, TEXT, LIGHT, DUST} WORLDMAPATTTYPE;

private:
// 상태기계 클래스의 한 인스턴스
	CStateMachine<CWorldMap>* m_pStateMachine;

public:
	CWorldMap(int id);
	~CWorldMap();

	// 이것은 반드시 설치되어야 한다.
	void Update(){ m_pStateMachine->Update();}

	// 이 메소드는 현재 상태를 새로운 상태로 변화시킨다.
	CStateMachine<CWorldMap>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
	virtual void RenderOrgan();
};

#endif