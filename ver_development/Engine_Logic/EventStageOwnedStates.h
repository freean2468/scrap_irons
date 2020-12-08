////////////////////////////////////////////////////
// ���� �̺�Ʈ
////////////////////////////////////////////////////
#ifndef _EventStageOwnedStates_H_
#define _EventStageOwnedStates_H_

class CEventStage;

///////////////////////////////////////////////////////////
// ���� ����
///////////////////////////////////////////////////////////
class CEventStageGlobal : public CState<CEventStage>{
private:  
  CEventStageGlobal(){}

  //copy ctor and assignment should be private
  CEventStageGlobal(const CEventStageGlobal&);
  CEventStageGlobal& operator=(const CEventStageGlobal&);
 
public:
  //this is a singleton
	static CEventStageGlobal* Instance(){
		static CEventStageGlobal instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg){return false;}
};

#define EventStageGlobal CEventStageGlobal::Instance()

///////////////////////////////////////////////////////////
// Check ���� 
///////////////////////////////////////////////////////////
class CEventStageCheck : public CState<CEventStage>{
private:  
  CEventStageCheck(){}

  //copy ctor and assignment should be private
  CEventStageCheck(const CEventStageCheck&);
  CEventStageCheck& operator=(const CEventStageCheck&);
 
public:
  //this is a singleton
	static CEventStageCheck* Instance(){
		static CEventStageCheck instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg){return false;}
};

#define EventStageCheck CEventStageCheck::Instance()

///////////////////////////////////////////////////////////
// RunAway ���� 
///////////////////////////////////////////////////////////
class CEventStageRunAway : public CState<CEventStage>{
private:  
  CEventStageRunAway(){}

  //copy ctor and assignment should be private
  CEventStageRunAway(const CEventStageRunAway&);
  CEventStageRunAway& operator=(const CEventStageRunAway&);

