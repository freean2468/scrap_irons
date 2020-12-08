////////////////////////////////////////////////////
// GoodHope가 가질 상태들
////////////////////////////////////////////////////
#ifndef _GoodHopeOwnedStates_H_
#define _GoodHopeOwnedStates_H_

class CStageGoodHope;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CStageGoodHopeUsual : public CState<CStageGoodHope>{
private:  
	CStageGoodHopeUsual(){}

	//copy ctor and assignment should be private
	CStageGoodHopeUsual(const CStageGoodHopeUsual&);
	CStageGoodHopeUsual& operator=(const CStageGoodHopeUsual&);
 
public:
  //this is a singleton
	static CStageGoodHopeUsual* Instance(){
		static CStageGoodHopeUsual instance;

		return &instance;
	}

	virtual void Enter(CStageGoodHope* pGoodHope);

	virtual void Execute(CStageGoodHope* pGoodHope);

	virtual void Exit(CStageGoodHope* pGoodHope);

	virtual bool OnMessage(CStageGoodHope* agent, const Telegram& msg);
};

#define StageGoodHopeUsual CStageGoodHopeUsual::Instance()

#endif