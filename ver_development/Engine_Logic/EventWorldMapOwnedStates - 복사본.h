////////////////////////////////////////////////////
// WorldMapStageClear 이벤트
////////////////////////////////////////////////////
#ifndef _EventWorldMapOwnedStates_H_
#define _EventWorldMapOwnedStates_H_

class CEventWorldMap;

///////////////////////////////////////////////////////////
// WorldMap 이벤트 
///////////////////////////////////////////////////////////
class CEventWorldMapStageClear : public CState<CEventWorldMap>{
private:  
  CEventWorldMapStageClear(){}

  //copy ctor and assignment should be private
  CEventWorldMapStageClear(const CEventWorldMapStageClear&);
  CEventWorldMapStageClear& operator=(const CEventWorldMapStageClear&);
 
public:
  //this is a singleton
	static CEventWorldMapStageClear* Instance(){
		static CEventWorldMapStageClear instance;

		return &instance;
	}

	virtual void Enter(CEventWorldMap* p_pEvent);

	virtual void Execute(CEventWorldMap* p_pEvent);

	virtual void Exit(CEventWorldMap* p_pEvent);

	virtual bool OnMessage(CEventWorldMap* agent, const Telegram& msg){return false;}
};

#define EventWorldMapStageClear CEventWorldMapStageClear::Instance()