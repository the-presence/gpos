#include <gpxmlio/GpMember.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <debug.hpp>

using namespace std;

namespace gpos
{
  GpMember::GpMember()
    :mConst(false),
       mDirec(DIRECT)
  {
  }

  bool GpMember::Const()
  {
    return mConst;
  }
  void GpMember::Const(bool val)
  {
    mConst = val;
  }

  GpDType GpMember::Direc()
  {
    return mDirec;
  }
  void GpMember::Direc(GpDType val)
  {
    mDirec = val;
  }

  const string& GpMember::Type()
  {
    return mType;
  }

  void GpMember::Type(const string& val)
  {
    mType = val;
  }

  const string& GpMember::Name()
  {
    return mName;
  }

  void GpMember::Name(const string& val)
  {
    mName = val;
  }

  void GpMember::WriteAsXml(ofstream& ofstr)
  {
    DEBOUT("GpMember::WriteAsXml()");
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
