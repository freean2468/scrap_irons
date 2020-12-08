////////////////////////////////////////////////////
// Wagoo가 가질 상태들
////////////////////////////////////////////////////
#ifndef _WagooOwnedStates_H_
#define _WagooOwnedStates_H_

class CWagoo;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CWagooUsual : public CState<CWagoo>{
private:  
	CWagooUsual(){}

	//copy ctor and assignment should be private
	CWagooUsual(const CWagooUsual&);
	CWagooUsual& operator=(const CWagooUsual&);
 
public:
  //this is a singleton
	static CWagooUsual* Instance(){
		static CWagooUsual instance;

		return &instance;
	}

	virtual void Enter(CWagoo* pWagoo);

	virtual void Execute(CWagoo* pWagoo);

	virtual void Exit(CWagoo* pWagoo);

	virtual bool OnMessage(CWagoo* agent, const Telegram& msg);
};

#define WagooUsual CWagooUsual::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CWagooEvent : public CState<CWagoo>{
private:  
	CWagooEvent(){}

	//copy ctor and assignment should be private
	CWagooEvent(const CWagooEvent&);
	CWagooEvent& operator=(const CWagooEvent&);
 
public:
  //this is a singleton
	static CWagooEvent* Instance(){
		static CWagooEvent instance;

		return &instance;
	}

	virtual void Enter(CWagoo* pWagoo);

	virtual void Execute(CWagoo* pWagoo);

	virtual void Exit(CWagoo* pWagoo);

	virtual bool OnMessage(CWagoo* agent, const Telegram& msg);
};

#define WagooEvent CWagooEvent::Instance()

///////////////////////////////////////////////////////////
// Create State
///////////////////////////////////////////////////////////
class CWagooCreate : public CState<CWagoo>{
private:  
	CWagooCreate(){}

	//copy ctor and assignment should be private
	CWagooCreate(const CWagooCreate&);
	CWagooCreate& operator=(const CWagooCreate&);
 
public:
  //this is a singleton
	static CWagooCreate* Instance(){
		static CWagooCreate instance;

		return &instance;
	}

	virtual void Enter(CWagoo* pWagoo);

	virtual void Execute(CWagoo* pWagoo);

	virtual void Exit(CWagoo* pWagoo);

	virtual bool OnMessage(CWagoo* agent, const Telegram& msg);
};

#define WagooCreate CWagooCreate::Instance()

///////////////////////////////////////////////////////////
// Not Render State
///////////////////////////////////////////////////////////
class CWagooNotRender : public CState<CWagoo>{
private:  
	CWagooNotRender(){}

	//copy ctor and assignment should be private
	CWagooNotRender(const CWagooNotRender&);
	CWagooNotRender& operator=(const CWagooNotRender&);
 
public:
  //this is a singleton
	static CWagooNotRender* Instance(){
		static CWagooNotRender instance;

		return &instance;
	}

	virtual void Enter(CWagoo* pWagoo);

	virtual void Execute(CWagoo* pWagoo);

	virtual void Exit(CWagoo* pWagoo);

	virtual bool OnMessage(CWagoo* agent, const Telegram& msg);
};

#define WagooNotRender CWagooNotRender::Instance()

///////////////////////////////////////////////////////////
// Attack State
///////////////////////////////////////////////////////////
class CWagooAttack : public CState<CWagoo>{
private:  
	CWagooAttack(){}

	//copy ctor and assignment should be private
	CWagooAttack(const CWagooAttack&);
	CWagooAttack& operator=(const CWagooAttack&);

public:
  //this is a singleton
	static CWagooAttack* Instance(){
		static CWagooAttack instance;

		return &instance;
	}

	virtual void Enter(CWagoo* pWagoo);

	virtual void Execute(CWagoo* pWagoo);

	virtual void Exit(CWagoo* pWagoo);

	virtual bool OnMessage(CWagoo* agent, const Telegram& msg);
};

#define WagooAttack CWagooAttack::Instance()

