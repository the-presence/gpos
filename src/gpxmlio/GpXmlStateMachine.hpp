#ifndef GPXMLSTATEMACHINE_H
#define GPXMLSTATEMACHINE_H
#include <xercesc/sax2/Attributes.hpp>
#include <debug.hpp>
#include <string>
#ifndef GPXMLELEMENT_H
#include <gpxmlio/GpXmlElementMap.hpp>
#endif

#ifndef GPCLASS_H
#include <gpxmlio/GpClass.hpp>
#endif

#include <gpxmlio/GpCodeModel.hpp>
#include <gpxmlio/GpMethod.hpp>
#include <gpxmlio/GpArgument.hpp>

#include <stack>
XERCES_CPP_NAMESPACE_USE
  namespace gpos
{
  enum GpContext
  {
    NONE,
    GPCLASS,
    GPDEPENDS,
    GPINTERFACE,
    GPINHERIT,
    GPPARENT,
    GPMETHOD,
    GPIMPLEMENT,
    GPSTATE,
    GPMEMBER,
    GPARGLIST,
    GPARG
  };
  using namespace std;

  typedef std::map<std::string, std::string>MAP;

  class GpXmlStateMachine
  {
  public:
    GpXmlStateMachine();
    void FoundElement(const GpElement, const Attributes&);
    void ClosedElement(const GpElement);
    void ProcessChars(const string&);
    void AddModel(GpCodeModel*);
    void Context(GpContext);
    GpContext Context();


  private:

    bool FindAttribute(MAP& attribs, const string& compstr, string& retstr);

    GpContext mContext;
    stack<GpElement> mElementStack;
    GpClass* mCurrentClass;
    GpCodeModel* mCurrentModel;
    GpMethod* mCurrentMethod;
    GpArgument* mCurrentArgument;

    static string const PureStr;
    static string const VirtualStr;
    static string const ConstStr;
    static string const StaticStr;
    static string const DirecStr;
    static string const TrueStr;

  };
}
#endif
