#include <iostream>
#include "E:\stl_to_gnu\header\model.h"
using namespace std;

int main()
{
	Model model;
	model.read();
	model.generate_new_triangles();
	model.write();

	cout << "Successfull." << endl;
}
