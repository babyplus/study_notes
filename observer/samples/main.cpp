#include "fileSplitter.h"
#include "consoleNotifier.h"

int main()
{
    FileSplitter splitter("path......", 10);
    ConsoleNotifier cn;
    splitter.add_iprogress(&cn);
    splitter.split();
    splitter.remove_iprogress(&cn);
    splitter.split();
}
