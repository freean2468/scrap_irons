#ifndef _LQueue_H_
#define _LQueue_H_

template<class Datatype>
class CLQueue : public CDLinkedList<Datatype>{
public:
	void Enqueue(Datatype p_Data);
	void Dequeue();
	Datatype Front();
	int Count();
};

template<class Datatype>
void CLQueue<Datatype>::Enqueue(Datatype p_data){
	Append(p_data);
}

template<class Datatype>
void CLQueue<Datatype>::Dequeue(){
	RemoveHead();
}

// Top �Լ��� ������ ��� ������ ����� �۵����� �ʴ´�.
template<class Datatype>
Datatype CLQueue<Datatype>::Front(){
	return m_head->m_data;
}

template<class Datatype>
int CLQueue<Datatype>::Count(){
	return m_count;
}

#endif