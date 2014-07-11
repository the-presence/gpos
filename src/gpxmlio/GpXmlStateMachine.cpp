#include <gpxmlio/GpXmlStateMachine.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <map>
#include <stdexcept>

XERCES_CPP_NAMESPACE_USE

  namespace gpos
{
  using namespace std;

  const string GpXmlStateMachine::PureStr = "pure";
  const string GpXmlStateMachine::TrueStr = "true";
  const string GpXmlStateMachine::ConstStr = "const";
  const string GpXmlStateMachine::StaticStr = "static";
  const string GpXmlStateMachine::DirecStr = "direc";
  const string GpXmlStateMachine::VirtualStr = "virtual";

  GpXmlStateMachine::GpXmlStateMachine()
    :mContext(NONE),
       mCurrentClass(0),
       mCurrentModel(0),
       mCurrentMethod(0),
       mCurrentArgument(0)
  {
    DEBOUT("GpXmlStateMachine::GpXmlStateMachine()");
  }

  void GpXmlStateMachine::AddModel(GpCodeModel* obj)
  {
    #ifdef DEBUG
    cout << "GpXmlStateMachine::mCurrentModel = "<< mCurrentModel << endl;
    #endif
    DEBOUT("GpXmlStateMachine::AddModel()");
    if(!obj)
    {
      throw std::invalid_argument("Null pointer passed to GpXmlStateMachine::AddModel");
    }
    mCurrentModel = obj;
    #ifdef DEBUG
    cout << "GpXmlStateMachine::mCurrentModel = "<< mCurrentModel << endl;
    #endif
  }

  bool GpXmlStateMachine::FindAttribute(MAP& attribs, const string& compstr, string& retstr)
  {
    bool retval = false;
    MAP::const_iterator search = attribs.find(compstr);
    if(search != attribs.end())
    {
      retstr = attribs[compstr];
      retval = true;
    }
    return retval;
  }

  void GpXmlStateMachine::Context(GpContext val)
  {
    mContext = val;

    #ifdef DEBUG
    switch(mContext)
    {
      case NONE:
        cout << "--- Context changed to: NONE\n";
        break;
      case GPCLASS:
        cout << "--- Context changed to: GPCLASS\n";
        break;
      case GPDEPENDS:
        cout << "--- Context changed to: GPDEPENDS\n";
        break;
      case GPINTERFACE:
        cout << "--- Context changed to: GPINTERFACE\n";
        break;
      case GPINHERIT:
        cout << "--- Context changed to: GPINHERIT\n";
        break;
      case GPPARENT:
        cout << "--- Context changed to: GPPARENT\n";
        break;
      case GPIMPLEMENT:
        cout << "--- Context changed to: GPIMPLEMENT\n";
        break;
      case GPMETHOD:
        cout << "--- Context changed to: GPMETHOD\n";
        break;
      case GPARGLIST:
        cout << "--- Context changed to: GPARGLIST\n";
        break;
      case GPARG:
        cout << "--- Context changed to: GPARG\n";
        break;
      default:
        cout << "--- Context changed to: something inexplicable = "<< (int)mContext << "\n";
        break;
    }
    #endif
  }

  GpContext GpXmlStateMachine::Context()
  {
    return mContext;
  }

