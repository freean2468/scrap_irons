////////////////////////////////////////////////////
// Worker가 가질 상태들
////////////////////////////////////////////////////
#ifndef _WorkerOwnedStates_H_
#define _WorkerOwnedStates_H_

class CWorker;

///////////////////////////////////////////////////////////
// Ready State
///////////////////////////////////////////////////////////
class CWorkerReady : public CState<CWorker>{
private:  
	CWorkerReady(){}

	//copy ctor and assignment should be private
	CWorkerReady(const CWorkerReady&);
	CWorkerReady& operator=(const CWorkerReady&);

	bool _setTimer;
	bool _destinationArrive;

public:
  //this is a singleton
	static CWorkerReady* Instance(){
		static CWorkerReady instance;

		return &instance;
	}

	virtual void Enter(CWorker* pWorker);

	virtual void Execute(CWorker* pWorker);

	virtual void Exit(CWorker* pWorker);

	virtual bool OnMessage(CWorker* agent, const Telegram& msg);
};

#define WorkerReady CWorkerReady::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CWorkerEvent : public CState<CWorker>{
private:  
	CWorkerEvent(){}

	//copy ctor and assignment should be private
	CWorkerEvent(const CWorkerEvent&);
	CWorkerEvent& operator=(const CWorkerEvent&);
 
public:
  //this is a singleton
	static CWorkerEvent* Instance(){
		static CWorkerEvent instance;

		return &instance;
	}

	virtual void Enter(CWorker* pWorker);

	virtual void Execute(CWorker* pWorker);

	virtual void Exit(CWorker* pWorker);

	virtual bool OnMessage(CWorker* agent, const Telegram& msg);
};

#define WorkerEvent CWorkerEvent::Instance()

///////////////////////////////////////////////////////////
// Normal Attack State
///////////////////////////////////////////////////////////
class CWorkerChinAttack : public CState<CWorker>{
private:  
	CWorkerChinAttack(){}

	//copy ctor and assignment should be private
	CWorkerChinAttack(const CWorkerChinAttack&);
	CWorkerChinAttack& operator=(const CWorkerChinAttack&);

	float _requireDistance;
	float _moveDistance;
 
public:
  //this is a singleton
	static CWorkerChinAttack* Instance(){
		static CWorkerChinAttack instance;

		return &instance;
	}

	virtual void Enter(CWorker* pWorker);

	virtual void Execute(CWorker* pWorker);

	virtual void Exit(CWorker* pWorker);

	virtual bool OnMessage(CWorker* agent, const Telegram& msg);
};

#define WorkerChinAttack CWorkerChinAttack::Instance()

///////////////////////////////////////////////////////////
// Walking Attack State
///////////////////////////////////////////////////////////
class CWorkerWalkingChinAttack : public CState<CWorker>{
private:  
	CWorkerWalkingChinAttack(){}

	//copy ctor and assignment should be private
	CWorkerWalkingChinAttack(const CWorkerWalkingChinAttack&);
	CWorkerWalkingChinAttack& operator=(const CWorkerWalkingChinAttack&);

	float _requireDistance;
	float _moveDistance;
 
public:
  //this is a singleton
	static CWorkerWalkingChinAttack* Instance(){
		static CWorkerWalkingChinAttack instance;

		return &instance;
	}

	virtual void Enter(CWorker* pWorker);

	virtual void Execute(CWorker* pWorker);

	virtual void Exit(CWorker* pWorker);

	virtual bool OnMessage(CWorker* agent, const Telegram& msg);
};

#define WorkerWalkingChinAttack CWorkerWalkingChinAttack::Instance()

///////////////////////////////////////////////////////////
// Charge Attack State
///////////////////////////////////////////////////////////
class CWorkerChargeAttack : public CState<CWorker>{
private:  
	CWorkerChargeAttack(){}

	//copy ctor and assignment should be private
	CWorkerChargeAttack(const CWorkerChargeAttack&);
	CWorkerChargeAttack& operator=(const CWorkerChargeAttack&);

	float _requireDistance;
	float _moveDistance;
	CTimer* _timer;
 
public:
  //this is a singleton
	static CWorkerChargeAttack* Instance(){
		static CWorkerChargeAttack instance;

		return &instance;
	}

	virtual void Enter(CWorker* pWorker);

	virtual void Execute(CWorker* pWorker);

	virtual void Exit(CWorker* pWorker);

	virtual bool OnMessage(CWorker* agent, const Telegram& msg);
};

#define WorkerChargeAttack CWorkerChargeAttack::Instance()

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
class CWorkerEscape : public CState<CWorker>{
private:  
	CWorkerEscape(){}

	//copy ctor and assignment should be private
	CWorkerEscape(const CWorkerEscape&);
	CWorkerEscape& operator=(const CWorkerEscape&);

public:
  //this is a singleton
	static CWorkerEscape* Instance(){
		static CWorkerEscape instance;

		return &instance;
	}

	virtual void Enter(CWorker* pWorker);

	virtual void Execute(CWorker* pWorker);

	virtual void Exit(CWorker* pWorker);

	virtual bool OnMessage(CWorker* agent, const Telegram& msg);
};

#define WorkerEscape CWorkerEscape::Instance()

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
class CWorkerDie : public CState<CWorker>{
private:  
	CWorkerDie(){}

	//copy ctor and assignment should be private
	CWorkerDie(const CWorkerDie&);
	CWorkerDie& operator=(const CWorkerDie&);
 
public:
  //this is a singleton
	static CWorkerDie* Instance(){
		static CWorkerDie instance;

		return &instance;
	}

	virtual void Enter(CWorker* pWorker);

	virtual void Execute(CWorker* pWorker);

	virtual void Exit(CWorker* pWorker);

	virtual bool OnMessage(CWorker* agent, const Telegram& msg);
};

#define WorkerDie CWorkerDie::Instance()

///////////////////////////////////////////////////////////
// WorkerItemEat State
///////////////////////////////////////////////////////////
class CWorkerItemEat : public CState<CWorker>{
private:  
	CWorkerItemEat(){}

	//copy ctor and assignment should be private
	CWorkerItemEat(const CWorkerItemEat&);
	CWorkerItemEat& operator=(const CWorkerItemEat&);

	float _mouseAngle;
	int _nCount;
 
public:
  //this is a singleton
	static CWorkerItemEat* Instance(){
		static CWorkerItemEat instance;

		return &instance;
	}

	virtual void Enter(CWorker* pWorker);

	virtual void Execute(CWorker* pWorker);

	virtual void Exit(CWorker* pWorker);

	virtual bool OnMessage(CWorker* agent, const Telegram& msg);
};

#define WorkerItemEat CWorkerItemEat::Instance()

#endif