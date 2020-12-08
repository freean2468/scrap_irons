////////////////////////////////////////////////////
// Commander가 가질 상태들
////////////////////////////////////////////////////
#ifndef _CommanderOwnedStates_H_
#define _CommanderOwnedStates_H_

class CCommander;

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
class CCommanderMinimize : public CState<CCommander>{
private:  
	CCommanderMinimize(){}

	//copy ctor and assignment should be private
	CCommanderMinimize(const CCommanderMinimize&);
	CCommanderMinimize& operator=(const CCommanderMinimize&);
 
public:
  //this is a singleton
	static CCommanderMinimize* Instance(){
		static CCommanderMinimize instance;

		return &instance;
	}

	virtual void Enter(CCommander* pCommander);

	virtual void Execute(CCommander* pCommander);

	virtual void Exit(CCommander* pCommander);

	virtual bool OnMessage(CCommander* agent, const Telegram& msg);
};

#define CommanderMinimize CCommanderMinimize::Instance()

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
class CCommanderActive : public CState<CCommander>{
private:  
	CCommanderActive(){}

	//copy ctor and assignment should be private
	CCommanderActive(const CCommanderActive&);
	CCommanderActive& operator=(const CCommanderActive&);
 
public:
  //this is a singleton
	static CCommanderActive* Instance(){
		static CCommanderActive instance;

		return &instance;
	}

	virtual void Enter(CCommander* pCommander);

	virtual void Execute(CCommander* pCommander);

	virtual void Exit(CCommander* pCommander);

	virtual bool OnMessage(CCommander* agent, const Telegram& msg);
};

#define CommanderActive CCommanderActive::Instance()

#endif