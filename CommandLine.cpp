#include "CommandLine.h"
namespace CommandSpace {
  /* Constructor for CommandLine */
  CommandLine::CommandLine() {
    cmd_.type = NO_TYPE;
    cmd_.flag = NO_FLAG;
    cmd_.value = "";
  }
 
  /* Reads user input and parses a command from it
   * Returns 1 if input is valid. Returns 0 if input is invalid 
   */
  short CommandLine:: GetCommand() {
    string cmdline;
    int position;
    string type;
    string flag;

    cout << "\nEnter a command below" << endl;
    cout << "> ";
    getline (cin, cmdline);

    //Find command type
    position = cmdline.find(" "); 
    type = cmdline.substr(0, position);
    cmd_.type = StrToType(type);
    if (cmd_.type == NO_TYPE) {
      cout << "Invalid input" << endl;
      return 0;
    }

    //Find command flag; remove type from cmdline
    cmdline = cmdline.substr(position+1);

    //If cmdline has a flag
    if (cmdline != type) {
      position = cmdline.find(" ");
      flag = cmdline.substr(0, position);
      cmd_.flag = StrToFlag(flag);
      if (cmd_.flag == NO_FLAG) {
	cout << "Invalid input" << endl;
	return 0;
      }

      //remove flag from cmdline; ready to extract value
      cmdline = cmdline.substr(position+1);
      //If cmdline has a value
      if (cmdline != flag) {
	cmd_.value = cmdline;
	if (cmd_.value.find(" ") != -1) {
	  cout << "Error. Too many inputs" << endl;
	  return 0;
	}
	return 1; //e.g., set count 15
      }
      //cmdline has no value 
      else {
	cmd_.value.clear();
	return 1;
      }
    }

    //cmdline has no flag and no value
    else {
      cmd_.flag = NO_FLAG; //No flag
      cmd_.value.clear(); //value = "";
      return 1; //e.g., help
    }
  }

  /* Converts string from user input into a Type
   * Input: user input string
   * Returns a Type
   */
  Type CommandLine::StrToType(string const& type) {
    if (type == "run")
      return RUN;
    else if (type == "set")
      return SET;
    else if (type == "print")
      return PRINT;
    else if (type == "save")
      return SAVE;
    else if (type ==  "exit")
      return EXIT;
    else if (type == "help")
      return HELP;
    else
      return NO_TYPE;
  }

  /* Converts string from user input into a Flag
   * Input: user input string
   * Returns a Flag
   */
  Flag CommandLine::StrToFlag(string const& flag) {
    if (flag == "interval")
      return INTERVAL;
    else if (flag == "count")
      return COUNT;
    else if (flag == "report")
      return REPORT;
    else if (flag == "conf")
      return CONF;
    else if (flag == "blk_read")
      return BLK_READ;
    else if (flag == "blk_read/s")
      return BLK_READ_S;
    else if (flag == "kb_read/s")
      return KB_READ_S;
    else if (flag == "blk_write")
      return BLK_WRITE;
    else if (flag == "blk_write/s")
      return BLK_WRITE_S;
    else if (flag == "kb_write/s")
      return KB_WRITE_S;
    else 
      return NO_FLAG;
  }
}
