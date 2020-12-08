////////////////////////////////////////////////////////////
// 추상적인 x,y 좌표계 에서의 실제 위치를 나타내는 클래스
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