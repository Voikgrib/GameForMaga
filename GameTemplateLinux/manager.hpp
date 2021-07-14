
//
// List of game objects for game manager
//
class ObjListElement
{
    public:
    GameObject* obj;
    ObjListElement* next;
    ObjListElement* prev;

    ObjListElement();        
};

ObjListElement::ObjListElement()
{
    obj = NULL;
    next = NULL;
    prev = NULL;
}

//
// Manager to do GameObjects func and metods for list
//
class Manager
{
    private:
    ObjListElement* _objs;
    ObjListElement* _tail;
    
    public:
    Manager();
    Manager(GameObject* first);
    ~Manager();
    
    void addObj(GameObject *obj);
    void addObjArray(void *obj, int size, unsigned long int sizeType);
    void drawAll();
    void moveAll(float dt);
    void updateAll(float dt);
};


Manager::Manager()
{
    _objs = NULL;
    _tail = NULL;
}


Manager::Manager(GameObject* first)
{
    addObj(first);
    _objs = _tail;
}


Manager::~Manager()
{
    ObjListElement* cur = _objs;
    
    while(cur != _tail)
    {
        cur = cur->next;
        delete cur->prev;
    }
    
    delete cur;
}


void Manager::updateAll(float dt)
{
    ObjListElement* cur = _objs;
    
    while(cur->next != NULL)
    {
        cur->obj->update(dt);
            
        cur = cur->next;
    }
}


void Manager::moveAll(float dt)
{
    ObjListElement* cur = _objs;
    
    while(cur->next != NULL)
    {
        cur->obj->move(dt);
            
        cur = cur->next;        
    }
}


void Manager::drawAll()
{
    ObjListElement* cur = _objs;
    
    while(cur->next != NULL)
    {
        cur->obj->draw();
            
        cur = cur->next;
    }
}


void Manager::addObjArray(void *obj, int size, unsigned long int sizeType)
{
    for(int i = 0; i != size; i++)
    {
        addObj((class GameObject*)(obj + i * sizeType));
    }
}


void Manager::addObj(GameObject *obj)
{
    ObjListElement* newElem = new ObjListElement;
    
    newElem->obj = obj;
    newElem->prev = _tail;
    newElem->next = NULL;
    
    if(_tail != NULL)
        _tail->next = newElem;
    else
    {
        _objs = newElem;
    }
    
    _tail = newElem;
    //printf("Object added!\n");
}


