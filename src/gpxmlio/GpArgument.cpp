#include <gpxmlio/GpArgument.hpp>
#include <debug.hpp>

namespace gpos
{
  GpArgument::GpArgument()
    :mConst(false),
       mDirec(DIRECT)
  {
  }

  bool GpArgument::Const()
  {
    return mConst;
  }
  void GpArgument::Const(bool val)
  {
    mConst = val;
  }

  GpDType GpArgument::Direc()
  {
    return mDirec;
  }
  void GpArgument::Direc(GpDType val)
  {
    mDirec = val;
  }

  const string& GpArgument::Type()
  {
    return mType;
  }

  void GpArgument::Type(const string& val)
  {
    mType = val;
  }

  const string& GpArgument::Name()
  {
    return mName;
  }

  void GpArgument::Name(const string& val)
  {
    mName = val;
  }

  void GpArgument::WriteAsXml(ofstream& ofstr)
  {
    DEBOUT("GpArgument::WriteAsXml()");
    if(mConst)
    {
      ofstr << "const ";
    }
    ofstr << mType;
    switch(mDirec)
    {
      case DIRECT:
        //ofstr << " ";
        break;
      case REFERENCE:
        //ofstr << "& ";
        break;
      case POINTER:
        //ofstr << "* ";
        break;
      default:
        break;
    }
    ofstr << mName;
  }
}
