////////////////////////////////////////////////////////////////////////////////////////////////////////
// ID ��ȣ�� �����ϱ� ���� private����� ������ �ִ� Ŭ����
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BaseGameEntity_H_
#define _BaseGameEntity_H_

// ID ��ȣ�� �����ϱ� ���� private����� ������ �ִ� Ŭ����
class CBaseGameEntity{
private:
  // ��� Entity���� ������ �ĺ���ȣ�� ���´�.
  int          m_ID;

  // �̰��� ��ȿ�� ���� �ĺ���ȣ�̴�. CBaseGameEntity�� �Ź� �ʱ�ȭ�� �� ��
  // �� ���� ���ŵȴ�.
  static int  m_iNextValidID;

  // �̰��� ID�� ��Ȯ�ϰ� �����ǵ��� ������ ���ο��� ȣ��ȴ�.
  // �̰��� ID�� �����ϰ� ��ȿ�� ���� ID�� ������Ű�� ����,
  // �޼ҵ忡 ���޵� ���� ��ȿ�� ���� ID���� �� ū�� �ƴϸ� �������� Ȯ���Ѵ�.
  void SetID(int val);

public:
  CBaseGameEntity(int id){
    SetID(id);
  }

  virtual ~CBaseGameEntity(){}

  // ��� ��ƼƼ���� ���� �Լ��� ��ġ�ϰ� �־�߸� �Ѵ�.
  virtual void  Update()=0;

  int ID()const{return m_ID;}  

  // ��� ���� Ŭ�������� �޽����� ����Ͽ� ����� �� �ִ�.
  virtual bool HandleMessage(const Telegram& msg)=0;
};

#endif