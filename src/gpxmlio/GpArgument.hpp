#ifndef GPARGUMENT_H
#define GPARGUMENT_H

#include <gpxmlio/Gpos.hpp>
#include <gpxmlio/GpType.hpp>
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

    GpType&       Type();
    const string& Name();

    void Type(const GpType&);
    void Name(const string&);
    void WriteAsXml(ofstream&);
    #ifdef DEBUG
    void dump();
    #endif

  private:

    GpType mType;
    string mName;
  };
}

#endif
