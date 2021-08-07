#include "delete.h"
#include "application.h"

Application::Application():Library()
{
    printf("Application begin\n");
}

Application::~Application()
{
    printf("Application end\n");
}

void Application::do_step2()
{
    printf("step2\n");
}

void Application::do_step4()
{
    printf("step4\n");
}

int main()
{
    Library * l = new Application();
    l->run();
    DELETE(l);
    return 0;
}

