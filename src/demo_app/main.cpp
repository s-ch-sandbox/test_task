#include <cstdlib>
#include "Demo.h"


int main() {
    demo::Run();
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
