#include <gpxmlio/GpCodeModel.hpp>
#include <debug.hpp>
#include <stdexcept>

namespace gpos
{

    GpCodeModel::GpCodeModel()
    {
        DEBOUT("GpCodeModel::GpCodeModel()");
    }

    void GpCodeModel::AddClass(GpClass* obj)
    {
        DEBOUT("GpCodeModel::AddClass()");
        if (!obj)
        {
            throw std::invalid_argument("Null pointer passed to GpCodeModel::AddClass()");
        }
        mClasses.push_back(obj);
    }

    void GpCodeModel::WriteAsXml()
    {
        DEBOUT("GpCodeModel::WriteAsXml()");
        int lim = mClasses.size();
        if (lim > 0)
        {
            for (int i = 0; i < lim; i++)
            {
                mClasses[i]->WriteAsXml();
            }
        }

    }

    // ostream& operator<< (ostream& ostr, const GpCodeModel& gpcm)
    // {
    //   DEBOUT("ostream& operator<< (ostream& ostr, const GpCodeModel& gpcm)");

    //   std::list<GpClass*>::const_iterator iterator;
    //   for (iterator = gpcm.mClasses.begin(); iterator != gpcm.mClasses.end(); ++iterator)
    //   {
    //     ostr << (*iterator);
    //   }
    //   return ostr;
    // }
}
