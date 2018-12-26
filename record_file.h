#ifndef RECORD_FILE_H
#define RECORD_FILE_H

#include <vector>

using namespace std;

class Record_file {
public:
    const static string path;
    static vector<pair<string, int>> getRecords();
    static void writeRecords(vector<pair<string, int>>);
};

#endif // RECORD_FILE_H
