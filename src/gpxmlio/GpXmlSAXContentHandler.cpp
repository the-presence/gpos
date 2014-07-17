#ifndef GPXMLSAXCONTENTHANDLER_H
#include <gpxmlio/GpXmlSAXContentHandler.hpp>
#endif
#include <debug.hpp>
#include <stdexcept>
#include <string>
#include <iostream>
#include <ctype.h>

XERCES_CPP_NAMESPACE_USE

namespace gpos
{
    using namespace std;

    GpXmlSAXContentHandler::GpXmlSAXContentHandler(GpCodeModel* val)
    {
        DEBOUT("GpXmlSAXContentHandler::GpXmlSAXContentHandler()");
        if (!val)
        {
            throw std::invalid_argument("Null pointer passed to GpXmlSAXContentHandler::GpXmlSAXContentHandler()");
        }
        mModel = val;
        mStateMachine.AddModel(mModel);
    }

    void GpXmlSAXContentHandler::startElement(const XMLCh        * const /*uri*/,
                                              const XMLCh* const localname,
                                              const XMLCh        * const /*qname*/,
                                              const Attributes&  attrs)
    {
        string elementName(XMLString::transcode(localname) );
        mStateMachine.FoundElement(mElementMap[elementName], attrs);

        //   for (XMLSize_t i = 0; i < numAtts; i++)
        //   {
        //     string Qname(XMLString::transcode(attrs.getQName(i)));
        //     string URI(XMLString::transcode(attrs.getURI(i)));
        //     string local(XMLString::transcode(attrs.getLocalName(i)));
        //     string type(XMLString::transcode(attrs.getType(i)));
        //     string value(XMLString::transcode(attrs.getValue(i)));
        //     cout << "\t" << i <<", "<<Qname<<", "<<URI<<", "<<local<<", "<<type<<", "<<value<<"\n";
        //   }
        // }

    }

    void GpXmlSAXContentHandler::endElement(const XMLCh        * const /*uri*/,
                                            const XMLCh* const localname,
                                            const XMLCh        * const /*qname*/)
    {
        string elementName(XMLString::transcode(localname) );
        mStateMachine.ClosedElement(mElementMap[elementName]);
    }

    void GpXmlSAXContentHandler::characters(const XMLCh* const chars,
                                            const XMLSize_t /*len*/)
    {
        string str(XMLString::transcode(chars) );
        size_t strBegin = str.find_first_not_of(" \n\r\t");
        if (strBegin == std::string::npos)
        {
            return; // no content
        }
        mStateMachine.ProcessChars(str);
    }

    void GpXmlSAXContentHandler::fatalError(const SAXParseException& exception)
    {
        char* message = XMLString::transcode(exception.getMessage() );
        cout << "Fatal Error: " << message
             << " at line: " << exception.getLineNumber()
             << endl;
        XMLString::release(&message);
    }
}
