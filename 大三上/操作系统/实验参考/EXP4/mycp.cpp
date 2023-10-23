#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string filename = "Y:/cad/Scan.txt";
    string targetRow = "001";
    string targetCol = "014";

    ifstream fin(filename);
    string line;
    bool imagesSection = false;
    int row = -1, col = -1;
    while (getline(fin, line)) {
        if (line == "[Images]") {
            imagesSection = true;
            continue;
        }
        if (imagesSection) {
            int pos = line.find('=');
            if (pos != string::npos) {
                string key = line.substr(0, pos);
                if (key == "Row" + targetRow) {
                    row = stoi(line.substr(pos + 1));
                } else if (key == "Col" + targetCol) {
                    col = stoi(line.substr(pos + 1));
                }
            }
        }
        if (row != -1 && col != -1) {
            break;
        }
    }
    fin.close();

    if (row == -1 || col == -1) {
        cout << "Error: target row or column not found." << endl;
    } else {
        cout << "Row" << targetRow << ": " << row << endl;
        cout << "Col" << targetCol << ": " << col << endl;
    }

    return 0;
}

