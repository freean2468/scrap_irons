////////////////////////////////////////////////////////////////////////////////////////////////////////
// MessageDispatcher�� �����ϵ��� �����Ǵ� �ν��Ͻ�ȭ�� Item��� ������
// ������ ������ ���̽�
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ItemDB_H_
#define _ItemDB_H_

class CItem;

class CItemDataBase{
private:
	// ������ �����͵��� ������ ���� ���� ��
	typedef std::map<int, CItem*> ItemMap;

private:
	// ���� ������ �� �ֵ��� ��ƼƼ���� std::map�� ����Ǵµ�,
	// ���⼭ �����۵���� �����͵��� �ڽ��� �ĺ� ��ȣ�� ���� ���������ȴ�.
	ItemMap	m_ItemMap;

	CItemDataBase(){}

	// �����ڿ� �Ҹ��ڸ� �����ϰ� �Ҵ��� private�̾�� �Ѵ�.
	CItemDataBase(const CItemDataBase&);
	CItemDataBase& operator=(const CItemDataBase&);

public:
	static CItemDataBase* Instance(){
		 static CItemDataBase instance;

		 return &instance;
	}

	// �� �޼ҵ�� std::vector ���� Item������ �����͸� �����ϰ�
	// Item�� ID�� �����ϴ� ���� ��ġ������ m_Item
	// (�� ���� �����ϰ� ���ش�)
	void RegisterItem(CItem* NewItem);

	// �Ű������� �־��� ID�� ���� �ִ� Item�� ����Ű�� �����͸� ��ȯ�Ѵ�.
	CItem* GetItemFromID(int id)const;

	// �� �޼ҵ�� Item�� ����Ʈ���� �����Ѵ�.
	void RemoveItem(CItem* pItem);
};

// ItemDataBase�� �ν��Ͻ��� ���� ������ �� �ִ� ����� �����Ѵ�.
#define ItemDB CItemDataBase::Instance()

#endif