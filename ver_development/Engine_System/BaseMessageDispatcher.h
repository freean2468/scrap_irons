////////////////////////////////////////////////////
// �޽��� �߼��� �����ϴ� Ŭ����
// ������ �ٸ� DB Ȯ���� ���� BaseŬ������ �������.
// ������ EntityDB���� �޽����� ����Ϸ� �Ѵٸ�
////////////////////////////////////////////////////
#ifndef _BaseMessageDispatcher_H_
#define _BaseMessageDispatcher_H_

class CBaseSection;
struct Telegram;

#define SEND_MSG_IMMEDIATELY 0
#define NO_ADDITIONAL_INFO NULL

class CBaseMessageDispatcher{
private:
	// std::set�� �ڵ� ���İ� �ߺ� ȸ�Ƕ�� ���� ������,
	// ������ �޽����� ��� �ֱ� ���� ���� ���ȴ�. �޽�������
	// �ڽŵ��� �߼۵� �ð��� ���� ���ĵȴ�.
	std::set<Telegram> PriorityQ;

	// �� �޼ҵ带 DispatchMessage�� DispatchDelayedMessages�� Ȱ���Ѵ�.
	// �� �޼ҵ��, ���ſ� ��ƼƼ�� pReceiver��� �ϴ� �޽��� ó�� ��� �Լ���
	// ���� ������ ����ȭ �Բ� ȣ���Ѵ�.
	void Discharge(CBaseGameEntity* pReceiver, const Telegram& msg);

	CBaseMessageDispatcher(){}

public:
	// �� Ŭ������ ���� ��ü�̴�.
	static CBaseMessageDispatcher* Instance(){
		 static CBaseMessageDispatcher instance;

		 return &instance;
	}

	// �ٸ� ������Ʈ���� �޽����� ������.
	void DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo);
	
	// ������ ��� �޽����� ������. �� �޼ҵ�� ������ �� ������ ���ؼ� �Ź� ȣ��ȴ�.
	void DispatchDelayedMessages();
};

// ���� �� �� ���� �ϱ� ���ؼ�
#define Dispatch CBaseMessageDispatcher::Instance()

#endif