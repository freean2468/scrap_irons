#ifndef _MainMenu_H_
#define _MainMenu_H_

class CMainMenu : public CBaseSection{
private:
	// ���±�� Ŭ������ �� �ν��Ͻ�
	CStateMachine<CMainMenu>* m_pStateMachine;

public:
	CMainMenu::CMainMenu(int id):CBaseSection(id){
		// ���±�踦 �����Ѵ�.
		m_pStateMachine = new CStateMachine<CMainMenu>(this);

		m_pStateMachine->SetCurrentState(NULL);

		m_pStateMachine->SetGlobalState(NULL);
	}
	~CMainMenu(){}

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update(){ m_pStateMachine->Update();}

	// �� �޼ҵ�� ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	CStateMachine<CMainMenu>* GetFSM()const{return m_pStateMachine;}

	virtual bool HandleMessage(const Telegram& msg){
		return m_pStateMachine->HandleMessage(msg);
	}
};

#endif