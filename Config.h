#ifndef CONFIG_H
#define CONFIG_H
#include "CommandLine.h"
#include <stdlib.h>
using std::cout;
using std::string;
using namespace CommandSpace;

namespace ConfigSpace {
  
  class Configuration {
  private:
    int interval_;
    int count_;
    bool blk_read_flag_;
    bool blk_reads_flag_;
    bool kb_reads_flag_;
    bool blk_wrtn_flag_;
    bool blk_wrtns_flag_;
    bool kb_wrtns_flag_;
    bool changed_;
    string filename_; //report filename
  public:
    int getInterval() const {return interval_;} //returns interval_
    int getCount() const {return count_;} //returns count_
    string GetFilename() const {return filename_;}; //returns filename_
    void SetFilename(string filename) {filename_ = filename;} //sets filename_
    bool IsChanged() {return changed_;} //boolean that tells whether the config file has been changed
    void PrintConf() const;   //prototype of PrintConf().
    void SaveConf(); //prototype of SaveConf()
    void LoadConf(); //prototype of LoadConf()
    void Set (const CommandLine& cmdline);  //prototype of Set()
    bool Get (Flag flag) const; //prototype of Get()
  };
}


#endif
