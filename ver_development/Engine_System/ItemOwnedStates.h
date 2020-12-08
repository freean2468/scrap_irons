////////////////////////////////////////////////////
// Item이 가질 상태들
////////////////////////////////////////////////////
#ifndef _ItemOwnedStates_H_
#define _ItemOwnedStates_H_

class CItem;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CItemUsual : public CState<CItem>{
private:  
	CItemUsual(){}

	//copy ctor and assignment should be private
	CItemUsual(const CItemUsual&);
	CItemUsual& operator=(const CItemUsual&);
 
public:
  //this is a singleton
	static CItemUsual* Instance(){
		static CItemUsual instance;

		return &instance;
	}

	virtual void Enter(CItem* pItem);

	virtual void Execute(CItem* pItem);

	virtual void Exit(CItem* pItem);

	virtual bool OnMessage(CItem* agent, const Telegram& msg);
};

#define ItemUsual CItemUsual::Instance()

///////////////////////////////////////////////////////////
// Get State
///////////////////////////////////////////////////////////
class CItemGet : public CState<CItem>{
private:
	float _fYVelocity;
	float _fXVelocity;
	float _fVelocity;

private:  
	CItemGet(){}

	//copy ctor and assignment should be private
	CItemGet(const CItemGet&);
	CItemGet& operator=(const CItemGet&);
 
public:
  //this is a singleton
	static CItemGet* Instance(){
		static CItemGet instance;

		return &instance;
	}

	virtual void Enter(CItem* pItem);

	virtual void Execute(CItem* pItem);

	virtual void Exit(CItem* pItem);

	virtual bool OnMessage(CItem* agent, const Telegram& msg);
};

#define ItemGet CItemGet::Instance()

///////////////////////////////////////////////////////////
// InInven State
///////////////////////////////////////////////////////////
class CItemInInven : public CState<CItem>{
private:  
	CItemInInven(){}

	//copy ctor and assignment should be private
	CItemInInven(const CItemInInven&);
	CItemInInven& operator=(const CItemInInven&);
 
public:
  //this is a singleton
	static CItemInInven* Instance(){
		static CItemInInven instance;

		return &instance;
	}

	virtual void Enter(CItem* pItem);

	virtual void Execute(CItem* pItem);

	virtual void Exit(CItem* pItem);

	virtual bool OnMessage(CItem* agent, const Telegram& msg);
};

#define ItemInInven CItemInInven::Instance()

///////////////////////////////////////////////////////////
// Destroyed State
///////////////////////////////////////////////////////////
class CItemDestroyed : public CState<CItem>{
private:
	float _fYVelocity;
	float _fXVelocity;

private:  
	CItemDestroyed(){}

	//copy ctor and assignment should be private
	CItemDestroyed(const CItemDestroyed&);
	CItemDestroyed& operator=(const CItemDestroyed&);
 
public:
  //this is a singleton
	static CItemDestroyed* Instance(){
		static CItemDestroyed instance;

		return &instance;
	}

	virtual void Enter(CItem* pItem);

	virtual void Execute(CItem* pItem);

	virtual void Exit(CItem* pItem);

	virtual bool OnMessage(CItem* agent, const Telegram& msg);
};

#define ItemDestroyed CItemDestroyed::Instance()

#endif