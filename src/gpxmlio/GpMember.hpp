#ifndef GPMEMBER_H
#define GPMEMBER_H

#include <gpxmlio/Gpos.hpp>
#include <gpxmlio/GpType.hpp>

#include <string>

namespace gpos
{

    using namespace std;

    class GpMember
    {
public:
    GpMember();

    void Type(const GpType&);
    void Name(const string&);
    void Access(const GpAccessType);

    void WriteAsXml(ofstream&);

    GpType&       Type();
    const string& Name();
    GpAccessType Access();

private:
    GpType        mType;
    string        mName;
    GpAccessType  mAccess;
    };
}

#endif
