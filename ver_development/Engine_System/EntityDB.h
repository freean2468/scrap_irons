////////////////////////////////////////////////////////////////////////////////////////////////////////
// MessageDispatcher�� �����ϵ��� �����Ǵ� �ν��Ͻ�ȭ�� Entity��� ������
// ������ ������ ���̽�
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _EntityDB_H_
#define _EntityDB_H_

class COrganEntity;

class CEntityDataBase{
private:
	// ������ �����͵��� ������ ���� ���� ��
	typedef std::map<int, CBaseGameEntity*> EntityMap;

private:
	// ���� ������ �� �ֵ��� ��ƼƼ���� std::map�� ����Ǵµ�,
	// ���⼭ ��ƼƼ����� �����͵��� �ڽ��� �ĺ� ��ȣ�� ���� ���������ȴ�.
	EntityMap	m_EntityMap;

	CEntityDataBase(){}

	// �����ڿ� �Ҹ��ڸ� �����ϰ� �Ҵ��� private�̾�� �Ѵ�.
	CEntityDataBase(const CEntityDataBase&);
	CEntityDataBase& operator=(const CEntityDataBase&);

public:
	static CEntityDataBase* Instance(){
		 static CEntityDataBase instance;

		 return &instance;
	}

	// �� �޼ҵ�� std::vector ���� Entity������ �����͸� �����ϰ�
	// Entity�� ID�� �����ϴ� ���� ��ġ������ m_Entity
	// (�� ���� �����ϰ� ���ش�)
	void RegisterEntity(CBaseGameEntity* NewEntity);

	// �Ű������� �־��� ID�� ���� �ִ� Entity�� ����Ű�� �����͸� ��ȯ�Ѵ�.
	CBaseGameEntity* GetEntityFromID(int id)const;

	// �� �޼ҵ�� Entity�� ����Ʈ���� �����Ѵ�.
	void RemoveEntity(CBaseGameEntity* pEntity);
};

// EntityDataBase�� �ν��Ͻ��� ���� ������ �� �ִ� ����� �����Ѵ�.
#define EntityDB CEntityDataBase::Instance()

#endif