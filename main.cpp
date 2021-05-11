#include <iostream>
#include <fstream>
#include <sstream>

#include<string>
#include<vector>

#include "iglHeader.h"
#include "Stitch.h"

int main(int argc, char *argv[])
{
	std::string path = "../data/teddy3.st";

	Stitches st;
	st.load_stitches(path);
	st.display();

	return EXIT_SUCCESS;
}
