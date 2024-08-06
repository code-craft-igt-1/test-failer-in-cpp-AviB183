#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

const char* majorColor[] = { "White", "Red", "Black", "Yellow", "Violet" };
const char* minorColor[] = { "Blue", "Orange", "Green", "Brown", "Slate" };

int printColorMap()
{
    int i = 0, j = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            cout << i * 5 + j << " | " << majorColor[i] << " | " << minorColor[i] << "\n";
        }
    }
    return i * j;
}

static void _convertStrStreamToStrList(stringstream strStream, vector<string> &strList)
{
    strList.clear();

    while (strStream.good())
    {
        std::string singleLine;
        getline(strStream, singleLine);
        strList.push_back(singleLine);
    }
}

static void _getColorMapOutputLines(vector <string>& outputLines)
{
    ostringstream outputStream;
    streambuf* coutBuffBackup = cout.rdbuf();
    cout.rdbuf(outputStream.rdbuf());

    int result = printColorMap();

    cout.rdbuf(coutBuffBackup);

    _convertStrStreamToStrList(stringstream(outputStream.str()), outputLines);
}

static bool _checkContents(const vector <string> &outputList)
{
    bool contentPresent = true;
    int listIndex = 0;
	for (int i = 0; i < 5 && contentPresent; ++i)
        for (int j = 0; j < 5 && contentPresent; ++j)
        {
            contentPresent = (outputList[listIndex].find(majorColor[i]) != string::npos &&
                outputList[listIndex].find(minorColor[j]) != string::npos);
            ++listIndex;
        }

    return contentPresent;
}

static bool _checkFormat(const vector <string>& outputList, const char& delim)
{
    bool formatIsCorrect = true;

    size_t pos1 = outputList[0].find(delim);
    size_t pos2 = outputList[0].find(delim, pos1 + 1);
    formatIsCorrect = (pos1 != string::npos && pos2 != string::npos);

    for (int i = 0; i < outputList.size() && formatIsCorrect; ++i)
        formatIsCorrect = (outputList[i][pos1] == delim && outputList[i][pos2] == delim);

    return formatIsCorrect;
}

int main()
{
    vector <string> outputLines;
    _getColorMapOutputLines(outputLines);

    assert(outputLines.size() == 25);
    assert(_checkContents(outputLines) == true);
    assert(_checkFormat(outputLines, '|') == true);
    
    cout << "All is well (maybe!)\n";
    return 0;
}
