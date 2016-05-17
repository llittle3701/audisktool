#include "Tool.h"

namespace ToolSpace {
 
  /*Loads the configuration file, loads report.adt (or creates one if it it not present)
   * and prints a welcome message 
   * Input: Configuration object and a Report object
   */ 
  void Tool::Init(Configuration &conf, Report &report) {
     conf.LoadConf();
     conf.SetFilename("report.adt");
    ifstream inStream;
    inStream.open("report.adt");
    if (inStream.fail()) {
      ofstream out_file ("report.adt");
      out_file.close();
      return;
    }
    report.LoadReport("report.adt");

    cout << "auDiskTool, version 1.0.0. Type 'help' to find out more about commands." << endl;
  }

  /* Given a command, responds with the appropriate action
   * Input: a CommandLine object, a Configuration object, and a Report object
   */
  void Tool::RespondCmd(const CommandLine& cmd, Configuration &conf, Report &report) {
    Type type;
    Flag flag;
    string value;

    type = cmd.GetType();
    flag = cmd.GetFlag();
    value = cmd.GetValue();
  
    switch (type) {
    case RUN:
      if (flag != NO_FLAG)
	cout << "Error. Too many inputs" << endl;
      Run(conf, report);
      break;
    case SET:
      if (value == "") {
	cout << "Invalid input" << endl;
	break;
      }
      if (flag == REPORT) {
	if (value.length() < 4 || value.substr(value.length() - 4) != ".adt") {
	  value = value + ".adt";
	}
	ifstream ifile((char*)value.c_str());
	if (ifile) {
	  cout << "The report file is changed from '" << conf.GetFilename() << "' to '" << value << "'" << endl;
	  cout << "Because this file already exists, new records will be appended to '" << value << "'" << endl;
	  conf.SetFilename(value);
	}

	else {
	  cout << "The report file is changed from '" << conf.GetFilename() << "' to '" << value << "'" << endl;
	  rename((char*)conf.GetFilename().c_str(), (char*)value.c_str());
	  conf.SetFilename(value);
	}
	break;
      }
      conf.Set(cmd);
      break;
    case PRINT:
      if (flag == CONF) {
	if (value != "") {
	  cout << "Error. Too many inputs" << endl;
	  break;
	}
	conf.PrintConf();
      }
      else if (flag == REPORT) {
	if (value != "") {
	  cout << "Error. Too many inputs" << endl;
	  break;
	}
	report.PrintReport(conf);
      }
      else
	cout << "Invalid input" << endl;
      break;
    case SAVE:
      if (flag != NO_FLAG) {
	cout << "Error. Too many inputs" << endl;
	break;
      }
      conf.SaveConf();
      break;
    case HELP:
      if (flag != NO_FLAG) {
	cout << "Error. Too many inputs" << endl;
	break;
      }
      Help();
      break;
    case EXIT:
      if (conf.IsChanged()) {
	conf.SaveConf();
      }
      break;

    default :
      cout << "ERROR" << endl;
      break;
    }
  }

  /*Outputs a list of valid user commands */
  void Tool:: Help() {
    string message = "run - run the monitoring tool\n"
      "set interval [value] - set the sampling period to [value]\n"
      "set count [value] - set the number of records to [value]\n"
      "set report [name] - set report filename to [name]\n"
      "set blk_read    [0|1] - set print_blk_read to 0 or 1\n"
      "set blk_read/s  [0|1] - set print_blk_read/s to 0 or 1\n"
      "set kb_read/s   [0|1] - set print_kb_read/s to 0 or 1\n"
      "set blk_write   [0|1] - set print_blk_write to 0 or 1\n"
      "set blk_write/s [0|1] - set print_blk_write/s to 0 or 1\n"
      "set kb_write/s  [0|1] - set print_kb_write/s to 0 or 1\n"
      "print conf - display all the parameters\n" 
      "print report - open and display the report file\n"
      "save - the configuration file audisktool.conf is updated\n"
      "exit - exit the tool";

    cout << message << endl;
  }

