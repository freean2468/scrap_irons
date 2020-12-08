////////////////////////////////////////////////////
// Production Menu가 가질 상태들
////////////////////////////////////////////////////
#ifndef _ProductionOwnedStates_H_
#define _ProductionOwnedStates_H_

class CProduction;

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
class CProductionMinimize : public CState<CProduction>{
private:  
	CProductionMinimize(){}

	//copy ctor and assignment should be private
	CProductionMinimize(const CProductionMinimize&);
	CProductionMinimize& operator=(const CProductionMinimize&);
 
public:
  //this is a singleton
	static CProductionMinimize* Instance(){
		static CProductionMinimize instance;

		return &instance;
	}

	virtual void Enter(CProduction* pProduction);

	virtual void Execute(CProduction* pProduction);

	virtual void Exit(CProduction* pProduction);

	virtual bool OnMessage(CProduction* agent, const Telegram& msg);
};

#define ProductionMinimize CProductionMinimize::Instance()

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
class CProductionActive : public CState<CProduction>{
private:  
	CProductionActive(){}

	//copy ctor and assignment should be private
	CProductionActive(const CProductionActive&);
	CProductionActive& operator=(const CProductionActive&);
 
public:
  //this is a singleton
	static CProductionActive* Instance(){
		static CProductionActive instance;

		return &instance;
	}

	virtual void Enter(CProduction* pProduction);

	virtual void Execute(CProduction* pProduction);

	virtual void Exit(CProduction* pProduction);

	virtual bool OnMessage(CProduction* agent, const Telegram& msg);
};

#define ProductionActive CProductionActive::Instance()

#endif