////////////////////////////////////////////////////
// BluePrint가 가질 상태들
////////////////////////////////////////////////////
#ifndef _BluePrintScrollOwnedStates_H_
#define _BluePrintScrollOwnedStates_H_

class CBluePrintScroll;

///////////////////////////////////////////////////////////
// Show State
///////////////////////////////////////////////////////////
class CBluePrintScrollShow : public CState<CBluePrintScroll>{
private:  
	CBluePrintScrollShow(){}

	//copy ctor and assignment should be private
	CBluePrintScrollShow(const CBluePrintScrollShow&);
	CBluePrintScrollShow& operator=(const CBluePrintScrollShow&);
 
public:
  //this is a singleton
	static CBluePrintScrollShow* Instance(){
		static CBluePrintScrollShow instance;

		return &instance;
	}

	virtual void Enter(CBluePrintScroll* pScroll);

	virtual void Execute(CBluePrintScroll* pScroll);

	virtual void Exit(CBluePrintScroll* pScroll);

	virtual bool OnMessage(CBluePrintScroll* agent, const Telegram& msg);
};

#define BluePrintScrollShow CBluePrintScrollShow::Instance()

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
class CBluePrintScrollMinimize : public CState<CBluePrintScroll>{
private:  
	CBluePrintScrollMinimize(){}

	//copy ctor and assignment should be private
	CBluePrintScrollMinimize(const CBluePrintScrollMinimize&);
	CBluePrintScrollMinimize& operator=(const CBluePrintScrollMinimize&);
 
public:
  //this is a singleton
	static CBluePrintScrollMinimize* Instance(){
		static CBluePrintScrollMinimize instance;

		return &instance;
	}

	virtual void Enter(CBluePrintScroll* pScroll);

	virtual void Execute(CBluePrintScroll* pScroll);

	virtual void Exit(CBluePrintScroll* pScroll);

	virtual bool OnMessage(CBluePrintScroll* agent, const Telegram& msg);
};

#define BluePrintScrollMinimize CBluePrintScrollMinimize::Instance()

///////////////////////////////////////////////////////////
// InProduction State
///////////////////////////////////////////////////////////
class CBluePrintScrollInProduction : public CState<CBluePrintScroll>{
private:  
	CBluePrintScrollInProduction(){}

	//copy ctor and assignment should be private
	CBluePrintScrollInProduction(const CBluePrintScrollInProduction&);
	CBluePrintScrollInProduction& operator=(const CBluePrintScrollInProduction&);
 
public:
  //this is a singleton
	static CBluePrintScrollInProduction* Instance(){
		static CBluePrintScrollInProduction instance;

		return &instance;
	}

	virtual void Enter(CBluePrintScroll* pScroll);

	virtual void Execute(CBluePrintScroll* pScroll);

	virtual void Exit(CBluePrintScroll* pScroll);

	virtual bool OnMessage(CBluePrintScroll* agent, const Telegram& msg);
};

#define BluePrintScrollInProduction CBluePrintScrollInProduction::Instance()

#endif