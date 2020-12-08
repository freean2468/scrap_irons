////////////////////////////////////////////////////
// WorldMap가 가질 상태들
////////////////////////////////////////////////////
#ifndef _WorldMapOwnedStates_H_
#define _WorldMapOwnedStates_H_

class CWorldMap;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CWorldMapUsual : public CState<CWorldMap>{
private:  
	CWorldMapUsual(){}

	//copy ctor and assignment should be private
	CWorldMapUsual(const CWorldMap&);
	CWorldMapUsual& operator=(const CWorldMap&);
 
public:
  //this is a singleton
	static CWorldMapUsual* Instance(){
		static CWorldMapUsual instance;

		return &instance;
	}

	virtual void Enter(CWorldMap* pWorldMap);

	virtual void Execute(CWorldMap* pWorldMap);

	virtual void Exit(CWorldMap* pWorldMap);

	virtual bool OnMessage(CWorldMap* agent, const Telegram& msg);
};

#define WorldMapUsual CWorldMapUsual::Instance()

///////////////////////////////////////////////////////////
// Ending State
///////////////////////////////////////////////////////////
class CWorldMapEnding : public CState<CWorldMap>{
private:  
	CWorldMapEnding(){}

	//copy ctor and assignment should be private
	CWorldMapEnding(const CWorldMap&);
	CWorldMapEnding& operator=(const CWorldMap&);
 
public:
  //this is a singleton
	static CWorldMapEnding* Instance(){
		static CWorldMapEnding instance;

		return &instance;
	}

	virtual void Enter(CWorldMap* pWorldMap);

	virtual void Execute(CWorldMap* pWorldMap);

	virtual void Exit(CWorldMap* pWorldMap);

	virtual bool OnMessage(CWorldMap* agent, const Telegram& msg);
};

#define WorldMapEnding CWorldMapEnding::Instance()

#endif