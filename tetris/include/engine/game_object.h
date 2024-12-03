#pragma once


class Object
{
public:
    virtual ~Object() {}
};

class GameObject: public Object 
{
public:
    virtual ~GameObject() {}
    virtual void Update() = 0;
};


