#ifndef GPMETHOD_H
#define GPMETHOD_H

#include <vector>
#include <fstream>
#include <gpxmlio/Gpos.hpp>
#include <gpxmlio/GpType.hpp>
#include <gpxmlio/GpArgument.hpp>

namespace gpos
{
    using namespace std;

    class GpMethod
    {
public:
    GpMethod();

    void AddArg(GpArgument*);
    void WriteAsXml(ofstream&);
    void Const(bool);
    void Pure(bool);
    //void Direc(GpDType);
    void Virtual(bool);
    void Name(const string&);
    void Type(const GpType&);
    void Access(const GpAccessType);

    bool Virtual();
    bool Pure();
    bool Const();
    //GpDirecType Direc();
    const string&       Name();
    GpType&             Type();
    GpAccessType Access();

private:
    bool                mConst;
    bool                mVirtual;
    bool                mPure;
    //GpDType             mDirec;
    string              mName;
    GpType              mType;
    GpAccessType        mAccess;

    vector<GpArgument*> mArgs;
    };
}

#endif
