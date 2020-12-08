////////////////////////////////////////////////////
// StageMountain가 가질 상태들
////////////////////////////////////////////////////
#ifndef _StageMountainOwnedStates_H_
#define _StageMountainOwnedStates_H_

class CStageMountain;

///////////////////////////////////////////////////////////
// AreaSelection State
///////////////////////////////////////////////////////////
class CStageMountainAreaSelection : public CState<CStageMountain>{
private:  
	CStageMountainAreaSelection(){}

	//copy ctor and assignment should be private
	CStageMountainAreaSelection(const CStageMountain&);
	CStageMountainAreaSelection& operator=(const CStageMountain&);
 
public:
  //this is a singleton
	static CStageMountainAreaSelection* Instance(){
		static CStageMountainAreaSelection instance;

		return &instance;
	}

	virtual void Enter(CStageMountain* pStageMountain);

	virtual void Execute(CStageMountain* pStageMountain);

	virtual void Exit(CStageMountain* pStageMountain);

	virtual bool OnMessage(CStageMountain* agent, const Telegram& msg);
};

#define StageMountainAreaSelection CStageMountainAreaSelection::Instance()

///////////////////////////////////////////////////////////
// Area1 State
///////////////////////////////////////////////////////////
class CStageMountainArea1 : public CState<CStageMountain>{
private:  
	CStageMountainArea1(){}

	//copy ctor and assignment should be private
	CStageMountainArea1(const CStageMountain&);
	CStageMountainArea1& operator=(const CStageMountain&);
 
public:
  //this is a singleton
	static CStageMountainArea1* Instance(){
		static CStageMountainArea1 instance;

		return &instance;
	}

	virtual void Enter(CStageMountain* pStageMountain);

	virtual void Execute(CStageMountain* pStageMountain);

	virtual void Exit(CStageMountain* pStageMountain);

	virtual bool OnMessage(CStageMountain* agent, const Telegram& msg);
};

#define StageMountainArea1 CStageMountainArea1::Instance()

///////////////////////////////////////////////////////////
// Area2 State
///////////////////////////////////////////////////////////
class CStageMountainArea2 : public CState<CStageMountain>{
private:  
	CStageMountainArea2(){}

	//copy ctor and assignment should be private
	CStageMountainArea2(const CStageMountain&);
	CStageMountainArea2& operator=(const CStageMountain&);
 
public:
  //this is a singleton
	static CStageMountainArea2* Instance(){
		static CStageMountainArea2 instance;

		return &instance;
	}

	virtual void Enter(CStageMountain* pStageMountain);

	virtual void Execute(CStageMountain* pStageMountain);

	virtual void Exit(CStageMountain* pStageMountain);

	virtual bool OnMessage(CStageMountain* agent, const Telegram& msg);
};

#define StageMountainArea2 CStageMountainArea2::Instance()

///////////////////////////////////////////////////////////
// Area3 State
///////////////////////////////////////////////////////////
class CStageMountainArea3 : public CState<CStageMountain>{
private:  
	CStageMountainArea3(){}

	//copy ctor and assignment should be private
	CStageMountainArea3(const CStageMountain&);
	CStageMountainArea3& operator=(const CStageMountain&);
 
public:
  //this is a singleton
	static CStageMountainArea3* Instance(){
		static CStageMountainArea3 instance;

		return &instance;
	}

	virtual void Enter(CStageMountain* pStageMountain);

	virtual void Execute(CStageMountain* pStageMountain);

	virtual void Exit(CStageMountain* pStageMountain);

	virtual bool OnMessage(CStageMountain* agent, const Telegram& msg);
};

#define StageMountainArea3 CStageMountainArea3::Instance()

#endif