
#define PI 3.1415

const int Left = -1;
const int Right = 1;
const float RotSpeed = PI;
const float SpeedMod = 300;
const float SpeedMax = SpeedMod * 2;

class Player : public GameObject
{
	private:
	Vector2 _direction;
	float _curAngle;
	float _shootColldown = 1;
	float _timeFromLastShoot = 1;
	
	public:
	Player(int hp, Vector2 pos);
	Player(int hp, Vector2 pos, uint32_t color);
	
	void setSpeed(Vector2 speed);	
	void setCoord(Vector2 coords);
	void setShootCooldown(float cooldown);
	void rotate(float dt, int dir);
	void updSpeed(float dt);
	
	void getDamage(int damage);
	void heal(int hp);
	void shoot(Bullet* bullets, int size);
	void checkHitByAsteroids(Asteroid* asteroids, int size);
	
	virtual void draw() override;
	virtual void update(float dt) override;
};






Player::Player(int hp, Vector2 pos)
{
	_isAlive = true;
	_hp = hp;
	_curAngle = 0;
	_size = 20;
	
	_coords = pos;
	
	_direction.x = 0;
	_direction.y = 1;
	_color = 0x00ff00ff;
	_shootColldown = 1;
	_timeFromLastShoot = 1;
}

Player::Player(int hp, Vector2 pos, uint32_t color)
{
	_isAlive = true;
	_hp = hp;
	_curAngle = 0;
	_size = 20;
	
	_coords = pos;
	
	_direction.x = 0;
	_direction.y = 1;
	_color = color;
	_shootColldown = 1;
	_timeFromLastShoot = 1;
}

//
// Check if player center and both ends touch the asteroid
//
void Player::checkHitByAsteroids(Asteroid* asteroids, int size)
{
    for(int i = 0; i != size; i++)
    {
        if(!asteroids[i].isAlive())
            continue;
            
        if (asteroids[i].isCollideWithCoord(_coords) ||
            asteroids[i].isCollideWithCoord(_coords + _direction * size) || 
            asteroids[i].isCollideWithCoord(_coords - _direction * size))
            {
                getDamage(1);
                asteroids[i].getDamage(1000);
            }
    }
}

void Player::setShootCooldown(float cooldown)
{
    _shootColldown = cooldown;
    _timeFromLastShoot = cooldown;
}

void Player::update(float dt)
{
    if(!_isAlive)
        return;
        
    _timeFromLastShoot += dt;
}


void Player::shoot(Bullet* bullets, int size)
{
    //bullet->shoot(_coords, _direction * 300, 10, 0xffffff00, 1, _curAngle);
    int tmp = -1;
    
    if(_timeFromLastShoot <= _shootColldown)
        return;

    for(int i = 0; i != size; i++)
    {
        if(!bullets[i].isAlive())
        {
            tmp = i;
            break;
        }
    }
        
    if(tmp == -1)
        return;
        
    bullets[tmp].shoot(_coords + _direction * size, 
                     _direction * 300 + _speed,
                     10, 
                     0xffffff00, 
                     1,
                     _curAngle);
                     
    _timeFromLastShoot = 0;
}


void Player::draw() //
{	
    if(!_isAlive)
        return;
        
	Vector2 tmp;
	Vector2 tmp_l;
	Vector2 tmp_r;
	
	// some math for triangle
	tmp = _direction * _size;
	
	tmp_l.x = tmp.y;
	tmp_l.y = - tmp.x;

	tmp_r.x = - tmp.y;
	tmp_r.y = tmp.x;
	
	tmp_l.normalize();
	tmp_r.normalize();
	
	// draw player here
	for(int i = -_size; i <= _size; i++)
	{
		tmp = _coords - _direction * i;
		
		for(int j = -_size - i; j != _size + i; j++)
		{
		    tmp = tmp - tmp_l * j / 10;
		    
		    if(tmp.x < 0)
    			tmp.x = SCREEN_HEIGHT + tmp.x;
    		if(tmp.y < 0)
    			tmp.y = SCREEN_WIDTH + tmp.y;
        
    		buffer[((int) tmp.x) % SCREEN_HEIGHT][((int) tmp.y) % SCREEN_WIDTH] = _color;
    		
    		tmp = tmp - tmp_r * j / 10;
		    
		    if(tmp.x < 0)
    			tmp.x = SCREEN_HEIGHT + tmp.x;
    		if(tmp.y < 0)
    			tmp.y = SCREEN_WIDTH + tmp.y;
        
    		buffer[((int) tmp.x) % SCREEN_HEIGHT][((int) tmp.y) % SCREEN_WIDTH] = _color;
		}
	}
}


void Player::updSpeed(float dt) //
{
	_speed = _speed + (_direction * SpeedMod * dt);
}


void Player::rotate(float dt, int dir) //
{
	_curAngle += fmod((dt * dir * RotSpeed), (2 * PI));
	
	_direction.x = sin(_curAngle);
	_direction.y = cos(_curAngle);
}



void Player::setSpeed(Vector2 speed)
{
	_speed = speed;
}


void Player::setCoord(Vector2 coords)
{
	_coords = coords;
}


void Player::getDamage(int damage)
{
	_hp -= damage;
	
	if(_hp <= 0)
		_isAlive = false;	
}


void Player::heal(int hp)
{
	_hp += hp;		
}
