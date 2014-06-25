#ifndef GPXMLSTATEMACHINE_H
#define GPXMLSTATEMACHINE_H

#ifndef GPXMLELEMENT_H
#include <gpxmlio/GpXmlElementMap.hpp>
#endif

#ifndef GPCLASS_H
#include <gpxmlio/GpClass.hpp>
#endif

namespace gpos
{
  enum GpContext
  {
    NONE,
    GPCLASS,
    GPMETHOD,
    GPARGLIST,
    GPARG
  };

  class GpXmlStateMachine
  {
  public:
    GpXmlStateMachine();
    void FoundElement(const GpElement);
    void ClosedElement(const GpElement);
    void ProcessChars(const string&);
  private:
    GpContext context;
    GpClass* currentClass;
  };
}
#endif
