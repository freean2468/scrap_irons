#ifndef _BinarySearchTree_H_
#define _BinarySearchTree_H_

template<class DataType> class CBinaryTree;

// ������ BST Ŭ������ �ϳ��� �����̳��� ���̴�.
template<class DataType>
class CBinarySearchTree{
public:	
	typedef CBinaryTree<DataType> Node;
	Node* m_root;							// ���� Ʈ��, ��Ʈ ��忡 ���� ������
	int (*m_compare)(DataType, DataType);	// �� �Լ��� ����Ű�� �Լ� ������

public:
	CBinarySearchTree(int (*p_compare)(DataType, DataType));
	~CBinarySearchTree();

	void Insert(DataType p_data);
	CBinaryTree<DataType>* Find(DataType p_data);
};

// �� �Լ��� Ʈ���� �ڷḦ ������ �� ���̸�, �ڷ���� Ʈ���� ���Ե� �� �� �Լ��� �ٲ�� ��������� �� Ʈ���� ��ȿ���� ������ �ȴ�.
template<class DataType>
CBinarySearchTree<DataType>::CBinarySearchTree(int (*p_compare)(DataType, DataType)){
	m_root = 0;
	m_compare = p_compare;
}

template<class DataType>
CBinarySearchTree<DataType>::~CBinarySearchTree(){
	if(m_root != 0) delete m_root;
}

// �Ϲ������� BST�� �ߺ��� �ڷ��� ������ ������� ������, �� Insert�Լ��� �ڷ��� �ߺ��� �������� �ʴ´�.
// �Դٰ� �� BST Ŭ������ ����� ���Ÿ� �������� �����Ƿ�, �ߺ��� �ڷḦ Ʈ���� �����ϸ� �ᱹ
// ������ ����ȴ�. Find �Լ��� �ߺ��� �ڷḦ ���� ã�� ���ϹǷ�(�׳� ù������ ������ ����
// ������ ���̴�), �ߺ��� �ڷ�� �ƹ� �ǹ� ���� ������ �����ϰ� �ȴ�.
template<class DataType>
void CBinarySearchTree<DataType>::Insert(DataType p_data){
	Node* current = m_root;
	if(m_root == 0)
		m_root = new Node(p_data);
	else{
		while(current != 0){
			if(m_compare(p_data, current->m_data) < 0){
				if(current->m_left == 0){
					current->m_left = new Node(p_data);
					current->m_left->m_parent = current;
					current = 0;
				}
				else
					current = current->m_left;
			}
			else{
				if(current->m_right = 0){
					current->m_right = new Node(p_data);
					current->m_right->m_parent = current;
					current = 0;
				}
				else
					current = current->m_right;
			}
		}
	}
}

template<class DataType>
CBinaryTree<DataType>* CBinarySearchTree<DataType>::Find(DataType p_data){
	Node* current = m_root;
	int temp;
	while(current != 0){
		temp = m_compare(p_data, current->m_data);
		if( temp == 0)
			return curreunt;
		if(temp <0)
			current = current->m_left;
		else
			current = current->m_right;
	}
	return 0;
}

#endif