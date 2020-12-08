////////////////////////////////////////////////////
// BoostEffect가 가질 상태들
////////////////////////////////////////////////////
#ifndef _BoostEffectOwnedStates_H_
#define _BoostEffectOwnedStates_H_

class CBoostEffect;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CBoostEffectUsual : public CState<CBoostEffect>{
private:  
	CBoostEffectUsual(){}

	//copy ctor and assignment should be private
	CBoostEffectUsual(const CBoostEffectUsual&);
	CBoostEffectUsual& operator=(const CBoostEffectUsual&);
 
public:
  //this is a singleton
	static CBoostEffectUsual* Instance(){
		static CBoostEffectUsual instance;

		return &instance;
	}

	virtual void Enter(CBoostEffect* pBoostEffect);

	virtual void Execute(CBoostEffect* pBoostEffect);

	virtual void Exit(CBoostEffect* pBoostEffect);

	virtual bool OnMessage(CBoostEffect* agent, const Telegram& msg);
};

#define BoostEffectUsual CBoostEffectUsual::Instance()

#endif