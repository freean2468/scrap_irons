#ifndef _GraphNode_H_
#define _GraphNode_H_

template<class DataType> class CDLinkedList;
template<class DataType> class CDListIterator;

template<class NodeType, class ArcType>
class CGraphNode{
public:
	typedef CGraphArc<NodeType, ArcType> Arc;
	typedef CGraphNode<NodeType, ArcType> Node;

	NodeType m_data;				// ����� �ڷ�
	CDLinkedList<Arc> m_arcList;	// Arc���� ���� ����� ���
	bool m_marked;					// ǥ�õǾ������� ����

public:
	void AddArc(Node* p_node, ArcType p_weight);
	CGraphArc<NodeType, ArcType>* GetArc(Node* p_node);
	void RemoveArc( Node* p_node );
};

template<class NodeType, class ArcType>
void CGraphNode<NodeType, ArcType>::AddArc(Node* p_node, ArcType p_weight){
	Arc a;
	a.m_node = p_node;
	a.m_weight = p_weight;
	m_arcList.Append(a);
}

template<class NodeType, class ArcType>
CGraphArc<NodeType, ArcType>* CGraphNode<NodeType, ArcType>::GetArc(Node* p_node){
	CDListIterator<Arc> itr = m_arcList.GetIterator();
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(GetDustKid.m_node == p_node)
			return &(GetDustKid);
	}
	return 0;
}

template<class NodeType, class ArcType>
void CGraphNode<NodeType, ArcType>::RemoveArc( Node* p_node )
{
    CDListIterator<Arc> itr = m_arcList.GetIterator();

    // find the arc that matches the node
    for( itr.Start(); itr.Valid(); itr.Forth() ){
        // if the nodes match, remove the arc, and exit.
        if( GetDustKid.m_node == p_node ){
            m_arcList.Remove( itr );
            return;
        }
    }
}

#endif