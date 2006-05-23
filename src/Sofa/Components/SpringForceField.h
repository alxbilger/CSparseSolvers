// Author: François Faure, INRIA-UJF, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
#ifndef SOFA_COMPONENTS_SPRINGFORCEFIELD_H
#define SOFA_COMPONENTS_SPRINGFORCEFIELD_H

#include "Sofa/Core/InteractionForceField.h"
#include "Sofa/Core/MechanicalObject.h"
#include "Sofa/Abstract/VisualModel.h"
#include "Common/Vec.h"

namespace Sofa
{

namespace Components
{

using namespace Common;

template<class DataTypes>
class SpringForceField : public Core::InteractionForceField, public Abstract::VisualModel
{
public:
    typedef typename DataTypes::VecCoord VecCoord;
    typedef typename DataTypes::VecDeriv VecDeriv;
    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::Deriv Deriv;
    typedef typename Coord::value_type Real;

protected:
    Core::MechanicalObject<DataTypes>* object1;
    Core::MechanicalObject<DataTypes>* object2;

    class Spring
    {
    public:
        int     m1, m2;		// the two extremities of the spring: masses m1 and m2
        double  ks;			// spring stiffness
        double  kd;			// damping factor
        double  initpos;	// rest length of the spring

        Spring(int m1=0, int m2=0, double ks=0.0, double kd=0.0, double initpos=0.0)
            : m1(m1), m2(m2), ks(ks), kd(kd), initpos(initpos)
        {
        }
    };

    std::vector<Spring> springs;
    class Loader;
    void init(const char *filename);

    void addSpringForce(VecDeriv& f1, VecCoord& p1, VecDeriv& v1, VecDeriv& f2, VecCoord& p2, VecDeriv& v2, int i, const Spring& spring);

public:
    SpringForceField(Core::MechanicalObject<DataTypes>* object1, Core::MechanicalObject<DataTypes>* object2, const char* filename)
        : object1(object1), object2(object2)
    {
        init(filename);
    }

    SpringForceField(Core::MechanicalObject<DataTypes>* object, const char* filename)
        : object1(object), object2(object)
    {
        init(filename);
    }

    SpringForceField(Core::MechanicalObject<DataTypes>* object1, Core::MechanicalObject<DataTypes>* object2)
        : object1(object1), object2(object2)
    {
    }

    SpringForceField(Core::MechanicalObject<DataTypes>* object)
        : object1(object), object2(object)
    {
    }

    Core::MechanicalObject<DataTypes>* getObject1() { return object1; }
    Core::MechanicalObject<DataTypes>* getObject2() { return object2; }

    virtual void addForce();

    virtual void addDForce();

    // -- VisualModel interface
    void draw();
    void initTextures() { }
    void update() { }

    // -- Modifiers

    void clear(int reserve=0)
    {
        springs.clear();
        if (reserve) springs.reserve(reserve);
    }

    void addSpring(int m1, int m2, double ks, double kd, double initlen)
    {
        springs.push_back(Spring(m1,m2,ks,kd,initlen));
    }
};

} // namespace Components

} // namespace Sofa

#endif