  void GpXmlStateMachine::FoundElement(const GpElement element, const Attributes& attrs)
  {

    XMLSize_t numAtts = attrs.getLength();
    string retValue;

    map<string, string> attributes;
    if(numAtts > 0)
    {
      for (XMLSize_t i = 0; i < numAtts; i++)
      {
        string local(XMLString::transcode(attrs.getLocalName(i)));
        string value(XMLString::transcode(attrs.getValue(i)));
        attributes[local] = value;
        DEBOUT(i);
        DEBOUT(local);
        DEBOUT(value);
      }
    }

    switch(element)
    {
      case CLASS:
        switch(Context())
        {
          case NONE:
            mCurrentClass = new GpClass();
            mCurrentModel->AddClass(mCurrentClass);
            Context(GPCLASS);
            break;
          default:
            break;
        }
        break;
      case DEPENDS:
        switch(Context())
        {
          case GPCLASS:
            Context(GPDEPENDS);
            break;
          default:
            break;
        }
        break;
      case DESCENT:
        switch(Context())
        {
          case GPCLASS:
            Context(GPINHERIT);
            break;
          default:
            break;
        }
        break;
      case PARENT:
        switch(Context())
        {
          case GPINHERIT:
            Context(GPPARENT);
            break;
          default:
            break;
        }
        break;
      case INTERFACE:
        switch(Context())
        {
          case GPCLASS:
            Context(GPINTERFACE);
            break;
          default:
            break;
        }
        break;
      case STATE:
        switch(Context())
        {
          case GPCLASS:
            Context(GPSTATE);
            break;
          default:
            break;
        }
        break;
      case MEMBER:
        switch(Context())
        {
          case GPCLASS:
            Context(GPMEMBER);
            break;
          default:
            break;
        }
        break;
      case METHOD:
        switch(Context())
        {
          case GPINTERFACE:
            mCurrentMethod  = new GpMethod();
            mCurrentClass->AddMethod(mCurrentMethod);
            if(attributes.size() > 0)
            {
              // Checking the method for constness
              if(FindAttribute(attributes, ConstStr, retValue))
              {
                if(retValue.compare(TrueStr) == 0)
                {
                  mCurrentMethod->Const(true);
                }
              }
              // Checking the method for runtime binding
              if(FindAttribute(attributes, VirtualStr, retValue))
              {
                if(retValue.compare(TrueStr) == 0)
                {
                  mCurrentMethod->Virtual(true);
                }
              }
              // Checking if the method defines an abstract class
              if(FindAttribute(attributes, PureStr, retValue))
              {
                if(retValue.compare(TrueStr) == 0)
                {
                  // Can't have a pure non-virtual
                  if(mCurrentMethod->Virtual())
                  {
                    mCurrentMethod->Pure(true);
                  }
                }
              }
            }
            Context(GPMETHOD);
            break;
          default:
            break;
        }
        break;
      case ARGLIST:
        switch(Context())
        {
          case GPMETHOD:
            Context(GPARGLIST);
            break;
          default:
            break;
        }
        break;
      case ARG:
        switch(Context())
        {
          case GPARGLIST:
            mCurrentArgument = new GpArgument();
            mCurrentMethod->AddArg(mCurrentArgument);
            Context(GPARG);
            break;
          default:
            break;
        }
        break;
      case TYPE:
        break;
      case IMPLEMENT:
        switch(Context())
        {
          case GPMETHOD:
            Context(GPIMPLEMENT);
            break;
          default:
            break;
        }
        break;
        DEBOUT(" FoundElement:IMPLEMENT");
        break;
      case UUID:
        DEBOUT(" FoundElement:UUID");
        break;
      case CODE:
        DEBOUT(" FoundElement:CODE");
        break;
      default:
        break;
    }
    mElementStack.push(element);
  }

  void GpXmlStateMachine::ClosedElement(const GpElement element)
  {
    switch(element)
    {
      case CLASS:
        switch(Context())
        {
          case GPCLASS:
            Context(NONE);
            break;
          default:
            break;
        }
        DEBOUT("ClosedElement:CLASS");
        break;
      case NAMESPACE:
        DEBOUT("ClosedElement:NAMESPACE");
        break;
      case DEPENDS:
        switch(Context())
        {
          case GPDEPENDS:
            Context(GPCLASS);
            DEBOUT("ClosedElement:DEPENDS");
            break;
          default:
            break;
        }
        break;
      case DECL:
        DEBOUT("ClosedElement:DECL");
        break;
      case MEMBER:
        Context(GPSTATE);
        DEBOUT("ClosedElement:DECL");
        break;
      case STATE:
        Context(GPCLASS);
        DEBOUT("ClosedElement:DECL");
        break;
      case DECLUSING:
        DEBOUT("ClosedElement:DECLUSING");
        break;
      case IMPL:
        DEBOUT("ClosedElement:IMPL");
        break;
      case IMPLUSING:
        DEBOUT("ClosedElement:IMPLUSING");
        break;
      case NAME:
        switch(Context())
        {
          case GPPARENT:
            Context(GPINHERIT);
            break;
          default:
            break;
        }
        break;
        break;
      case DESCENT:
        Context(GPCLASS);
        break;
      case PARENT:
        Context(GPINHERIT);
        break;
      case INTERFACE:
        Context(GPCLASS);
        DEBOUT("ClosedElement:INTERFACE");
        break;
      case METHOD:
        Context(GPINTERFACE);
        DEBOUT("ClosedElement:METHOD");
        break;
      case TYPE:
        DEBOUT("ClosedElement:TYPE");
        break;
      case ARGLIST:
        Context(GPMETHOD);
        DEBOUT("ClosedElement:ARGLIST");
        break;
      case ARG:
        Context(GPARGLIST);
        DEBOUT("ClosedElement:ARG");
        break;
      case IMPLEMENT:
        Context(GPMETHOD);
        DEBOUT("ClosedElement:IMPLEMENT");
        break;
      case UUID:
        DEBOUT("ClosedElement:UUID");
        break;
      case CODE:
        DEBOUT("ClosedElement:CODE");
        break;
      default:
        // Throw an exception - should never get here!
        break;
    }
    mElementStack.pop();
  }

