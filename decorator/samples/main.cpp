#include "delete.h"
#include "fileStream.h"
#include "cryptoStream.h"

int main()
{
    TRACK("new s1");
    Stream* s1 = new FileStream();
    char buf[10240] = {0};
    s1->read(1, buf, sizeof(buf));
    TRACK("------------------------------");
    TRACK("add decorator");
    TRACK("new s2");
    CryptoStream* s2 = new CryptoStream(s1);
    char buf2[10240] = {0};
    s2->read(1, buf2, sizeof(buf2));
    TRACK("delete s1");
    DELETE(s1);
    TRACK("delete s2");
    DELETE(s2);
    return 0;
}
