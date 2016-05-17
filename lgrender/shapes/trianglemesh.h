

#ifndef LGRENDER_SHAPES_TRIANGLEMESH_H
#define LGRENDER_SHAPES_TRIANGLEMESH_H

#include "lgrender/core/shape.h"
#include <map>
using std::map;
using std::vector;

template <typename T> class Texture;

// TriangleMesh Declarations
class TriangleMesh : public Shape 
{
public:
    // TriangleMesh Public Methods
    TriangleMesh(const Transform *o2w, const Transform *w2o, bool ro,
        int ntris, int nverts, const int *vptr,
        const Point *P, const Normal *N, const Vector *S,
        const float *uv, const Reference<Texture<float> > &atex);
    ~TriangleMesh();
    BoundingBox object_bound() const;
    BoundingBox world_bound() const;
    bool canIntersect() const { return false; }
    void refine(vector<Reference<Shape> > &refined) const;
    friend class Triangle;
    template <typename T> friend class VertexTexture;
protected:
    // TriangleMesh Protected Data
    int ntris, nverts;
    int *vertexIndex;
    Point *p;
    Normal *n;
    Vector *s;
    float *uvs;
    Reference<Texture<float> > alphaTexture;
};


class Triangle : public Shape 
{
public:
    Triangle(const Transform *o2w, const Transform *w2o, bool ro,
        TriangleMesh *mesh, int n);

    BoundingBox object_bound() const;
    BoundingBox world_bound() const;
    bool intersect(const Ray &ray, float *t_hit, float *ray_epsilon,
        DifferentialGeometry *dg) const;
    bool intersectP(const Ray &ray) const;
    float area() const;

    /*void getUVs(float uv[3][2]) const {
        if (mesh->uvs) {
            uv[0][0] = mesh->uvs[2 * v[0]];
            uv[0][1] = mesh->uvs[2 * v[0] + 1];
            uv[1][0] = mesh->uvs[2 * v[1]];
            uv[1][1] = mesh->uvs[2 * v[1] + 1];
            uv[2][0] = mesh->uvs[2 * v[2]];
            uv[2][1] = mesh->uvs[2 * v[2] + 1];
        }
        else {
            uv[0][0] = 0.; uv[0][1] = 0.;
            uv[1][0] = 1.; uv[1][1] = 0.;
            uv[2][0] = 1.; uv[2][1] = 1.;
        }
    }*/
    
    /*virtual void GetShadingGeometry(const Transform &obj2world,
        const DifferentialGeometry &dg,
        DifferentialGeometry *dgShading) const;
    Point Sample(float u1, float u2, Normal *Ns) const;*/
private:
    // Triangle Private Data
    Reference<TriangleMesh> mesh_;
    int *v_;
};


//TriangleMesh *CreateTriangleMeshShape(const Transform *o2w, const Transform *w2o,
//    bool reverseOrientation, const ParamSet &params,
//    map<string, Reference<Texture<float> > > *floatTextures = NULL);

#endif // LGRENDER_SHAPES_TRIANGLEMESH_H
