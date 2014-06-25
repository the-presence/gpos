#ifndef GPCLASS_H
#define GPCLASS_H

#include <string>
#include <list>
namespace gpos
{
  using namespace std;

  class GpClass
  {
  public:
    GpClass();
    void Name(const string&);
    const string& Name();
    void Namespace(const string&);
    const string& Namespace();

  private:
    string name;
    string nspace;
    // list<GpMember> privateMembers;
    // list<GpMember> publicMembers;
    // list<GpMember> protectedMembers;
    // list<GpMethod> privateMethods;
    // list<GpMethod> publicMethods;
    // list<GpMethod> protectedMethods;

  };
}
#endif
