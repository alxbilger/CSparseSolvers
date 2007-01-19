#ifndef SOFA_COMPONENTS_LAGRANGIANMULTIPLIERCONSTRAINT_H
#define SOFA_COMPONENTS_LAGRANGIANMULTIPLIERCONSTRAINT_H

#include "Common/Vec3Types.h"
#include "Sofa/Core/Constraint.h"
#include "Sofa/Core/MechanicalObject.h"

#include <vector>

namespace Sofa
{

namespace Components
{

template<class DataTypes>
class LagrangianMultiplierConstraint : public Core::BasicConstraint
{
public:
    typedef typename DataTypes::VecCoord VecCoord;
    typedef typename DataTypes::VecDeriv VecDeriv;
    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::Deriv Deriv;
    typedef typename DataTypes::Real Real;

    class LMTypes
    {
    public:
        typedef typename DataTypes::Real Real;
        typedef Real Coord;
        typedef Real Deriv;
        typedef vector<Coord> VecCoord;
        typedef vector<Deriv> VecDeriv;

        template <class T>
        class SparseData
        {
        public:
            SparseData(unsigned int _index, T& _data): index(_index), data(_data) {};
            unsigned int index;
            T data;
        };

        typedef SparseData<Coord> SparseCoord;
        typedef SparseData<Deriv> SparseDeriv;

        typedef vector<SparseCoord> SparseVecCoord;
        typedef vector<SparseDeriv> SparseVecDeriv;

        //! All the Constraints applied to a state Vector
        typedef	vector<SparseVecDeriv> VecConst;


        static void set(Coord& c, double x, double , double )
        {
            c = (Real)x;
        }

        static void add(Coord& c, double x, double , double )
        {
            c += (Real)x;
        }
    };
    typedef typename LMTypes::VecCoord LMCoord;
    typedef typename LMTypes::VecDeriv LMDeriv;

protected:
    /// Langrange multipliers
    Core::MechanicalObject<LMTypes>* lambda;

public:

    LagrangianMultiplierConstraint()
    {
        lambda = new Core::MechanicalObject<LMTypes>;
    }

    ~LagrangianMultiplierConstraint()
    {
        delete lambda;
    }

    virtual void projectResponse() ///< project dx to constrained space
    {
    }
    virtual void projectVelocity() {} ///< project dx to constrained space (dx models a velocity)
    virtual void projectPosition() {} ///< project x to constrained space (x models a position)

    virtual Core::BasicMechanicalModel* getDOFs()
    {
        return lambda;
    }
};

} // namespace Components

} // namespace Sofa

#endif
