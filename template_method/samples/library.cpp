#include "library.h"

Library::Library()
{
    printf("Library begin\n");	
}
Library::~Library()
{
    printf("Library end\n");	
}
void Library::step1()
{
    printf("step1\n");
}
void Library::step3()
{
    printf("step3\n");
}
void Library::step5()
{
    printf("step5\n");
}
void Library::run()
{
    step1();
    do_step2();
    step3();
    do_step4();
    step5();
}
//int main()
//{
//    Library * l = new Library();
//    l->run();
//    delete l;
//    return 0;
//}
