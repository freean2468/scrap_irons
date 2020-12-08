////////////////////////////////////////////////////////////////////////////////
// Furnace 스테이지 담당 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _StageFurnace_H_
#define _StageFurnace_H_

#include "./Engine_System/BaseManager.h"

class CStageFurnace : public COrganEntity{
public:
	typedef enum StageFurnaceAttType {DOOR = 0} STAGEFURNACETTTYPE;

public:
	CStageFurnace(int id);
	~CStageFurnace();

	virtual void Update(){this->CalculationOrgan(EngineMgr->GetTimeDelta());}
	virtual bool HandleMessage(const Telegram& msg){return false;}

	virtual void TransformOrgan(float timeDelta);

	virtual void CalculationOrgan(float timeDelta);
};

#endif