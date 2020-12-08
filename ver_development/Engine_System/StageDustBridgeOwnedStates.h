////////////////////////////////////////////////////
// DustBridge가 가질 상태들
////////////////////////////////////////////////////
#ifndef _DustBridgeOwnedStates_H_
#define _DustBridgeOwnedStates_H_

class CStageDustBridge;

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
class CStageDustBridgeUsual : public CState<CStageDustBridge>{
private:  
	CStageDustBridgeUsual(){}

	//copy ctor and assignment should be private
	CStageDustBridgeUsual(const CStageDustBridgeUsual&);
	CStageDustBridgeUsual& operator=(const CStageDustBridgeUsual&);
 
public:
  //this is a singleton
	static CStageDustBridgeUsual* Instance(){
		static CStageDustBridgeUsual instance;

		return &instance;
	}

	virtual void Enter(CStageDustBridge* pDustBridge);

	virtual void Execute(CStageDustBridge* pDustBridge);

	virtual void Exit(CStageDustBridge* pDustBridge);

	virtual bool OnMessage(CStageDustBridge* agent, const Telegram& msg);
};

#define StageDustBridgeUsual CStageDustBridgeUsual::Instance()

#endif