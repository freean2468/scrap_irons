////////////////////////////////////////////////////
// DustKing가 가질 상태들
////////////////////////////////////////////////////
#ifndef _DustKingOwnedStates_H_
#define _DustKingOwnedStates_H_

class CDustKing;

///////////////////////////////////////////////////////////
// Ready State
///////////////////////////////////////////////////////////
class CDustKingReady : public CState<CDustKing>{
private:  
	CDustKingReady(){}

	//copy ctor and assignment should be private
	CDustKingReady(const CDustKingReady&);
	CDustKingReady& operator=(const CDustKingReady&);

	bool _setTimer;
	bool _destinationArrive;

public:
  //this is a singleton
	static CDustKingReady* Instance(){
		static CDustKingReady instance;

		return &instance;
	}

	virtual void Enter(CDustKing* pDustKing);

	virtual void Execute(CDustKing* pDustKing);

	virtual void Exit(CDustKing* pDustKing);

	virtual bool OnMessage(CDustKing* agent, const Telegram& msg);
};

#define DustKingReady CDustKingReady::Instance()

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
class CDustKingEvent : public CState<CDustKing>{
private:  
	CDustKingEvent(){}

	//copy ctor and assignment should be private
	CDustKingEvent(const CDustKingEvent&);
	CDustKingEvent& operator=(const CDustKingEvent&);
 
public:
  //this is a singleton
	static CDustKingEvent* Instance(){
		static CDustKingEvent instance;

		return &instance;
	}

	virtual void Enter(CDustKing* pDustKing);

	virtual void Execute(CDustKing* pDustKing);

	virtual void Exit(CDustKing* pDustKing);

	virtual bool OnMessage(CDustKing* agent, const Telegram& msg);
};

#define DustKingEvent CDustKingEvent::Instance()

///////////////////////////////////////////////////////////
// Normal Attack State
///////////////////////////////////////////////////////////
class CDustKingNormalAttack : public CState<CDustKing>{
private:  
	CDustKingNormalAttack(){}

	//copy ctor and assignment should be private
	CDustKingNormalAttack(const CDustKingNormalAttack&);
	CDustKingNormalAttack& operator=(const CDustKingNormalAttack&);
 
	float _requireDistance;
	float _moveDistance;

public:
  //this is a singleton
	static CDustKingNormalAttack* Instance(){
		static CDustKingNormalAttack instance;

		return &instance;
	}

	virtual void Enter(CDustKing* pDustKing);

	virtual void Execute(CDustKing* pDustKing);

	virtual void Exit(CDustKing* pDustKing);

	virtual bool OnMessage(CDustKing* agent, const Telegram& msg);
};

#define DustKingNormalAttack CDustKingNormalAttack::Instance()

///////////////////////////////////////////////////////////
// Hand Attack State
///////////////////////////////////////////////////////////
class CDustKingHandAttack : public CState<CDustKing>{
private:  
	CDustKingHandAttack(){}

	//copy ctor and assignment should be private
	CDustKingHandAttack(const CDustKingHandAttack&);
	CDustKingHandAttack& operator=(const CDustKingHandAttack&);
 
	float _requireDistance;
	float _moveDistance;

	D3DXVECTOR3 _vHandOrigin;

public:
  //this is a singleton
	static CDustKingHandAttack* Instance(){
		static CDustKingHandAttack instance;

		return &instance;
	}

	virtual void Enter(CDustKing* pDustKing);

	virtual void Execute(CDustKing* pDustKing);

	virtual void Exit(CDustKing* pDustKing);

	virtual bool OnMessage(CDustKing* agent, const Telegram& msg);
};

#define DustKingHandAttack CDustKingHandAttack::Instance()

///////////////////////////////////////////////////////////
// Dust Attack State
///////////////////////////////////////////////////////////
class CDustKingDustAttack : public CState<CDustKing>{
private:  
	CDustKingDustAttack(){}

	//copy ctor and assignment should be private
	CDustKingDustAttack(const CDustKingDustAttack&);
	CDustKingDustAttack& operator=(const CDustKingDustAttack&);

	CTimer* _timer;
	int _nCount;
	D3DXVECTOR3 _vHandOrigin;

public:
  //this is a singleton
	static CDustKingDustAttack* Instance(){
		static CDustKingDustAttack instance;

		return &instance;
	}

	virtual void Enter(CDustKing* pDustKing);

	virtual void Execute(CDustKing* pDustKing);

	virtual void Exit(CDustKing* pDustKing);

	virtual bool OnMessage(CDustKing* agent, const Telegram& msg);
};

#define DustKingDustAttack CDustKingDustAttack::Instance()

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
class CDustKingEscape : public CState<CDustKing>{
private:  
	CDustKingEscape(){}

	//copy ctor and assignment should be private
	CDustKingEscape(const CDustKingEscape&);
	CDustKingEscape& operator=(const CDustKingEscape&);

public:
  //this is a singleton
	static CDustKingEscape* Instance(){
		static CDustKingEscape instance;

		return &instance;
	}

	virtual void Enter(CDustKing* pDustKing);

	virtual void Execute(CDustKing* pDustKing);

	virtual void Exit(CDustKing* pDustKing);

	virtual bool OnMessage(CDustKing* agent, const Telegram& msg);
};

#define DustKingEscape CDustKingEscape::Instance()

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
class CDustKingDie : public CState<CDustKing>{
private:  
	CDustKingDie(){}

	//copy ctor and assignment should be private
	CDustKingDie(const CDustKingDie&);
	CDustKingDie& operator=(const CDustKingDie&);
 
public:
  //this is a singleton
	static CDustKingDie* Instance(){
		static CDustKingDie instance;

		return &instance;
	}

	virtual void Enter(CDustKing* pDustKing);

	virtual void Execute(CDustKing* pDustKing);

	virtual void Exit(CDustKing* pDustKing);

	virtual bool OnMessage(CDustKing* agent, const Telegram& msg);
};

#define DustKingDie CDustKingDie::Instance()

#endif