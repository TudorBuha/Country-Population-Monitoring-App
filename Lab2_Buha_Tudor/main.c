#include <stdio.h>
#include "ui.h"
#include "tests.h"
#include <crtdbg.h>


int main()
{
    testAll();
    startApplication();
    _CrtDumpMemoryLeaks();
    return 0;
}
