#pragma once
#include "Mesh.h"
#include "../Parsing/exprtk.hpp"
#include <vector>
#include <string>

namespace Nome::Scene
{

typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double> expression_t;
typedef exprtk::parser<double> parser_t;

typedef struct{
    double x, y, z;
}Xyz;

typedef struct{
    int p[3];
}Triangle;

typedef struct{
    Xyz p[8];
    double val[8];
}Gridcell;


class CGenImplicitSurf : public CMesh

{
    DEFINE_INPUT(float, x_start) { MarkDirty(); }
    DEFINE_INPUT(float, x_end) { MarkDirty(); }
    DEFINE_INPUT(float, y_start) { MarkDirty(); }
    DEFINE_INPUT(float, y_end) { MarkDirty(); }
    DEFINE_INPUT(float, z_start) { MarkDirty(); }
    DEFINE_INPUT(float, z_end) { MarkDirty(); }
    DEFINE_INPUT(float, num_segs) { MarkDirty(); }

public:
    DECLARE_META_CLASS(CGenImplicitSurf, CMesh);
    CGenImplicitSurf() = default;
    CGenImplicitSurf(const std::string& name)
        : CMesh(std::move(name))
    {
    }

    void UpdateEntity() override;


private:
    double functionXyz(double x, double y, double z);
    void runMarchingCubes(int gridSize, double xMin, double yMin, double zMin, double xMax, double yMax, double zMax);
    void addVerticesAndFaces(std::vector <Xyz> vertex, std::vector <Triangle> Triangles, int nv, int nt);

    expression_t expression;
    symbol_table_t symbol_table;
};

}
