#ifndef REPORT_H
#define REPORT_H
#include <iostream>
#include <fstream>
#include <vector>
#include "Config.h"
#include <iomanip>
using std::ios;
using std::setw;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using namespace ConfigSpace;

namespace ReportSpace {
  struct Record {
    double interval;
    unsigned int count;
    double blk_read;
    double blk_read_s;
    double kb_read_s;
    double blk_write;
    double blk_write_s;
    double kb_write_s;
  };

  class Report {
  private:
    vector<Record> record_list_;
  public:
    void AddRecord(Record newRecord) {record_list_.push_back(newRecord);} //Adds a record to the record_list_ vector
    void PrintReport(const Configuration &conf); //prototype of PrintReport()
    bool SaveReport(string filename); //prototype of SaveReport()
    bool LoadReport(string filename); //prototype of LoadReport()
  };

}

#endif
