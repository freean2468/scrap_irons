////////////////////////////////////////////////////
// LightEffect가 가질 상태들
////////////////////////////////////////////////////
#ifndef _LightEffectOwnedStates_H_
#define _LightEffectOwnedStates_H_

class CLightEffect;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CLightEffectUsual : public CState<CLightEffect>{
private:  
	CLightEffectUsual(){}

	//copy ctor and assignment should be private
	CLightEffectUsual(const CLightEffectUsual&);
	CLightEffectUsual& operator=(const CLightEffectUsual&);
 
public:
  //this is a singleton
	static CLightEffectUsual* Instance(){
		static CLightEffectUsual instance;

		return &instance;
	}

	virtual void Enter(CLightEffect* pLightEffect);

	virtual void Execute(CLightEffect* pLightEffect);

	virtual void Exit(CLightEffect* pLightEffect);

	virtual bool OnMessage(CLightEffect* agent, const Telegram& msg);
};

#define LightEffectUsual CLightEffectUsual::Instance()

#endif