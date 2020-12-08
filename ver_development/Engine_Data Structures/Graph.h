// �׷����� ��ǥ�ϴ� Graph Ŭ����
// �� Ŭ������ ��� ������ �����ϸ� ��� �߰� �� ����, ȣ �߰� �� ����, ȣ�� ǥ�� �� ����, ��� Ž�� ��
// �׷����� ���õ� ��� ��ɵ��� �����Ѵ�.
#ifndef _Graph_H_
#define _Graph_H_

template<class NodeType, class ArcType> class CGraphArc;
template<class NodeType, class ArcType> class CGraphNode;
template<class NodeType, class ArcType> class CGraph;
template<class DataType> class CArray;
template<class DataType> class CLQueue;

template<class NodeType, class ArcType>
class CGraph{
public:
	typedef CGraphArc<NodeType, ArcType> Arc;
	typedef CGraphNode<NodeType, ArcType> Node;

	CArray<Node*> m_nodes;	// Node �����͵��� �迭
	int m_count;			// ������ ������ ���ϴ� ���� ����

public:
	CGraph(int p_size);
	~CGraph();

	bool AddNode(NodeType p_data, int p_index);
	void RemoveNode(int p_index);

	bool AddArc(int p_from, int p_to, ArcType p_weight);
	void RemoveArc(int p_from, int p_to);

	CGraphArc<NodeType, ArcType>* GetArc(int p_from, int p_to);

	void ClearMarks();

	void DepthFirst(Node* p_node, void (*p_process)(Node*));
	void BreadthFirst(Node* p_node, void (*p_process)(Node*));
};

template<class NodeType, class ArcType>
CGraph<NodeType, ArcType>::CGraph(int p_size)
: m_nodes(p_size){
	int i;
	for(i = 0; i<p_size; i++)
		m_nodes[i] = 0;
	m_count = 0;
}

template<class NodeType, class ArcType>
CGraph<NodeType, ArcType>::~CGraph(){
	int index;
	for(index = 0; index < m_nodes.m_size; index++){
		if(m_nodes[index] != 0)
			delete m_nodes[index];
	}
}

template<class NodeType, class ArcType>
bool CGraph<NodeType, ArcType>::AddNode(NodeType p_data, int p_index){
	if(m_nodes[p_index] !=)
		return false;
	m_nodes[p_index] = new Node;
	m_nodes[p_index]->m_data = p_data;
	m_nodes[p_index]->m_marked = false;
	m_count++;
	return true;
}

template<class NodeType, class ArcType>
void CGraph<NodeType, ArcType>::RemoveNode(int p_index){
	if(m_nodes[p_index] == 0)
		return;

	int node;
	Arc* arc;

	for(node = 0; node < m_node.Size(); node++){
		if(m_nodes[node] != 0){
			// �� ����� ȣ�� �� ������ ��带 ����Ű�� ȣ���� �ִ��� ����.
			arc = m_nodes[node]->GetArc(m_nodes[p_index]);
			// ������ ��带 ����Ű�� ȣ�� �����Ѵٸ� arc�� 0�� �ƴϸ�,
			// ���ٸ� 0�̴�.
			// �� ��忡�� p_index�� �ش��ϴ� ���(������ ���)�� ����Ű�� ȣ�� �����Ѵٸ�,
			// �� ȣ�� �����Ѵ�.
			if(arc != 0)
				RemoveArc(node, p_index);
		}
	}
	delete m_nodes[p_index];
	m_nodes[p_index] = 0;
	m_count--;
}

