#ifndef SOFA_COMPONENTS_VOXELGRID_H
#define SOFA_COMPONENTS_VOXELGRID_H

#include "Collision/BroadPhaseDetection.h"
#include "Collision/NarrowPhaseDetection.h"
#include "Sofa/Abstract/CollisionElement.h"
#include "Sofa/Abstract/VisualModel.h"
#include "Common/Vec.h"

#include <set>

namespace Sofa
{

namespace Components
{

using namespace Common;

// inherit of VisualModel for debugging, then we can see the voxel grid
class BruteForceDetection : public Collision::BroadPhaseDetection, public Collision::NarrowPhaseDetection, public Abstract::VisualModel
{
private:
    std::string _name;
    std::vector<Abstract::CollisionModel*> collisionModels;

public:
    BruteForceDetection(const std::string& name)
    {
        _name = name;
    }

    ~BruteForceDetection () {}

    const char* getName() { return _name.c_str(); }

    void addCollisionModel (Abstract::CollisionModel *cm);
    void addCollisionPair (const std::pair<Abstract::CollisionModel*, Abstract::CollisionModel*>& cmPair);

    virtual void clearBroadPhase()
    {
        Collision::BroadPhaseDetection::clearBroadPhase();
        collisionModels.clear();
    }

    /* for debugging, VisualModel */
    void draw();
    void initTextures() { }
    void update() { }
};

} // namespace Components

} // namespace Sofa

#endif