///////////////////////////////////////////////////////////
// Defense State
///////////////////////////////////////////////////////////
class CWagooDefense : public CState<CWagoo>{
private:  
	CWagooDefense(){}

	//copy ctor and assignment should be private
	CWagooDefense(const CWagooDefense&);
	CWagooDefense& operator=(const CWagooDefense&);

public:
  //this is a singleton
	static CWagooDefense* Instance(){
		static CWagooDefense instance;

		return &instance;
	}

	virtual void Enter(CWagoo* pWagoo);

	virtual void Execute(CWagoo* pWagoo);

	virtual void Exit(CWagoo* pWagoo);

	virtual bool OnMessage(CWagoo* agent, const Telegram& msg);
};

#define WagooDefense CWagooDefense::Instance()

///////////////////////////////////////////////////////////
// RunAway State
///////////////////////////////////////////////////////////
class CWagooRunAway : public CState<CWagoo>{
private:  
	CWagooRunAway(){}

	//copy ctor and assignment should be private
	CWagooRunAway(const CWagooRunAway&);
	CWagooRunAway& operator=(const CWagooRunAway&);

public:
  //this is a singleton
	static CWagooRunAway* Instance(){
		static CWagooRunAway instance;

		return &instance;
	}

	virtual void Enter(CWagoo* pWagoo);

	virtual void Execute(CWagoo* pWagoo);

	virtual void Exit(CWagoo* pWagoo);

	virtual bool OnMessage(CWagoo* agent, const Telegram& msg);
};

#define WagooRunAway CWagooRunAway::Instance()

///////////////////////////////////////////////////////////
// Shock State
///////////////////////////////////////////////////////////
class CWagooShock : public CState<CWagoo>{
private:  
	CWagooShock(){}

	//copy ctor and assignment should be private
	CWagooShock(const CWagooShock&);
	CWagooShock& operator=(const CWagooShock&);
	
	CTimer* _shockTime;

public:
  //this is a singleton
	static CWagooShock* Instance(){
		static CWagooShock instance;

		return &instance;
	}

	virtual void Enter(CWagoo* pWagoo);

	virtual void Execute(CWagoo* pWagoo);

	virtual void Exit(CWagoo* pWagoo);

	virtual bool OnMessage(CWagoo* agent, const Telegram& msg);
};

#define WagooShock CWagooShock::Instance()

///////////////////////////////////////////////////////////
// SpringUp State
///////////////////////////////////////////////////////////
class CWagooSpringUp : public CState<CWagoo>{
private:  
	CWagooSpringUp(){}

	//copy ctor and assignment should be private
	CWagooSpringUp(const CWagooSpringUp&);
	CWagooSpringUp& operator=(const CWagooSpringUp&);
	
	float _accelarationX;
	float _accelarationY;
	int _boundCount;

public:
  //this is a singleton
	static CWagooSpringUp* Instance(){
		static CWagooSpringUp instance;

		return &instance;
	}

	virtual void Enter(CWagoo* pWagoo);

	virtual void Execute(CWagoo* pWagoo);

	virtual void Exit(CWagoo* pWagoo);

	virtual bool OnMessage(CWagoo* agent, const Telegram& msg);
};

#define WagooSpringUp CWagooSpringUp::Instance()

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
class CWagooDie : public CState<CWagoo>{
private:  
	CWagooDie(){}

	//copy ctor and assignment should be private
	CWagooDie(const CWagooDie&);
	CWagooDie& operator=(const CWagooDie&);

public:
  //this is a singleton
	static CWagooDie* Instance(){
		static CWagooDie instance;

		return &instance;
	}

	virtual void Enter(CWagoo* pWagoo);

	virtual void Execute(CWagoo* pWagoo);

	virtual void Exit(CWagoo* pWagoo);

	virtual bool OnMessage(CWagoo* agent, const Telegram& msg);
};

#define WagooDie CWagooDie::Instance()

#endif