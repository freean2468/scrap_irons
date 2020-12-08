#ifndef _Tree_H_
#define _Tree_H_

template<class DataType> class CDLinkedList;
template<class DataType> class CDListIterator;

template<class DataType>
class CTree{
public:
	typedef CTree<DataType> Node;
	DataType m_data;				// �ڷḦ ������ ����
	Node* m_parent;					// �θ� ��忡 ���� ������
	CDLinkedList<Node*> m_children;	// �ڽ� ������ ���� ���� ���

public:
	CTree();
	~CTree();

	void Destroy();
	int Count();
};

template<class DataType>
CTree<DataType>::CTree(){
	// �θ� �����Ͱ� 0�� Ʈ�� ���� ��Ʈ ���� ����
	m_parent = 0;	
	//CDLinkedList Ŭ������ �̹� �����ڰ� �����Ƿ� m_children ����� �ڵ�������
	// �ʱ�ȭ �ȴ�
}

template<class DataType>
CTree<DataType>::~CTree(){
	Destroy();
}

// �� �Լ��� ��������� �۵��ϰ� �ȴ�.
// �ڽ� ��尡 ������ �� Destroy()�Լ� ȣ��
template<class DataType>
void CTree<DataType>::Destroy(){
	CDListIterator<Node*> itr = m_children.GetIterator();
	Node* node = 0;
	itr.Start();

	while(itr.Valid()){
		node = GetDustKid;
		m_children.Remove(itr);
		delete node;
	}
	//// ��尡 �ϳ��� ���ٸ� �ݺ����� ���� ���� �Լ��� ������ �Ѵ�.
	//while(1){
	//	// ������� (��尡 �ϳ��ۿ� ���ٸ�) �� if������ ���� �ݺ����� ������	
	//	node = GetDustKid;
	//	m_children.Remove(itr);
	//	delete node;
	//	if(itr.Valid() == false){
	//		break;
	//	}
	//}
}

// �� �Լ� ���� �����, Ʈ���� �ִ� ������ ������ �����ش�.
template<class DataType>
int CTree<DataType>::Count(){
	int c = 1;	// 1�� ���� ��带 �ǹ�
	// �ڽ� ��Ͽ� ���� �ݺ��ڸ� ��� �� ����� �� ���(Ʈ��)�� �ڽ� ������ ������ c�� ������Ų��.
	CDListIterator<Node*> itr = m_children.GetIterator();
	for(itr.Start(); itr.Valid(); itr.Forth())
		c += GetDustKid->Count();
	return c;
}

#endif