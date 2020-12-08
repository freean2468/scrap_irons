////////////////////////////////////////////////////
// Event�� ���� �پ��� ���� ����
////////////////////////////////////////////////////
#ifndef _EventStage_H_
#define _EventStage_H_

class CEventStage : public COrganEntity{
public:
	typedef enum EventStageAttType{FIRST = 0} EVENTSTAGEATTTYPE;

	// First Event
	bool _firstMeeting;
	bool _firstArea;
	bool _secondArea;
	bool _thirdArea;
	bool _furnace;
	bool _chimney;
	bool _dustbridge;
	bool _goodHopeIntro;
	bool _goodHope;
	
	// Enemy Die
	bool _dustKidDie;
	bool _workerDie;
	bool _gatekeeperDie;
	bool _dustKingDie;

private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CEventStage>* m_pStateMachine;

	// ��Ʈ �������̽� ����
	ID3DXFont*	_pFont;		

	// Ÿ�̸�
	CTimer* _timer;

public:
	CEventStage(int id);
	~CEventStage();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	virtual void RenderOrgan();

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CEventStage>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}

	void SetTimer(DWORD dwDelayTime){_timer = new CTimer(dwDelayTime);}

	CTimer* GetTimer(){return _timer;}
};

#endif