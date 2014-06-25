#ifndef GPCODEMODEL_H
#define GPCODEMODEL_H

#include <gpxmlio/GpClass.hpp>
#include <list>

namespace gpos
{
  using namespace std;

  class GpCodeModel
  {
  public:
    GpCodeModel();


  private:
    list<GpClass> classes;

  };
}

#endif /* GPCODEMODEL_H */
