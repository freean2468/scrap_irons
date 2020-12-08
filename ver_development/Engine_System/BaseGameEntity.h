////////////////////////////////////////////////////////////////////////////////////////////////////////
// ID 번호를 저장하기 위한 private멤버를 가지고 있는 클래스
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BaseGameEntity_H_
#define _BaseGameEntity_H_

// ID 번호를 저장하기 위한 private멤버를 가지고 있는 클래스
class CBaseGameEntity{
private:
  // 모든 Entity들은 고유한 식별번호를 갖는다.
  int          m_ID;

  // 이것은 유효한 다음 식별번호이다. CBaseGameEntity이 매번 초기화가 될 때
  // 이 값도 갱신된다.
  static int  m_iNextValidID;

  // 이것은 ID가 정확하게 설정되도록 생성자 내부에서 호출된다.
  // 이것은 ID를 설정하고 유효한 다음 ID를 증가시키기 전에,
  // 메소드에 전달된 값이 유효한 다음 ID보다 더 큰지 아니면 같은지를 확인한다.
  void SetID(int val);

public:
  CBaseGameEntity(int id){
    SetID(id);
  }

  virtual ~CBaseGameEntity(){}

  // 모든 엔티티들은 갱신 함수를 설치하고 있어야만 한다.
  virtual void  Update()=0;

  int ID()const{return m_ID;}  

  // 모든 하위 클래스들은 메시지를 사용하여 통신할 수 있다.
  virtual bool HandleMessage(const Telegram& msg)=0;
};

#endif