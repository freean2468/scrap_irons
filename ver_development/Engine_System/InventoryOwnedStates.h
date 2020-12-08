////////////////////////////////////////////////////
// Inventory가 가질 상태들
////////////////////////////////////////////////////
#ifndef _InventoryOwnedStates_H_
#define _InventoryOwnedStates_H_

class CInventory;

///////////////////////////////////////////////////////////
// Show State
///////////////////////////////////////////////////////////
class CInventoryShow : public CState<CInventory>{
private:  
	CInventoryShow(){}

	//copy ctor and assignment should be private
	CInventoryShow(const CInventoryShow&);
	CInventoryShow& operator=(const CInventoryShow&);
 
public:
  //this is a singleton
	static CInventoryShow* Instance(){
		static CInventoryShow instance;

		return &instance;
	}

	virtual void Enter(CInventory* pInventory);

	virtual void Execute(CInventory* pInventory);

	virtual void Exit(CInventory* pInventory);

	virtual bool OnMessage(CInventory* agent, const Telegram& msg);
};

#define InventoryShow CInventoryShow::Instance()

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
class CInventoryMinimize : public CState<CInventory>{
private:  
	CInventoryMinimize(){}

	//copy ctor and assignment should be private
	CInventoryMinimize(const CInventoryMinimize&);
	CInventoryMinimize& operator=(const CInventoryMinimize&);
 
public:
  //this is a singleton
	static CInventoryMinimize* Instance(){
		static CInventoryMinimize instance;

		return &instance;
	}

	virtual void Enter(CInventory* pInventory);

	virtual void Execute(CInventory* pInventory);

	virtual void Exit(CInventory* pInventory);

	virtual bool OnMessage(CInventory* agent, const Telegram& msg);
};

#define InventoryMinimize CInventoryMinimize::Instance()

///////////////////////////////////////////////////////////
// InProduction State
///////////////////////////////////////////////////////////
class CInventoryInProduction : public CState<CInventory>{
private:  
	CInventoryInProduction(){}

	//copy ctor and assignment should be private
	CInventoryInProduction(const CInventoryInProduction&);
	CInventoryInProduction& operator=(const CInventoryInProduction&);
 
public:
  //this is a singleton
	static CInventoryInProduction* Instance(){
		static CInventoryInProduction instance;

		return &instance;
	}

	virtual void Enter(CInventory* pInventory);

	virtual void Execute(CInventory* pInventory);

	virtual void Exit(CInventory* pInventory);

	virtual bool OnMessage(CInventory* agent, const Telegram& msg);
};

#define InventoryInProduction CInventoryInProduction::Instance()

#endif