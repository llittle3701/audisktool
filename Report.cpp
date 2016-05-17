#include "Report.h"

namespace ReportSpace {
  /* Prints all records within the report, omitting some values depending on configuration parameters
   * Input: an object of the Configuration class
   */
  void Report::PrintReport(const Configuration &conf) {
    cout.precision(3);
    ifstream inStream;
    inStream.open((char*)conf.GetFilename().c_str());

    bool isEmpty = inStream.peek() == EOF;
    if (isEmpty) {
      cout << "No record found in '" << conf.GetFilename() << "'" << endl;
      return;
    }
   
    LoadReport(conf.GetFilename());
    cout << record_list_.size() << " records found in '" << conf.GetFilename() << "'" << endl;
    cout << "blk_read blk_read/s kb_read/s blk_write blk_write/s kb_write/s" << endl;
    for (int i = 0; i < record_list_.size(); i++) {
      if (conf.Get(BLK_READ))
	cout << record_list_[i].blk_read << setw(12);
      else
	cout << "N/A" << setw(12);
      if (conf.Get(BLK_READ_S))
	cout << record_list_[i].blk_read_s << setw(12);
      else
	cout << "N/A" << setw(12);
      if (conf.Get(KB_READ_S))
	cout << record_list_[i].kb_read_s << setw(11);
      else
	cout << "N/A" << setw(11);
      if (conf.Get(BLK_WRITE))
	cout << record_list_[i].blk_write << setw(11);
      else
	cout << "N/A" << setw(11);
      if (conf.Get(BLK_WRITE_S))
	cout << record_list_[i].blk_write_s << setw(11);
      else
	cout << "N/A" << setw(11);
      if (conf.Get(KB_WRITE_S))
	cout << record_list_[i].kb_write_s << "\n";
      else
	cout << "N/A" << "\n";
    }
    record_list_.clear();
  }

  /* Saves all records in the report to the file matching the inputted filename
   * Input: a filename   
   * Returns true if successful, false otherwise
   */
  bool Report::SaveReport(string filename) {
    ofstream outStream;
    outStream.open((char*)filename.c_str(), ios::app);
    if (outStream.is_open() == false) {
      cout << "Failed in opening the file." << endl;
      return 0;
    }

    // outStream.setf(ios_base::fixed);
    outStream.precision(3); 
  

    for(int i = 0; i < record_list_.size(); i++) {
      outStream << record_list_[i].blk_read << " ";
      outStream << record_list_[i].blk_read_s << " ";
      outStream << record_list_[i].kb_read_s << " ";
      outStream << record_list_[i].blk_write << " ";
      outStream << record_list_[i].blk_write_s << " ";
      outStream << record_list_[i].kb_write_s << "\n";
    }
    record_list_.clear();
    outStream.close();
  }

  /* Loads all records to the report from the file matching the inputted filename
   * Input: a filename   
   * Returns true if successful, false otherwise
   */
  bool Report::LoadReport(string filename) {
    record_list_.clear();
    ifstream inStream;
    inStream.open((char*)filename.c_str());
 
    if (inStream.is_open() == false) {
      cout << "Failed in opening the file." << endl;
      return 0;
    }
    bool isEmpty = inStream.peek() == EOF;
    if (isEmpty) {
      return 1;
    }

    while (! inStream.eof()) {
      Record record;
      inStream >> record.blk_read;
      if(!inStream)
	break;
      inStream >> record.blk_read_s;
      inStream >> record.kb_read_s;
      inStream >> record.blk_write;
      inStream >> record.blk_write_s;
      inStream >> record.kb_write_s;
      AddRecord(record);
    }
    return 1;
    inStream.close();
  }
}
