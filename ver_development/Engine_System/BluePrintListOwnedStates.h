////////////////////////////////////////////////////
// BluePrint가 가질 상태들
////////////////////////////////////////////////////
#ifndef _BluePrintListOwnedStates_H_
#define _BluePrintListOwnedStates_H_

class CBluePrintList;

///////////////////////////////////////////////////////////
// Show State
///////////////////////////////////////////////////////////
class CBluePrintListShow : public CState<CBluePrintList>{
private:  
	CBluePrintListShow(){}

	//copy ctor and assignment should be private
	CBluePrintListShow(const CBluePrintListShow&);
	CBluePrintListShow& operator=(const CBluePrintListShow&);
 
public:
  //this is a singleton
	static CBluePrintListShow* Instance(){
		static CBluePrintListShow instance;

		return &instance;
	}

	virtual void Enter(CBluePrintList* pList);

	virtual void Execute(CBluePrintList* pList);

	virtual void Exit(CBluePrintList* pList);

	virtual bool OnMessage(CBluePrintList* agent, const Telegram& msg);
};

#define BluePrintListShow CBluePrintListShow::Instance()

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
class CBluePrintListMinimize : public CState<CBluePrintList>{
private:  
	CBluePrintListMinimize(){}

	//copy ctor and assignment should be private
	CBluePrintListMinimize(const CBluePrintListMinimize&);
	CBluePrintListMinimize& operator=(const CBluePrintListMinimize&);
 
public:
  //this is a singleton
	static CBluePrintListMinimize* Instance(){
		static CBluePrintListMinimize instance;

		return &instance;
	}

	virtual void Enter(CBluePrintList* pList);

	virtual void Execute(CBluePrintList* pList);

	virtual void Exit(CBluePrintList* pList);

	virtual bool OnMessage(CBluePrintList* agent, const Telegram& msg);
};

#define BluePrintListMinimize CBluePrintListMinimize::Instance()

///////////////////////////////////////////////////////////
// InProduction State
///////////////////////////////////////////////////////////
class CBluePrintListInProduction : public CState<CBluePrintList>{
private:  
	CBluePrintListInProduction(){}

	//copy ctor and assignment should be private
	CBluePrintListInProduction(const CBluePrintListInProduction&);
	CBluePrintListInProduction& operator=(const CBluePrintListInProduction&);
 
public:
  //this is a singleton
	static CBluePrintListInProduction* Instance(){
		static CBluePrintListInProduction instance;

		return &instance;
	}

	virtual void Enter(CBluePrintList* pList);

	virtual void Execute(CBluePrintList* pList);

	virtual void Exit(CBluePrintList* pList);

	virtual bool OnMessage(CBluePrintList* agent, const Telegram& msg);
};

#define BluePrintListInProduction CBluePrintListInProduction::Instance()

#endif