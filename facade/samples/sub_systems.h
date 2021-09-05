#include "sub_system.h"

class SubSystemA : public SubSystem
{
    public:
        SubSystemA();
        virtual ~SubSystemA();
        virtual void methodA();
        virtual void method();
};

class SubSystemB : public SubSystem
{
    public:
        SubSystemB();
        virtual ~SubSystemB();
        virtual void methodB();
        virtual void method();
};

class SubSystemC : public SubSystem
{
    public:
        SubSystemC();
        virtual ~SubSystemC();
        virtual void methodC();
        virtual void method();
};

class SubSystemD : public SubSystem
{
    public:
        SubSystemD();
        virtual ~SubSystemD();
        virtual void methodD();
        virtual void method();
};

