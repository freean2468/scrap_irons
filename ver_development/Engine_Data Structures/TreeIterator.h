#ifndef _TreeIterator_H_
#define _TreeIterator_H_

template<class DataType> class CDListIterator;

template<class DataType>
class CTreeIterator{
public:
	typedef CTree<DataType> Node;
	Node * m_node;						// ���� ��带 ����Ű�� ������
	CDListIterator<Node*> m_childitr;	// ���� ����� ���� �ڽ��� ����Ű�� �ݺ���

public:
	CTreeIterator(Node* p_node = 0);
	
	void ResetIterator();

	// ���� �ݺ��� �Լ�
	void Root();
	void Up();
	void Down();

	// ���� �ݺ��� �Լ�
	void ChildForth();
    void ChildBack();
    void ChildStart();
    void ChildEnd();

	bool ChildValid();
    DataType& ChildItem();
    void AppendChild( Node* p_node );
    void PrependChild( Node* p_node );
    void InsertChildBefore( Node* p_node );
    void InsertChildAfter( Node* p_node );
    void RemoveChild();

	void operator= (Node* p_node);
};

template<class DataType>
CTreeIterator<DataType>::CTreeIterator(Node* p_node){
	// ���������� ȣ��
	*this = p_node;
}

// ���� �����ڴ� ��� ����(const &)�� �޴� ���� �Ϲ����̳�, �� ���� �����ڴ� Ʈ�� ��� �����͸� �޴´�.
template<class DataType>
void CTreeIterator<DataType>::operator =(Node* p_node){
	m_node = p_node;	// �ݺ��ڰ� �־��� ��带 ����Ű�� �Ѵ�.
	ResetIterator();	// m_childitr �ݺ��ڰ� p_node�� ù ��° �ڽ� ��带 ����Ű�� �����.
}

// �ڽ� �ݺ��ڰ� �ڽ� ����� ù ��° ��带 ����Ű���� �����. �� �Լ���
// m_node �����Ͱ� ����� ������ ȣ��ȴ�.
template<class DataType>
void CTreeIterator<DataType>::ResetIterator(){
	// ���� ��尡 ��ȿ���� ����
	if(m_node != 0){
		m_childitr = m_node->m_children.GetIterator();
	}
	else{
		m_childitr.m_list = 0;
		m_childitr.m_node = 0;
	}
}

// �ݺ��ڸ� Ʈ���� ��Ʈ�� �ű��.
template<class DataType>
void CTreeIterator<DataType>::Root(){
    if( m_node != 0 )
    {
		// ���� ����� �θ� 0�� �� ������, �� ��Ʈ�� ������ ������ ��� �ݺ��ڸ� �� ���� ���� �ø���.
        while( m_node->m_parent != 0 )
        {
            m_node = m_node->m_parent;
        }
    }
    ResetIterator();
}

template<class DataType>
void CTreeIterator<DataType>::Up(){
	if(m_node != 0){
		m_node = m_node->m_parent;
	}
	ResetIterator();
}

template<class DataType>
void CTreeIterator<DataType>::Down(){
	if(m_childitr.Valid()){
		m_node = m_childGetDustKid;
		ResetIterator();
	}
}

template<class DataType>
void CTreeIterator<DataType>::ChildForth(){
    m_childitr.Forth();
}

template<class DataType>
void CTreeIterator<DataType>::ChildBack(){
    m_childitr.Back();
}

template<class DataType>
void CTreeIterator<DataType>::ChildStart(){
    m_childitr.Start();
}

template<class DataType>
void CTreeIterator<DataType>::ChildEnd(){
    m_childitr.End();
}

template<class DataType>
bool CTreeIterator<DataType>::ChildValid(){
    return m_childitr.Valid();
}

template<class DataType>
DataType& CTreeIterator<DataType>::ChildItem(){
    return m_childGetDustKid->m_data;
}

template<class DataType>
void CTreeIterator<DataType>::AppendChild( Node* p_node ){
    if( m_node != 0 ){
        m_node->m_children.Append( p_node );
        p_node->m_parent = m_node;
    }
}

template<class DataType>
void CTreeIterator<DataType>::PrependChild( Node* p_node ){
    if( m_node != 0 ){
        m_node->m_children.Prepend( p_node );
        p_node->m_parent = m_node;
    }
}

template<class DataType>
void CTreeIterator<DataType>::InsertChildBefore( Node* p_node ){
    if( m_node != 0 ){
        m_node->m_children.InsertBefore( m_childitr, p_node );
        p_node->m_parent = m_node;
    }
}

template<class DataType>
void CTreeIterator<DataType>::InsertChildAfter( Node* p_node ){
    if( m_node != 0 ){
        m_node->m_children.InsertAfter( m_childitr, p_node );
        p_node->m_parent = m_node;
    }
}

template<class DataType>
void CTreeIterator<DataType>::RemoveChild(){
    if( m_node != 0 && m_childitr.Valid() ){
        m_childGetDustKid->m_parent = 0;
        m_node->m_children.Remove( m_childitr );
    }
}

// ������ ������ Ʈ���� ���ؼ� ���������ϴ� �Լ�
// �Լ� �����Ͱ� ����Ű�� �Լ��� �ϳ��� CTree�����͸� �Ű������� �ް� �ƹ� �͵� ��ȯ���� �ʾƾ� �Ѵ�.
// � �Լ��� ��� ��忡 ���� �۵���Ű�� �ʹٸ� �� �Լ��� ȣ��
template<class DataType>
void Preorder(CTree<DataType>* p_node, void (*p_process)(CTree<DataType>*)){
	// �־��� ��忡 ���� p_process �Լ� �������� �Լ� ȣ��
	p_process(p_node);
	// �־��� ����� �ڽ� ����� ����Ű�� �ݺ��� ����
	CDListIterator< CTree<DataType>* > itr = p_node->m_children.GetIterator();
	// �� �ݺ��ڸ� �̿��ؼ� �� �ڽ� ��忡 ���� Preorder�� ȣ��
	for(itr.Start(); itr.Valid(); itr.Forth())
		Preorder(GetDustKid, p_process);
}

// ������ ������ Ʈ���� ���ؼ� ���������ϴ� �Լ�
template <class DataType>
void Postorder( CTree<DataType>* p_node, void (*p_process)(CTree<DataType>*) )
{
    // loop through each child and process it
    CDListIterator< CTree<DataType>* > itr = p_node->m_children.GetIterator();
    for( itr.Start(); itr.Valid(); itr.Forth() )
        Postorder( GetDustKid, p_process );

    // process the current node
    p_process( p_node );
}

#endif