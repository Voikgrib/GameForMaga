#ifndef GAMEOBJ_H
#define GAMEOBJ_H

class GameObject
{
	public:
	int _size;
	int _hp;	
	bool _isAlive = false;
	Vector2 _speed;
	Vector2 _coords;
	uint32_t _color;
	
	virtual void draw();
	virtual void move(float dt);
	virtual void update(float dt);
	virtual void setColor(uint32_t color);
	
	void setSpeed(Vector2 speed);
	void setCoord(Vector2 coords);
	
	Vector2 getCoords();
	
	int getHp();
	bool isAlive();
};

Vector2 GameObject::getCoords()
{
    return _coords;
}

void GameObject::setSpeed(Vector2 speed)
{
	_speed = speed;
}

void GameObject::setCoord(Vector2 coords)
{
	_coords = coords;
}

int GameObject::getHp()
{
    return _hp;
}

void GameObject::update(float dt)
{
	printf("ERROR: Update must to be declare in child class!\n");
}

void GameObject::draw()
{
	printf("ERROR: Draw must to be declare in child class!\n");
}

void GameObject::setColor(uint32_t color)
{
    _color = color;
}

void GameObject::move(float dt)
{
    if(!_isAlive)
        return;

	_coords = _coords + _speed * dt;
	
	if(_coords.x < 0)
		_coords.x = SCREEN_HEIGHT + _coords.x;

	if(_coords.y < 0)
		_coords.y = SCREEN_WIDTH + _coords.y;
	
	_coords.x = fmod(_coords.x, SCREEN_HEIGHT);
	_coords.y = fmod(_coords.y, SCREEN_WIDTH);
}

bool GameObject::isAlive()
{
	return _isAlive;
}

#endif
