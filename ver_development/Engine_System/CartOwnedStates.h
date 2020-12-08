////////////////////////////////////////////////////
// Cart가 가질 상태들
////////////////////////////////////////////////////
#ifndef _CartOwnedStates_H_
#define _CartOwnedStates_H_

class CCart;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CCartUsual : public CState<CCart>{
private:  
	CCartUsual(){}

	//copy ctor and assignment should be private
	CCartUsual(const CCartUsual&);
	CCartUsual& operator=(const CCartUsual&);
 
public:
  //this is a singleton
	static CCartUsual* Instance(){
		static CCartUsual instance;

		return &instance;
	}

	virtual void Enter(CCart* pCart);

	virtual void Execute(CCart* pCart);

	virtual void Exit(CCart* pCart);

	virtual bool OnMessage(CCart* agent, const Telegram& msg);
};

#define CartUsual CCartUsual::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CCartEvent : public CState<CCart>{
private:  
	CCartEvent(){}

	//copy ctor and assignment should be private
	CCartEvent(const CCartEvent&);
	CCartEvent& operator=(const CCartEvent&);
 
public:
  //this is a singleton
	static CCartEvent* Instance(){
		static CCartEvent instance;

		return &instance;
	}

	virtual void Enter(CCart* pCart);

	virtual void Execute(CCart* pCart);

	virtual void Exit(CCart* pCart);

	virtual bool OnMessage(CCart* agent, const Telegram& msg);
};

#define CartEvent CCartEvent::Instance()

///////////////////////////////////////////////////////////
// Hero에 의해 끌릴 때
///////////////////////////////////////////////////////////
class CPulledByHero : public CState<CCart>{
private:  
	CPulledByHero(){}

	//copy ctor and assignment should be private
	CPulledByHero(const CPulledByHero&);
	CPulledByHero& operator=(const CPulledByHero&);
 
public:
  //this is a singleton
	static CPulledByHero* Instance(){
		static CPulledByHero instance;

		return &instance;
	}

	virtual void Enter(CCart* pCart);

	virtual void Execute(CCart* pCart);

	virtual void Exit(CCart* pCart);

	virtual bool OnMessage(CCart* agent, const Telegram& msg);
};

#define PulledByHero CPulledByHero::Instance()

#endif