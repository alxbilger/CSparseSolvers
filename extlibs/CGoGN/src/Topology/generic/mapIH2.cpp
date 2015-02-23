#include "Topology/generic/mapImpl/mapIH2.hpp"
#include "Topology/map/map2.h"

namespace CGoGN
{

void MapIH2::clear(bool removeAttrib)
{
    GenericMap::clear(removeAttrib) ;
    if (removeAttrib)
    {
        m_permutation.clear();
        m_permutation_inv.clear();
        m_involution.clear();
    }
}

void MapIH2::addInvolution()
{
    std::stringstream sstm;
    sstm << "involution_" << m_involution.size();
    m_involution.push_back(addRelation(sstm.str()));
}

void MapIH2::addPermutation()
{
    std::stringstream sstm;
    sstm << "permutation_" << m_permutation.size();
    m_permutation.push_back(addRelation(sstm.str()));
    std::stringstream sstm2;
    sstm2 << "permutation_inv_" << m_permutation_inv.size();
    m_permutation_inv.push_back(addRelation(sstm2.str()));
}

void MapIH2::removeLastInvolutionPtr()
{
    m_involution.pop_back();
}

void MapIH2::compactTopo()
{
    std::vector<unsigned int> oldnew;
    m_attribs[DART].compact(oldnew);

    for (unsigned int i = m_attribs[DART].begin(); i != m_attribs[DART].end(); m_attribs[DART].next(i))
    {
        for (unsigned int j = 0; j < m_permutation.size(); ++j)
        {
            Dart d = (*m_permutation[j])[i];
            if (d.index != oldnew[d.index])
                (*m_permutation[j])[i] = Dart(oldnew[d.index]);
        }
        for (unsigned int j = 0; j < m_permutation_inv.size(); ++j)
        {
            Dart d = (*m_permutation_inv[j])[i];
            if (d.index != oldnew[d.index])
                (*m_permutation_inv[j])[i] = Dart(oldnew[d.index]);
        }
        for (unsigned int j = 0; j < m_involution.size(); ++j)
        {
            Dart d = (*m_involution[j])[i];
            if (d.index != oldnew[d.index])
                (*m_involution[j])[i] = Dart(oldnew[d.index]);
        }
    }
}

bool MapIH2::saveMapBin(const std::string &filename) const
{
    // TODO
    return false;
}

bool MapIH2::loadMapBin(const std::string &filename)
{
    // TODO
    return false;
}

bool MapIH2::copyFrom(const GenericMap &map)
{
    // TODO
    return false;
}

void MapIH2::restore_topo_shortcuts()
{

}



Dart MapIH2::newDart()
{
    const Dart d = GenericMap::newDart() ;

    for (unsigned int i = 0; i < m_permutation.size(); ++i)
        (*m_permutation[i])[d.index] = d ;
    for (unsigned int i = 0; i < m_permutation_inv.size(); ++i)
        (*m_permutation_inv[i])[d.index] = d ;
    for (unsigned int i = 0; i < m_involution.size(); ++i)
        (*m_involution[i])[d.index] = d ;

    (*m_dartLevel)[d.index] = m_curLevel ;
    if(m_curLevel > m_maxLevel)			// update max level
        m_maxLevel = m_curLevel ;		// if needed
    return d ;
}





} // namespace CGoGN


