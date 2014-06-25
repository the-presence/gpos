#include <gpxmlio/GpClass.hpp>

namespace gpos
{

  GpClass::GpClass()
  {
  }

  void GpClass::Name(const string& val)
  {
    name = val;
  }

  const string& GpClass::Name()
  {
    return name;
  }

  void GpClass::Namespace(const string& val)
  {
    nspace = val;
  }

  const string& GpClass::Namespace()
  {
    return nspace;
  }



}
