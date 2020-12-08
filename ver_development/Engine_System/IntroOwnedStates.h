////////////////////////////////////////////////////
// Intro가 가질 상태들
////////////////////////////////////////////////////
#ifndef _IntroOwnedStates_H_
#define _IntroOwnedStates_H_

class CIntro;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CIntroUsual : public CState<CIntro>{
private:  
	CIntroUsual(){}

	//copy ctor and assignment should be private
	CIntroUsual(const CIntroUsual&);
	CIntroUsual& operator=(const CIntroUsual&);
 
public:
  //this is a singleton
	static CIntroUsual* Instance(){
		static CIntroUsual instance;

		return &instance;
	}

	virtual void Enter(CIntro* pIntro);

	virtual void Execute(CIntro* pIntro);

	virtual void Exit(CIntro* pIntro);

	virtual bool OnMessage(CIntro* agent, const Telegram& msg);
};

#define IntroUsual CIntroUsual::Instance()

#endif