// �� �Լ��� ���� ��� p_from���� ��ǥ ��� p_to��带 ����Ű��
// ����ġ�� p_weight�� ȣ�� �߰��Ѵ�. �Լ��� �켱 �� ������ ��ȿ���� �����ϰ�,
// �� �� �ϳ��� ��ȿ���� �ʴٸ� ���и� ���ϴ� false�� ��ȯ�Ѵ�.
template<class NodeType, class ArcType>
bool CGraph<NodeType, ArcType>::AddArc(int p_from, int p_to, ArcType p_weight){
	if(m_nodes[p_from] == 0 || m_nodes[p_to] == 0)
		return false;
	// �� �� ��ȿ�ϴٸ�, ���� ��忡�� ��ǥ ��带 ����Ű�� ȣ�� �̹� �����ϴ��� �����Ѵ�.
	if(m_ndoes[p_from]->GetArc(m_nodes[p_to]) != 0)
		return false;
	m_nodes[p_from]->AddArc(m_nodes[p_to], p_weight);
	return true;
}

template<class NodeType, class ArcType>
void CGraph<NodeType, ArcType>::RemoveArc(int p_from, int p_to){
	if(m_nodes[p_from] == 0 || m_nodes[p_to] == 0)
		return;
	m_nodes[p_from]->RemoveArc(m_nodes[p_to]);
}

template<class NodeType, class ArcType>
CGraphArc<NodeType, ArcType>* CGraph<NodeType, ArcType>::GetArc(int p_from, int p_to){
	if(m_nodes[p_from] == 0 || m_nodes[p_to] == 0)
		return 0;
	return m_nodes[p_from]->GetArc(m_nodes[p_to]);
}

template<class NodeType, class ArcType>
void CGraph<NodeType, ArcType>::ClearMarks(){
	int index;
	for(index = 0; index < m_nodes.m_size; index++){
		if(m_nodes[index] != 0)
			m_nodes[index]->m_marked = false;
	}
}

// ���� �켱 Ž�� �Լ�
// ���� ��带 ����Ű�� ��� �����Ϳ� ��带 ó���ϴ� �� ���̴� �Լ��� ����Ű�� �Լ� �����͸� �޴´�.
template<class NodeType, class ArcType>
void CGraph<NodeType, ArcType>::DepthFirst(Node* p_node, void (*p_process)(Node*)){
	if(p_node == 0)
		return;

	p_process(p_node);
	p_node->m_marked = true;

	CDListIterator<CGraphArc <CCoordinates, int> > itr = p_node->m_arcList.GetIterator();

	// ���� ����� ��� ȣ���� �����鼭 ���� ǥ�õ��� ���� ��带 ����Ű�� ȣ�� ������
	// �� ��忡 ���� �� �Լ��� ��������� ȣ��
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(GetDustKid.m_node->m_marked == false){
			DepthFirst(GetDustKid.m_node, p_process);
		}
	}
}

// �ʺ� �켱 Ž�� �Լ�
template<class NodeType, class ArcType>
void CGraph<NodeType, ArcType>::BreadthFirst(Node *p_node, void (*p_process)(Node*)){
	if(p_node == 0)
		retrurn;

	// ��⿭�� ȣ �ݺ��� ����
	CLQueue<Node*> quque;
	CDListIterator<Arc> itr;

	// ���� ��带 ��⿭�� �ְ� ǥ��
	queue.Enqueue(p_node);
	p_node->m_marked = true;

	// ��⿭�� �� ������
	while(queue.Count() != 0){
		// ��⿭�� ó�� ��带 ó���� ����
		p_process(queue.Front());
		itr = queue.Front()->m_arcList.GetIterator();
		for(itr.Start(); itr.Valid(); itr.Forth()){
			// �� ����� �ڽ� ���� �� ǥ�ð� �Ǿ� ���� ���� ��� ������
			// ��⿭�� �ְ� ǥ���Ѵ�.
			if(GetDustKid.m_node->m_marked == false){
				GetDustKid.m_node->m_marked = true;
				queue.Enqueue(GetDustKid.m_node);
			}
		}
		// �׷� ���� ó�� ��带 ť���� �̰� ������ �ݺ��Ѵ�.
		queue.Dequeue();
	}
}

#endif