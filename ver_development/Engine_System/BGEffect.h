////////////////////////////////////////////////////////////////////////////////
// 배경 효과 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _BGEffect_H_
#define _BGEffect_H_

#include "./Engine_System/BaseManager.h"

class CBGEffect : public COrganEntity{
public:
	typedef enum BGEffectAttType {BLACK_SMOKE_ONE = 0, BLACK_SMOKE_TWO} BGEFFECTATTTYPE;

private:
	int nEffectType;
	CBaseObject::OWNER eBGType;
	d3d::BoundingBox _box;

public:
	CBGEffect(int id, CBaseObject::OWNER p_eOwner, CBGEffect::BGEFFECTATTTYPE p_eType, d3d::BoundingBox* p_pbox);
	~CBGEffect();

	CBaseObject::OWNER GetBGType(){return eBGType;}

	virtual void LoadEntityData(char* name, COrganEntity* p_pEntity, int p_nType);

	virtual void Update(){this->CalculationOrgan(EngineMgr->GetTimeDelta());}
	virtual bool HandleMessage(const Telegram& msg){return false;}

	virtual void TransformOrgan(float timeDelta);

	virtual void CalculationOrgan(float timeDelta);
};

#endif