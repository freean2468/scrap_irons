#include "../BaseHeader.h"

// �� �޼ҵ�� �ϳ��� ��ƼƼ�� �ٸ� ��ƼƼ���� �޽����� ���� �� ȣ��ȴ�.
void CBaseMessageDispatcher::DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo){
	// �޽��� �߽��ڿ� �����ڸ� ����Ű�� �����͸� ����.
	CBaseGameEntity* pSender = EntityDB->GetEntityFromID(sender);
	CBaseGameEntity* pReceiver = EntityDB->GetEntityFromID(receiver);

	// ������ �����Ѵ�.
	Telegram telegram(0, sender, receiver, msg, ExtraInfo);

	// ������ �ʿ䰡 ���ٸ�, �� ������ ���� �߼��Ѵ�.
	if(delay <= SmallestDelay){
		// ������ �����ڿ��� ������.
		Discharge(pReceiver, telegram);
	}
	else{ // �ƴϸ� ������ ���� �߼۵Ǿ�� �ϴ��� �� �ð��� ����Ѵ�.
		double CurrentTime = Clock->GetCurrentTime();

		telegram.DispatchTime = CurrentTime + delay;

		// �׸��� ť�� ���� �ִ´�.
		PriorityQ.insert(telegram);
	}
}

void CBaseMessageDispatcher::Discharge(CBaseGameEntity* pReceiver, const Telegram& telegram){
  if (!pReceiver->HandleMessage(telegram)){
    //telegram could not be handled
	  OutputDebugString("Message not handled");
  }
}

void CBaseMessageDispatcher::DispatchDelayedMessages(){
	// �켱 ���� �ð��� �����´�.
	double CurrentTime = Clock->GetCurrentTime();

	// ���۵� �ʿ䰡 �ִ� ������ �ִ����� �˾ƺ��� ����, ť�� �鿩�ٺ���.
	// �ð��� ��������� ���� �������� ť�� �պκк��� ������ ������.
	while((PriorityQ.begin()->DispatchTime < CurrentTime) && (PriorityQ.begin()->DispatchTime > 0)){
		// ť�� �պκк��� ������ �о� ������.
		Telegram telegram = *PriorityQ.begin();

		// �����ڸ� ã�Ƴ���.
		CBaseGameEntity* pReceiver = EntityDB->GetEntityFromID(telegram.Receiver);

		// �����ڿ��� ������ ������.
		Discharge(pReceiver, telegram);

		// �׸��� ť�κ��� �����Ѵ�.
		PriorityQ.erase(PriorityQ.begin());
	}
}