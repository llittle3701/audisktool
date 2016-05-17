#include "Config.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

namespace ConfigSpace {
  /* Returns the parameter that matches the inputted flag
   * Input: A Flag
   * Return: true if the matching parameter is set to 1, false otherwise
   */
  bool Configuration:: Get(Flag flag) const {
    switch (flag) {
    case BLK_READ:
      return blk_read_flag_;
      break;
    case BLK_READ_S:
      return blk_reads_flag_;
      break;
    case KB_READ_S:
      return kb_reads_flag_;
      break;
    case BLK_WRITE:
      return blk_wrtn_flag_;
      break;
    case BLK_WRITE_S:
      return blk_wrtns_flag_;
      break;
    case KB_WRITE_S:
      return kb_wrtns_flag_;
      break;
    default:
      cout << "Error. Invalid flag" << endl;
    }
  }

 
  /* Prints the values of all configuration file parameters */
  void Configuration::PrintConf() const {
    cout << "Monitoring time = " << interval_ << " seconds, Number of records = " << count_ << ",\nprint_blk_read = " << blk_read_flag_ << ", print_blk_read/s = " << blk_reads_flag_ << ", print_kb_read/s = " << kb_reads_flag_ << ",\nprint_blk_write = " << blk_wrtn_flag_ << ", print_blk_write/s = " << blk_wrtns_flag_ << ", print_kb_write/s = " << kb_wrtns_flag_ <<",\nreport file name = '" << filename_ << "'" << endl;
  }

  /*Saves the configuration file parameters in audisktool.conf */
  void Configuration::SaveConf() {
    if (changed_ == false) {
      cout << "audisktool.conf has not been updated. There is no need to save the file" << endl;
      return;
    }
    changed_ = false;
    remove("audisktool.conf");
    ofstream outStream;
    outStream.open("audisktool.conf");
    if (outStream.fail()) {
      cout << "output file opening failed." << endl;
      return;
    }
    outStream << interval_ << " ";
    outStream << count_ << " ";
    outStream << blk_read_flag_ << " ";
    outStream << blk_reads_flag_ << " ";
    outStream << kb_reads_flag_ << " ";
    outStream << blk_wrtn_flag_ << " ";
    outStream << blk_wrtns_flag_ << " ";
    outStream << kb_wrtns_flag_;
  
    cout << "audisktool.conf has been updated" << endl;
    outStream.close();
  }

  /*Loads config parameters from audisktool.conf. Exits the program if audisktool.conf is not present */
  void Configuration::LoadConf() {
    changed_ = false;
    SetFilename("report.adt");
    ifstream inStream;
    inStream.open("audisktool.conf");
    if (inStream.fail()) {
      cout << "Configuration file 'audisktool.conf' opening failed. Make sure there is a configuration file in the auDiskTool's directory" << endl;
      exit(1);
    }

    bool isEmpty = inStream.peek() == EOF;
    if (isEmpty) {
      cout << "ERROR. Configuration file cannot be empty" << endl;
      exit(1);
    }

    inStream >> interval_ >> count_ >> blk_read_flag_ >> blk_reads_flag_ >> kb_reads_flag_ >> blk_wrtn_flag_ >> blk_wrtns_flag_ >> kb_wrtns_flag_;
  
    inStream.close();
    
  }

  /* Sets the config parameter based on the command in cmdline
   * Input: An object of the CommandLine class, containing a command from user input
   */
  void Configuration::Set(const CommandLine& cmdline) {
    Flag flag = cmdline.GetFlag();
    string value = cmdline.GetValue();
    int test;

    switch (flag) {
    case INTERVAL:
      test = atoi(value.c_str());
      if (test <= 0 ) {
	cout << "Invalid input. Be sure that interval is a non-negative, non-zero integer" << endl;
	break;
      }
      changed_ = true;
      interval_ = test;
      cout << "The sampling interval has been changed to " << test << " seconds" << endl;
      break;
  
    case COUNT:
      test = atoi(value.c_str());
      if (test <= 0 ) {
	cout << "Invalid input. Be sure that count is a non-negative, non-zero integer" << endl;
	break;
      }
      changed_ = true;
      count_ = test;
      cout << "The number of records generated in each run has been changed to " << test << endl;
      break;

    case BLK_READ:
      if (value != "1" && value != "0") {
	cout << "Invalid input. You can only set parameters to 0 or 1" << endl;
	break;
      }
      changed_ = true;
      blk_read_flag_ = atoi(value.c_str());	
      cout << "print_blk_read has been set to " << blk_read_flag_ << endl;
      break;

    case BLK_READ_S:
      if (value != "1" && value != "0") {
	cout << "Invalid input. You can only set parameters to 0 or 1" << endl;
	break;
      }
      changed_ = true;
      blk_reads_flag_ = atoi(value.c_str());
      cout << "print_blk_read/s has been set to " << blk_reads_flag_ << endl;
      break;

    case KB_READ_S:
      if (value != "1" && value != "0") {
	cout << "Invalid input. You can only set parameters to 0 or 1" << endl;
	break;
      }
      changed_ = true;
      kb_reads_flag_ = atoi(value.c_str());
      cout << "print_kb_read/s has been set to " << kb_reads_flag_ << endl;
      break;
   
    case BLK_WRITE:
      if (value != "1" && value != "0") {
	cout << "Invalid input. You can only set parameters to 0 or 1" << endl;
	break;
      }
      changed_ = true;
      blk_wrtn_flag_ = atoi(value.c_str());
      cout << "print_blk_write has been set to " << blk_wrtn_flag_ << endl;
      break;

    case BLK_WRITE_S:
      if (value != "1" && value != "0") {
	cout << "Invalid input. You can only set parameters to 0 or 1" << endl;
	break;
      }
      changed_ = true;
      blk_wrtns_flag_ = atoi(value.c_str());
      cout << "print_blk_write/s has been set to " << blk_wrtns_flag_ << endl;
      break;

    case KB_WRITE_S:
      if (value != "1" && value != "0") {
	cout << "Invalid input. You can only set parameters to 0 or 1" << endl;
	break;
      }
      changed_ = true;
      kb_wrtns_flag_ = atoi(value.c_str());
      cout << "print_kb_write/s has been set to " << kb_wrtns_flag_ << endl;
      break;
    }
  }
}
