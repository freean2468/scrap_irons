////////////////////////////////////////////////////
// GateKeeper가 가질 상태들
////////////////////////////////////////////////////
#ifndef _GateKeeperOwnedStates_H_
#define _GateKeeperOwnedStates_H_

class CGateKeeper;

///////////////////////////////////////////////////////////
// Ready State
///////////////////////////////////////////////////////////
class CGateKeeperReady : public CState<CGateKeeper>{
private:  
	CGateKeeperReady(){}

	//copy ctor and assignment should be private
	CGateKeeperReady(const CGateKeeperReady&);
	CGateKeeperReady& operator=(const CGateKeeperReady&);

	bool _setTimer;
	bool _destinationArrive;

public:
  //this is a singleton
	static CGateKeeperReady* Instance(){
		static CGateKeeperReady instance;

		return &instance;
	}

	virtual void Enter(CGateKeeper* pGateKeeper);

	virtual void Execute(CGateKeeper* pGateKeeper);

	virtual void Exit(CGateKeeper* pGateKeeper);

	virtual bool OnMessage(CGateKeeper* agent, const Telegram& msg);
};

#define GateKeeperReady CGateKeeperReady::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CGateKeeperEvent : public CState<CGateKeeper>{
private:  
	CGateKeeperEvent(){}

	//copy ctor and assignment should be private
	CGateKeeperEvent(const CGateKeeperEvent&);
	CGateKeeperEvent& operator=(const CGateKeeperEvent&);
 
public:
  //this is a singleton
	static CGateKeeperEvent* Instance(){
		static CGateKeeperEvent instance;

		return &instance;
	}

	virtual void Enter(CGateKeeper* pGateKeeper);

	virtual void Execute(CGateKeeper* pGateKeeper);

	virtual void Exit(CGateKeeper* pGateKeeper);

	virtual bool OnMessage(CGateKeeper* agent, const Telegram& msg);
};

#define GateKeeperEvent CGateKeeperEvent::Instance()

///////////////////////////////////////////////////////////
// Normal Attack State
///////////////////////////////////////////////////////////
class CGateKeeperNormalAttack : public CState<CGateKeeper>{
private:  
	CGateKeeperNormalAttack(){}

	//copy ctor and assignment should be private
	CGateKeeperNormalAttack(const CGateKeeperNormalAttack&);
	CGateKeeperNormalAttack& operator=(const CGateKeeperNormalAttack&);
 
	float _aceX;
	float _moveDistance;
	float _requireDistance;

public:
  //this is a singleton
	static CGateKeeperNormalAttack* Instance(){
		static CGateKeeperNormalAttack instance;

		return &instance;
	}

	virtual void Enter(CGateKeeper* pGateKeeper);

	virtual void Execute(CGateKeeper* pGateKeeper);

	virtual void Exit(CGateKeeper* pGateKeeper);

	virtual bool OnMessage(CGateKeeper* agent, const Telegram& msg);
};

#define GateKeeperNormalAttack CGateKeeperNormalAttack::Instance()

///////////////////////////////////////////////////////////
// Under Attack State
///////////////////////////////////////////////////////////
class CGateKeeperUnderAttack : public CState<CGateKeeper>{
private:  
	CGateKeeperUnderAttack(){}

	//copy ctor and assignment should be private
	CGateKeeperUnderAttack(const CGateKeeperUnderAttack&);
	CGateKeeperUnderAttack& operator=(const CGateKeeperUnderAttack&);
 
	float _aceX;
	float _moveDistance;
	float _requireDistance;

public:
  //this is a singleton
	static CGateKeeperUnderAttack* Instance(){
		static CGateKeeperUnderAttack instance;

		return &instance;
	}

	virtual void Enter(CGateKeeper* pGateKeeper);

	virtual void Execute(CGateKeeper* pGateKeeper);

	virtual void Exit(CGateKeeper* pGateKeeper);

	virtual bool OnMessage(CGateKeeper* agent, const Telegram& msg);
};

#define GateKeeperUnderAttack CGateKeeperUnderAttack::Instance()

///////////////////////////////////////////////////////////
// Side Attack State
///////////////////////////////////////////////////////////
class CGateKeeperSideAttack : public CState<CGateKeeper>{
private:  
	CGateKeeperSideAttack(){}

	//copy ctor and assignment should be private
	CGateKeeperSideAttack(const CGateKeeperSideAttack&);
	CGateKeeperSideAttack& operator=(const CGateKeeperSideAttack&);
 
	float _aceX;
	float _moveDistance;
	float _requireDistance;

public:
  //this is a singleton
	static CGateKeeperSideAttack* Instance(){
		static CGateKeeperSideAttack instance;

		return &instance;
	}

	virtual void Enter(CGateKeeper* pGateKeeper);

	virtual void Execute(CGateKeeper* pGateKeeper);

	virtual void Exit(CGateKeeper* pGateKeeper);

	virtual bool OnMessage(CGateKeeper* agent, const Telegram& msg);
};

#define GateKeeperSideAttack CGateKeeperSideAttack::Instance()

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
class CGateKeeperEscape : public CState<CGateKeeper>{
private:  
	CGateKeeperEscape(){}

	//copy ctor and assignment should be private
	CGateKeeperEscape(const CGateKeeperEscape&);
	CGateKeeperEscape& operator=(const CGateKeeperEscape&);

public:
  //this is a singleton
	static CGateKeeperEscape* Instance(){
		static CGateKeeperEscape instance;

		return &instance;
	}

	virtual void Enter(CGateKeeper* pGateKeeper);

	virtual void Execute(CGateKeeper* pGateKeeper);

	virtual void Exit(CGateKeeper* pGateKeeper);

	virtual bool OnMessage(CGateKeeper* agent, const Telegram& msg);
};

#define GateKeeperEscape CGateKeeperEscape::Instance()

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
class CGateKeeperDie : public CState<CGateKeeper>{
private:  
	CGateKeeperDie(){}

	//copy ctor and assignment should be private
	CGateKeeperDie(const CGateKeeperDie&);
	CGateKeeperDie& operator=(const CGateKeeperDie&);
 
	float _aceX;
	float _aceY;

public:
  //this is a singleton
	static CGateKeeperDie* Instance(){
		static CGateKeeperDie instance;

		return &instance;
	}

	virtual void Enter(CGateKeeper* pGateKeeper);

	virtual void Execute(CGateKeeper* pGateKeeper);

	virtual void Exit(CGateKeeper* pGateKeeper);

	virtual bool OnMessage(CGateKeeper* agent, const Telegram& msg);
};

#define GateKeeperDie CGateKeeperDie::Instance()

#endif