#include <iostream>
#include <fstream>
#include <sstream>

#include "Stitch.h"

// Stitch
bool Stitch::check_type() const
{
	if (type == Start) 
	{
		return (in_0 == -1U && in_1 == -1U &&
				out_0 != -1U && out_1 == -1U);
	}
	else if (type == End) 
	{
		return (in_0 != -1U && in_1 == -1U &&
				out_0 == -1U && out_1 == -1U);
	}
	else if (type == Tuck || type == Miss || type == Knit) 
	{
		return (in_0 != -1U && in_1 == -1U &&
				out_0 != -1U && out_1 == -1U);
	}
	else if (type == Increase) 
	{
		return (in_0 != -1U && in_1 == -1U &&
				out_0 != -1U && out_1 != -1U);
	}
	else if (type == Decrease) 
	{
		return (in_0 != -1U && in_1 != -1U &&
				out_0 != -1U && out_1 == -1U);
	}
	else 
	{
		return false;
	}
}




// Stitches
bool Stitches::load_stitches(std::string const& path)
{
	std::ifstream file(path);
	std::string   line;
	uint32_t	  idx = 0;

	if (!file.is_open())
	{
		std::cout << "Cannot open file£º \"" << path << "\" !";
		return false;
	}

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		Stitch temp;
		temp.index = idx;
		temp.vertex.resize(1, 3);

		int32_t in[2];
		int32_t out[2];

		if (!(iss >> temp.yarn >> temp.type >> temp.direction
				 >> in[0] >> in[1] >> out[0] >> out[1]
				 >> temp.vertex(0,0) >> temp.vertex(0,1) >> temp.vertex(0,2)))
		{
			std::cerr << "ERROR: Failed to read Stitches." << std::endl;
			return EXIT_FAILURE;
		}

		temp.in_0 = in[0];
		temp.in_1 = in[1];
		temp.out_0 = out[0];
		temp.out_1 = out[1];

		switch (temp.type)
		{
		case 's':
		case 'e':
		{
			temp.color = RVec_3d(1, 0, 0); // red
			break;
		}
		case 'i':
		case 'd':
		{
			temp.color = RVec_3d(0, 1, 1); // cyan
			break;
		}
		default:
		{
			temp.color = RVec_3d(0.7, 0.7, 0.7); // grey
			break;
		}
		}

		if (!temp.check_type()) 
		{
			std::cerr << "ERROR: Stitches does not have proper in/out for type." << std::endl;
			std::cerr << "  line " << idx + 1 << ": '" << line << "'" << std::endl;
			temp.color = RVec_3d(1, 0, 0);
		}

		this->stitches.push_back(temp);

		++idx;
	}

	return EXIT_SUCCESS;
}

const std::vector<Stitch>& Stitches::get()
{
	return this->stitches;
}

bool Stitches::display()
{
	return display(0, 0);
}

bool Stitches::display(size_t pos, size_t len)
{
	uint32_t numV = this->stitches.size();
	uint32_t numE;

	IGL_Viewer viewer;
	viewer.data().line_width = 4;
	viewer.data().point_size = 6;

	// add vertices
	MAT_3d V;
	V.resize(numV, 3);
	for (auto& st : stitches)
	{
		auto& idx = st.index;
		auto& v = st.vertex;
		auto& color_v = st.color;

		V(idx, 0) = v(0);
		V(idx, 1) = v(1);
		V(idx, 2) = v(2);

		viewer.data().add_points(v, color_v);
		//std::cout << "V" << idx << ": " << v << std::endl;
	}
	//viewer.data().add_points(V, RVec_3d(1, 1, 0)); // yellow

	// add edges
	auto it_stitches_begin = this->stitches.begin();
	auto it_stitches_end   = this->stitches.end();

	size_t len_max     = it_stitches_end - it_stitches_begin;
	auto it_line_begin = (pos > 0 && pos < len_max)         ? it_stitches_begin + pos : it_stitches_begin;
	auto it_line_end   = (len > 0 && (pos + len) < len_max) ? it_line_begin + len     : it_stitches_end;

	auto it_stitches = it_line_begin;
	auto it_last_stitch = it_line_begin;
	

	for (; it_stitches != it_line_end; ++it_stitches)
	{
		auto& idx_last = it_last_stitch->index;
		auto& idx = it_stitches->index;
		
		if (idx == 0) { continue; }
		else
		{
			auto& it_source = V.row(idx_last);
			auto& it_target = V.row(idx);
			
			RVec_3d color_eg;
			if (it_last_stitch->direction == 'c' && it_stitches->direction == 'c')
			{
				color_eg = (idx_last == 0) ? RVec_3d(1, 0, 0) : RVec_3d(1, 1, 1); // white
			}
			else if (it_last_stitch->direction == 'a' && it_stitches->direction == 'a')
			{
				color_eg = (idx_last == 0) ? RVec_3d(1, 0, 0) : RVec_3d(0, 0, 0.7); // blue
			}

			viewer.data().add_edges(it_source, it_target, color_eg);
			//std::cout << "E " << idx_last << " -> " << idx << std::endl;
		}
		
		switch (it_stitches->type)
		{
		case 'e':
		case 't':
		case 'm':
		case 'k':
		case 'i':
		{
			uint32_t in_0 = it_stitches->in_0;
			auto& it_source = V.row(in_0);
			auto& it_target = V.row(idx);
			auto& color_eg = RVec_3d(0, 1, 0);	// green

			viewer.data().add_edges(it_source, it_target, color_eg);
			//std::cout << "E " << in_0 << " -> " << idx << std::endl;

			break;
		}
		case 'd':
		{
			uint32_t in_0 = it_stitches->in_0;
			uint32_t in_1 = it_stitches->in_1;

			auto& it_source_0 = V.row(in_0);
			auto& it_source_1 = V.row(in_1);
			auto& it_target = V.row(idx);
			auto& color_eg = RVec_3d(0, 1, 0);	// green

			viewer.data().add_edges(it_source_0, it_target, color_eg);
			viewer.data().add_edges(it_source_1, it_target, color_eg);
			//std::cout << "E " << in_0 << " -> " << idx << std::endl;
			//std::cout << "E " << in_1 << " -> " << idx << std::endl;

			break;
		}
		}

		it_last_stitch = it_stitches;
	}

	viewer.launch();

	return EXIT_SUCCESS;
}