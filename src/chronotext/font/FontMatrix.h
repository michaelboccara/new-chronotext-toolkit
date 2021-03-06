#pragma once

#include "cinder/Matrix44.h"

namespace chronotext
{
    class FontMatrix
    {
        union
        {
            float m[16];
            
            struct
            {
                float m00, m10, m20, m30;
                float m01, m11, m21, m31;
                float m02, m12, m22, m32;
                float m03, m13, m23, m33;
            };
        };
        
    public:
        void setToIdentity();
        void load(const ci::Matrix44f &matrix);
        void load(const ci::MatrixAffine2f &matrix);

        void translate(float x, float y, float z);
        void setTranslation(float x, float y, float z);
        void scale(float x, float y, float z);
        void rotateX(float a);
        void rotateY(float a);
        void rotateZ(float a);
        void rotateXY(float sx, float sy);
        
        void transform3D(float x, float y, float* res);
        void transform3D(float x1, float y1, float x2, float y2, float* res);
        
        void transform2D(float x, float y, float* res);
        void transform2D(float x1, float y1, float x2, float y2, float* res);
    };
}

namespace chr = chronotext;
