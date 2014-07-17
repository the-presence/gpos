#ifdef DEBUG
#include <iostream>
using namespace std;
#define DEBOUT(val) cout << val << endl
#define DUMPR(object) object.dump()
#define DUMPP(object) object->dump()
#else
#define DEBOUT(val)
#define DUMPP(object)
#define DUMPR(object)
#endif
