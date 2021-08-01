#include "iProgress.h"
#include "tracker.h"

class ConsoleNotifier : public IProgress
{
    public:
        ConsoleNotifier();
        virtual ~ConsoleNotifier();
        virtual void do_progress(float value);
};
