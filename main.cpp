//Author: Lane Little
//Date: May 3, 2016
//Development Environment: emacs, g++, Linux
//Compile using make and run the main.o


#include "CommandLine.h"
#include "Tool.h"
#include "Report.h"
using namespace ToolSpace;
using namespace ReportSpace;
using namespace CommandSpace;
using namespace ConfigSpace;

/*auDiskTool driver */
int main() {

    Tool          tool;
    CommandLine   cmdline;
    Configuration config;
    Report        report;
    Type type;

    tool.Init(config, report);
      
    while ((type = cmdline.GetType())!= EXIT) {
      if (cmdline.GetCommand() != 0)
	tool.RespondCmd(cmdline, config, report);
    }
  
    tool.Exit();
    return 0;
}
