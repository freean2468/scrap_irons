#include "../BaseHeader.h"

CBitvector::CBitvector(int p_size){
	m_array = 0;
	m_size = 0;
	Resize(p_size);
}

CBitvector::~CBitvector(){
	if(m_array != 0)
		delete[] m_array;
	m_array = 0;
}

void CBitvector::Resize(int p_size){
	unsigned long int* newvector = 0;

	if(p_size % 32 == 0) p_size = p_size / 32;
	else				 p_size = (p_size / 32) + 1;

	newvector = new unsigned long int[p_size];

	if(newvector == 0)	return;

	int min;

	if(p_size < m_size) min = p_size;
	else				min = m_size;

	int index;
	for(index = 0; index < min; index++) newvector[index] = m_array[index];

	m_size = p_size;

	if(m_array != 0) delete[] m_array;

	m_array = newvector;
}

void CBitvector::Set(int p_index, bool p_value){
	int cell = p_index/32;
	int bit = p_index%32;

	if(p_value = true) m_array[cell] = (m_array[cell] | (1 << bit));
	else			   m_array[cell] = (m_array[cell] & (~(1 << bit)));
}

void CBitvector::ClearAll(){
	int index;
	for(index = 0; index < m_size; index++) m_array[index] = 0;
}

void CBitvector::SetAll(){
	int index;
	for(index = 0; index < m_size; index++) m_array[index] = 0xFFFFFFFF;	// F �� 4��Ʈ
}

bool CBitvector::WriteFile(const char* p_filename){
	try{
		FILE* outfile = 0;
		int written = 0;

		outfile = fopen(p_filename, "wb");
		if(outfile == 0) throw;

		written = (int)fwrite(m_array, (size_t)sizeof(unsigned long int), (size_t)m_size, outfile);

		fclose(outfile);
		if(written != m_size) throw;

		return true;
	}
	catch(...){
		return false;
	}
}

bool CBitvector::ReadFile(const char* p_filename){
	try{
		FILE* infile = 0;
		int read = 0;

		infile = fopen(p_filename, "rb");
		if(infile == 0) throw;

		read = (int)fread(m_array, sizeof(unsigned long int), m_size, infile);
		
		fclose(infile);
		if(read != m_size) throw;

		return true;
	}
	catch(...){
		return false;
	}
}

bool CBitvector::operator[](int p_index){
	// �ش� ��Ʈ�� �ִ� ĭ�� ã�´�.
	int cell = p_index / 32;		

	// �� ĭ���� �ش� ��Ʈ�� ��ġ�� ã�´�.
	int bit = p_index % 32;

	// �ش� ��Ʈ�� 0 �Ǵ� 1�� �ǵ��� ������ �ڸ��� �̵���Ų��.
	return ((m_array[cell] & (1 << bit)) >> bit);
}