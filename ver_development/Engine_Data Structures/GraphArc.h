#ifndef _GraphArc_H_
#define _GraphArc_H_

template<class NodeType, class ArcType> class CGraphNode;

// �׷����� ȣ�� ��ǥ�ϴ� ������ Ŭ����,
// ��带 ����Ű�� ������ �ϳ��� ȣ�� �ο��� ����ġ �ϳ��� �����Ѵ�.
template<class NodeType, class ArcType>
class CGraphArc{
public:
	CGraphNode<NodeType, ArcType>* m_node;
	ArcType m_weight;
};

#endif