#include "tracker.h"
#include "iProgress.h"
#include <cstdio> 

IProgress::~IProgress()
{
    TRACK("IProgress end");
}
