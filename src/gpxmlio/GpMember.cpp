#include <gpxmlio/GpMember.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <debug.hpp>

using namespace std;

namespace gpos
{
    GpMember::GpMember()
        : mAccess(PRIVATE)
    {
        DEBOUT("GpMember::GpMember");
    }

    GpType& GpMember::Type()
    {
        return mType;
    }

    void GpMember::Type(const GpType& val)
    {
        mType = val;
    }

    GpAccessType GpMember::Access()
    {
        return mAccess;
    }

    void GpMember::Access(GpAccessType val)
    {
        mAccess = val;
    }

    const string& GpMember::Name()
    {
        return mName;
    }

    void GpMember::Name(const string& val)
    {
        mName = val;
    }

    void GpMember::WriteAsXml(ofstream& ofstr)
    {
        DEBOUT("GpMember::WriteAsXml");

        ofstr << "<member";
        switch (mAccess)
        {
        case PRIVATE:
            ofstr << " access=\"private\"";
            break;
        case PUBLIC:
            ofstr << " access=\"public\"";
            break;
        case PROTECTED:
            ofstr << " access=\"protected\"";
            break;
        default:
            break;
        }
        ofstr << ">\n";
        mType.WriteAsXml(ofstr);
        ofstr << "<name>" << Name() << "</name>\n";
        ofstr << "</member>\n";

    #ifdef DEBUG
        cout << "<name>" << Name() << "</name>\n";
        cout << "</member>\n";
    #endif
    }
}
