#include <iostream>
#include <fstream>
#include <sstream>

#include<string>
#include<vector>

#include "iglHeader.h"
#include "Stitch.h"

void get_settings(Settings& settings)
{
    std::string fileName = "settings/Settings.csv";
    std::string dirs[4] = {
        "",
        "../",
        "../../",
        "../../../",
    };

    std::fstream file;

    for (std::string dir : dirs)
    {
        file.open(dir + fileName, std::ios::in);
        if (file)
        {
            settings.ROOT_DIR = dir;
            break;
        }
    }

    std::string line;
    while (std::getline(file, line))
    {
        size_t len = line.length();
        if (len <= 2) continue; // _ , _ : at least 3 characters

        std::string key, value;

        size_t comma = line.find_first_of(",");
        if (comma > 0)
        {
            key = line.substr(0, comma);
            value = line.substr(comma + 1, len - comma - 1);    //_ _ , _ _ _ _
        }

        if (key == "FILE_NAME") { settings.FILE_NAME = value; }
        else if (key == "first-line") { settings.pos = stoi(value); }
        else if (key == "length") { settings.len = stoi(value); }
    }
}

int main(int argc, char *argv[])
{
    // 1. get parameters from Settings.csv
    Settings settings;
    get_settings(settings);

    if (settings.FILE_NAME.length() == 0)
    {
        std::cout << "Cannot find file name in Settings.csv !" << std::endl;
        return EXIT_SUCCESS;
    }

	std::string path = settings.ROOT_DIR + "data/" + settings.FILE_NAME;

	Stitches st;
	st.load_stitches(path);
	st.display(settings.pos, settings.len);

	return EXIT_SUCCESS;
}
