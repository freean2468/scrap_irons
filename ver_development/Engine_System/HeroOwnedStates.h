////////////////////////////////////////////////////
// Hero가 가질 상태들
////////////////////////////////////////////////////
#ifndef _HeroOwnedStates_H_
#define _HeroOwnedStates_H_

class CHero;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CHeroStand : public CState<CHero>{
private:  
	CHeroStand(){}

	//copy ctor and assignment should be private
	CHeroStand(const CHeroStand&);
	CHeroStand& operator=(const CHeroStand&);
 
public:
  //this is a singleton
	static CHeroStand* Instance(){
		static CHeroStand instance;

		return &instance;
	}

	virtual void Enter(CHero* pHero);

	virtual void Execute(CHero* pHero);

	virtual void Exit(CHero* pHero);

	virtual bool OnMessage(CHero* agent, const Telegram& msg);
};

#define HeroStand CHeroStand::Instance()


///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CHeroEvent : public CState<CHero>{
private:  
	CHeroEvent(){}

	//copy ctor and assignment should be private
	CHeroEvent(const CHeroEvent&);
	CHeroEvent& operator=(const CHeroEvent&);
 
public:
  //this is a singleton
	static CHeroEvent* Instance(){
		static CHeroEvent instance;

		return &instance;
	}

	virtual void Enter(CHero* pHero);

	virtual void Execute(CHero* pHero);

	virtual void Exit(CHero* pHero);

	virtual bool OnMessage(CHero* agent, const Telegram& msg);
};

#define HeroEvent CHeroEvent::Instance()

///////////////////////////////////////////////////////////
// Pull to Cart State
///////////////////////////////////////////////////////////
class CPullToCart : public CState<CHero>{
private:  
	CPullToCart(){}

	//copy ctor and assignment should be private
	CPullToCart(const CPullToCart&);
	CPullToCart& operator=(const CPullToCart&);
 
public:
  //this is a singleton
	static CPullToCart* Instance(){
		static CPullToCart instance;

		return &instance;
	}

	virtual void Enter(CHero* pHero);

	virtual void Execute(CHero* pHero);

	virtual void Exit(CHero* pHero);

	virtual bool OnMessage(CHero* agent, const Telegram& msg);
};

#define PullToCart CPullToCart::Instance()

///////////////////////////////////////////////////////////
// Shock State
///////////////////////////////////////////////////////////
class CHeroShock : public CState<CHero>{
private:  
	CHeroShock(){}

	//copy ctor and assignment should be private
	CHeroShock(const CHeroShock&);
	CHeroShock& operator=(const CHeroShock&);
	
	CTimer* _shockTime;

public:
  //this is a singleton
	static CHeroShock* Instance(){
		static CHeroShock instance;

		return &instance;
	}

	virtual void Enter(CHero* pHero);

	virtual void Execute(CHero* pHero);

	virtual void Exit(CHero* pHero);

	virtual bool OnMessage(CHero* agent, const Telegram& msg);
};

#define HeroShock CHeroShock::Instance()

///////////////////////////////////////////////////////////
// SpringUp State
///////////////////////////////////////////////////////////
class CHeroSpringUp : public CState<CHero>{
private:  
	CHeroSpringUp(){}

	//copy ctor and assignment should be private
	CHeroSpringUp(const CHeroSpringUp&);
	CHeroSpringUp& operator=(const CHeroSpringUp&);
	
	float _accelarationX;
	float _accelarationY;
	int _boundCount;

public:
  //this is a singleton
	static CHeroSpringUp* Instance(){
		static CHeroSpringUp instance;

		return &instance;
	}

	virtual void Enter(CHero* pHero);

	virtual void Execute(CHero* pHero);

	virtual void Exit(CHero* pHero);

	virtual bool OnMessage(CHero* agent, const Telegram& msg);
};

#define HeroSpringUp CHeroSpringUp::Instance()

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
class CHeroEscape : public CState<CHero>{
private:  
	CHeroEscape(){}

	//copy ctor and assignment should be private
	CHeroEscape(const CHeroEscape&);
	CHeroEscape& operator=(const CHeroEscape&);
 
public:
  //this is a singleton
	static CHeroEscape* Instance(){
		static CHeroEscape instance;

		return &instance;
	}

	virtual void Enter(CHero* pHero);

	virtual void Execute(CHero* pHero);

	virtual void Exit(CHero* pHero);

	virtual bool OnMessage(CHero* agent, const Telegram& msg);
};

#define HeroEscape CHeroEscape::Instance()

#endif