  /* Opens /proc/diskstats and reads data pertaining to the device that the user specifies. Then, generates a report from that data.
   * Input: a Configuration object and a Report object
   */
  void Tool::Run(const Configuration &conf, Report &report) {
    unsigned int blk_read1;
    unsigned int blk_read2;
    unsigned int blk_write1;
    unsigned int blk_write2;
    unsigned int sectors_read1;
    unsigned int sectors_read2;
    unsigned int sectors_write1;
    unsigned int sectors_write2;
    unsigned int total_sectors_read;
    unsigned int total_sectors_written;
    ifstream file;
    string device;
    string sda_check;
    bool first_iteration = true;
    bool found = false;

    cout << "Which disk or partition would you like to test? (sda is usually the most active)" << endl;
    cout << "> ";
    cin.clear();
    cin >> device;
    cin.ignore();

    file.open("/proc/diskstats"); 
    if (file.is_open()) {
      conf.PrintConf();
      cout << "Please wait..." << endl;
   
      for (int count = 0; count < 2 * conf.getCount(); count++) {
	double val;
	file.seekg(0, file.beg);
                     
	while (file.good()) {
	  file >> sda_check;
	
	  if (first_iteration == true) {                 
	    if (sda_check == device) {
              found = true;               
	      file >> val; // Total Amount of Reads
	      blk_read1 = val;
                             
	      file >> val; // Total Amount of Reads Merged
                             
	      file >> val; // Amount of Sectors read
	      sectors_read1 = val;
                                
	      file >> val; // Amount of Milliseconds spent reading
                             
	      file >> val; // Amount of writes completed
	      blk_write1 = val;
                             
	      file >> val; // Amount of writes merged
                             
	      file >> val; // Amount of sectors written
	      sectors_write1 = val;
                              
	      file >> val; // Amount of Milliseconds spent writing
                             
	      file >> val; // Amount of I/Os currently in progress
                             
	      file >> val; // Amount of Milliseconds spent doing I/Os
                             
	      file >> val; // Weighted Amount of Millisecond spent doing I/Os
         
	      file.clear();
	      file.close();
	      sleep(conf.getInterval());
	      file.open("/proc/diskstats");
	      first_iteration = false;
	      break;
	    }
	  }

	  else {
	    if (sda_check == device) {
	      Record record;  
           
	      file >> val; // Total Amount of Reads
	      blk_read2 = val;
                               
	      file >> val; // Total Amount of Reads Merged
                             
	      file >> val; // Amount of Sectors read
	      sectors_read2 = val;
                            
	      file >> val; // Amount of Milliseconds spent reading
                             
	      file >> val; // Amount of writes completed
	      blk_write2 = val;
                              
	      file >> val; // Amount of writes merged
                             
	      file >> val; // Amount of sectors written
	      sectors_write2 = val;
                 
	      file >> val; // Amount of Milliseconds spent writing
                             
	      file >> val; // Amount of I/Os currently in progress
                             
	      file >> val; // Amount of Milliseconds spent doing I/Os
                             
	      file >> val; // Weighted Amount of Millisecond spent doing I/Os
            
	      record.blk_read = blk_read2 - blk_read1;
	      record.blk_write = blk_write2 - blk_write1;
	      total_sectors_read = sectors_read2 - sectors_read1;
	      total_sectors_written = sectors_write2 - sectors_write1;
	    
	      // Formula provided to check for IO Throughput
	      record.blk_read_s = record.blk_read / (conf.getInterval());
	      record.blk_write_s = record.blk_write / (conf.getInterval());
	      record.kb_read_s = static_cast<double>(total_sectors_read) / (2 * conf.getInterval()); //assuming 512 bytes per sector
	      record.kb_write_s = static_cast<double>(total_sectors_written) / (2 * conf.getInterval()); //assuming 512 bytes per sector
                             
	      report.AddRecord(record);
	      file.clear();
	      first_iteration = true;
	      break;
	    }
	  }
	  }
	if (found == false) {
	  cout << "\nDevice '" << device << "' not found" << endl;
	  return;
	}
      }
      cout << "\nThe file \"" << conf.GetFilename() << "\" was updated.\n";
      file.close();
      report.SaveReport(conf.GetFilename());
    }
    else {
      cout << "Error opening file.";
    }

  }

}
