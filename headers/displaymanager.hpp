#ifndef DISPLAYMANAGER_HPP
#define DISPLAYMANAGER_HPP

#include <string>

class DisplayManager
{
    public:
             DisplayManager(std::ostream& stream, bool autoIncrement = true)
             : mStream(&stream)
             , mAutoIncrement(autoIncrement)
             , mIncrement(0)
             {
             }

        template <typename OUTPUT>
        void display(OUTPUT out)
        {
            (*mStream) << out;
        }


        template <typename D>
        friend DisplayManager& operator<<(DisplayManager& dm, const D& data)
        {
            if(dm.mAutoIncrement)
                (*dm.mStream) << dm.mIncrement++ << " ";
            (*dm.mStream) << data << "\n";

            return dm;
        }

    private:
        std::ostream*   mStream;
        bool            mAutoIncrement;
        unsigned int    mIncrement;

};


#endif // DISPLAYMANAGER_HPP
