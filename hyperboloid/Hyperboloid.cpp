#include "Hyperboloid.h"
#include <vector>
#include <cmath>

#undef M_PI

namespace Nome::Scene
{

DEFINE_META_OBJECT(CHyperboloid)
{
    BindPositionalArgument(&CHyperboloid::A, 1, 0);
    BindPositionalArgument(&CHyperboloid::C, 1, 1);
    BindPositionalArgument(&CHyperboloid::UMax, 1, 2);
    BindPositionalArgument(&CHyperboloid::UIncrement, 1, 3);
    BindPositionalArgument(&CHyperboloid::VIncrement, 1, 4);
    BindPositionalArgument(&CHyperboloid::Sheet, 1, 5); // 0->one sheet,  1->paraboloid,  2->two sheets
//    BindPositionalArgument(&CHyperboloid::mathExpr, 1, 6);
}

void CHyperboloid::UpdateEntity()
{
    if (!IsDirty())
        return;

    Super::UpdateEntity();

    // code references:
    // One Sheet -> https://mathworld.wolfram.com/One-SheetedHyperboloid.html
    // Two Sheet -> https://mathworld.wolfram.com/Two-SheetedHyperboloid.html

    float a = (float)A.GetValue(1.0f);
    float c = (float)C.GetValue(1.0f);
    float uMax = (float)UMax.GetValue(10.0f);
    float uIncrement = uMax / (float)UIncrement.GetValue(20.0f);
    float vIncrement = (float)tc::M_PI / (float)VIncrement.GetValue(20.0f);
    int sheet = (int)Sheet.GetValue(0);

//    std::string mathExpression = mathExpr.GetValue("");
//    std::cout << "\n\n" << mathExpression << " finished\n";

    // check valid sheet size
    if (sheet < 0 || sheet > 2) // sheet must be 0, 1, or 2
        sheet = 0;

    int uCounter = 0; // used to name vertices, and then set as 'max' num of cross sections when adding faces
    int vCounter = 0; // used to name vertices, and then set as 'max' num of vertices on a cross section when adding faces
    // add vertices
    if (sheet > 0) { // shape is either paraboloid or two-sheet hyperboloid
        // add positive sheet vertices
        uCounter = 0;
        float x;
        float y;
        float z;
        float v;
        for (float u = 0; u < uMax + (uIncrement/5); u += uIncrement) {
            vCounter = 0;
            for (v = 0; v < 2*(float)tc::M_PI + (vIncrement/5); v += vIncrement) {
                x = a * sinh(u) * cosf(v);
                y = a * sinh(u) * sinf(v);
                z = c * cosh(u);

                AddVertex("v_" + std::to_string(uCounter) + "_" + std::to_string(vCounter) + "_pos", // name ex. "v_0_5_pos"
                          { x, y, z } );
                vCounter++;
            }
            uCounter++;
        }

        // add negative sheet vertices
        if (sheet == 2) {
            uCounter = 0;
            float x;
            float y;
            float z;
            float v;
            for (float u = 0; u > -1.0f*(uMax + (uIncrement/5)); u -= uIncrement) {
                vCounter = 0;
                for (v = 0; v < 2*(float)tc::M_PI + (vIncrement/5); v += vIncrement) {
                    x = a * sinh(u) * cosf(v);
                    y = a * sinh(u) * sinf(v);
                    z = c * cosh(u);

                    AddVertex("v_" + std::to_string(uCounter) + "_" + std::to_string(vCounter) + "_neg", // name ex. "v_0_5_neg"
                              { -x, -y, -z } );
                    vCounter++;
                }
                uCounter++;
            }
        }
    } else { // case when sheet == 0
        // add one-sheet hyperboloid vertices
        uCounter = 0;
        float x;
        float y;
        float z;
        float v;
        for (float u = -1.0f*(uMax + (uIncrement/5)); u < (uMax + (uIncrement/5)); u += uIncrement) {
            vCounter = 0;
            for (v = 0; v < 2*(float)tc::M_PI + (vIncrement/5); v += vIncrement) {
                x = a * sqrt(1 + pow(u, 2)) * cosf(v);
                y = a * sqrt(1 + pow(u, 2)) * sinf(v);
                z = c * u;

                AddVertex("v_" + std::to_string(uCounter) + "_" + std::to_string(vCounter), // name ex. "v_0_5"
                          { x, y, z } );
                vCounter++;
            }
            uCounter++;
        }
    }



    // add faces
    int faceCounter = 0;
    if (sheet > 0) { // shape is either paraboloid or two-sheet hyperboloid
        // add positive sheet faces
        for (int u = 0; u + 1 < uCounter; u++) {
            for (int v = 0; v < vCounter - 1; v++) {
                std::vector<std::string> face;

                face.push_back("v_" + std::to_string(u) + "_" + std::to_string(v) + "_pos");
                face.push_back("v_" + std::to_string(u+1) + "_" + std::to_string(v) + "_pos");
                face.push_back("v_" + std::to_string(u+1) + "_" + std::to_string(v+1) + "_pos");
                face.push_back("v_" + std::to_string(u) + "_" + std::to_string(v+1) + "_pos");
                AddFace("f1_" + std::to_string(faceCounter++), face);
            }
        }
        // add negative sheet faces
        if (sheet == 2) {
            for (int u = 0; u + 1 < uCounter; u++) {
                for (int v = 0; v < vCounter - 1; v++) {
                    std::vector<std::string> face;

                    face.push_back("v_" + std::to_string(u) + "_" + std::to_string(v) + "_neg");
                    face.push_back("v_" + std::to_string(u+1) + "_" + std::to_string(v) + "_neg");
                    face.push_back("v_" + std::to_string(u+1) + "_" + std::to_string(v+1) + "_neg");
                    face.push_back("v_" + std::to_string(u) + "_" + std::to_string(v+1) + "_neg");
                    AddFace("f1_" + std::to_string(faceCounter++), face);
                }
            }
        }
    } else { // case when sheet == 0
        // add one-sheet hyperboloid faces
        for (int u = 0; u + 1 < uCounter; u++) {
            for (int v = 0; v < vCounter - 1; v++) {
                std::vector<std::string> face;

                face.push_back("v_" + std::to_string(u) + "_" + std::to_string(v));
                face.push_back("v_" + std::to_string(u+1) + "_" + std::to_string(v));
                face.push_back("v_" + std::to_string(u+1) + "_" + std::to_string(v+1));
                face.push_back("v_" + std::to_string(u) + "_" + std::to_string(v+1));
                AddFace("f1_" + std::to_string(faceCounter++), face);
            }
        }
    }
}

}