  void GpXmlStateMachine::ProcessChars(const string& str)
  {
    GpElement eletop = mElementStack.top();

    switch(eletop)
    {
      case CLASS:
        break;
      case NAMESPACE:
        switch(Context())
        {
          case GPCLASS:
            DEBOUT(" ProcessChars:NAMESPACE");
            mCurrentClass->Namespace(str);
            DEBOUT(mCurrentClass->Namespace());
            break;
          default:
            break;
        }
        break;
      case DEPENDS:
        // DEBOUT("ProcessChars:DEPENDS");
        break;
      case DECL:
        // DEBOUT("ProcessChars:DECL");
        switch(Context())
        {
          case GPDEPENDS:
            mCurrentClass->AddDeclDepend(str);
            DEBOUT("ProcessChars:DECL");
            break;
          default:
            break;
        }
        break;
      case DECLUSING:
        // DEBOUT("ProcessChars:DECLUSING");
        switch(Context())
        {
          case GPDEPENDS:
            mCurrentClass->AddDeclUsingDepend(str);
            DEBOUT("ProcessChars:DECLUSING");
            break;
          default:
            break;
        }
        break;
      case IMPL:
        // DEBOUT("ProcessChars:IMPL");
        switch(Context())
        {
          case GPDEPENDS:
            mCurrentClass->AddImplDepend(str);
            DEBOUT("ProcessChars:IMPL");
            break;
          default:
            break;
        }
        break;
      case IMPLUSING:
        // DEBOUT("ProcessChars:IMPLUSING");
        switch(Context())
        {
          case GPDEPENDS:
            mCurrentClass->AddImplUsingDepend(str);
            DEBOUT("ProcessChars:IMPLUSING");
            break;
          default:
            break;
        }
        break;
      case DESCENT:
        // DEBOUT("ProcessChars:DESCENT");
        break;
      case PARENT:
        // DEBOUT("ProcessChars:PARENT");
        break;
      case NAME:
        switch(Context())
        {
          case GPCLASS:
            DEBOUT(" ProcessChars:NAME");
            mCurrentClass->Name(str);
            DEBOUT(mCurrentClass->Name());
            break;
          case GPMETHOD:
            mCurrentMethod->Name(str);
            break;
          case GPARG:
            mCurrentArgument->Name(str);
            break;
          default:
            break;
        }
        break;
        // DEBOUT("ProcessChars:NAME");
        break;
      case INTERFACE:
        // DEBOUT("ProcessChars:INTERFACE");
        break;
      case METHOD:
        // DEBOUT("ProcessChars:METHOD");
        break;
      case TYPE:
        switch(Context())
        {
          case GPMETHOD:
            mCurrentMethod->Type(str);
            break;
          case GPARG:
            mCurrentArgument->Type(str);
          default:
            break;
        }
        break;
      case ARGLIST:
        // DEBOUT("ProcessChars:ARGLIST");
        break;
      case ARG:
        // DEBOUT("ProcessChars:ARG");
        break;
      case IMPLEMENT:
        // DEBOUT("ProcessChars:IMPLEMENT");
        break;
      case UUID:
        // DEBOUT("ProcessChars:UUID");
        break;
      case CODE:
        // DEBOUT("ProcessChars:CODE");
        break;
      default:
        // Throw an exception - should never get here!
        break;
    }
  }

}
