#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace CommandSpace {

//Type - the first input in a command
enum Type {RUN, SET, PRINT, SAVE, EXIT, HELP, NO_TYPE};
//Flag - the second input in a command
enum Flag {INTERVAL, COUNT, REPORT, CONF, BLK_READ, BLK_READ_S, KB_READ_S, BLK_WRITE, BLK_WRITE_S, KB_WRITE_S, NO_FLAG};

struct Command {
  Type type;
  Flag flag;
  string value;
};

class CommandLine {
private:
  Command cmd_;
  Type StrToType(string const& type);
  Flag StrToFlag(string const& flag);
public:
  CommandLine(); //constructor
  Type GetType() const {return cmd_.type;} //returns type from cmd_
  Flag GetFlag() const {return cmd_.flag;} //returns flag from cmd_
  string GetValue() const {return cmd_.value;} //returns value from cmd_
  short GetCommand(); //prototype of GetCommand()
};
}



#endif
