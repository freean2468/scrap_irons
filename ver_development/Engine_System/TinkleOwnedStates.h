////////////////////////////////////////////////////
// Tinkle가 가질 상태들
////////////////////////////////////////////////////
#ifndef _TinkleOwnedStates_H_
#define _TinkleOwnedStates_H_

class CTinkle;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CTinkleUsual : public CState<CTinkle>{
private:  
	CTinkleUsual(){}

	//copy ctor and assignment should be private
	CTinkleUsual(const CTinkleUsual&);
	CTinkleUsual& operator=(const CTinkleUsual&);
 
public:
  //this is a singleton
	static CTinkleUsual* Instance(){
		static CTinkleUsual instance;

		return &instance;
	}

	virtual void Enter(CTinkle* pTinkle);

	virtual void Execute(CTinkle* pTinkle);

	virtual void Exit(CTinkle* pTinkle);

	virtual bool OnMessage(CTinkle* agent, const Telegram& msg);
};

#define TinkleUsual CTinkleUsual::Instance()

///////////////////////////////////////////////////////////
// Stand In Event State
///////////////////////////////////////////////////////////
class CTinkleCreate : public CState<CTinkle>{
private:  
	CTinkleCreate(){}

	//copy ctor and assignment should be private
	CTinkleCreate(const CTinkleCreate&);
	CTinkleCreate& operator=(const CTinkleCreate&);
 
public:
  //this is a singleton
	static CTinkleCreate* Instance(){
		static CTinkleCreate instance;

		return &instance;
	}

	virtual void Enter(CTinkle* pTinkle);

	virtual void Execute(CTinkle* pTinkle);

	virtual void Exit(CTinkle* pTinkle);

	virtual bool OnMessage(CTinkle* agent, const Telegram& msg);
};

#define TinkleCreate CTinkleCreate::Instance()

#endif