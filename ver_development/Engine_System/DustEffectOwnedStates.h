////////////////////////////////////////////////////
// DustEffect가 가질 상태들
////////////////////////////////////////////////////
#ifndef _DustEffectOwnedStates_H_
#define _DustEffectOwnedStates_H_

class CDustEffect;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CDustEffectUsual : public CState<CDustEffect>{
private:  
	CDustEffectUsual(){}

	//copy ctor and assignment should be private
	CDustEffectUsual(const CDustEffectUsual&);
	CDustEffectUsual& operator=(const CDustEffectUsual&);
 
public:
  //this is a singleton
	static CDustEffectUsual* Instance(){
		static CDustEffectUsual instance;

		return &instance;
	}

	virtual void Enter(CDustEffect* pDustEffect);

	virtual void Execute(CDustEffect* pDustEffect);

	virtual void Exit(CDustEffect* pDustEffect);

	virtual bool OnMessage(CDustEffect* agent, const Telegram& msg);
};

#define DustEffectUsual CDustEffectUsual::Instance()

#endif