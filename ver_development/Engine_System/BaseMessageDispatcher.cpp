#include "../BaseHeader.h"

// 이 메소드는 하나의 엔티티가 다른 엔티티에게 메시지를 보낼 때 호출된다.
void CBaseMessageDispatcher::DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo){
	// 메시지 발신자와 수신자를 가리키는 포인터를 얻어낸다.
	CBaseGameEntity* pSender = EntityDB->GetEntityFromID(sender);
	CBaseGameEntity* pReceiver = EntityDB->GetEntityFromID(receiver);

	// 전보를 생성한다.
	Telegram telegram(0, sender, receiver, msg, ExtraInfo);

	// 지연될 필요가 없다면, 그 전보를 당장 발송한다.
	if(delay <= SmallestDelay){
		// 전보를 수신자에게 보낸다.
		Discharge(pReceiver, telegram);
	}
	else{ // 아니면 전보가 언제 발송되어야 하는지 그 시간을 계산한다.
		double CurrentTime = Clock->GetCurrentTime();

		telegram.DispatchTime = CurrentTime + delay;

		// 그리고 큐에 집어 넣는다.
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
	// 우선 현재 시간을 가져온다.
	double CurrentTime = Clock->GetCurrentTime();

	// 전송될 필요가 있는 전보가 있는지를 알아보기 위해, 큐를 들여다본다.
	// 시간상 유통기한이 지난 전보들을 큐의 앞부분부터 제거해 나간다.
	while((PriorityQ.begin()->DispatchTime < CurrentTime) && (PriorityQ.begin()->DispatchTime > 0)){
		// 큐의 앞부분부터 전보를 읽어 나간다.
		Telegram telegram = *PriorityQ.begin();

		// 수신자를 찾아낸다.
		CBaseGameEntity* pReceiver = EntityDB->GetEntityFromID(telegram.Receiver);

		// 수신자에게 전보를 보낸다.
		Discharge(pReceiver, telegram);

		// 그리고 큐로부터 제거한다.
		PriorityQ.erase(PriorityQ.begin());
	}
}