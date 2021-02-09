#include "sphere.h"
#include <vector>
#include <cmath>

#undef M_PI

namespace Nome::Scene
{

DEFINE_META_OBJECT(CSphere)
{
    BindPositionalArgument(&CSphere::Segments, 1, 0);
    BindPositionalArgument(&CSphere::Radius, 1, 1);
    BindPositionalArgument(&CSphere::Density, 1, 2);
    BindPositionalArgument(&CSphere::Degrees, 1, 3);
    BindPositionalArgument(&CSphere::CrossDegrees, 1, 4);
}

void CSphere::addCircle(int n, float radius, float zTheta, int vertexSetName, int maxPoints) //float threshold
{
    int currPoints = 0;
    for (int i = 0; i < (n + 1); i++)
    {
        if (currPoints >= maxPoints + 1)
            break;
        currPoints++;
        float theta = (float)i / n * 2.f * (float)tc::M_PI;
        float x = radius * cosf(zTheta) * cosf(theta);
        float y = radius * cosf(zTheta) * sinf(theta);
        float z = radius * sinf(zTheta);//radius - ((zTheta/(float)tc::M_PI) * radius * 2);

        AddVertex("v" + std::to_string(vertexSetName) + "_" + std::to_string(i),
                  { x, y, z } ); // creates vertex called "vsi" ex. "v0_1" -> semicircle 0 vertex 1
        //radius * cosf(zTheta) * cosf(theta), radius * cosf(zTheta) * sinf(theta), radius * sinf(zTheta)
    }
}

void CSphere::UpdateEntity()
{
    if (!IsDirty())
        return;

    Super::UpdateEntity();

    // load in arguments to sphere generator
    int n = (int)Segments.GetValue(6.0f);
    float radius = Radius.GetValue(1.0f);
    int density = (int)Density.GetValue(24.0f);
    float degrees = Degrees.GetValue(360.0f);
    float crossDegrees = CrossDegrees.GetValue(360.0f);

    // we can't have sphere with degrees > 360
    if (degrees > 360)
        degrees = 360;
    if (crossDegrees > 360)
        crossDegrees = 360;

    // build sphere vertices from circles
    float maxDegrees = degrees/360.0f;
    float maxCrossDegrees = crossDegrees/360.0f;
    float maxPoints = maxCrossDegrees * n;
//    float threshold = 90.0f/180.0f * (float)n;
    for (int i = 0; i < density + 1; i++)
    {
        float zTheta = ((float)i / density * maxDegrees * (float)tc::M_PI) - (float)tc::M_PI/2;
        addCircle(n, radius, zTheta, i, (int)maxPoints); //threshold
    }

     //add faces
    if (crossDegrees == 360.0f)
    {
        for (int i = 0; i < density; i++)
        {
            for (int j = 0; j < maxPoints; j++)
            {
                std::vector<std::string> upperFace;

                if (j + 1 < maxPoints + 1)
                    upperFace.push_back("v" + std::to_string(i) + "_" + std::to_string(j + 1));
                upperFace.push_back("v" + std::to_string(i) + "_" + std::to_string(j));
                upperFace.push_back("v" + std::to_string(i + 1) + "_" + std::to_string(j));
                if (j + 1 < maxPoints + 1)
                    upperFace.push_back("v" + std::to_string(i + 1) + "_" + std::to_string(j + 1));
                AddFace("f1_" + std::to_string(i) + "_" + std::to_string(j), upperFace);
            }
        }
    }
    else
    {
        for (int i = 0; i < density; i++)
        {
            for (int j = 0; j < maxPoints; j++)
            {
                std::vector<std::string> upperFace;

                if (j + 1 < maxPoints)
                    upperFace.push_back("v" + std::to_string(i) + "_" + std::to_string(j + 1));
                upperFace.push_back("v" + std::to_string(i) + "_" + std::to_string(j));
                upperFace.push_back("v" + std::to_string(i + 1) + "_" + std::to_string(j));
                if (j + 1 < maxPoints)
                    upperFace.push_back("v" + std::to_string(i + 1) + "_" + std::to_string(j + 1));
                AddFace("f1_" + std::to_string(i) + "_" + std::to_string(j), upperFace);
            }
        }
    }
}

}
