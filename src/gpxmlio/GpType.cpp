#include <gpxmlio/GpType.hpp>
#include <debug.hpp>
namespace gpos
{

  GpType::GpType()
    : mConst(false),
        mStatic(false),
        mDirec(DIRECT)
  {
  }

  GpType::GpType(const GpType& rhs)
  {
    DEBOUT("GpType::GpType");
    mType = rhs.Type();
    DEBOUT(mType);
    mStatic = rhs.Static();
    mConst = rhs.Const();
    mDirec = rhs.Direc();
  }

  const GpType& GpType::operator=(const GpType& rhs)
  {
    DEBOUT("GpType::operator=");
    mType = rhs.Type();
    DEBOUT(mType);
    mStatic = rhs.Static();
    mConst = rhs.Const();
    mDirec = rhs.Direc();
    return *this;
  }

  void GpType::WriteAsXml(ofstream& ofstr)
  {
    DEBOUT("GpType::WriteAsXml");
    // if(Type().length() != 0)
    // {
    //  DEBOUT("mType.length() != 0");
    ofstr << "<type";
    if (mConst)
    {
      ofstr << " const=\"true\"";
    }
    if (mStatic)
    {
      ofstr << " static=\"true\"";
    }
    switch (mDirec)
    {
      case POINTER:
        ofstr << " direc=\"ptr\"";
        break;
      case REFERENCE:
        ofstr << " direc=\"ref\"";
        break;
      default:
        break;
    }
    ofstr << ">" << mType << "</type>\n";
    //  }
  }

  void GpType::Const(bool val)
  {
    mConst = val;
  }

  void GpType::Static(bool val)
  {
    mStatic = val;
  }

  void GpType::Type(const string& val)
  {
    DEBOUT("GpType::Type");
    mType = val;
    DEBOUT(mType);
  }

  void GpType::Direc(GpDirecType val)
  {
    mDirec = val;
  }

  bool GpType::Const() const
  {
    return mConst;
  }

  bool GpType::Static() const
  {
    return mStatic;
  }

  const string& GpType::Type() const
  {
    return mType;
  }

  GpDirecType GpType::Direc() const
  {
    return mDirec;
  }

  #ifdef DEBUG
  void GpType::dump()
  {
    cout << "  GpType :: " << this << endl;
    cout << "    size :: " << sizeof(this) << endl;
    cout << "  mConst :: " << mConst << endl;
    cout << " mStatic :: " << mStatic << endl;
    cout << "  mDirec :: " << mDirec << endl;
    cout << "   mType :: " << mType << endl;
  }
  #endif

}
