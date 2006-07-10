#ifndef SOFA_COMPONENTS_SPHEREMODEL_H
#define SOFA_COMPONENTS_SPHEREMODEL_H

#include "Sofa/Abstract/CollisionModel.h"
#include "Sofa/Abstract/VisualModel.h"
#include "Sofa/Core/MechanicalObject.h"
#include "Common/Vec3Types.h"
#include "Sphere.h"

namespace Sofa
{

namespace Components
{

using namespace Common;

class SphereModel : public Core::MechanicalObject<Vec3Types>, public Abstract::CollisionModel, public Abstract::VisualModel
{
protected:
    std::vector<Abstract::CollisionElement*> elems;
    Abstract::CollisionModel* previous;
    Abstract::CollisionModel* next;

    double defaultRadius;

    class Loader;

    bool static_;
public:
    typedef Vec3Types DataTypes;
    typedef Sphere Element;

    SphereModel(double radius = 1.0);

    virtual void resize(int size);

    int addSphere(const Vector3& pos, double radius);
    void setSphere(int index, const Vector3& pos, double radius);

    bool load(const char* filename);

    bool isStatic() { return static_; }
    void setStatic(bool val=true) { static_ = val; }

    // -- CollisionModel interface

    void computeBoundingBox();

    std::vector<Abstract::CollisionElement*> & getCollisionElements()
    { return elems; }

    Abstract::CollisionModel* getNext()
    { return next; }

    Abstract::CollisionModel* getPrevious()
    { return previous; }

    void setNext(Abstract::CollisionModel* n)
    { next = n; }

    void setPrevious(Abstract::CollisionModel* p)
    { previous = p; }

    //void applyTranslation(double dx, double dy, double dz);

    //void applyScale(double s);

    // -- VisualModel interface

    void draw();

    void initTextures() { }

    void update() { }
};

} // namespace Components

} // namespace Sofa

#endif
