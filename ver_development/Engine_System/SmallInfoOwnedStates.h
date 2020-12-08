////////////////////////////////////////////////////
// SmallInfo가 가질 상태들
////////////////////////////////////////////////////
#ifndef _SmallInfoOwnedStates_H_
#define _SmallInfoOwnedStates_H_

class CSmallInfo;

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
class CSmallInfoMinimize : public CState<CSmallInfo>{
private:  
	CSmallInfoMinimize(){}

	//copy ctor and assignment should be private
	CSmallInfoMinimize(const CSmallInfoMinimize&);
	CSmallInfoMinimize& operator=(const CSmallInfoMinimize&);
 
public:
  //this is a singleton
	static CSmallInfoMinimize* Instance(){
		static CSmallInfoMinimize instance;

		return &instance;
	}

	virtual void Enter(CSmallInfo* pSmallInfo);

	virtual void Execute(CSmallInfo* pSmallInfo);

	virtual void Exit(CSmallInfo* pSmallInfo);

	virtual bool OnMessage(CSmallInfo* agent, const Telegram& msg);
};

#define SmallInfoMinimize CSmallInfoMinimize::Instance()

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
class CSmallInfoActive : public CState<CSmallInfo>{
private:  
	CSmallInfoActive(){}

	//copy ctor and assignment should be private
	CSmallInfoActive(const CSmallInfoActive&);
	CSmallInfoActive& operator=(const CSmallInfoActive&);
 
public:
  //this is a singleton
	static CSmallInfoActive* Instance(){
		static CSmallInfoActive instance;

		return &instance;
	}

	virtual void Enter(CSmallInfo* pSmallInfo);

	virtual void Execute(CSmallInfo* pSmallInfo);

	virtual void Exit(CSmallInfo* pSmallInfo);

	virtual bool OnMessage(CSmallInfo* agent, const Telegram& msg);
};

#define SmallInfoActive CSmallInfoActive::Instance()

#endif