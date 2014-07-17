#include <gpxmlio/GpArgument.hpp>
#include <gpxmlio/GpType.hpp>
#include <debug.hpp>

namespace gpos
{
  GpArgument::GpArgument()
  {
    DEBOUT("GpArgument::GpArgument");
    DUMPR(mType);
  }

  GpType& GpArgument::Type()
  {
    return mType;
  }

  void GpArgument::Type(const GpType& val)
  {
    DEBOUT("GpArgument::Type");
    mType = val;
    DUMPR(mType);
  }

  const string& GpArgument::Name()
  {
    return mName;
  }

  void GpArgument::Name(const string& val)
  {
    DEBOUT("GpArgument::Name");
    mName = val;
    DUMPR(mType);
  }

  void GpArgument::WriteAsXml(ofstream& ofstr)
  {
    DEBOUT("GpArgument::WriteAsXml");
    ofstr << "<arg>\n";
    mType.WriteAsXml(ofstr);
    ofstr << "<name>" << mName << "</name>\n";
    ofstr << "</arg>\n";
  }

  #ifdef DEBUG
  void GpArgument::dump()
  {
    cout << "GpArgument :: " << this << endl;
    cout << "      size :: " << sizeof(this) << endl;
    cout << "     mName :: " << mName << endl;
    cout << "     mType :: " << &mType << endl;
  }
  #endif

}
