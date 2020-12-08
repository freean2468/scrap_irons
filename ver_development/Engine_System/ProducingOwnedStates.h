////////////////////////////////////////////////////
// Producing Menu가 가질 상태들
////////////////////////////////////////////////////
#ifndef _ProducingOwnedStates_H_
#define _ProducingOwnedStates_H_

class CProducing;

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
class CProducingMinimize : public CState<CProducing>{
private:  
	CProducingMinimize(){}

	//copy ctor and assignment should be private
	CProducingMinimize(const CProducingMinimize&);
	CProducingMinimize& operator=(const CProducingMinimize&);
 
public:
  //this is a singleton
	static CProducingMinimize* Instance(){
		static CProducingMinimize instance;

		return &instance;
	}

	virtual void Enter(CProducing* pProducing);

	virtual void Execute(CProducing* pProducing);

	virtual void Exit(CProducing* pProducing);

	virtual bool OnMessage(CProducing* agent, const Telegram& msg);
};

#define ProducingMinimize CProducingMinimize::Instance()

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
class CProducingActive : public CState<CProducing>{
private:  
	CProducingActive(){}

	//copy ctor and assignment should be private
	CProducingActive(const CProducingActive&);
	CProducingActive& operator=(const CProducingActive&);
 
public:
  //this is a singleton
	static CProducingActive* Instance(){
		static CProducingActive instance;

		return &instance;
	}

	virtual void Enter(CProducing* pProducing);

	virtual void Execute(CProducing* pProducing);

	virtual void Exit(CProducing* pProducing);

	virtual bool OnMessage(CProducing* agent, const Telegram& msg);
};

#define ProducingActive CProducingActive::Instance()

#endif