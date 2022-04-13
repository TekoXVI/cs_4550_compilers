#include "instructions.h"
#include <iostream>

InstructionsClass code;

code.PushValue(1000);
code.PopAndWrite(); // Should print 1000

code.Finish();
code.Execute();
std::cout << "Success!" << std::endl;