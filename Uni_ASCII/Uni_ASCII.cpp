#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <algorithm>
    
using namespace std;
namespace fs = std::filesystem;

bool compareCatalogs(const fs::path & dir1, const fs::path & dir2) {     
    int cond = 0;
    
    for (const auto& entry : fs::directory_iterator(dir1)) {
        
        string filename1 = entry.path().filename().string();
        transform(filename1.begin(), filename1.end(), filename1.begin(), ::tolower);
            
        fs::path corresponding_path = dir2 / filename1;     

        if (!fs::exists(corresponding_path)) {      
            cout << filename1 << " отсутствует во втором каталоге.\n";
            cond++;
        }

            
        if (fs::is_directory(entry.status())) {     
            if (!compareCatalogs(entry.path(), corresponding_path))
                cond++;
        }
    }
        
    cout << "\n";
    for (const auto& entry : fs::directory_iterator(dir2)) {    
        string filename2 = entry.path().filename().string();
        transform(filename2.begin(), filename2.end(), filename2.begin(), ::tolower);

        fs::path corresponding_path = dir1 / filename2;

        if (!fs::exists(corresponding_path)) {
            cout << filename2 << " отсутствует в первом каталоге.\n";
            cond++;
        }
    }

    if (cond == 0)
        return true;
    else
        return false;
}

int main() {
    
    SetConsoleOutputCP(1251);

    string directory1 = "C:\\Uni_ASCII_test1";
    string directory2 = "C:\\Uni_ASCII_test2";
        
    if (!directory1.empty() && directory1.back() == '\\')    
        directory1.pop_back();
    

    fs::path path1 = directory1;
    fs::path path2 = directory2;

    if (compareCatalogs(path1, path2)) {
        cout << "\n\t\t-------- EQUAL --------\n";
    }
    else  {
        cout << "\n\t\t-------- NOT EQUAL --------\n";
    }

    return 0;
}
