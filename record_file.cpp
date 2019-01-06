#include "record_file.h"
#include <fstream>

vector<pair<string, int>> Record_File::getRecords(string path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw string("Error while opening high scores file on reading");
    }
    vector<pair<string, int>> vect = vector<pair<string, int>>();
    char* buf = new char[50];
    int score;
    try {
        while (!file.eof()) {
            file>>buf;
            file>>score;
            vect.push_back(pair<string, int>(string(buf), score));
        }

    } catch (exception) {
        delete[] buf;
        file.close();
        throw string("Error while reading from high scores file");
    }

    delete[] buf;
    file.close();

    return vect;
}

void Record_File::writeRecords(vector<pair<string, int>> records, string path) {
    ofstream file(path);
    if (!file.is_open()) {
        throw string("Error while opening high scores file on writing");
    }
    try {
        for (auto record : records) {
            for (size_t i = 0; i < record.first.length(); i++) {
                if (record.first[i] == ' ') {
                    record.first.replace(i, 1, "_");
                }
            }
            file<<record.first.c_str();
            file<<" ";
            file<<record.second;
            if (record != records.at(records.size() - 1)) {
                file<<endl;
            }
        }

    } catch (exception) {
        file.close();
        throw string("Error while writing to high scores file");
    }
    file.close();
}
