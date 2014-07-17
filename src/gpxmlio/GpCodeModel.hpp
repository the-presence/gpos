#ifndef GPCODEMODEL_H
#define GPCODEMODEL_H

#include <debug.hpp>

#include <gpxmlio/GpClass.hpp>

#include <ostream>
#include <vector>

namespace gpos
{
    using namespace std;

    class GpCodeModel
    {
public:
    GpCodeModel();
    void AddClass(GpClass*);
    void WriteAsXml();

    // friend ostream& operator<< (ostream& , const GpCodeModel&);
private:
    vector<GpClass*> mClasses;

    };
}

#endif /* GPCODEMODEL_H */
