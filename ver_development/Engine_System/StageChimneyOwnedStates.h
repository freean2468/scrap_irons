////////////////////////////////////////////////////
// Chimney가 가질 상태들
////////////////////////////////////////////////////
#ifndef _ChimneyOwnedStates_H_
#define _ChimneyOwnedStates_H_

class CStageChimney;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CStageChimneyUsual : public CState<CStageChimney>{
private:  
	CStageChimneyUsual(){}

	//copy ctor and assignment should be private
	CStageChimneyUsual(const CStageChimneyUsual&);
	CStageChimneyUsual& operator=(const CStageChimneyUsual&);
 
public:
  //this is a singleton
	static CStageChimneyUsual* Instance(){
		static CStageChimneyUsual instance;

		return &instance;
	}

	virtual void Enter(CStageChimney* pChimney);

	virtual void Execute(CStageChimney* pChimney);

	virtual void Exit(CStageChimney* pChimney);

	virtual bool OnMessage(CStageChimney* agent, const Telegram& msg);
};

#define StageChimneyUsual CStageChimneyUsual::Instance()

#endif