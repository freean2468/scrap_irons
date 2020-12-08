////////////////////////////////////////////////////
// ���� ������ ���Ͽ� ���� ���� ���� Ŭ����
////////////////////////////////////////////////////
#ifndef _State_H_
#define _State_H_

struct Telegram;

template <class entity_type>
class CState{
public:
  virtual ~CState(){}

  // ���¿� ������ �� �̰��� ����ȴ�.
  virtual void Enter(entity_type*)=0;

  // �̰��� ���� �ܰ迡�� entity�� ���� �Լ��� ȣ��ȴ�.
  virtual void Execute(entity_type*)=0;

  // �̰��� ���� ���� �ÿ� ����ȴ�.
  virtual void Exit(entity_type*)=0;

  // ������Ʈ�� �޽��� �߼۱�κ��� �޽����� �����ϸ� �� �κ��� ����ȴ�.
  virtual bool OnMessage(entity_type* , const Telegram&)=0;
};

#endif