  D3DXVECTOR3 _cameraPos;
 
public:
  //this is a singleton
	static CEventStageRunAway* Instance(){
		static CEventStageRunAway instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageRunAway CEventStageRunAway::Instance()

///////////////////////////////////////////////////////////
// ù���� �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageFirstMeeting : public CState<CEventStage>{
private:  
  CEventStageFirstMeeting(){}

  //copy ctor and assignment should be private
  CEventStageFirstMeeting(const CEventStageFirstMeeting&);
  CEventStageFirstMeeting& operator=(const CEventStageFirstMeeting&);
 
public:
  //this is a singleton
	static CEventStageFirstMeeting* Instance(){
		static CEventStageFirstMeeting instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageFirstMeeting CEventStageFirstMeeting::Instance()

///////////////////////////////////////////////////////////
// ù��° Area �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageFirstArea : public CState<CEventStage>{
private:  
  CEventStageFirstArea(){}

  //copy ctor and assignment should be private
  CEventStageFirstArea(const CEventStageFirstArea&);
  CEventStageFirstArea& operator=(const CEventStageFirstArea&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageFirstArea* Instance(){
		static CEventStageFirstArea instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageFirstArea CEventStageFirstArea::Instance()

///////////////////////////////////////////////////////////
// DustDie �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageDustKidDie : public CState<CEventStage>{
private:  
  CEventStageDustKidDie(){}

  //copy ctor and assignment should be private
  CEventStageDustKidDie(const CEventStageDustKidDie&);
  CEventStageDustKidDie& operator=(const CEventStageDustKidDie&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageDustKidDie* Instance(){
		static CEventStageDustKidDie instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageDustKidDie CEventStageDustKidDie::Instance()

///////////////////////////////////////////////////////////
// SecondArea �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageSecondArea : public CState<CEventStage>{
private:  
  CEventStageSecondArea(){}

  //copy ctor and assignment should be private
  CEventStageSecondArea(const CEventStageSecondArea&);
  CEventStageSecondArea& operator=(const CEventStageSecondArea&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageSecondArea* Instance(){
		static CEventStageSecondArea instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageSecondArea CEventStageSecondArea::Instance()

///////////////////////////////////////////////////////////
// ThirdArea �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageThirdArea : public CState<CEventStage>{
private:  
  CEventStageThirdArea(){}

  //copy ctor and assignment should be private
  CEventStageThirdArea(const CEventStageThirdArea&);
  CEventStageThirdArea& operator=(const CEventStageThirdArea&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageThirdArea* Instance(){
		static CEventStageThirdArea instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageThirdArea CEventStageThirdArea::Instance()

///////////////////////////////////////////////////////////
// Worker �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageWorkerDie : public CState<CEventStage>{
private:  
  CEventStageWorkerDie(){}

  //copy ctor and assignment should be private
  CEventStageWorkerDie(const CEventStageWorkerDie&);
  CEventStageWorkerDie& operator=(const CEventStageWorkerDie&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageWorkerDie* Instance(){
		static CEventStageWorkerDie instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageWorkerDie CEventStageWorkerDie::Instance()

///////////////////////////////////////////////////////////
// Furnace �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageFurnace : public CState<CEventStage>{
private:  
  CEventStageFurnace(){}

  //copy ctor and assignment should be private
  CEventStageFurnace(const CEventStageFurnace&);
  CEventStageFurnace& operator=(const CEventStageFurnace&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageFurnace* Instance(){
		static CEventStageFurnace instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageFurnace CEventStageFurnace::Instance()

///////////////////////////////////////////////////////////
// GateKeeper �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageGateKeeperDie : public CState<CEventStage>{
private:  
  CEventStageGateKeeperDie(){}

  //copy ctor and assignment should be private
  CEventStageGateKeeperDie(const CEventStageGateKeeperDie&);
  CEventStageGateKeeperDie& operator=(const CEventStageGateKeeperDie&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageGateKeeperDie* Instance(){
		static CEventStageGateKeeperDie instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageGateKeeperDie CEventStageGateKeeperDie::Instance()

///////////////////////////////////////////////////////////
// Chimney �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageChimney : public CState<CEventStage>{
private:  
  CEventStageChimney(){}

  //copy ctor and assignment should be private
  CEventStageChimney(const CEventStageChimney&);
  CEventStageChimney& operator=(const CEventStageChimney&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageChimney* Instance(){
		static CEventStageChimney instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageChimney CEventStageChimney::Instance()

///////////////////////////////////////////////////////////
// DustBridge �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageDustBridge : public CState<CEventStage>{
private:  
  CEventStageDustBridge(){}

  //copy ctor and assignment should be private
  CEventStageDustBridge(const CEventStageDustBridge&);
  CEventStageDustBridge& operator=(const CEventStageDustBridge&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageDustBridge* Instance(){
		static CEventStageDustBridge instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageDustBridge CEventStageDustBridge::Instance()

///////////////////////////////////////////////////////////
// DustKingDie �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageDustKingDie : public CState<CEventStage>{
private:  
  CEventStageDustKingDie(){}

  //copy ctor and assignment should be private
  CEventStageDustKingDie(const CEventStageDustKingDie&);
  CEventStageDustKingDie& operator=(const CEventStageDustKingDie&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageDustKingDie* Instance(){
		static CEventStageDustKingDie instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageDustKingDie CEventStageDustKingDie::Instance()

///////////////////////////////////////////////////////////
// GoodHopeIntro �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageGoodHopeIntro : public CState<CEventStage>{
private:  
  CEventStageGoodHopeIntro(){}

  //copy ctor and assignment should be private
  CEventStageGoodHopeIntro(const CEventStageGoodHopeIntro&);
  CEventStageGoodHopeIntro& operator=(const CEventStageGoodHopeIntro&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageGoodHopeIntro* Instance(){
		static CEventStageGoodHopeIntro instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageGoodHopeIntro CEventStageGoodHopeIntro::Instance()

///////////////////////////////////////////////////////////
// GoodHope �̺�Ʈ
///////////////////////////////////////////////////////////
class CEventStageGoodHope : public CState<CEventStage>{
private:  
  CEventStageGoodHope(){}

  //copy ctor and assignment should be private
  CEventStageGoodHope(const CEventStageGoodHope&);
  CEventStageGoodHope& operator=(const CEventStageGoodHope&);
 
  D3DXVECTOR3 _cameraPos;

public:
  //this is a singleton
	static CEventStageGoodHope* Instance(){
		static CEventStageGoodHope instance;

		return &instance;
	}

	virtual void Enter(CEventStage* p_pEvent);

	virtual void Execute(CEventStage* p_pEvent);

	virtual void Exit(CEventStage* p_pEvent);

	virtual bool OnMessage(CEventStage* agent, const Telegram& msg);
};

#define EventStageGoodHope CEventStageGoodHope::Instance()

#endif