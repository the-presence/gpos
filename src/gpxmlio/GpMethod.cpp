#include <gpxmlio/GpMethod.hpp>
#include <debug.hpp>

namespace gpos
{

    GpMethod::GpMethod()
        : mConst(false),
        mVirtual(false),
        mPure(false),
        mAccess(PRIVATE)
    {
        DEBOUT("GpMethod::GpMethod");

    }

    void GpMethod::AddArg(GpArgument* arg)
    {
        DEBOUT("GpMethod::AddArg");

        mArgs.push_back(arg);
    }

    void GpMethod::WriteAsXml(ofstream& ofstr)
    {
        DEBOUT("GpMethod::WriteAsXml");

        // Method element and attributes
        ofstr << "<method";
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
        if (Virtual() )
        {
            ofstr << " virtual=\"true\"";
            if (Pure() )
            {
                ofstr << " pure=\"true\"";
            }
        }
        if (Const() )
        {
            ofstr << " const=\"true\"";
        }
        ofstr << ">\n";

        // Type element

        Type().WriteAsXml(ofstr);

        // Name element
        ofstr << "<name>" << Name() << "</name>\n";

        // Arglist element
        int numargs = mArgs.size();
        if (numargs > 0)
        {
            ofstr << "<arglist>\n";
            for (int ia = 0; ia < numargs; ia++)
            {
                mArgs[ia]->WriteAsXml(ofstr);
            }
            ofstr << "</arglist>\n";
        }
        // End of method element
        ofstr << "</method>\n";
    }


    void GpMethod::Const(bool val)
    {
        mConst = val;
    }

    bool GpMethod::Const()
    {
        return mConst;
    }

    void GpMethod::Virtual(bool val)
    {
        mVirtual = val;
    }

    bool GpMethod::Virtual()
    {
        return mVirtual;
    }

    void GpMethod::Pure(bool val)
    {
        mPure = val;
    }

    bool GpMethod::Pure()
    {
        return mPure;
    }

    void GpMethod::Name(const string& val)
    {
        mName = val;
    }

    const string& GpMethod::Name()
    {
        return mName;
    }

    void GpMethod::Type(const GpType& val)
    {
        mType = val;
    }

    GpType& GpMethod::Type()
    {
        return mType;
    }

    GpAccessType GpMethod::Access()
    {
        return mAccess;
    }

    void GpMethod::Access(GpAccessType val)
    {
        mAccess = val;
    }

    // GpDirecType GpMethod::Direc()
    // {
    //   return mDirec;
    // }
    // void GpMethod::Direc(GpDirecType val)
    // {
    //   mDirec = val;
    // }
}

