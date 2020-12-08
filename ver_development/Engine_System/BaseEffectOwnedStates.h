////////////////////////////////////////////////////
// BaseEffect가 가질 상태들
////////////////////////////////////////////////////
#ifndef _BaseEffectOwnedStates_H_
#define _BaseEffectOwnedStates_H_

class CBaseEffect;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CBaseEffectUsual : public CState<CBaseEffect>{
private:  
	CBaseEffectUsual(){}

	//copy ctor and assignment should be private
	CBaseEffectUsual(const CBaseEffectUsual&);
	CBaseEffectUsual& operator=(const CBaseEffectUsual&);
 
public:
  //this is a singleton
	static CBaseEffectUsual* Instance(){
		static CBaseEffectUsual instance;

		return &instance;
	}

	virtual void Enter(CBaseEffect* pBaseEffect);

	virtual void Execute(CBaseEffect* pBaseEffect);

	virtual void Exit(CBaseEffect* pBaseEffect);

	virtual bool OnMessage(CBaseEffect* agent, const Telegram& msg);
};

#define BaseEffectUsual CBaseEffectUsual::Instance()

#endif