////////////////////////////////////////////////////
// Area가 가질 상태들
////////////////////////////////////////////////////
#ifndef _AreaOwnedStates_H_
#define _AreaOwnedStates_H_

class CArea;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CAreaUsual : public CState<CArea>{
private:  
	CAreaUsual(){}

	//copy ctor and assignment should be private
	CAreaUsual(const CAreaUsual&);
	CAreaUsual& operator=(const CAreaUsual&);
 
public:
  //this is a singleton
	static CAreaUsual* Instance(){
		static CAreaUsual instance;

		return &instance;
	}

	virtual void Enter(CArea* pArea);

	virtual void Execute(CArea* pArea);

	virtual void Exit(CArea* pArea);

	virtual bool OnMessage(CArea* agent, const Telegram& msg);
};

#define AreaUsual CAreaUsual::Instance()

#endif