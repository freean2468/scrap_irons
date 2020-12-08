////////////////////////////////////////////////////////////////////////////////
// StageDustBridge Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _StageDustBridge_H_
#define _StageDustBridge_H_

class CStageDustBridge : public COrganEntity{
public:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CStageDustBridge>* m_pStateMachine;

public:
	CStageDustBridge(int id);
	~CStageDustBridge();

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CStageDustBridge>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}

	virtual void CalculationOrgan(float timeDelta){}
};

#endif