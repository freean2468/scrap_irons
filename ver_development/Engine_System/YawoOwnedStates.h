////////////////////////////////////////////////////
// Yawo가 가질 상태들
////////////////////////////////////////////////////
#ifndef _YawoOwnedStates_H_
#define _YawoOwnedStates_H_

class CYawo;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CYawoUsual : public CState<CYawo>{
private:  
	CYawoUsual(){}

	//copy ctor and assignment should be private
	CYawoUsual(const CYawoUsual&);
	CYawoUsual& operator=(const CYawoUsual&);
 
public:
  //this is a singleton
	static CYawoUsual* Instance(){
		static CYawoUsual instance;

		return &instance;
	}

	virtual void Enter(CYawo* pYawo);

	virtual void Execute(CYawo* pYawo);

	virtual void Exit(CYawo* pYawo);

	virtual bool OnMessage(CYawo* agent, const Telegram& msg);
};

#define YawoUsual CYawoUsual::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CYawoEvent : public CState<CYawo>{
private:  
	CYawoEvent(){}

	//copy ctor and assignment should be private
	CYawoEvent(const CYawoEvent&);
	CYawoEvent& operator=(const CYawoEvent&);
 
public:
  //this is a singleton
	static CYawoEvent* Instance(){
		static CYawoEvent instance;

		return &instance;
	}

	virtual void Enter(CYawo* pYawo);

	virtual void Execute(CYawo* pYawo);

	virtual void Exit(CYawo* pYawo);

	virtual bool OnMessage(CYawo* agent, const Telegram& msg);
};

#define YawoEvent CYawoEvent::Instance()

///////////////////////////////////////////////////////////
// Create State
///////////////////////////////////////////////////////////
class CYawoCreate : public CState<CYawo>{
private:  
	CYawoCreate(){}

	//copy ctor and assignment should be private
	CYawoCreate(const CYawoCreate&);
	CYawoCreate& operator=(const CYawoCreate&);
 
public:
  //this is a singleton
	static CYawoCreate* Instance(){
		static CYawoCreate instance;

		return &instance;
	}

	virtual void Enter(CYawo* pYawo);

	virtual void Execute(CYawo* pYawo);

	virtual void Exit(CYawo* pYawo);

	virtual bool OnMessage(CYawo* agent, const Telegram& msg);
};

#define YawoCreate CYawoCreate::Instance()

///////////////////////////////////////////////////////////
// Not Render State
///////////////////////////////////////////////////////////
class CYawoNotRender : public CState<CYawo>{
private:  
	CYawoNotRender(){}

	//copy ctor and assignment should be private
	CYawoNotRender(const CYawoNotRender&);
	CYawoNotRender& operator=(const CYawoNotRender&);
 
public:
  //this is a singleton
	static CYawoNotRender* Instance(){
		static CYawoNotRender instance;

		return &instance;
	}

	virtual void Enter(CYawo* pYawo);

	virtual void Execute(CYawo* pYawo);

	virtual void Exit(CYawo* pYawo);

	virtual bool OnMessage(CYawo* agent, const Telegram& msg);
};

#define YawoNotRender CYawoNotRender::Instance()

///////////////////////////////////////////////////////////
// Attack State
///////////////////////////////////////////////////////////
class CYawoAttack : public CState<CYawo>{
private:  
	CYawoAttack(){}

	//copy ctor and assignment should be private
	CYawoAttack(const CYawoAttack&);
	CYawoAttack& operator=(const CYawoAttack&);

public:
  //this is a singleton
	static CYawoAttack* Instance(){
		static CYawoAttack instance;

		return &instance;
	}

	virtual void Enter(CYawo* pYawo);

	virtual void Execute(CYawo* pYawo);

	virtual void Exit(CYawo* pYawo);

	virtual bool OnMessage(CYawo* agent, const Telegram& msg);
};

#define YawoAttack CYawoAttack::Instance()

///////////////////////////////////////////////////////////
// Defense State
///////////////////////////////////////////////////////////
class CYawoDefense : public CState<CYawo>{
private:  
	CYawoDefense(){}

	//copy ctor and assignment should be private
	CYawoDefense(const CYawoDefense&);
	CYawoDefense& operator=(const CYawoDefense&);

public:
  //this is a singleton
	static CYawoDefense* Instance(){
		static CYawoDefense instance;

		return &instance;
	}

	virtual void Enter(CYawo* pYawo);

	virtual void Execute(CYawo* pYawo);

	virtual void Exit(CYawo* pYawo);

	virtual bool OnMessage(CYawo* agent, const Telegram& msg);
};

#define YawoDefense CYawoDefense::Instance()

///////////////////////////////////////////////////////////
// RunAway State
///////////////////////////////////////////////////////////
class CYawoRunAway : public CState<CYawo>{
private:  
	CYawoRunAway(){}

	//copy ctor and assignment should be private
	CYawoRunAway(const CYawoRunAway&);
	CYawoRunAway& operator=(const CYawoRunAway&);

public:
  //this is a singleton
	static CYawoRunAway* Instance(){
		static CYawoRunAway instance;

		return &instance;
	}

	virtual void Enter(CYawo* pYawo);

	virtual void Execute(CYawo* pYawo);

	virtual void Exit(CYawo* pYawo);

	virtual bool OnMessage(CYawo* agent, const Telegram& msg);
};

#define YawoRunAway CYawoRunAway::Instance()

///////////////////////////////////////////////////////////
// Shock State
///////////////////////////////////////////////////////////
class CYawoShock : public CState<CYawo>{
private:  
	CYawoShock(){}

	//copy ctor and assignment should be private
	CYawoShock(const CYawoShock&);
	CYawoShock& operator=(const CYawoShock&);
	
	CTimer* _shockTime;

public:
  //this is a singleton
	static CYawoShock* Instance(){
		static CYawoShock instance;

		return &instance;
	}

	virtual void Enter(CYawo* pYawo);

	virtual void Execute(CYawo* pYawo);

	virtual void Exit(CYawo* pYawo);

	virtual bool OnMessage(CYawo* agent, const Telegram& msg);
};

#define YawoShock CYawoShock::Instance()

///////////////////////////////////////////////////////////
// SpringUp State
///////////////////////////////////////////////////////////
class CYawoSpringUp : public CState<CYawo>{
private:  
	CYawoSpringUp(){}

	//copy ctor and assignment should be private
	CYawoSpringUp(const CYawoSpringUp&);
	CYawoSpringUp& operator=(const CYawoSpringUp&);
	
	float _accelarationX;
	float _accelarationY;
	int _boundCount;

public:
  //this is a singleton
	static CYawoSpringUp* Instance(){
		static CYawoSpringUp instance;

		return &instance;
	}

	virtual void Enter(CYawo* pYawo);

	virtual void Execute(CYawo* pYawo);

	virtual void Exit(CYawo* pYawo);

	virtual bool OnMessage(CYawo* agent, const Telegram& msg);
};

#define YawoSpringUp CYawoSpringUp::Instance()

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
class CYawoDie : public CState<CYawo>{
private:  
	CYawoDie(){}

	//copy ctor and assignment should be private
	CYawoDie(const CYawoDie&);
	CYawoDie& operator=(const CYawoDie&);

public:
  //this is a singleton
	static CYawoDie* Instance(){
		static CYawoDie instance;

		return &instance;
	}

	virtual void Enter(CYawo* pYawo);

	virtual void Execute(CYawo* pYawo);

	virtual void Exit(CYawo* pYawo);

	virtual bool OnMessage(CYawo* agent, const Telegram& msg);
};

#define YawoDie CYawoDie::Instance()

#endif