#include <string>
#include "myCollection.h"

int main()
{
    std::string s0 = "s0";
    std::string s1 = "s1";
    std::string s2 = "s2";
    std::string s3 = "s3";
    MyCollection<std::string*>* mc = new MyCollection<std::string*>();
    mc->add(&s0);
    mc->add(&s1);
    mc->add(&s2);
    mc->add(&s3);

    MyIterator<MyCollection<std::string*>>* it = mc->get_iterator();
    for(it->first();it->is_done();it->next())
    {
        TRACK("%s\n", mc->get(it->get_current())->c_str());
    }

    DELETE(mc);
    return 0;
}
