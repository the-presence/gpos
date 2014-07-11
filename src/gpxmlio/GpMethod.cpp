#include <gpxmlio/GpMethod.hpp>
#include <debug.hpp>

namespace gpos
{

  GpMethod::GpMethod()
  {
  }

  void GpMethod::AddArg(GpArgument* arg)
  {
  }

  void GpMethod::WriteAsXml(ofstream& ofstr)
  {
    DEBOUT("GpMethod::WriteAsXml()");
    ofstr << "<method";
    if(mVirtual)
    {
      ofstr << " virtual=\"true\"";
      if(mPure)
      {
        ofstr << " pure=\"true\"";
      }
    }
    if(mConst)
    {
      ofstr << " const=\"true\"";
    }
    ofstr << ">\n";
    // more stuff
    ofstr << "</method>\n";
  }


  void GpMethod::Const(bool val)
  {
    mConst = val;
  }

  bool GpMethod::Const()
  {
    return mConst;
  }

  void GpMethod::Virtual(bool val)
  {
    mVirtual = val;
  }

  bool GpMethod::Virtual()
  {
    return mVirtual;
  }

  void GpMethod::Pure(bool val)
  {
    mPure = val;
  }

  bool GpMethod::Pure()
  {
    return mPure;
  }

  void GpMethod::Name(const string& val)
  {
    mName = val;
  }

  const string& GpMethod::Name()
  {
    return mName;
  }

  void GpMethod::Type(const string& val)
  {
    mType = val;
  }

  const string& GpMethod::Type()
  {
    return mType;
  }
}

