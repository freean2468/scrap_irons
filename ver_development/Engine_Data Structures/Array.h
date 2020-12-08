#ifndef _Array_H_
#define _Array_H_

template<class Datatype>
class CArray{
protected:
	Datatype* m_array;		// �迭 ������
	int m_size;				// �迭�� ũ��
	int m_count;			// �׸��� ����
public:
	CArray();
	CArray(int p_size);
	~CArray();
	void Resize(int p_size);					// ũ�� ����
	void Insert(Datatype p_item, int p_index);	// ���� �׸� ����
	void Remove(int p_index);					// ���� �׸� ����
	void IncreseCount();						// �׸� ���� ����
	int GetCount();								// �׸� ���� ����
	int GetSize();								// ũ�� ��ȸ
	Datatype& Get(int p_y);

	bool WriteFile(const char* p_filename);		// �迭�� ��ũ�� ���
	bool ReadFile(const char* p_filename);		// ��ũ�κ��� �迭�� �б�

	Datatype& operator[](int p_index);		// ���� ������ �����ε�
	operator Datatype*();					// ��ȯ ������
};

template<class Datatype>
CArray<Datatype>::CArray(){
	m_array = NULL;
	m_size = 0;
	m_count = 0;
}

template<class Datatype>
CArray<Datatype>::CArray(int p_size){
	m_array = new Datatype[p_size];
	m_size = p_size;
	m_count = 0;

	for(int i = 0; i < m_size; i++){
		m_count++;
	}
}

template<class Datatype>
CArray<Datatype>::~CArray(){
	if(m_array != 0) delete[] m_array;
	m_array = 0;
}

template<class Datatype>
void CArray<Datatype>::Resize(int p_size){
	try{
		Datatype* newarray = new Datatype[p_size];

		int min, index;

		if(p_size < m_size) min = p_size;
		else				min = m_size;

		for(index = 0; index < min; index++){
			newarray[index] = m_array[index];
		}

		m_size = p_size;
		
		if(m_array != 0) delete[] m_array;
		m_array = newarray;
	}
	catch(bad_alloc ex){
		return;
	}
}

template<class Datatype>
void CArray<Datatype>::Insert(Datatype p_item, int p_index){
	int index;

	for(index = m_size - 1; index > p_index; index--){
		m_array[index] = m_array[index-1];
	}

	m_array[p_index] = p_item;
}

template<class Datatype>
void CArray<Datatype>::Remove(int p_index){
	delete m_array[p_index];
	m_array[p_index] = NULL;

	m_count--;
}

template<class Datatype>
void CArray<Datatype>::IncreseCount(){
	m_count++;
}

template<class Datatype>
int CArray<Datatype>::GetCount(){
	return m_count;
}

template<class Datatype>
int CArray<Datatype>::GetSize(){
	return m_size;
}

template<class Datatype>
Datatype& CArray<Datatype>::Get(int p_y){
	// p_y = ��, p_x = ��
	return m_array[p_y];
}

template<class Datatype>
Datatype& CArray<Datatype>::operator[](int p_index){
	return m_array[p_index];
}

template<class Datatype>
CArray<Datatype>::operator Datatype*(){
	return m_array;
}

template<class Datatype>
bool CArray<Datatype>::WriteFile(const char* p_filename){
	FILE* outfile = 0;
	int written = 0;

	try{
	outfile = fopen(p_filename, "wb");

	if(outfile == 0) throw;

	written = fwrite(m_array, sizeof(Datatype), m_size, outfile);
	fclose(outfile);

	if(written != m_size) throw;
	}
	catch(...){
		return false;
	}

	return true;
}

template<class Datatype>
bool CArray<Datatype>::ReadFile(const char* p_filename){
	FILE* infile = 0;
	int read = 0;

	try{
		infile = fopen(p_filename, "rb");
		if(infile = 0) throw;
	
		read = fread(m_array, sizeof(Datatype), m_size, infile);
		fclose(infile);
		if(read != m_size) throw;
	}
	catch(...){
		return false;
	}

	return true;
}

#endif