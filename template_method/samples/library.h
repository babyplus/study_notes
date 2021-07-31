#include <cstdio>

class Library
{
    public:
        Library();
        virtual ~Library();
	void run();

    private:
	void step1();
	virtual void do_step2() = 0;
	void step3();
	virtual void do_step4() = 0;
	void step5();
};
