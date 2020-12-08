////////////////////////////////////////////////////
// Section�� ���� ���µ�
////////////////////////////////////////////////////
#ifndef _SectionOwnedStates_H_
#define _SectionOwnedStates_H_

class CSection;

///////////////////////////////////////////////////////////
// �ΰ� �����ֱ� ����
///////////////////////////////////////////////////////////
class CLogoShow : public CState<CSection>{
private:  
  CLogoShow(){}

  //copy ctor and assignment should be private
  CLogoShow(const CLogoShow&);
  CLogoShow& operator=(const CLogoShow&);
 
public:
  //this is a singleton
	static CLogoShow* Instance(){
		static CLogoShow instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define LogoShow CLogoShow::Instance()

///////////////////////////////////////////////////////////
// ���θ޴� ����
///////////////////////////////////////////////////////////
class CMainMenuPart : public CState<CSection>{
private:  
  CMainMenuPart(){}

  //copy ctor and assignment should be private
  CMainMenuPart(const CMainMenuPart&);
  CMainMenuPart& operator=(const CMainMenuPart&);
 
public:
  //this is a singleton
	static CMainMenuPart* Instance(){
		static CMainMenuPart instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define MainMenu CMainMenuPart::Instance()

///////////////////////////////////////////////////////////
// Intro ����
///////////////////////////////////////////////////////////
class CIntroShow : public CState<CSection>{
private:  
  CIntroShow(){}

  //copy ctor and assignment should be private
  CIntroShow(const CIntroShow&);
  CIntroShow& operator=(const CIntroShow&);
 
public:
  //this is a singleton
	static CIntroShow* Instance(){
		static CIntroShow instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define IntroShow CIntroShow::Instance()

///////////////////////////////////////////////////////////
// ���� �����ֱ� ����
///////////////////////////////////////////////////////////
class CWorldMapShow : public CState<CSection>{
private:  
  CWorldMapShow(){}

  //copy ctor and assignment should be private
  CWorldMapShow(const CWorldMapShow&);
  CWorldMapShow& operator=(const CWorldMapShow&);
 
public:
  //this is a singleton
	static CWorldMapShow* Instance(){
		static CWorldMapShow instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define WorldMapShow CWorldMapShow::Instance()

///////////////////////////////////////////////////////////
// Area Selection ����
///////////////////////////////////////////////////////////
class CAreaSelection : public CState<CSection>{
private:  
  CAreaSelection(){}

  //copy ctor and assignment should be private
  CAreaSelection(const CAreaSelection&);
  CAreaSelection& operator=(const CAreaSelection&);
 
public:
  //this is a singleton
	static CAreaSelection* Instance(){
		static CAreaSelection instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define AreaSelection CAreaSelection::Instance()

///////////////////////////////////////////////////////////
// Stage::Home Show ����
///////////////////////////////////////////////////////////
class CStageHomeShow : public CState<CSection>{
private:  
  CStageHomeShow(){}

  //copy ctor and assignment should be private
  CStageHomeShow(const CStageHomeShow&);
  CStageHomeShow& operator=(const CStageHomeShow&);
 
public:
  //this is a singleton
	static CStageHomeShow* Instance(){
		static CStageHomeShow instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define StageHomeShow CStageHomeShow::Instance()

///////////////////////////////////////////////////////////
// Stage::Mountain Show ����
///////////////////////////////////////////////////////////
class CStageMountainShow : public CState<CSection>{
private:  
  CStageMountainShow(){}

  //copy ctor and assignment should be private
  CStageMountainShow(const CStageMountainShow&);
  CStageMountainShow& operator=(const CStageMountainShow&);
 
public:
  //this is a singleton
	static CStageMountainShow* Instance(){
		static CStageMountainShow instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define StageMountainShow CStageMountainShow::Instance()

///////////////////////////////////////////////////////////
// Stage::Furnace Show ����
///////////////////////////////////////////////////////////
class CStageFurnaceShow : public CState<CSection>{
private:  
  CStageFurnaceShow(){}

  //copy ctor and assignment should be private
  CStageFurnaceShow(const CStageFurnaceShow&);
  CStageFurnaceShow& operator=(const CStageFurnaceShow&);
 
public:
  //this is a singleton
	static CStageFurnaceShow* Instance(){
		static CStageFurnaceShow instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define StageFurnaceShow CStageFurnaceShow::Instance()

///////////////////////////////////////////////////////////
// Stage::Chimney Show ����
///////////////////////////////////////////////////////////
class CStageChimneyShow : public CState<CSection>{
private:  
  CStageChimneyShow(){}

  //copy ctor and assignment should be private
  CStageChimneyShow(const CStageChimneyShow&);
  CStageChimneyShow& operator=(const CStageChimneyShow&);
 
public:
  //this is a singleton
	static CStageChimneyShow* Instance(){
		static CStageChimneyShow instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define StageChimneyShow CStageChimneyShow::Instance()

///////////////////////////////////////////////////////////
// Stage::DustBridge Show ����
///////////////////////////////////////////////////////////
class CStageDustBridgeShow : public CState<CSection>{
private:  
  CStageDustBridgeShow(){}

  //copy ctor and assignment should be private
  CStageDustBridgeShow(const CStageDustBridgeShow&);
  CStageDustBridgeShow& operator=(const CStageDustBridgeShow&);
 
public:
  //this is a singleton
	static CStageDustBridgeShow* Instance(){
		static CStageDustBridgeShow instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define StageDustBridgeShow CStageDustBridgeShow::Instance()

///////////////////////////////////////////////////////////
// Stage::GoodHope Show ����
///////////////////////////////////////////////////////////
class CStageGoodHopeShow : public CState<CSection>{
private:  
  CStageGoodHopeShow(){}

  //copy ctor and assignment should be private
  CStageGoodHopeShow(const CStageGoodHopeShow&);
  CStageGoodHopeShow& operator=(const CStageGoodHopeShow&);
 
public:
  //this is a singleton
	static CStageGoodHopeShow* Instance(){
		static CStageGoodHopeShow instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define StageGoodHopeShow CStageGoodHopeShow::Instance()

///////////////////////////////////////////////////////////
// ���� �� ����
///////////////////////////////////////////////////////////
class CGameEnd : public CState<CSection>{
private:  
  CGameEnd(){}

  //copy ctor and assignment should be private
  CGameEnd(const CGameEnd&);
  CGameEnd& operator=(const CGameEnd&);
 
public:
  //this is a singleton
	static CGameEnd* Instance(){
		static CGameEnd instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define GameEnd CGameEnd::Instance()

///////////////////////////////////////////////////////////
// Ending
///////////////////////////////////////////////////////////
class CEndingShow : public CState<CSection>{
private:  
  CEndingShow(){}

  //copy ctor and assignment should be private
  CEndingShow(const CEndingShow&);
  CEndingShow& operator=(const CEndingShow&);
 
public:
  //this is a singleton
	static CEndingShow* Instance(){
		static CEndingShow instance;

		return &instance;
	}

	virtual void Enter(CSection* pSection);

	virtual void Execute(CSection* pSection);

	virtual void Exit(CSection* pSection);

	virtual bool OnMessage(CSection* agent, const Telegram& msg){return false;}
};

#define EndingShow CEndingShow::Instance()

#endif