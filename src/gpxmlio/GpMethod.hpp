#ifndef GPMETHOD_H
#define GPMETHOD_H

#include <vector>
#include <fstream>
#include <gpxmlio/GpArgument.hpp>

namespace gpos
{
  using namespace std;

  class GpMethod
  {
  public:
    GpMethod();
    void AddArg(GpArgument*);
    void WriteAsXml(ofstream&);
    void Const(bool);
    bool Const();
    void Virtual(bool);
    bool Virtual();
    void Pure(bool);
    bool Pure();
    void Name(const string&);
    const string&  Name();
    void Type(const string&);
    const string&  Type();

  private:
    bool mConst;
    bool mVirtual;
    bool mPure;
    string mName;
    string mType;;

    vector<GpArgument*> mArgs;
  };
}

#endif
