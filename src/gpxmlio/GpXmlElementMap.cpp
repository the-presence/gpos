#include <gpxmlio/GpXmlElementMap.hpp>
#include <debug.hpp>
namespace gpos
{
    //GpElement Nothing = NOTHING;

    GpXmlElementMap::GpXmlElementMap()
    {
        DEBOUT("GpXmlElementMap::GpXmlElementMap()");
        Initialise();
    }

    void GpXmlElementMap::Initialise()
    {
        mImap[string("nothing")] = NOTHING;
        mImap[string("class")] = CLASS;
        mImap[string("namespace")] = NAMESPACE;
        mImap[string("depends")] = DEPENDS;
        mImap[string("decl")] = DECL;
        mImap[string("decl-using")] = DECLUSING;
        mImap[string("impl")] = IMPL;
        mImap[string("impl-using")] = IMPLUSING;
        mImap[string("descent")] = DESCENT;
        mImap[string("parent")] = PARENT;
        mImap[string("name")] = NAME;
        mImap[string("interface")] = INTERFACE;
        mImap[string("method")] = METHOD;
        mImap[string("state")] = STATE;
        mImap[string("member")] = MEMBER;
        mImap[string("type")] = TYPE;
        mImap[string("arglist")] = ARGLIST;
        mImap[string("arg")] = ARG;
        mImap[string("implement")] = IMPLEMENT;
        mImap[string("uuid")] = UUID;
        mImap[string("code")] = CODE;
    }

    const GpElement& GpXmlElementMap::operator[](const string& ind)
    {
        map<string, GpElement>::iterator iter = mImap.find(ind);
        if ( iter != mImap.end() )
        {
            return mImap[ind];
        }
        else
        {
            // Throw exception?
            return mImap[string("nothing")];
        }
    }
}
