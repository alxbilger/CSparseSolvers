#ifndef _EDGEPRESSUREFORCEFIELD_H_
#define _EDGEPRESSUREFORCEFIELD_H_


#include "Sofa/Core/ForceField.h"
#include "Sofa/Core/MechanicalObject.h"
#include "Sofa/Abstract/VisualModel.h"
#include "Sofa/Components/MeshTopology.h"

#include "Common/Vec.h"
#include "Common/Mat.h"


namespace Sofa
{


namespace Components
{


using namespace Common;


template<class DataTypes>
class EdgePressureForceField : public Core::BasicForceField, public Abstract::VisualModel
{
public:
    typedef typename DataTypes::VecCoord VecCoord;
    typedef typename DataTypes::VecDeriv VecDeriv;
    typedef typename DataTypes::Coord    Coord   ;
    typedef typename DataTypes::Deriv    Deriv   ;
    typedef typename Coord::value_type   Real    ;

    typedef MeshTopology::index_type Index;
    typedef MeshTopology::Triangle Element;
    typedef MeshTopology::SeqTriangles VecElement;


protected:

    class EdgePressureInformation
    {
    public:
        Index index[2];
        Real length;
        Deriv force;

        EdgePressureInformation()
        {
        }
        EdgePressureInformation(const EdgePressureInformation &e)
            : length(e.length),force(e.force)
        {
            index[0]=e.index[0];
            index[1]=e.index[1];
        }
    };

    std::vector<EdgePressureInformation> edgeInfo;

    Core::MechanicalObject<DataTypes>* _object;

    unsigned int nbEdges;  // number of edge pressure forces

    MeshTopology* _mesh;
    const VecElement *_indexedElements;
    VecCoord _initialPoints;										///< the intial positions of the points

    Deriv pressure;
public:

    EdgePressureForceField(Core::MechanicalObject<DataTypes>* object)
        : _object(object)
        , nbEdges(0)
        , _mesh(NULL)
    {
    }

    virtual ~EdgePressureForceField();


    virtual void init();
    virtual void addForce();
    virtual void addDForce() {}


    // -- VisualModel interface
    void draw();
    void initTextures() { };
    void update() { };
    void addEdgePressure(Index ind1,Index ind2);

    void setPressure(Deriv _pressure) { this->pressure = _pressure; updateEdgeInformation(); }

    Core::MechanicalObject<DataTypes>* getObject() { return _object; }

protected :
    void updateEdgeInformation();
    void initEdgeInformation();

};


} // namespace Components


} // namespace Sofa



#endif /* _EDGEPRESSUREFORCEFIELD_H_ */
