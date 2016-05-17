#ifndef TOOL_H
#define TOOL_H
#include <iostream>
#include "Config.h"
#include "Report.h"
#include <string>
#include <unistd.h>
using std::cout;
using std::string;

using namespace ConfigSpace;
using namespace ReportSpace;

namespace ToolSpace {
  class Tool {
  private:
    void Run(const Configuration &conf, Report &report); //prototype of Run()
    void Help(); //prototype of Help()
  public:
    void RespondCmd(const CommandLine& cmd, Configuration &conf, Report &report); //prototype of RespondCmd()
    void Init(Configuration &conf, Report &report); //prototype of Init()
    void Exit() {exit(1);} //Exits the program
  };

}





#endif
