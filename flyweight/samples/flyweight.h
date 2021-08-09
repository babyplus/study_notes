#include <unordered_map>
#include <string>
#include "entry.h"
#include "tracker.h"
#include "delete.h"

class Flyweight
{
    private:
        std::unordered_map<std::string, Entry*> pool;

    public:
        Flyweight();
        virtual ~Flyweight();
        virtual Entry* findEntryOrCreate(const std::string&);
};

