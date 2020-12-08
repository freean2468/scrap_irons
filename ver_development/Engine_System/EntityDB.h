////////////////////////////////////////////////////////////////////////////////////////////////////////
// MessageDispatcher가 참조하도록 제공되는 인스턴스화된 Entity들로 구성된
// 일종의 데이터 베이스
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _EntityDB_H_
#define _EntityDB_H_

class COrganEntity;

class CEntityDataBase{
private:
	// 기존의 포인터들을 저장해 놓기 위한 것
	typedef std::map<int, CBaseGameEntity*> EntityMap;

private:
	// 급히 참조할 수 있도록 엔티티들은 std::map에 저장되는데,
	// 여기서 엔티티들로의 포인터들은 자신의 식별 번호에 의해 교차참조된다.
	EntityMap	m_EntityMap;

	CEntityDataBase(){}

	// 생성자와 소멸자를 복사하고 할당은 private이어야 한다.
	CEntityDataBase(const CEntityDataBase&);
	CEntityDataBase& operator=(const CEntityDataBase&);

public:
	static CEntityDataBase* Instance(){
		 static CEntityDataBase instance;

		 return &instance;
	}

	// 이 메소드는 std::vector 내의 Entity으로의 포인터를 저장하고
	// Entity의 ID가 지정하는 색인 위치에서의 m_Entity
	// (더 빨리 접근하게 해준다)
	void RegisterEntity(CBaseGameEntity* NewEntity);

	// 매개변수로 주어진 ID를 갖고 있는 Entity을 가리키는 포인터를 반환한다.
	CBaseGameEntity* GetEntityFromID(int id)const;

	// 이 메소드는 Entity를 리스트에서 제거한다.
	void RemoveEntity(CBaseGameEntity* pEntity);
};

// EntityDataBase의 인스턴스를 쉽게 접근할 수 있는 방법을 제공한다.
#define EntityDB CEntityDataBase::Instance()

#endif