#include "consoleNotifier.h"

ConsoleNotifier::ConsoleNotifier()
{
    TRACK("begin");
}

ConsoleNotifier::~ConsoleNotifier()
{
    TRACK("end");
}

void ConsoleNotifier::do_progress(float value)
{
    TRACK();
}

