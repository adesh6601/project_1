#pragma once
#include <set>
#include <vector>

class Model
{
private:
    std::set<std::vector<float>> _points;
    float radius = 0.8660254037844386;
    std::vector<float> center{0.5, 0.5, 0.5};

    std::vector<std::vector<float>> _normals;
    std::vector<std::vector<std::vector<float>>> _triangles;
    

public:
    Model();

    ~Model();

    void read();

    void write();

    std::vector<float> cross(std::vector<float> point, std::vector<float> normal);

    void generate_new_triangles();
};
