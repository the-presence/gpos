#include <gpxmlio/GpXmlElementMap.hpp>

namespace gpos
{

  GpXmlElementMap::GpXmlElementMap()
  {
    Initialise();
  }

  void GpXmlElementMap::Initialise()
  {
    imap[string("class")] = CLASS;
    imap[string("namespace")] = NAMESPACE;
    imap[string("depends")] = DEPENDS;
    imap[string("decl")] = DECL;
    imap[string("decl-using")] = DECLUSING;
    imap[string("impl")] = IMPL;
    imap[string("impl-using")] = IMPLUSING;
    imap[string("descent")] = DESCENT;
    imap[string("parent")] = PARENT;
    imap[string("name")] = NAME;
    imap[string("interface")] = INTERFACE;
    imap[string("method")] = METHOD;
    imap[string("type")] = TYPE;
    imap[string("arglist")] = ARGLIST;
    imap[string("arg")] = ARG;
    imap[string("implement")] = IMPLEMENT;
    imap[string("uuid")] = UUID;
    imap[string("code")] = CODE;
  }

  const GpElement& GpXmlElementMap::operator[](const string& ind)
  {
    map<string, GpElement>::iterator iter = imap.find(ind);
    if( iter != imap.end() )
    {
      return imap[ind];
    }
    else
    {
      // Throw exception?
      return NOTHING;
    }
  }
}
