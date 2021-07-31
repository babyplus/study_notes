#include <cstdio> 
#include "library.h"

class Application : public Library
{
    public:
        Application();
	virtual ~Application();
	void do_step2();
	void do_step4();
};
