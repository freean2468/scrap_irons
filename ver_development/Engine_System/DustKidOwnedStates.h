////////////////////////////////////////////////////
// DustKid가 가질 상태들
////////////////////////////////////////////////////
#ifndef _DustKidOwnedStates_H_
#define _DustKidOwnedStates_H_

class CDustKid;

///////////////////////////////////////////////////////////
// Ready State
///////////////////////////////////////////////////////////
class CDustKidReady : public CState<CDustKid>{
private:  
	CDustKidReady(){}

	//copy ctor and assignment should be private
	CDustKidReady(const CDustKidReady&);
	CDustKidReady& operator=(const CDustKidReady&);

	bool _setTimer;
	bool _destinationArrive;

public:
  //this is a singleton
	static CDustKidReady* Instance(){
		static CDustKidReady instance;

		return &instance;
	}

	virtual void Enter(CDustKid* pDustKid);

	virtual void Execute(CDustKid* pDustKid);

	virtual void Exit(CDustKid* pDustKid);

	virtual bool OnMessage(CDustKid* agent, const Telegram& msg);
};

#define DustKidReady CDustKidReady::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CDustKidEvent : public CState<CDustKid>{
private:  
	CDustKidEvent(){}

	//copy ctor and assignment should be private
	CDustKidEvent(const CDustKidEvent&);
	CDustKidEvent& operator=(const CDustKidEvent&);
 
public:
  //this is a singleton
	static CDustKidEvent* Instance(){
		static CDustKidEvent instance;

		return &instance;
	}

	virtual void Enter(CDustKid* pDustKid);

	virtual void Execute(CDustKid* pDustKid);

	virtual void Exit(CDustKid* pDustKid);

	virtual bool OnMessage(CDustKid* agent, const Telegram& msg);
};

#define DustKidEvent CDustKidEvent::Instance()

///////////////////////////////////////////////////////////
// Normal Attack State
///////////////////////////////////////////////////////////
class CDustKidNormalAttack : public CState<CDustKid>{
private:  
	CDustKidNormalAttack(){}

	//copy ctor and assignment should be private
	CDustKidNormalAttack(const CDustKidNormalAttack&);
	CDustKidNormalAttack& operator=(const CDustKidNormalAttack&);

	float _requireDistance;

public:
  //this is a singleton
	static CDustKidNormalAttack* Instance(){
		static CDustKidNormalAttack instance;

		return &instance;
	}

	virtual void Enter(CDustKid* pDustKid);

	virtual void Execute(CDustKid* pDustKid);

	virtual void Exit(CDustKid* pDustKid);

	virtual bool OnMessage(CDustKid* agent, const Telegram& msg);
};

#define DustKidNormalAttack CDustKidNormalAttack::Instance()

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
class CDustKidEscape : public CState<CDustKid>{
private:  
	CDustKidEscape(){}

	//copy ctor and assignment should be private
	CDustKidEscape(const CDustKidEscape&);
	CDustKidEscape& operator=(const CDustKidEscape&);

public:
  //this is a singleton
	static CDustKidEscape* Instance(){
		static CDustKidEscape instance;

		return &instance;
	}

	virtual void Enter(CDustKid* pDustKid);

	virtual void Execute(CDustKid* pDustKid);

	virtual void Exit(CDustKid* pDustKid);

	virtual bool OnMessage(CDustKid* agent, const Telegram& msg);
};

#define DustKidEscape CDustKidEscape::Instance()

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
class CDustKidDie : public CState<CDustKid>{
private:  
	CDustKidDie(){}

	//copy ctor and assignment should be private
	CDustKidDie(const CDustKidDie&);
	CDustKidDie& operator=(const CDustKidDie&);
 
public:
  //this is a singleton
	static CDustKidDie* Instance(){
		static CDustKidDie instance;

		return &instance;
	}

	virtual void Enter(CDustKid* pDustKid);

	virtual void Execute(CDustKid* pDustKid);

	virtual void Exit(CDustKid* pDustKid);

	virtual bool OnMessage(CDustKid* agent, const Telegram& msg);
};

#define DustKidDie CDustKidDie::Instance()

#endif