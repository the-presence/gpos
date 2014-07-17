#ifndef GPXMLWRITER_H
#include <gpxmlio/GpXmlWriter.hpp>
#endif
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <stdexcept>
#include <fstream>
#include <iostream>

XERCES_CPP_NAMESPACE_USE

namespace gpos
{
    using namespace std;

    GpXmlWriter::GpXmlWriter()
    {
        try
        {
            XMLPlatformUtils::Initialize();
        }
        catch (const XMLException& toCatch)
        {
            char* message = XMLString::transcode(toCatch.getMessage() );
            cout << "Error during initialization! :\n";
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            exit(1);
        }
    }

    GpXmlWriter::~GpXmlWriter()
    {
        XMLPlatformUtils::Terminate();
    }

    void GpXmlWriter::WriteToFile(GpCodeModel* model)
    {
        if (!model)
        {
            throw std::invalid_argument("Null pointer passed to GpXmlWriter::WriteFile()");
        }
        model->WriteAsXml();
    }
}
