#ifndef RECORD_FILE_H
#define RECORD_FILE_H

#include <vector>

using namespace std;

class Record_File {
public:
    static vector<pair<string, int>> getRecords(string path);
    static void writeRecords(vector<pair<string, int>>, string path);
};

#endif // RECORD_FILE_H
