

class Vector2
{
	public:
	
	float x;
	float y;

	Vector2& operator= (Vector2 vec)
	{
		x = vec.x;
		y = vec.y;

		return *this;
	}
	
	Vector2(float inx, float iny)
	{
		x = inx;
		y = iny;
	}
	
	Vector2() 
	{
		x = 0; 
		y = 0;
	}
	
	void normalize();
	float lenSqr();
};









float Vector2::lenSqr()
{
	return x*x + y*y;
}


void Vector2::normalize()
{
	float tmp = sqrt(x * x + y * y);
	x = x / tmp;
	y = y / tmp;
}


Vector2 operator+ (Vector2 fir, Vector2 sec)
{
	Vector2 ret(0, 0);
	
	ret.x = fir.x + sec.x;
	ret.y = fir.y + sec.y;

	return ret;
}

Vector2 operator- (Vector2 fir, Vector2 sec)
{
	Vector2 ret(0, 0);
	
	ret.x = fir.x - sec.x;
	ret.y = fir.y - sec.y;

	return ret;
}

Vector2 operator* (Vector2 vec, float num)
{
	Vector2 ret(0, 0);
	
	ret.x = vec.x * num;
	ret.y = vec.y * num;

	return ret;
}

Vector2 operator/ (Vector2 vec, float num)
{
	Vector2 ret(0, 0);
	
	ret.x = vec.x / num;
	ret.y = vec.y / num;

	return ret;
}
