#include "sub_systems.h"

SubSystemA::SubSystemA()
{
    TRACK("begin");
}

SubSystemA::~SubSystemA()
{
    TRACK("end");
}

void SubSystemA::methodA()
{
    TRACK();
}

void SubSystemA::method()
{
     methodA();
}

SubSystemB::SubSystemB()
{
    TRACK("begin");
}

SubSystemB::~SubSystemB()
{
    TRACK("end");
}

void SubSystemB::methodB()
{
    TRACK();
}

void SubSystemB::method()
{
     methodB();
}

SubSystemC::SubSystemC()
{
    TRACK("begin");
}

SubSystemC::~SubSystemC()
{
    TRACK("end");
}

void SubSystemC::methodC()
{
    TRACK();
}

void SubSystemC::method()
{
     methodC();
}

SubSystemD::SubSystemD()
{
    TRACK("begin");
}

SubSystemD::~SubSystemD()
{
    TRACK("end");
}

void SubSystemD::methodD()
{
    TRACK();
}

void SubSystemD::method()
{
     methodD();
}

