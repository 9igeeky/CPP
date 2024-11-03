#include <iostream>
#include <filesystem>
#include <cstdlib>

using namespace std;
namespace fs = filesystem;

int main(int argc, char* argv[]) {

    if(argc != 2) {
        cerr << "Usage: " << argv[0] << "<file name" << endl;
        return 1;
    }
    string sourceFile = argv[1];

    string hiddenDir = ".hidden_dir";

    try {
        if (!fs::exists(hiddenDir)) {
            fs::create_directory(hiddenDir);
            cout << "Created hidden directory: " << hiddenDir << endl;
        }

        if (!fs::exists(sourceFile)) {
            cerr << "Error: file " << sourceFile << "does not exist" << endl;
            return 1;
        }
        fs::path destination = fs::path(hiddenDir) / fs::path(sourceFile).filename();

        fs::rename(sourceFile, destination);
        cout << "File " << sourceFile << "successfully moved to " << destination << endl;
    }
    catch (const fs::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << endl;
        return 1;
    }
    return 0;
}

