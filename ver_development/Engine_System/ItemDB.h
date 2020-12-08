////////////////////////////////////////////////////////////////////////////////////////////////////////
// MessageDispatcher가 참조하도록 제공되는 인스턴스화된 Item들로 구성된
// 일종의 데이터 베이스
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ItemDB_H_
#define _ItemDB_H_

class CItem;

class CItemDataBase{
private:
	// 기존의 포인터들을 저장해 놓기 위한 것
	typedef std::map<int, CItem*> ItemMap;

private:
	// 급히 참조할 수 있도록 엔티티들은 std::map에 저장되는데,
	// 여기서 아이템들로의 포인터들은 자신의 식별 번호에 의해 교차참조된다.
	ItemMap	m_ItemMap;

	CItemDataBase(){}

	// 생성자와 소멸자를 복사하고 할당은 private이어야 한다.
	CItemDataBase(const CItemDataBase&);
	CItemDataBase& operator=(const CItemDataBase&);

public:
	static CItemDataBase* Instance(){
		 static CItemDataBase instance;

		 return &instance;
	}

	// 이 메소드는 std::vector 내의 Item으로의 포인터를 저장하고
	// Item의 ID가 지정하는 색인 위치에서의 m_Item
	// (더 빨리 접근하게 해준다)
	void RegisterItem(CItem* NewItem);

	// 매개변수로 주어진 ID를 갖고 있는 Item을 가리키는 포인터를 반환한다.
	CItem* GetItemFromID(int id)const;

	// 이 메소드는 Item를 리스트에서 제거한다.
	void RemoveItem(CItem* pItem);
};

// ItemDataBase의 인스턴스를 쉽게 접근할 수 있는 방법을 제공한다.
#define ItemDB CItemDataBase::Instance()

#endif