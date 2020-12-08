////////////////////////////////////////////////////
// DiggyEffect가 가질 상태들
////////////////////////////////////////////////////
#ifndef _DiggyEffectOwnedStates_H_
#define _DiggyEffectOwnedStates_H_

class CDiggyEffect;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CDiggyEffectUsual : public CState<CDiggyEffect>{
private:  
	CDiggyEffectUsual(){}

	//copy ctor and assignment should be private
	CDiggyEffectUsual(const CDiggyEffectUsual&);
	CDiggyEffectUsual& operator=(const CDiggyEffectUsual&);
 
public:
  //this is a singleton
	static CDiggyEffectUsual* Instance(){
		static CDiggyEffectUsual instance;

		return &instance;
	}

	virtual void Enter(CDiggyEffect* pDiggyEffect);

	virtual void Execute(CDiggyEffect* pDiggyEffect);

	virtual void Exit(CDiggyEffect* pDiggyEffect);

	virtual bool OnMessage(CDiggyEffect* agent, const Telegram& msg);
};

#define DiggyEffectUsual CDiggyEffectUsual::Instance()

#endif