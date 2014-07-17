#include <gpxmlio/GpClass.hpp>
#include <debug.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace gpos
{

    using namespace std;

    GpClass::GpClass()
    {
        DEBOUT("GpClass::GpClass");
    }

    void GpClass::Name(const string& val)
    {
        mName = val;
    }

    const string& GpClass::Name()
    {
        return mName;
    }

    void GpClass::Namespace(const string& val)
    {
        mNSpace = val;
    }

    const string& GpClass::Namespace()
    {
        return mNSpace;
    }

    void GpClass::AddDeclDepend(const string& str)
    {
        mDeclarationDependencies.push_back(str);
    }

    void GpClass::AddDeclUsingDepend(const string& str)
    {
        mDeclarationUsingDependencies.push_back(str);
    }

    void GpClass::AddImplDepend(const string& str)
    {
        mImplementationDependencies.push_back(str);
    }

    void GpClass::AddImplUsingDepend(const string& str)
    {
        mImplementationUsingDependencies.push_back(str);
    }

    void GpClass::AddMethod(GpMethod* mthd)
    {
        DEBOUT("GpClass::AddMethod");

        mInterface.push_back(mthd);
    }

    void GpClass::AddMember(GpMember* mbr)
    {
        DEBOUT("GpClass::AddMember");

        mState.push_back(mbr);
    }


    void GpClass::WriteAsXml()
    {
        DEBOUT("GpClass::WriteAsXml");
        string   ofilename(mName);
        string   post(".xml");
        ofilename += post;
        DEBOUT(ofilename);
        ofstream ofstr(ofilename.c_str() );
        if (!ofstr)
        {
            throw std::runtime_error("Can't open file for writing in GpClass::WriteAsXml()");
        }
        ofstr << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<class>\n";
        ofstr << "<namespace>" << mNSpace << "</namespace>\n";
        ofstr << "<name>" << mName << "</name>\n";
        int decl = mDeclarationDependencies.size();
        int decluse = mDeclarationUsingDependencies.size();
        int impl = mImplementationDependencies.size();
        int impluse = mImplementationUsingDependencies.size();
        if ( ( decl + decluse + impl + impluse ) > 0)
        {
            ofstr << "<depends>\n";
            if (decl)
            {
                for (int ia = 0; ia < decl; ia++)
                {
                    ofstr << "<decl>" << mDeclarationDependencies[ia] << "</decl>\n";
                }
            }
            if (decluse)
            {
                for (int ia = 0; ia < decluse; ia++)
                {
                    ofstr << "<decl-using>" << mDeclarationUsingDependencies[ia] << "</decl-using>\n";
                }
            }
            if (impl)
            {
                for (int ia = 0; ia < impl; ia++)
                {
                    ofstr << "<impl>" << mImplementationDependencies[ia] << "</impl>\n";
                }
            }
            if (impluse)
            {
                for (int ia = 0; ia < impluse; ia++)
                {
                    ofstr << "<impl-using>" << mImplementationUsingDependencies[ia] << "</impl-using>\n";
                }
            }
            ofstr << "</depends>\n";
        }
        int nummbrs = mState.size();
        if (nummbrs > 0)
        {
            ofstr << "<state>\n";
            for (int ia = 0; ia < nummbrs; ia++)
            {
                mState[ia]->WriteAsXml(ofstr);
            }
            ofstr << "</state>\n";
        }
        int nummthds = mInterface.size();
        if (nummthds > 0)
        {
            ofstr << "<interface>\n";
            for (int ia = 0; ia < nummthds; ia++)
            {
                mInterface[ia]->WriteAsXml(ofstr);
            }
            ofstr << "</interface>\n";
        }
        ofstr << "</class>\n";
        ofstr.close();
    }

    // ostream& operator<< (ostream& ostr, const GpClass& gpc)
    // {
    //   ostr<<"<class>\n";
    //   ostr<<"<namespace>"<<gpc.nspace<<"</namespace>\n";
    //   ostr<<"<name>"<<gpc.name<<"</name>\n";
    //   ostr<<"</class\n>";
    //   return ostr;
    // }

}
