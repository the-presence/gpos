#ifndef GPTYPE_H
#define GPTYPE_H
#include <debug.hpp>
#include <string>
#include <fstream>
#include <gpxmlio/Gpos.hpp>

namespace gpos
{
  using namespace std;

  class GpType
  {
  public:
    GpType();
    GpType(const GpType&);
    const GpType& operator=(const GpType&);

    void Const(bool);
    void Static(bool);
    void Direc(GpDirecType);
    void Type(const string&);

    void WriteAsXml(ofstream&);

    bool Const() const;
    bool Static() const;
    GpDirecType Direc() const;
    const string& Type() const;

    #ifdef DEBUG
    void dump();
    #endif

  private:

    bool          mConst;
    bool          mStatic;
    GpDirecType   mDirec;
    string        mType;
  };
}

#endif
