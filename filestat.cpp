#include <iostream>
#include <filesystem>
#include <map>

using namespace std;
namespace fs = filesystem;

int main() {
    map<string, int> fileTypesCount;

    fs::path currentDir = fs::current_path();

    for (const auto& entry : fs::directory_iterator(currentDir)) {
        if (entry.is_regular_file()) {
            fileTypesCount["file"]++;
        } else if (entry.is_directory()) {
            fileTypesCount["dir"]++;
        } else if (entry.is_symlink()) {
            fileTypesCount["symlink"]++;
        } else {
            fileTypesCount["other"]++;
        }
    }


    for (const auto& [type, count] : fileTypesCount) {
        cout << type << ": " << count << endl;
    }

    return 0;
}
