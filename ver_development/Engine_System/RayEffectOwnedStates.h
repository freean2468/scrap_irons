////////////////////////////////////////////////////
// RayEffect가 가질 상태들
////////////////////////////////////////////////////
#ifndef _RayEffectOwnedStates_H_
#define _RayEffectOwnedStates_H_

class CRayEffect;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CRayEffectUsual : public CState<CRayEffect>{
private:  
	CRayEffectUsual(){}

	//copy ctor and assignment should be private
	CRayEffectUsual(const CRayEffectUsual&);
	CRayEffectUsual& operator=(const CRayEffectUsual&);
 
public:
  //this is a singleton
	static CRayEffectUsual* Instance(){
		static CRayEffectUsual instance;

		return &instance;
	}

	virtual void Enter(CRayEffect* pRayEffect);

	virtual void Execute(CRayEffect* pRayEffect);

	virtual void Exit(CRayEffect* pRayEffect);

	virtual bool OnMessage(CRayEffect* agent, const Telegram& msg);
};

#define RayEffectUsual CRayEffectUsual::Instance()

#endif