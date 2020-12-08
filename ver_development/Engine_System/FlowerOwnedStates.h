////////////////////////////////////////////////////
// Flower가 가질 상태들
////////////////////////////////////////////////////
#ifndef _FlowerOwnedStates_H_
#define _FlowerOwnedStates_H_

class CFlower;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CFlowerUsual : public CState<CFlower>{
private:  
	CFlowerUsual(){}

	//copy ctor and assignment should be private
	CFlowerUsual(const CFlowerUsual&);
	CFlowerUsual& operator=(const CFlowerUsual&);
 
public:
  //this is a singleton
	static CFlowerUsual* Instance(){
		static CFlowerUsual instance;

		return &instance;
	}

	virtual void Enter(CFlower* pFlower);

	virtual void Execute(CFlower* pFlower);

	virtual void Exit(CFlower* pFlower);

	virtual bool OnMessage(CFlower* agent, const Telegram& msg);
};

#define FlowerUsual CFlowerUsual::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CFlowerEvent : public CState<CFlower>{
private:  
	CFlowerEvent(){}

	//copy ctor and assignment should be private
	CFlowerEvent(const CFlowerEvent&);
	CFlowerEvent& operator=(const CFlowerEvent&);
 
public:
  //this is a singleton
	static CFlowerEvent* Instance(){
		static CFlowerEvent instance;

		return &instance;
	}

	virtual void Enter(CFlower* pFlower);

	virtual void Execute(CFlower* pFlower);

	virtual void Exit(CFlower* pFlower);

	virtual bool OnMessage(CFlower* agent, const Telegram& msg);
};

#define FlowerEvent CFlowerEvent::Instance()

///////////////////////////////////////////////////////////
// FlowerMove State
///////////////////////////////////////////////////////////
class CFlowerMove : public CState<CFlower>{
private:  
	CFlowerMove(){}

	//copy ctor and assignment should be private
	CFlowerMove(const CFlowerMove&);
	CFlowerMove& operator=(const CFlowerMove&);
 
public:
  //this is a singleton
	static CFlowerMove* Instance(){
		static CFlowerMove instance;

		return &instance;
	}

	virtual void Enter(CFlower* pFlower);

	virtual void Execute(CFlower* pFlower);

	virtual void Exit(CFlower* pFlower);

	virtual bool OnMessage(CFlower* agent, const Telegram& msg);
};

#define FlowerMove CFlowerMove::Instance()

#endif