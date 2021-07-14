
class Bullet : public GameObject
{
	private:
	Vector2 _direction;
	float _curAngle;
	float _lifeTime;
	
	public:
	Bullet();
	
	void shoot(Vector2 coords, Vector2 speed, int size, uint32_t color, float lifetime, float angle);
	void off();
	
	virtual void draw() override;
	virtual void update(float dt) override;
};



Bullet::Bullet()
{
    _isAlive = false;
}

void Bullet::update(float dt)
{
    if(!_isAlive)
        return;

    _lifeTime -= dt;
   
    if(_lifeTime <= 0)
        _isAlive = false;
}

void Bullet::off()
{
    _isAlive = false;
}

void Bullet::shoot(Vector2 coords, Vector2 speed, int size, uint32_t color, float lifetime, float angle)
{
    _speed = speed;
    speed.normalize();
    _direction = speed;
    _color = color;
    _coords = coords;
    _lifeTime = lifetime;
    _curAngle = angle;
    _isAlive = true;
}


void Bullet::draw()
{
    if(!_isAlive)
        return;

	for(int i = _coords.x; i <= _coords.x + _size; i++)
		for(int j = _coords.y; j <= _coords.y + _size; j++)
		{
			if(i < 0)
				i = SCREEN_HEIGHT + i;
				
			if(j < 0)
				j = SCREEN_WIDTH + j;
						
			buffer[i % SCREEN_HEIGHT][j % SCREEN_WIDTH] = _color;
		}
}





//
//  functions not from bullet class, but it is connected with bullets
//




void allBulletsHitAsteroid(Bullet* bullets, int maxBullets, Asteroid* asteroids, int maxAsteroids)
{
    for(int curBullet = 0; curBullet != maxBullets; curBullet++)
    {
        if(!bullets[curBullet].isAlive())
            continue;
    
        for(int curAsteroid = 0; curAsteroid != maxAsteroids; curAsteroid++)
        {
            if(!asteroids[curAsteroid].isAlive())
                continue;
            if (asteroids[curAsteroid].isCollideWithCoord (bullets[curBullet].getCoords()) )
            {
                asteroids[curAsteroid].getDamage(1);
                bullets[curBullet].off();
                break;
            }
        }
    }
}



void drawAllBullets(Bullet* bullets, int size)
{
    for(int i = 0; i != size; i++)
    {
        if(bullets[i].isAlive())
            bullets[i].draw();
    }
}


void moveAllBullets(Bullet* bullets, int size, float dt)
{
    for(int i = 0; i != size; i++)
    {
        if(bullets[i].isAlive())
            bullets[i].move(dt);
    }
}

void updAllBullets(Bullet* bullets, int size, float dt)
{
    for(int i = 0; i != size; i++)
    {
        if(bullets[i].isAlive())
            bullets[i].update(dt);
    }
}




