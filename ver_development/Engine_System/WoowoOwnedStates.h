////////////////////////////////////////////////////
// Woowo가 가질 상태들
////////////////////////////////////////////////////
#ifndef _WoowoOwnedStates_H_
#define _WoowoOwnedStates_H_

class CWoowo;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CWoowoUsual : public CState<CWoowo>{
private:  
	CWoowoUsual(){}

	//copy ctor and assignment should be private
	CWoowoUsual(const CWoowoUsual&);
	CWoowoUsual& operator=(const CWoowoUsual&);
 
public:
  //this is a singleton
	static CWoowoUsual* Instance(){
		static CWoowoUsual instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoUsual CWoowoUsual::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CWoowoEvent : public CState<CWoowo>{
private:  
	CWoowoEvent(){}

	//copy ctor and assignment should be private
	CWoowoEvent(const CWoowoEvent&);
	CWoowoEvent& operator=(const CWoowoEvent&);
 
public:
  //this is a singleton
	static CWoowoEvent* Instance(){
		static CWoowoEvent instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoEvent CWoowoEvent::Instance()

///////////////////////////////////////////////////////////
// Create State
///////////////////////////////////////////////////////////
class CWoowoCreate : public CState<CWoowo>{
private:  
	CWoowoCreate(){}

	//copy ctor and assignment should be private
	CWoowoCreate(const CWoowoCreate&);
	CWoowoCreate& operator=(const CWoowoCreate&);
 
public:
  //this is a singleton
	static CWoowoCreate* Instance(){
		static CWoowoCreate instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoCreate CWoowoCreate::Instance()

///////////////////////////////////////////////////////////
// Not Render State
///////////////////////////////////////////////////////////
class CWoowoNotRender : public CState<CWoowo>{
private:  
	CWoowoNotRender(){}

	//copy ctor and assignment should be private
	CWoowoNotRender(const CWoowoNotRender&);
	CWoowoNotRender& operator=(const CWoowoNotRender&);
 
public:
  //this is a singleton
	static CWoowoNotRender* Instance(){
		static CWoowoNotRender instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoNotRender CWoowoNotRender::Instance()

///////////////////////////////////////////////////////////
// Attack State
///////////////////////////////////////////////////////////
class CWoowoAttack : public CState<CWoowo>{
private:  
	CWoowoAttack(){}

	//copy ctor and assignment should be private
	CWoowoAttack(const CWoowoAttack&);
	CWoowoAttack& operator=(const CWoowoAttack&);

public:
  //this is a singleton
	static CWoowoAttack* Instance(){
		static CWoowoAttack instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoAttack CWoowoAttack::Instance()

///////////////////////////////////////////////////////////
// Defense State
///////////////////////////////////////////////////////////
class CWoowoDefense : public CState<CWoowo>{
private:  
	CWoowoDefense(){}

	//copy ctor and assignment should be private
	CWoowoDefense(const CWoowoDefense&);
	CWoowoDefense& operator=(const CWoowoDefense&);
 
public:
  //this is a singleton
	static CWoowoDefense* Instance(){
		static CWoowoDefense instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoDefense CWoowoDefense::Instance()

///////////////////////////////////////////////////////////
// RunAway State
///////////////////////////////////////////////////////////
class CWoowoRunAway : public CState<CWoowo>{
private:  
	CWoowoRunAway(){}

	//copy ctor and assignment should be private
	CWoowoRunAway(const CWoowoRunAway&);
	CWoowoRunAway& operator=(const CWoowoRunAway&);
 
public:
  //this is a singleton
	static CWoowoRunAway* Instance(){
		static CWoowoRunAway instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoRunAway CWoowoRunAway::Instance()

///////////////////////////////////////////////////////////
// AttackAfter After State
///////////////////////////////////////////////////////////
class CWoowoAttackAfter : public CState<CWoowo>{
private:  
	CWoowoAttackAfter(){}

	//copy ctor and assignment should be private
	CWoowoAttackAfter(const CWoowoAttackAfter&);
	CWoowoAttackAfter& operator=(const CWoowoAttackAfter&);

public:
  //this is a singleton
	static CWoowoAttackAfter* Instance(){
		static CWoowoAttackAfter instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoAttackAfter CWoowoAttackAfter::Instance()

///////////////////////////////////////////////////////////
// Shock State
///////////////////////////////////////////////////////////
class CWoowoShock : public CState<CWoowo>{
private:  
	CWoowoShock(){}

	//copy ctor and assignment should be private
	CWoowoShock(const CWoowoShock&);
	CWoowoShock& operator=(const CWoowoShock&);
	
	CTimer* _shockTime;

public:
  //this is a singleton
	static CWoowoShock* Instance(){
		static CWoowoShock instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoShock CWoowoShock::Instance()

///////////////////////////////////////////////////////////
// SpringUp State
///////////////////////////////////////////////////////////
class CWoowoSpringUp : public CState<CWoowo>{
private:  
	CWoowoSpringUp(){}

	//copy ctor and assignment should be private
	CWoowoSpringUp(const CWoowoSpringUp&);
	CWoowoSpringUp& operator=(const CWoowoSpringUp&);
	
	float _accelarationX;
	float _accelarationY;
	int _boundCount;

public:
  //this is a singleton
	static CWoowoSpringUp* Instance(){
		static CWoowoSpringUp instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoSpringUp CWoowoSpringUp::Instance()

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
class CWoowoDie : public CState<CWoowo>{
private:  
	CWoowoDie(){}

	//copy ctor and assignment should be private
	CWoowoDie(const CWoowoDie&);
	CWoowoDie& operator=(const CWoowoDie&);
 
public:
  //this is a singleton
	static CWoowoDie* Instance(){
		static CWoowoDie instance;

		return &instance;
	}

	virtual void Enter(CWoowo* pWoowo);

	virtual void Execute(CWoowo* pWoowo);

	virtual void Exit(CWoowo* pWoowo);

	virtual bool OnMessage(CWoowo* agent, const Telegram& msg);
};

#define WoowoDie CWoowoDie::Instance()

#endif