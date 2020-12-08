////////////////////////////////////////////////////
// 메시지 발송을 관리하는 클래스
// 각각의 다른 DB 확장을 위한 Base클래스로 만들었음.
// 각각의 EntityDB에서 메시지를 사용하려 한다면
////////////////////////////////////////////////////
#ifndef _BaseMessageDispatcher_H_
#define _BaseMessageDispatcher_H_

class CBaseSection;
struct Telegram;

#define SEND_MSG_IMMEDIATELY 0
#define NO_ADDITIONAL_INFO NULL

class CBaseMessageDispatcher{
private:
	// std::set는 자동 정렬과 중복 회피라는 이점 때문에,
	// 지연된 메시지를 담고 있기 위한 용기로 사용된다. 메시지들은
	// 자신들이 발송된 시간에 따라 정렬된다.
	std::set<Telegram> PriorityQ;

	// 이 메소드를 DispatchMessage나 DispatchDelayedMessages가 활용한다.
	// 이 메소드는, 수신용 엔티티인 pReceiver라고 하는 메시지 처리 멤버 함수를
	// 새로 생성된 전보화 함께 호출한다.
	void Discharge(CBaseGameEntity* pReceiver, const Telegram& msg);

	CBaseMessageDispatcher(){}

public:
	// 이 클래스는 유일 객체이다.
	static CBaseMessageDispatcher* Instance(){
		 static CBaseMessageDispatcher instance;

		 return &instance;
	}

	// 다른 에이전트에게 메시지를 보낸다.
	void DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo);
	
	// 지연된 모든 메시지를 보낸다. 이 메소드는 게임의 주 루프를 통해서 매번 호출된다.
	void DispatchDelayedMessages();
};

// 일을 좀 더 쉽게 하기 위해서
#define Dispatch CBaseMessageDispatcher::Instance()

#endif