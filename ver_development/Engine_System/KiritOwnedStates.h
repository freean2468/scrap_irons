////////////////////////////////////////////////////
// Kirit가 가질 상태들
////////////////////////////////////////////////////
#ifndef _KiritOwnedStates_H_
#define _KiritOwnedStates_H_

class CKirit;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CKiritUsual : public CState<CKirit>{
private:  
	CKiritUsual(){}

	//copy ctor and assignment should be private
	CKiritUsual(const CKiritUsual&);
	CKiritUsual& operator=(const CKiritUsual&);
 
public:
  //this is a singleton
	static CKiritUsual* Instance(){
		static CKiritUsual instance;

		return &instance;
	}

	virtual void Enter(CKirit* pKirit);

	virtual void Execute(CKirit* pKirit);

	virtual void Exit(CKirit* pKirit);

	virtual bool OnMessage(CKirit* agent, const Telegram& msg);
};

#define KiritUsual CKiritUsual::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CKiritEvent : public CState<CKirit>{
private:  
	CKiritEvent(){}

	//copy ctor and assignment should be private
	CKiritEvent(const CKiritEvent&);
	CKiritEvent& operator=(const CKiritEvent&);
 
public:
  //this is a singleton
	static CKiritEvent* Instance(){
		static CKiritEvent instance;

		return &instance;
	}

	virtual void Enter(CKirit* pKirit);

	virtual void Execute(CKirit* pKirit);

	virtual void Exit(CKirit* pKirit);

	virtual bool OnMessage(CKirit* agent, const Telegram& msg);
};

#define KiritEvent CKiritEvent::Instance()

///////////////////////////////////////////////////////////
// Create State
///////////////////////////////////////////////////////////
class CKiritCreate : public CState<CKirit>{
private:  
	CKiritCreate(){}

	//copy ctor and assignment should be private
	CKiritCreate(const CKiritCreate&);
	CKiritCreate& operator=(const CKiritCreate&);
 
public:
  //this is a singleton
	static CKiritCreate* Instance(){
		static CKiritCreate instance;

		return &instance;
	}

	virtual void Enter(CKirit* pKirit);

	virtual void Execute(CKirit* pKirit);

	virtual void Exit(CKirit* pKirit);

	virtual bool OnMessage(CKirit* agent, const Telegram& msg);
};

#define KiritCreate CKiritCreate::Instance()

///////////////////////////////////////////////////////////
// Not Render State
///////////////////////////////////////////////////////////
class CKiritNotRender : public CState<CKirit>{
private:  
	CKiritNotRender(){}

	//copy ctor and assignment should be private
	CKiritNotRender(const CKiritNotRender&);
	CKiritNotRender& operator=(const CKiritNotRender&);
 
public:
  //this is a singleton
	static CKiritNotRender* Instance(){
		static CKiritNotRender instance;

		return &instance;
	}

	virtual void Enter(CKirit* pKirit);

	virtual void Execute(CKirit* pKirit);

	virtual void Exit(CKirit* pKirit);

	virtual bool OnMessage(CKirit* agent, const Telegram& msg);
};

#define KiritNotRender CKiritNotRender::Instance()

///////////////////////////////////////////////////////////
// Attack State
///////////////////////////////////////////////////////////
class CKiritAttack : public CState<CKirit>{
private:  
	CKiritAttack(){}

	//copy ctor and assignment should be private
	CKiritAttack(const CKiritAttack&);
	CKiritAttack& operator=(const CKiritAttack&);

public:
  //this is a singleton
	static CKiritAttack* Instance(){
		static CKiritAttack instance;

		return &instance;
	}

	virtual void Enter(CKirit* pKirit);

	virtual void Execute(CKirit* pKirit);

	virtual void Exit(CKirit* pKirit);

	virtual bool OnMessage(CKirit* agent, const Telegram& msg);
};

#define KiritAttack CKiritAttack::Instance()

///////////////////////////////////////////////////////////
// Defense State
///////////////////////////////////////////////////////////
class CKiritDefense : public CState<CKirit>{
private:  
	CKiritDefense(){}

	//copy ctor and assignment should be private
	CKiritDefense(const CKiritDefense&);
	CKiritDefense& operator=(const CKiritDefense&);

public:
  //this is a singleton
	static CKiritDefense* Instance(){
		static CKiritDefense instance;

		return &instance;
	}

	virtual void Enter(CKirit* pKirit);

	virtual void Execute(CKirit* pKirit);

	virtual void Exit(CKirit* pKirit);

	virtual bool OnMessage(CKirit* agent, const Telegram& msg);
};

#define KiritDefense CKiritDefense::Instance()

///////////////////////////////////////////////////////////
// RunAway State
///////////////////////////////////////////////////////////
class CKiritRunAway : public CState<CKirit>{
private:  
	CKiritRunAway(){}

	//copy ctor and assignment should be private
	CKiritRunAway(const CKiritRunAway&);
	CKiritRunAway& operator=(const CKiritRunAway&);

public:
  //this is a singleton
	static CKiritRunAway* Instance(){
		static CKiritRunAway instance;

		return &instance;
	}

	virtual void Enter(CKirit* pKirit);

	virtual void Execute(CKirit* pKirit);

	virtual void Exit(CKirit* pKirit);

	virtual bool OnMessage(CKirit* agent, const Telegram& msg);
};

#define KiritRunAway CKiritRunAway::Instance()

///////////////////////////////////////////////////////////
// Shock State
///////////////////////////////////////////////////////////
class CKiritShock : public CState<CKirit>{
private:  
	CKiritShock(){}

	//copy ctor and assignment should be private
	CKiritShock(const CKiritShock&);
	CKiritShock& operator=(const CKiritShock&);
	
	CTimer* _shockTime;

public:
  //this is a singleton
	static CKiritShock* Instance(){
		static CKiritShock instance;

		return &instance;
	}

	virtual void Enter(CKirit* pKirit);

	virtual void Execute(CKirit* pKirit);

	virtual void Exit(CKirit* pKirit);

	virtual bool OnMessage(CKirit* agent, const Telegram& msg);
};

#define KiritShock CKiritShock::Instance()

///////////////////////////////////////////////////////////
// SpringUp State
///////////////////////////////////////////////////////////
class CKiritSpringUp : public CState<CKirit>{
private:  
	CKiritSpringUp(){}

	//copy ctor and assignment should be private
	CKiritSpringUp(const CKiritSpringUp&);
	CKiritSpringUp& operator=(const CKiritSpringUp&);
	
	float _accelarationX;
	float _accelarationY;
	int _boundCount;

public:
  //this is a singleton
	static CKiritSpringUp* Instance(){
		static CKiritSpringUp instance;

		return &instance;
	}

	virtual void Enter(CKirit* pKirit);

	virtual void Execute(CKirit* pKirit);

	virtual void Exit(CKirit* pKirit);

	virtual bool OnMessage(CKirit* agent, const Telegram& msg);
};

#define KiritSpringUp CKiritSpringUp::Instance()

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
class CKiritDie : public CState<CKirit>{
private:  
	CKiritDie(){}

	//copy ctor and assignment should be private
	CKiritDie(const CKiritDie&);
	CKiritDie& operator=(const CKiritDie&);

public:
  //this is a singleton
	static CKiritDie* Instance(){
		static CKiritDie instance;

		return &instance;
	}

	virtual void Enter(CKirit* pKirit);

	virtual void Execute(CKirit* pKirit);

	virtual void Exit(CKirit* pKirit);

	virtual bool OnMessage(CKirit* agent, const Telegram& msg);
};

#define KiritDie CKiritDie::Instance()

#endif