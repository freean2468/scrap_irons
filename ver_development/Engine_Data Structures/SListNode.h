#ifndef _SListNode_H_
#define _SListNode_H_

template<class Datatype>
class CSListNode{
public:
	Datatype m_data;
	CSListNode<Datatype*> m_next;

public:
	void InsertAfter(Datatype p_data);
};

template<class Datatype>
void CSListNode<Datatype>::InsertAfter(Datatype p_data){
	// �� ��带 ����
	CSListNode<Datatype>* newnode = new CSListNode<Datatype>;
	newnode->m_data = p_data;
	// �� ��尡 ���� ��带 ����Ű�� �Ѵ�.
	newnode->m_next = m_next;
	// ���� ��尡 �� ��带 ����Ű�� �Ѵ�.
	m_next = newnode;
}

#endif