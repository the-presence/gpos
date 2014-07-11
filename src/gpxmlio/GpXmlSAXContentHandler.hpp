#ifndef GPXMLSAXCONTENTHANDLER_H
#define GPXMLSAXCONTENTHANDLER_H
#include <gpxmlio/GpXmlStateMachine.hpp>
#include <gpxmlio/GpXmlElementMap.hpp>
#include <gpxmlio/GpCodeModel.hpp>

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include <debug.hpp>

#include <string>

XERCES_CPP_NAMESPACE_USE

  namespace gpos
{
  using namespace std;

  class GpXmlSAXContentHandler : public DefaultHandler {
  public:
    GpXmlSAXContentHandler(GpCodeModel*);
    void startElement(const   XMLCh* const    uri,
                      const   XMLCh* const    localname,
                      const   XMLCh* const    qname,
                      const   Attributes&     attrs);

    void endElement(const   XMLCh* const    uri,
                    const   XMLCh* const    localname,
                    const   XMLCh* const    qname);

    void fatalError(const SAXParseException&);

    void characters(const XMLCh* const chars,
                    const XMLSize_t len);
  private:
    GpXmlStateMachine mStateMachine;
    GpXmlElementMap mElementMap;
    GpCodeModel* mModel;
  };
}

#endif
