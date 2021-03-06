#pragma once

#include <string>
#include <vector>

#include "iglHeader.h"

struct Stitch
{
	uint32_t index;
	uint32_t yarn;

	enum : char
	{
		Start	 = 's',
		End		 = 'e',
		Tuck	 = 't',
		Miss	 = 'm',
		Knit	 = 'k',
		Increase = 'i',
		Decrease = 'd',
	};

	enum : char
	{
		CW = 'c', Clockweise = CW,
		AC = 'a', Anticlockweise = AC, CCW = AC, Counterclockweise = AC,
	};

	char type = Knit;
	char direction = CW;

	uint32_t in_0 = -1U;
	uint32_t in_1 = -1U;
	uint32_t out_0 = -1U;
	uint32_t out_1 = -1U;

	MAT_3d vertex;
	RVec_3d color;

	bool check_type() const;
};

class Stitches
{
	std::vector<Stitch> stitches;
public:
	bool load_stitches(std::string const& path);
	const std::vector<Stitch>& get();
	bool display();
	bool display(size_t pos, size_t len);
};

class Settings
{
public:
	std::string ROOT_DIR = "../";	// root directory of current solution
	std::string FILE_NAME = "";		// file name of 3d mesh, read from Settings.csv
	size_t		pos = 0;
	size_t		len = 0;
};