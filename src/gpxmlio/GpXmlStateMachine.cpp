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
  const string GpXmlStateMachine::PtrStr = "ptr";
  const string GpXmlStateMachine::RefStr = "ref";
  const string GpXmlStateMachine::VirtualStr = "virtual";
  const string GpXmlStateMachine::AccessStr = "access";
  const string GpXmlStateMachine::PublicStr = "public";
  const string GpXmlStateMachine::PrivateStr = "private";
  const string GpXmlStateMachine::ProtectedStr = "protected";

  GpXmlStateMachine::GpXmlStateMachine()
    : mContext(NONE),
        mCurrentClass(0),
        mCurrentModel(0),
        mCurrentMethod(0),
        mCurrentArgument(0),
        mCurrentType(0)
  {
    DEBOUT("GpXmlStateMachine::GpXmlStateMachine()");
  }

  void GpXmlStateMachine::AddModel(GpCodeModel* obj)
  {
    #ifdef DEBUG
    cout << "GpXmlStateMachine::mCurrentModel = " << mCurrentModel << endl;
    #endif
    DEBOUT("GpXmlStateMachine::AddModel()");
    if (!obj)
    {
      throw std::invalid_argument("Null pointer passed to GpXmlStateMachine::AddModel");
    }
    mCurrentModel = obj;
    #ifdef DEBUG
    cout << "GpXmlStateMachine::mCurrentModel = " << mCurrentModel << endl;
    #endif
  }

  bool GpXmlStateMachine::FindAttribute(MAP& attribs, const string& compstr, string& retstr)
  {
    bool                retval = false;
    MAP::const_iterator search = attribs.find(compstr);
    #ifdef DEBUG
    cout << "Searching for attribute: " << compstr;
    #endif
    if (search != attribs.end() )
    {
      retstr = attribs[compstr];
      #ifdef DEBUG
      cout << " Found value: " << retstr;
      #endif
      retval = true;
    }
    #ifdef DEBUG
    cout << "\n";
    #endif
    return retval;
  }

  void GpXmlStateMachine::Context(GpContext val)
  {
    mContext = val;

    #ifdef DEBUG
    switch (mContext)
    {
      case NONE:
        DEBOUT("--- Context changed to: NONE\n");
        break;
      case GPCLASS:
        DEBOUT("--- Context changed to: GPCLASS\n");
        break;
      case GPDEPENDS:
        DEBOUT("--- Context changed to: GPDEPENDS\n");
        break;
      case GPINTERFACE:
        DEBOUT("--- Context changed to: GPINTERFACE\n");
        break;
      case GPINHERIT:
        DEBOUT("--- Context changed to: GPINHERIT\n");
        break;
      case GPPARENT:
        DEBOUT("--- Context changed to: GPPARENT\n");
        break;
      case GPMETHOD:
        DEBOUT("--- Context changed to: GPMETHOD\n");
        break;
      case GPIMPLEMENT:
        DEBOUT("--- Context changed to: GPIMPLEMENT\n");
        break;
      case GPCODE:
        DEBOUT("--- Context changed to: GPCODE\n");
        break;
      case GPSTATE:
        DEBOUT("--- Context changed to: GPSTATE\n");
        break;
      case GPMEMBER:
        DEBOUT("--- Context changed to: GPMEMBER\n");
        break;
      case GPARGLIST:
        DEBOUT("--- Context changed to: GPARGLIST\n");
        break;
      case GPARG:
        DEBOUT("--- Context changed to: GPARG\n");
        break;
      default:
        cout << "--- Context changed to: something inexplicable = " << (int)mContext << "\n";
        break;
    }
    #endif
  }

  GpContext GpXmlStateMachine::Context()
  {
    return mContext;
  }


  void GpXmlStateMachine::SetAttributes(GpType* target, const Attributes& attrs)
  {
    XMLSize_t           numAtts = attrs.getLength();
    string              retValue;

    map<string, string> attributes;
    DEBOUT("GpXmlStateMachine::SetAttributes - Type");

    if (numAtts > 0)
    {
      for (XMLSize_t i = 0; i < numAtts; i++)
      {
        string local(XMLString::transcode(attrs.getLocalName(i) ) );
        string value(XMLString::transcode(attrs.getValue(i) ) );
        attributes[local] = value;
        DEBOUT(i);
        DEBOUT(local);
        DEBOUT(value);
      }
      // Checking the member for constness
      if (FindAttribute(attributes, ConstStr, retValue) )
      {
        if (retValue.compare(TrueStr) == 0)
        {
          target->Const(true);
        }
      }
      // Checking the member for staticness
      if (FindAttribute(attributes, StaticStr, retValue) )
      {
        if (retValue.compare(TrueStr) == 0)
        {
          target->Static(true);
        }
      }
      // Checking if the member is a pointer or reference
      if (FindAttribute(attributes, DirecStr, retValue) )
      {
        if (retValue.compare(PtrStr) == 0)
        {
          target->Direc(POINTER);
          DEBOUT("Pointer");
        }
        else
        {
          if (retValue.compare(RefStr) == 0)
          {
            target->Direc(REFERENCE);
            DEBOUT("Reference");
          }
        }
      }
    }
  }

  void GpXmlStateMachine::SetAttributes(GpMember* target, const Attributes& attrs)
  {
    XMLSize_t           numAtts = attrs.getLength();
    string              retValue;

    map<string, string> attributes;
    DEBOUT("GpXmlStateMachine::SetAttributes - Member");

    if (numAtts > 0)
    {
      for (XMLSize_t i = 0; i < numAtts; i++)
      {
        string local(XMLString::transcode(attrs.getLocalName(i) ) );
        string value(XMLString::transcode(attrs.getValue(i) ) );
        attributes[local] = value;
        DEBOUT(i);
        DEBOUT(local);
        DEBOUT(value);
      }
      // Checking the member for access
      if (FindAttribute(attributes, AccessStr, retValue) )
      {
        if (retValue.compare(PublicStr) == 0)
        {
          target->Access(PUBLIC);
        }
        if (retValue.compare(PrivateStr) == 0)
        {
          target->Access(PRIVATE);
        }
        if (retValue.compare(ProtectedStr) == 0)
        {
          target->Access(PROTECTED);
        }
      }
    }
  }

  void GpXmlStateMachine::SetAttributes(GpMethod* target, const Attributes& attrs)
  {
    XMLSize_t           numAtts = attrs.getLength();
    string              retValue;

    map<string, string> attributes;
    DEBOUT("GpXmlStateMachine::SetAttributes - Method");

    if (numAtts > 0)
    {
      for (XMLSize_t i = 0; i < numAtts; i++)
      {
        string local(XMLString::transcode(attrs.getLocalName(i) ) );
        string value(XMLString::transcode(attrs.getValue(i) ) );
        attributes[local] = value;
        DEBOUT(i);
        DEBOUT(local);
        DEBOUT(value);
      }

      // Checking the method for constness
      if (FindAttribute(attributes, ConstStr, retValue) )
      {
        if (retValue.compare(TrueStr) == 0)
        {
          target->Const(true);
        }
      }
      // Checking the method for runtime binding
      if (FindAttribute(attributes, VirtualStr, retValue) )
      {
        if (retValue.compare(TrueStr) == 0)
        {
          target->Virtual(true);
        }
      }
      // Checking if the method defines an abstract class
      if (FindAttribute(attributes, PureStr, retValue) )
      {
        if (retValue.compare(TrueStr) == 0)
        {
          // Can't have a pure non-virtual
          if (mCurrentMethod->Virtual() )
          {
            target->Pure(true);
          }
        }
      }
      // Checking if the method returns a pointer or reference
      if (FindAttribute(attributes, DirecStr, retValue) )
      {
        if (retValue.compare(PtrStr) == 0)
        {
          target->Type().Direc(POINTER);
          DEBOUT("Pointer");
        }
        else
        {
          if (retValue.compare(RefStr) == 0)
          {
            target->Type().Direc(REFERENCE);
            DEBOUT("Reference");
          }
        }
      }
      // Checking the method for access
      if (FindAttribute(attributes, AccessStr, retValue) )
      {
        if (retValue.compare(PublicStr) == 0)
        {
          target->Access(PUBLIC);
        }
        if (retValue.compare(PrivateStr) == 0)
        {
          target->Access(PRIVATE);
        }
        if (retValue.compare(ProtectedStr) == 0)
        {
          target->Access(PROTECTED);
        }
      }
    }
  }


  void GpXmlStateMachine::FoundElement(const GpElement element, const Attributes& attrs)
  {
    XMLSize_t numAtts = attrs.getLength();

    switch (element)
    {
      case CLASS:
        switch (Context() )
        {
          case NONE:
            if (mCurrentClass)
            {
              delete mCurrentClass;
            }
            mCurrentClass = new GpClass();
            mCurrentModel->AddClass(mCurrentClass);
            Context(GPCLASS);
            break;
          default:
            break;
        }
        break;
      case DEPENDS:
        switch (Context() )
        {
          case GPCLASS:
            Context(GPDEPENDS);
            break;
          default:
            break;
        }
        break;
      case DESCENT:
        switch (Context() )
        {
          case GPCLASS:
            Context(GPINHERIT);
            break;
          default:
            break;
        }
        break;
      case PARENT:
        switch (Context() )
        {
          case GPINHERIT:
            Context(GPPARENT);
            break;
          default:
            break;
        }
        break;
      case INTERFACE:
        switch (Context() )
        {
          case GPCLASS:
            Context(GPINTERFACE);
            break;
          default:
            break;
        }
        break;
      case STATE:
        switch (Context() )
        {
          case GPCLASS:
            Context(GPSTATE);
            break;
          default:
            break;
        }
        break;
      case MEMBER:
        switch (Context() )
        {
          case GPSTATE:
            mCurrentMember = new GpMember();
            mCurrentClass->AddMember(mCurrentMember);
            if (numAtts > 0)
            {
              SetAttributes(mCurrentMember, attrs);
            }
            Context(GPMEMBER);
          default:
            break;
        }
        break;
      case METHOD:
        switch (Context() )
        {
          case GPINTERFACE:
            if (mCurrentMethod)
            {
              delete mCurrentMethod;
            }
            mCurrentMethod  = new GpMethod();
            mCurrentClass->AddMethod(mCurrentMethod);
            if (numAtts > 0)
            {
              SetAttributes(mCurrentMethod, attrs);
            }
            Context(GPMETHOD);
            break;
          default:
            break;
        }
        break;
      case ARGLIST:
        switch (Context() )
        {
          case GPMETHOD:
            Context(GPARGLIST);
            break;
          default:
            break;
        }
        break;
      case ARG:
        switch (Context() )
        {
          case GPARGLIST:
            if (mCurrentArgument)
            {
              delete mCurrentArgument;
            }
            mCurrentArgument = new GpArgument();
            mCurrentMethod->AddArg(mCurrentArgument);
            Context(GPARG);
            break;
          default:
            break;
        }
        break;
      case TYPE:
        if (mCurrentType)
        {
          delete mCurrentType;
        }
        mCurrentType = new GpType();
        if (numAtts > 0)
        {
          SetAttributes(mCurrentType, attrs);
        }
        switch (Context() )
        {
          case GPMEMBER:
            mCurrentMember->Type(*mCurrentType);
            break;
          case GPMETHOD:
            mCurrentMethod->Type(*mCurrentType);
            break;
          case GPARG:
            DUMPP(mCurrentArgument);
            mCurrentArgument->Type(*mCurrentType);
            DUMPP(mCurrentArgument);
            break;
          default:
            break;
        }
        break;
      case IMPLEMENT:
        switch (Context() )
        {
          case GPMETHOD:
            Context(GPIMPLEMENT);
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
    mElementStack.push(element);
  }

  void GpXmlStateMachine::ClosedElement(const GpElement element)
  {
    switch (element)
    {
      case CLASS:
        Context(NONE);
        break;
      case DEPENDS:
        Context(GPCLASS);
        break;
      case MEMBER:
        Context(GPSTATE);
        break;
      case STATE:
        Context(GPCLASS);
        break;
      case DESCENT:
        Context(GPCLASS);
        break;
      case PARENT:
        Context(GPINHERIT);
        break;
      case INTERFACE:
        Context(GPCLASS);
        break;
      case METHOD:
        Context(GPINTERFACE);
        break;
      case ARGLIST:
        Context(GPMETHOD);
        break;
      case ARG:
        Context(GPARGLIST);
        break;
      case IMPLEMENT:
        Context(GPMETHOD);
        break;
      default:
        // Anything else is a NOP
        break;
    }
    mElementStack.pop();
  }

  void GpXmlStateMachine::ProcessChars(const string& str)
  {
    GpElement eletop = mElementStack.top();

    switch (eletop)
    {
      case CLASS:
        break;
      case NAMESPACE:
        switch (Context() )
        {
          case GPCLASS:
            mCurrentClass->Namespace(str);
            break;
          default:
            break;
        }
        break;
      case DECL:
        switch (Context() )
        {
          case GPDEPENDS:
            mCurrentClass->AddDeclDepend(str);
            break;
          default:
            break;
        }
        break;
      case DECLUSING:
        switch (Context() )
        {
          case GPDEPENDS:
            mCurrentClass->AddDeclUsingDepend(str);
            break;
          default:
            break;
        }
        break;
      case IMPL:
        switch (Context() )
        {
          case GPDEPENDS:
            mCurrentClass->AddImplDepend(str);
            break;
          default:
            break;
        }
        break;
      case IMPLUSING:
        switch (Context() )
        {
          case GPDEPENDS:
            mCurrentClass->AddImplUsingDepend(str);
            break;
          default:
            break;
        }
        break;
      case NAME:
        switch (Context() )
        {
          case GPCLASS:
            mCurrentClass->Name(str);
            break;
          case GPMETHOD:
            mCurrentMethod->Name(str);
            break;
          case GPARG:
            mCurrentArgument->Name(str);
            break;
          case GPMEMBER:
            mCurrentMember->Name(str);
            break;
          default:
            break;
        }
        break;
      case TYPE:
        if (str.size() > 0)
        {
          switch (Context() )
          {
            case GPMETHOD:
              DEBOUT("mCurrentMethod->Type().Type(str)");
              mCurrentMethod->Type().Type(str);
              break;
            case GPARG:
              DEBOUT("mCurrentArgument->Type().Type(str)");
              mCurrentArgument->Type().Type(str);
              break;
            case GPMEMBER:
              DEBOUT("mCurrentMember->Type().Type(str)");
              mCurrentMember->Type().Type(str);
            default:
              break;
          }
        }
        break;
      case UUID:
        switch (Context() )
        {
          case GPIMPLEMENT:
            //mCurrentMethod->UUID(str);
            break;
          default:
            break;
        }
        break;
      case CODE:
        switch (Context() )
        {
          case GPCODE:
            //mCurrentMethod->Code(str);
            break;
          default:
            break;
        }
        break;
      default:
        // Throw an exception - should never get here!
        break;
    }
  }

}
