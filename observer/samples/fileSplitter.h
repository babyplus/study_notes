#include <string>
#include <vector>
#include "iProgress.h"
#include "tracker.h"

class FileSplitter
{
    public:
        FileSplitter(const std::string& file_path, int file_number);
        virtual ~FileSplitter();
        void split();
        void add_iprogress(IProgress* iprogress);
        void remove_iprogress(IProgress* iprogress);

    protected:
        virtual void on_progress(float value);

    private:
        std::string m_file_path;
        int m_file_number;
        std::vector<IProgress*> m_iprogress_list;
};
