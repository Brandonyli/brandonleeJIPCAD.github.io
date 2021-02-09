#pragma once
#include "Mesh.h"

namespace Nome::Scene
{

class CSphere : public CMesh
{
    DEFINE_INPUT(float, Segments) { MarkDirty(); }
    DEFINE_INPUT(float, Radius) { MarkDirty(); }
    DEFINE_INPUT(float, Density) { MarkDirty(); }
    DEFINE_INPUT(float, Degrees) { MarkDirty(); }
    DEFINE_INPUT(float, CrossDegrees) { MarkDirty(); }

public:
    DECLARE_META_CLASS(CSphere, CMesh);
    CSphere() = default;
    CSphere(const std::string& name)
        : CMesh(std::move(name))
    {
    }

    void UpdateEntity() override;

private:
    void addCircle(int n, float radius, float zTheta, int vertexSetName, int maxPoints); //float threshold
};

}
