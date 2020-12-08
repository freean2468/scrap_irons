////////////////////////////////////////////////////
// Interact가 가질 상태들
////////////////////////////////////////////////////
#ifndef _InteractOwnedStates_H_
#define _InteractOwnedStates_H_

class CInteract;

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
class CInteractMinimize : public CState<CInteract>{
private:  
	CInteractMinimize(){}

	//copy ctor and assignment should be private
	CInteractMinimize(const CInteractMinimize&);
	CInteractMinimize& operator=(const CInteractMinimize&);
 
public:
  //this is a singleton
	static CInteractMinimize* Instance(){
		static CInteractMinimize instance;

		return &instance;
	}

	virtual void Enter(CInteract* pInteract);

	virtual void Execute(CInteract* pInteract);

	virtual void Exit(CInteract* pInteract);

	virtual bool OnMessage(CInteract* agent, const Telegram& msg);
};

#define InteractMinimize CInteractMinimize::Instance()

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
class CInteractActive : public CState<CInteract>{
private:  
	CInteractActive(){}

	//copy ctor and assignment should be private
	CInteractActive(const CInteractActive&);
	CInteractActive& operator=(const CInteractActive&);
 
public:
  //this is a singleton
	static CInteractActive* Instance(){
		static CInteractActive instance;

		return &instance;
	}

	virtual void Enter(CInteract* pInteract);

	virtual void Execute(CInteract* pInteract);

	virtual void Exit(CInteract* pInteract);

	virtual bool OnMessage(CInteract* agent, const Telegram& msg);
};

#define InteractActive CInteractActive::Instance()

#endif