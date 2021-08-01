#ifndef __IPROGRESS__
#define __IPROGRESS__

class IProgress
{
    public:
        virtual void do_progress(float value) = 0;
        virtual ~IProgress();
};

#endif
