#ifndef _SLinkedList_H_
#define _SLinkedList_H_

template<class Datatype> class CSListNode;
template<class Datatype> class CSListIterator;

template<class Datatype>
class CSLinkedList{
public:
	CSListNode<Datatype>* m_head;
	CSListNode<Datatype>* m_tail;
	int m_count;

public:
	CSLinkedList();
	~CSLinkedList();

	void Append(Datatype p_data);
	void Prepend(Datatype p_data);
	void RemoveHead();
	void RemoveTail();
	CSListIterator<Datatype> GetIterator();
	void Insert(CSListIterator<Datatype>& p_iterator, Datatype p_data);
	void Remove(CSListIterator<Datatype>& p_iterator);
};

template<class Datatype>
CSLinkedList<Datatype>::CSLinkedList(){
	m_head = 0;
	m_tail = 0;
	m_count = 0;
}

template<class Datatype>
CSLinkedList<Datatype>::~CSLinkedList(){
	// �ӽ� ��� ������
	CSListNode<Datatype>* itr = m_head;
	CSListNode<Datatype>* next;

	while(itr != m_tail){
		//���� ��忡 ���� �����͸� ����
		next = itr->m_next;

		// ���� ��带 ����
		delete itr;

		// ���� ��带 ���� ���� ����
		itr = next;
	}
}

template<class Datatype>
void CSLinkedList<Datatype>::Append(Datatype p_data){
	// ����� ��� �ִ���?
	if(m_head == 0){
		// ��� �ִٸ� �� ��尡 �Ӹ��� �ǰ� �Ѵ�.
		m_head = m_tail = new CSListNode<Datatype>;
		
		m_head->m_data = p_data;
		
		m_head->m_next = m_tail;
	}
	else{
		// ���� ������ �� ��带 �����ϰ�, �� ��带 ������ �����.
		m_tail->InsertAfter(p_data);
		m_tail = m_tail->m_next;
	}
	m_count++;
}

template<class Datatype>
void CSLinkedList<Datatype>::Prepend(Datatype p_data){
	// �� ��带 ����
	SListNode<Datatype>* newnode = new SListNode<Datatype>;
	newnode->m_data = p_data;
	newnode->m_next = m_head;

	// �Ӹ� ��带 �����ϰ�, �ʿ��ϴٸ� ���� ��嵵 �����Ѵ�.
	m_head = newnode;
	if(m_tail ==0) m_tail = m_head;

	m_count++;
}

template<class Datatype>
void CSLinkedList<Datatype>::RemoveHead(){
	SListNode<Datatype>* node = 0;

	if(m_head != 0){
		// �Ӹ��� ���� ��带 ����Ű�� �����͸� ����
		node = m_head->m_next;

		// �Ӹ��� �����ϰ�, ���� ��尡 �Ӹ��� �ǰ� �Ѵ�.
		delete m_head;
		m_head = node;

		// m_head�� 0�̶�� ����� ������ �� ���̴�.
		// ���� ���� �����͵� 0���� �����ؾ� �Ѵ�.
		if(m_head == 0) m_tail = 0;

		m_count--;
	}
}

template<class Datatype>
void CSLinkedList<Datatype>::RemoveTail(){
	SListNode<Datatype>* node = m_head;

	// ����� ��� ���� ���� ��쿡�� ��带 �����Ѵ�.
	if(m_head != 0){
		// �Ӹ��� ������ ���� ����� ��Ͽ��� ��尡
		// �ϳ� ���� ���̴�. �� ��带 �����ϸ� �ȴ�.
		if(m_head == m_tail){
			// �� ��带 �����ϰ� �� �����͵��� ��� 0���� �����Ѵ�.
			delete m_head;
			m_head = m_tail = 0;
		}
		else{
			// ���� ��� ������ ��带 ã�´�.
			while(node->m_next != m_tail) node = node->m_next;
			// ������ ��尡 ���� ��尡 �ǰ� �ϰ�, ������ ���� ��带 �����Ѵ�.
			m_tail = node;
			delete node ->m_next;
			node->m_next = 0;
		}
		m_count--;
	}
}

template<class Datatype>
CSListIterator<Datatype> CSLinkedList<Datatype>::GetIterator(){
	return CSListIterator<Datatype>(this, m_head);
}

template<class Datatype>
void CSLinkedList<Datatype>::Insert(CSListIterator<Datatype>& p_iterator, Datatype p_data){
	// �ݺ��ڰ� �� ��Ͽ� ������ �ʴ´ٸ� �ƹ� �ϵ� ���� �ʴ´�.
	if(p_iterator.m_list != this) return;

	if(p_iterator.m_node != 0){
		// �ݺ��ڰ� ��ȿ�ϴٸ� �� ��带 ����
		p_iterator.m_node->InsertAfter(p_data);

		// �ݺ��ڰ� ���� ��带 ����Ű�� �ִٸ�, ���� ���Ե� ��尡 ���� ��尡 �ǰ� �Ѵ�.
		if(p_iterator.m_node == m_tail) m_tail = p_iterator.m_node->m_next;

		m_count++;
	}
	else{
		// �ݺ��ڰ� ��ȿ���� �ʴٸ� �׸��� ��� ���� �߰��Ѵ�.
		Append(p_data);
	}
}

template<class Datatype>
void CSLinkedList<Datatype>::Remove(CSListIterator<Datatype>& p_iterator){
	CSListNode<Datatype>* node = m_head;

	// �ݺ��ڰ� �� ��Ͽ� ���� ���� �ƴ϶�� �ƹ� �͵� ���� �ʴ´�.
	if(p_iterator.m_list != this) return;

	// �ݺ��ڰ� ��ȿ���� ������ �ƹ� �͵� ���� �ʴ´�.
	if(p_iterator.m_node == 0) return;

	if(p_iterator.m_node == m_head){ // ������ ��尡 �Ӹ��̸�
		// �ݺ��ڸ� ���� ���� �ű��, �Ӹ� ��带 �����Ѵ�.
		p_iterator.Forth();
		RemoveHead();
	}
	else{
		// ������ ��尡 �Ӹ��� �ƴϸ�,������ ����� �ٷ� �� ��带 ã�´�.
		while(node->m_next != p_iterator.m_node) node = node->m_next;

		// �ݺ��ڸ� ������Ų��.
		p_iterator.Forth();

		// ������ ��尡 ���� �����, ���� ��带 �����Ѵ�.
		if(node->m_next == m_tail) m_tail = node;

		// ��带 �����Ѵ�.
		delete node->m_next;

		// ����� �ٽ� �����Ų��.
		node->m_next = p_iterator.Start;
	}
	m_count--;
}

#endif