////////////////////////////////////////////////////////////
// �߻����� x,y ��ǥ�� ������ ���� ��ġ�� ��Ÿ���� Ŭ����
////////////////////////////////////////////////////////////
#ifndef _Coordinates_H_
#define _Coordinates_H_

class CCoordinates{
private:
	float x;
	float y;

public:
	CCoordinates();
	~CCoordinates();

	CCoordinates& operator=(float p_ftemp);
	float GetX(){return x;}
	float GetY(){return y;}
	void SetX(float _x){x = _x;}
	void SetY(float _y){y = _y;}
};

#endif