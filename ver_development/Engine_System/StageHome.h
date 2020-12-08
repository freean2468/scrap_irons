////////////////////////////////////////////////////////////////////////////////
// Home 스테이지 담당 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _StageHome_H_
#define _StageHome_H_

#include "./Engine_System/BaseManager.h"

class CStageHome : public COrganEntity{
public:
	typedef enum StageHomeAttType {OUTSIDE = 0} STAGEHOMEATTTYPE;

public:
	CStageHome(int id);
	~CStageHome();

	virtual void Update(){this->CalculationOrgan(EngineMgr->GetTimeDelta());}
	virtual bool HandleMessage(const Telegram& msg){return false;}

	virtual void TransformOrgan(float timeDelta);

	virtual void CalculationOrgan(float timeDelta);
};

#endif