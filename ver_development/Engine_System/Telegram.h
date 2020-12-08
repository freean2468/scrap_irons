////////////////////////////////////////////////////
// 메시지 정보
////////////////////////////////////////////////////
#ifndef _Telegram_H_
#define _Telegram_H_

struct Telegram{
	// 이 정보를 보내는 Entity
	int Sender;

	// 이 전보를 받는 엔티티
	int Receiver;

	// 메시지 자체. 이것들은 'MessageTypes.h'파일 내에 열거된 모든 것이다.
	int Msg;

	// 메시지들은 지금 당장 급송되거나 특정 시간 동안 지연된다.
	// 지연이 필요하면, 이 필드는 시간 도장이 찍힌 다음
	// 메시지가 보내져야 한다.
	double DispatchTime;

	// 메시지와 함께 따라갈 추가적인 정보
	void* ExtraInfo;

	Telegram():DispatchTime(-1),
                  Sender(-1),
                  Receiver(-1),
                  Msg(-1)
	{}

	Telegram(double time, int sender, int receiver, int msg, void* info = NULL): DispatchTime(time),
																				Sender(sender),
																				Receiver(receiver),
																				Msg(msg),
																				ExtraInfo(info)
	{}
};

const double SmallestDelay = 0.25;

// std::<set>에서 순서대로 자동 정렬이 되기 위해서는 크기 비교가 이루어져야 할 것,
// 아래의 연산자 오버로딩 함수들이 이를 가능하게 해준다.
inline bool operator==(const Telegram& t1, const Telegram& t2){
  return ( fabs(t1.DispatchTime-t2.DispatchTime) < SmallestDelay) &&
          (t1.Sender == t2.Sender)        &&
          (t1.Receiver == t2.Receiver)    &&
          (t1.Msg == t2.Msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2){
  if (t1 == t2)
  {
    return false;
  }

  else
  {
    return  (t1.DispatchTime < t2.DispatchTime);
  }
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t){
  os << "time: " << t.DispatchTime << "  Sender: " << t.Sender
     << "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;

  return os;
}

#endif