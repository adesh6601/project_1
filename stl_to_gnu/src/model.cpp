#include <fstream>
#include <string>
#include <sstream>
#include "E:\stl_to_gnu\header\model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::read()
{
	std::fstream model;
	model.open("E:\\stl_to_gnu\\model.stl");

	std::string line;
	std::vector<std::vector<float>> triangle;
	while (std::getline(model, line))
	{
		std::istringstream words(line);
		float x;
		float y;
		float z;

		std::string word;
		words >> word;

		if (word == "facet")
		{
			words >> word;
			words >> x;
			words >> y;
			words >> z;

			std::vector<float> normal{-1 * x, -1 * y, -1 * z};
			_normals.push_back(normal);
			continue;
		}

		if (word == "vertex")
		{
			words >> x;
			words >> y;
			words >> z;

			std::vector<float> point{x, y, z};
			_points.insert(point);

			triangle.push_back(point);
			if (triangle.size() == 3)
			{
				_triangles.push_back(triangle);
				triangle.clear();
			}
			continue;
		}
	}
}

void Model::write()
{
	std::fstream output;
	output.open("E:\\stl_to_gnu\\output.txt");

	for (std::vector<std::vector<float>> triangle : _triangles)
	{
		for (std::vector<float> point : triangle)
		{
			output << point[0] << " " << point[1] << " " << point[2] << std::endl;
		}
		output << triangle[0][0] << " " << triangle[0][1] << " " << triangle[0][2] << std::endl;
	}
}

std::vector<float> Model::cross(std::vector<float> point, std::vector<float> normal)
{
	// normal[0] = normal[0] * 1.5;
	// normal[1] = normal[1] * 1.5;
	// normal[2] = normal[2] * 1.5;

	std::vector<float> product{-1, -1, -1};

	product[0] = (point[1] * normal[2]) - (point[2] * normal[1]);
	product[1] = (point[0] * normal[2]) - (point[2] * normal[0]);
	product[2] = (point[0] * normal[1]) - (point[1] * normal[0]);

	return product;
}

void Model::generate_new_triangles()
{
	std::vector<std::vector<std::vector<float>>> new_triangles;
	for (std::vector<std::vector<float>> triangle : _triangles)
	{
		float centroid_x = (triangle[0][0] + triangle[1][0] + triangle[2][0]) / 3;
		float centroid_y = (triangle[0][1] + triangle[1][1] + triangle[2][1]) / 3;
		float centroid_z = (triangle[0][2] + triangle[1][2] + triangle[2][2]) / 3;

		std::vector<float> centroid;
		centroid.push_back(centroid_x);
		centroid.push_back(centroid_y);
		centroid.push_back(centroid_z);

		new_triangles.push_back(std::vector<std::vector<float>>{triangle[0], triangle[1], centroid});
		new_triangles.push_back(std::vector<std::vector<float>>{triangle[1], triangle[2], centroid});
		new_triangles.push_back(std::vector<std::vector<float>>{triangle[2], triangle[0], centroid});
	}

	_triangles.clear();
	_triangles = new_triangles;
}
