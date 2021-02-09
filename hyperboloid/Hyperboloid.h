#pragma once
#include "Mesh.h"

namespace Nome::Scene
{

class CHyperboloid : public CMesh
{
    DEFINE_INPUT(float, A) { MarkDirty(); }
    DEFINE_INPUT(float, C) { MarkDirty(); }
    DEFINE_INPUT(float, UMax) { MarkDirty(); }
    DEFINE_INPUT(float, UIncrement) { MarkDirty(); }
    DEFINE_INPUT(float, VIncrement) { MarkDirty(); }
    DEFINE_INPUT(float, Sheet) { MarkDirty(); }
//    DEFINE_INPUT(std::string, mathExpr) { MarkDirty(); }

public:
    DECLARE_META_CLASS(CHyperboloid, CMesh);
    CHyperboloid() = default;
    CHyperboloid(const std::string& name)
        : CMesh(std::move(name))
    {
    }

    void UpdateEntity() override;

private:
    // ...
};

}
