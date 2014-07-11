#ifndef GPARGUMENT_H
#define GPARGUMENT_H

#include <gpxmlio/Gpos.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace gpos
{

  using namespace std;

  class GpArgument
  {
  public:
    GpArgument();
    bool Const();
    void Const(bool);
    GpDType Direc();
    void Direc(GpDType);
    const string& Type();
    void Type(const string&);
    const string& Name();
    void Name(const string&);
    void WriteAsXml(ofstream&);

  private:
    bool mConst;
    GpDType mDirec;
    string mType;
    string mName;
  };
}

#endif
