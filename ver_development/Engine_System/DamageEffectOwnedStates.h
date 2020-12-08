////////////////////////////////////////////////////
// DamageEffect가 가질 상태들
////////////////////////////////////////////////////
#ifndef _DamageEffectOwnedStates_H_
#define _DamageEffectOwnedStates_H_

class CDamageEffect;

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
class CDamageEffectUsual : public CState<CDamageEffect>{
private:  
	CDamageEffectUsual(){}

	//copy ctor and assignment should be private
	CDamageEffectUsual(const CDamageEffectUsual&);
	CDamageEffectUsual& operator=(const CDamageEffectUsual&);

	float _deltaY;
 
public:
  //this is a singleton
	static CDamageEffectUsual* Instance(){
		static CDamageEffectUsual instance;

		return &instance;
	}

	virtual void Enter(CDamageEffect* pDamageEffect);

	virtual void Execute(CDamageEffect* pDamageEffect);

	virtual void Exit(CDamageEffect* pDamageEffect);

	virtual bool OnMessage(CDamageEffect* agent, const Telegram& msg);
};

#define DamageEffectUsual CDamageEffectUsual::Instance()

#endif