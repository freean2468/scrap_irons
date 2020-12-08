////////////////////////////////////////////////////
// MiniWorker가 가질 상태들
////////////////////////////////////////////////////
#ifndef _MiniWorkerOwnedStates_H_
#define _MiniWorkerOwnedStates_H_

class CMiniWorker;

///////////////////////////////////////////////////////////
// Ready State
///////////////////////////////////////////////////////////
class CMiniWorkerReady : public CState<CMiniWorker>{
private:  
	CMiniWorkerReady(){}

	//copy ctor and assignment should be private
	CMiniWorkerReady(const CMiniWorkerReady&);
	CMiniWorkerReady& operator=(const CMiniWorkerReady&);

	bool _setTimer;
	bool _destinationArrive;

public:
  //this is a singleton
	static CMiniWorkerReady* Instance(){
		static CMiniWorkerReady instance;

		return &instance;
	}

	virtual void Enter(CMiniWorker* pMiniWorker);

	virtual void Execute(CMiniWorker* pMiniWorker);

	virtual void Exit(CMiniWorker* pMiniWorker);

	virtual bool OnMessage(CMiniWorker* agent, const Telegram& msg);
};

#define MiniWorkerReady CMiniWorkerReady::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CMiniWorkerEvent : public CState<CMiniWorker>{
private:  
	CMiniWorkerEvent(){}

	//copy ctor and assignment should be private
	CMiniWorkerEvent(const CMiniWorkerEvent&);
	CMiniWorkerEvent& operator=(const CMiniWorkerEvent&);
 
public:
  //this is a singleton
	static CMiniWorkerEvent* Instance(){
		static CMiniWorkerEvent instance;

		return &instance;
	}

	virtual void Enter(CMiniWorker* pMiniWorker);

	virtual void Execute(CMiniWorker* pMiniWorker);

	virtual void Exit(CMiniWorker* pMiniWorker);

	virtual bool OnMessage(CMiniWorker* agent, const Telegram& msg);
};

#define MiniWorkerEvent CMiniWorkerEvent::Instance()

///////////////////////////////////////////////////////////
// Normal Attack State
///////////////////////////////////////////////////////////
class CMiniWorkerChinAttack : public CState<CMiniWorker>{
private:  
	CMiniWorkerChinAttack(){}

	//copy ctor and assignment should be private
	CMiniWorkerChinAttack(const CMiniWorkerChinAttack&);
	CMiniWorkerChinAttack& operator=(const CMiniWorkerChinAttack&);

	float _requireDistance;
	float _moveDistance;
 
public:
  //this is a singleton
	static CMiniWorkerChinAttack* Instance(){
		static CMiniWorkerChinAttack instance;

		return &instance;
	}

	virtual void Enter(CMiniWorker* pMiniWorker);

	virtual void Execute(CMiniWorker* pMiniWorker);

	virtual void Exit(CMiniWorker* pMiniWorker);

	virtual bool OnMessage(CMiniWorker* agent, const Telegram& msg);
};

#define MiniWorkerChinAttack CMiniWorkerChinAttack::Instance()

///////////////////////////////////////////////////////////
// Walking Attack State
///////////////////////////////////////////////////////////
class CMiniWorkerWalkingChinAttack : public CState<CMiniWorker>{
private:  
	CMiniWorkerWalkingChinAttack(){}

	//copy ctor and assignment should be private
	CMiniWorkerWalkingChinAttack(const CMiniWorkerWalkingChinAttack&);
	CMiniWorkerWalkingChinAttack& operator=(const CMiniWorkerWalkingChinAttack&);

	float _requireDistance;
	float _moveDistance;
 
public:
  //this is a singleton
	static CMiniWorkerWalkingChinAttack* Instance(){
		static CMiniWorkerWalkingChinAttack instance;

		return &instance;
	}

	virtual void Enter(CMiniWorker* pMiniWorker);

	virtual void Execute(CMiniWorker* pMiniWorker);

	virtual void Exit(CMiniWorker* pMiniWorker);

	virtual bool OnMessage(CMiniWorker* agent, const Telegram& msg);
};

#define MiniWorkerWalkingChinAttack CMiniWorkerWalkingChinAttack::Instance()

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
class CMiniWorkerEscape : public CState<CMiniWorker>{
private:  
	CMiniWorkerEscape(){}

	//copy ctor and assignment should be private
	CMiniWorkerEscape(const CMiniWorkerEscape&);
	CMiniWorkerEscape& operator=(const CMiniWorkerEscape&);

public:
  //this is a singleton
	static CMiniWorkerEscape* Instance(){
		static CMiniWorkerEscape instance;

		return &instance;
	}

	virtual void Enter(CMiniWorker* pMiniWorker);

	virtual void Execute(CMiniWorker* pMiniWorker);

	virtual void Exit(CMiniWorker* pMiniWorker);

	virtual bool OnMessage(CMiniWorker* agent, const Telegram& msg);
};

#define MiniWorkerEscape CMiniWorkerEscape::Instance()

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
class CMiniWorkerDie : public CState<CMiniWorker>{
private:  
	CMiniWorkerDie(){}

	//copy ctor and assignment should be private
	CMiniWorkerDie(const CMiniWorkerDie&);
	CMiniWorkerDie& operator=(const CMiniWorkerDie&);
 
public:
  //this is a singleton
	static CMiniWorkerDie* Instance(){
		static CMiniWorkerDie instance;

		return &instance;
	}

	virtual void Enter(CMiniWorker* pMiniWorker);

	virtual void Execute(CMiniWorker* pMiniWorker);

	virtual void Exit(CMiniWorker* pMiniWorker);

	virtual bool OnMessage(CMiniWorker* agent, const Telegram& msg);
};

#define MiniWorkerDie CMiniWorkerDie::Instance()

///////////////////////////////////////////////////////////
// MiniWorkerItemEat State
///////////////////////////////////////////////////////////
class CMiniWorkerItemEat : public CState<CMiniWorker>{
private:  
	CMiniWorkerItemEat(){}

	//copy ctor and assignment should be private
	CMiniWorkerItemEat(const CMiniWorkerItemEat&);
	CMiniWorkerItemEat& operator=(const CMiniWorkerItemEat&);

	float _mouseAngle;
	int _nCount;
 
public:
  //this is a singleton
	static CMiniWorkerItemEat* Instance(){
		static CMiniWorkerItemEat instance;

		return &instance;
	}

	virtual void Enter(CMiniWorker* pMiniWorker);

	virtual void Execute(CMiniWorker* pMiniWorker);

	virtual void Exit(CMiniWorker* pMiniWorker);

	virtual bool OnMessage(CMiniWorker* agent, const Telegram& msg);
};

#define MiniWorkerItemEat CMiniWorkerItemEat::Instance()

#endif