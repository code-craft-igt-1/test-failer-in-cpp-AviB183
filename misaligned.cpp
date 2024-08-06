#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

const char* majorColor[] = { "White", "Red", "Black", "Yellow", "Violet" };
const char* minorColor[] = { "Blue", "Orange", "Green", "Brown", "Slate" };

int printColorMap() {
    int i = 0, j = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            std::cout << i * 5 + j << " | " << majorColor[i] << " | " << minorColor[i] << "\n";
        }
    }
    return i * j;
}

static void _convertStrStreamToStrList(std::stringstream strStream,
    std::vector<std::string>& strList) {
    strList.clear();

    while (strStream.good()) {
        std::string singleLine;
        getline(strStream, singleLine);
        strList.push_back(singleLine);
    }
}

static void _getColorMapOutputLines(std::vector <std::string>& outputLines) {
    std::ostringstream outputStream;
    std::streambuf* coutBuffBackup = std::cout.rdbuf();
    std::cout.rdbuf(outputStream.rdbuf());

    int result = printColorMap();

    std::cout.rdbuf(coutBuffBackup);

    _convertStrStreamToStrList(std::stringstream(outputStream.str()), outputLines);
}

static bool _checkContents(const std::vector <std::string>& outputList) {
    bool contentPresent = true;
    int listIndex = 0;
    for (int i = 0; i < 5 && contentPresent; ++i)
        for (int j = 0; j < 5 && contentPresent; ++j) {
            contentPresent = (outputList[listIndex].find(majorColor[i]) != std::string::npos &&
                outputList[listIndex].find(minorColor[j]) != std::string::npos);
            ++listIndex;
        }

    return contentPresent;
}

static bool _checkFormat(const std::vector <std::string>& outputList, const char& delim) {
    bool formatIsCorrect = true;

    size_t pos1 = outputList[0].find(delim);
    size_t pos2 = outputList[0].find(delim, pos1 + 1);
    formatIsCorrect = (pos1 != std::string::npos && pos2 != std::string::npos);

    for (int i = 0; i < outputList.size() && formatIsCorrect; ++i)
        formatIsCorrect = (outputList[i][pos1] == delim && outputList[i][pos2] == delim);

    return formatIsCorrect;
}

int main() {
    std::vector <std::string> outputLines;
    _getColorMapOutputLines(outputLines);

    assert(outputLines.size() == 25);
    assert(_checkContents(outputLines) == true);
    assert(_checkFormat(outputLines, '|') == true);

    std::cout << "All is well (maybe!)\n";
    return 0;
}
