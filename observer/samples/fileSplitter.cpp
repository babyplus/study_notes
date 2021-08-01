#include "fileSplitter.h"

FileSplitter::FileSplitter(const std::string& file_path, int file_number):m_file_path(file_path),m_file_number(file_number)
{
    TRACK("begin");
}

FileSplitter::~FileSplitter()
{
    TRACK("end");
}

void FileSplitter::split()
{
    TRACK("todo: read the file(\"%s\")", m_file_path.c_str());
    int i = 0;
    for (i=0; i < m_file_number; i++)
    {
        float progress_value = m_file_number;
        progress_value = (i + 1) / progress_value;
        on_progress(progress_value);
    }
}

void FileSplitter::add_iprogress(IProgress* iprogress)
{
    TRACK();
    m_iprogress_list.push_back(iprogress);
}

void FileSplitter::remove_iprogress(IProgress* iprogress)
{
    for (std::vector<IProgress*>::iterator it = m_iprogress_list.begin() ; it != m_iprogress_list.end();)
    {
        if(iprogress == *it)
        {
            TRACK();
            m_iprogress_list.erase(it);
        }
        else ++it;
    }
}

void FileSplitter::on_progress(float value)
{
    TRACK();
    for (std::vector<IProgress*>::iterator it = m_iprogress_list.begin() ; it != m_iprogress_list.end(); ++it)
    {
        (*it)->do_progress(value);
    }
}


