#ifndef GPXMLELEMENTMAP_H
#define GPXMLELEMENTMAP_H

#include <string>
#include <map>

namespace gpos
{
  enum GpElement
  {
    NOTHING,
    CLASS,
    NAMESPACE,
    DEPENDS,
    DECL,
    DECLUSING,
    IMPL,
    IMPLUSING,
    DESCENT,
    PARENT,
    NAME,
    INTERFACE,
    METHOD,
    TYPE,
    ARGLIST,
    ARG,
    IMPLEMENT,
    UUID,
    CODE
  };

  using namespace std;

  class GpXmlElementMap
  {
  public:
    GpXmlElementMap();
    const GpElement& operator[](const string&);
  private:
    void Initialise();
    map<const string, GpElement> imap;
  };

}
#endif
