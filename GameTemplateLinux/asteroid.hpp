

class Asteroid : public GameObject
{
	private:
	
	public:
	Asteroid();
	Asteroid(int size, int hp);
	Asteroid(int size, int hp, uint32_t color);
	
	//void setSpeed(Vector2 speed);	
	//void setCoord(Vector2 coords);
	void getDamage(int damage);
	bool isCollideWithCoord(Vector2 coord); 
	
	virtual void update(float dt) override;
	virtual void draw() override;
	void awake(Vector2 coord, Vector2 speed, int size, int hp, uint32_t color); //
};




Asteroid::Asteroid()
{
    _isAlive = false;
}

Asteroid::Asteroid(int size, int hp)
{
	_size = size;
	_hp = hp;
	_isAlive = true;
	_color = 0x00ffff00;
}

Asteroid::Asteroid(int size, int hp, uint32_t color)
{
	_size = size;
	_hp = hp;
	_isAlive = true;
	_color = color;
}

//
// This function awakes dead asteroid and give it LIVVVVVE
// 
void Asteroid::awake(Vector2 coord, Vector2 speed, int size, int hp, uint32_t color)
{
    _coords = coord;
    _speed = speed;
    _size = size;
    _hp = hp;
    _color = color;
    _isAlive = true;
}

//
// This function check is asteroid hit some coordinates
//
bool Asteroid::isCollideWithCoord(Vector2 coord)
{
    Vector2 tmp = _coords - coord;
    
    if(tmp.lenSqr() < _size * _size)
        return true;
        
    return false; 
}


void Asteroid::getDamage(int damage)
{
	_hp -= damage;
	
	if(_hp <= 0)
	{
		_isAlive = false;	
		Score++;
	}
}

// TODO color change on damage
void Asteroid::update(float dt) 
{
    if(!_isAlive)
        return;
        
    return;
}


void Asteroid::draw() 
{
    if(!_isAlive)
        return;

	for(int i = (int) _coords.x - _size; i <= (int) _coords.x + _size; i++)
		for(int j = (int) _coords.y - _size; j <= (int) _coords.y + _size; j++)
		{
		    int tmp = pow(_coords.x - i, 2) + pow(_coords.y - j, 2);
		    
		    if(tmp <= (_size * _size))
            {		
			    if(i < 0)
			    { 
			        buffer[i + SCREEN_HEIGHT][j % SCREEN_WIDTH] = _color;
				    continue;
				}
				    
			    if(j < 0)
			    { 
			        buffer[i % SCREEN_HEIGHT][j + SCREEN_WIDTH] = _color;        
				    continue;
				}
						    
			    buffer[i % SCREEN_HEIGHT][j % SCREEN_WIDTH] = _color;
            } 
		}
}




//
//  functions not from asteroid class, but it is connected with asteroids
//
void addRandomAsteroid(Asteroid* asteroids, int size)
{
    int tmp = -1;

    for(int i = 0; i != size; i++)
    {
        if(!asteroids[i].isAlive())
        {
            tmp = i;
            break;
        }
    }
        
    if(tmp == -1)
        return;

    asteroids[tmp].awake(Vector2 (rand() % 100 + 10, rand() % 100 + 10),
                         Vector2 (rand() % 100 - 50, rand() % 300 - 150),
                         rand() % 30 + 10,
                         rand() % 3 + 1,
                         0x00ff00ff - (rand() % 4) * 0x00004400);
}


void drawAllAsteroids(Asteroid* asteroids, int size)
{
    for(int i = 0; i != size; i++)
    {
        if(asteroids[i].isAlive())
            asteroids[i].draw();
    }
}


void moveAllAsteroids(Asteroid* asteroids, int size, float dt)
{
    for(int i = 0; i != size; i++)
    {
        if(asteroids[i].isAlive())
            asteroids[i].move(dt);
    }
}

