#include <gpxmlio/GpXmlStateMachine.hpp>

namespace gpos
{

  GpXmlStateMachine::GpXmlStateMachine()
    :context(NONE),
       currentClass(NULL)
  {
  }

  void GpXmlStateMachine::FoundElement(const GpElement element)
  {
    switch(element)
    {
      case CLASS:
        if(context == NONE)
        {
          currentClass = new GpClass();
          context = GPCLASS;
        }
        else
        {
          // Throw an exception
        }
        break;
      case NAMESPACE: break;
      case DEPENDS: break;
      case DECL: break;
      case DECLUSING: break;
      case IMPL: break;
      case IMPLUSING: break;
      case DESCENT: break;
      case PARENT: break;
      case NAME: break;
      case INTERFACE: break;
      case METHOD: break;
      case TYPE: break;
      case ARGLIST: break;
      case ARG: break;
      case IMPLEMENT: break;
      case UUID: break;
      case CODE: break;
      default:
        // Throw an exception - should never get here!
        break;
    }
  }

  void GpXmlStateMachine::ClosedElement(const GpElement element)
  {
    switch(element)
    {
      case CLASS: break;
      case NAMESPACE: break;
      case DEPENDS: break;
      case DECL: break;
      case DECLUSING: break;
      case IMPL: break;
      case IMPLUSING: break;
      case DESCENT: break;
      case PARENT: break;
      case NAME: break;
      case INTERFACE: break;
      case METHOD: break;
      case TYPE: break;
      case ARGLIST: break;
      case ARG: break;
      case IMPLEMENT: break;
      case UUID: break;
      case CODE: break;
      default:
        // Throw an exception - should never get here!
        break;
    }
  }

  void GpXmlStateMachine::ProcessChars(const string& str)
  {
  }

}
