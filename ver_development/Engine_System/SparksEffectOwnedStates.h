////////////////////////////////////////////////////
// SparksEffect가 가질 상태들
////////////////////////////////////////////////////
#ifndef _SparksEffectOwnedStates_H_
#define _SparksEffectOwnedStates_H_

class CSparksEffect;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CSparksEffectUsual : public CState<CSparksEffect>{
private:  
	CSparksEffectUsual(){}

	//copy ctor and assignment should be private
	CSparksEffectUsual(const CSparksEffectUsual&);
	CSparksEffectUsual& operator=(const CSparksEffectUsual&);
 
public:
  //this is a singleton
	static CSparksEffectUsual* Instance(){
		static CSparksEffectUsual instance;

		return &instance;
	}

	virtual void Enter(CSparksEffect* pSparksEffect);

	virtual void Execute(CSparksEffect* pSparksEffect);

	virtual void Exit(CSparksEffect* pSparksEffect);

	virtual bool OnMessage(CSparksEffect* agent, const Telegram& msg);
};

#define SparksEffectUsual CSparksEffectUsual::Instance()

#endif