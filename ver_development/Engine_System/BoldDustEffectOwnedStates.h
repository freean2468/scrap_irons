////////////////////////////////////////////////////
// BoldDustEffect가 가질 상태들
////////////////////////////////////////////////////
#ifndef _BoldDustEffectOwnedStates_H_
#define _BoldDustEffectOwnedStates_H_

class CBoldDustEffect;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CBoldDustEffectUsual : public CState<CBoldDustEffect>{
private:  
	CBoldDustEffectUsual(){}

	//copy ctor and assignment should be private
	CBoldDustEffectUsual(const CBoldDustEffectUsual&);
	CBoldDustEffectUsual& operator=(const CBoldDustEffectUsual&);
 
public:
  //this is a singleton
	static CBoldDustEffectUsual* Instance(){
		static CBoldDustEffectUsual instance;

		return &instance;
	}

	virtual void Enter(CBoldDustEffect* pBoldDustEffect);

	virtual void Execute(CBoldDustEffect* pBoldDustEffect);

	virtual void Exit(CBoldDustEffect* pBoldDustEffect);

	virtual bool OnMessage(CBoldDustEffect* agent, const Telegram& msg);
};

#define BoldDustEffectUsual CBoldDustEffectUsual::Instance()

#endif