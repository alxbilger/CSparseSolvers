#ifndef SOFA_COMPONENTS_COMMON_FNDISPATCHER_INL
#define SOFA_COMPONENTS_COMMON_FNDISPATCHER_INL

#include "FnDispatcher.h"
#include "Factory.h" // for gettypename()
#include <iostream>

namespace Sofa
{

namespace Components
{

namespace Common
{

template <class BaseClass, typename ResulT>
BasicDispatcher<BaseClass, ResulT>::~BasicDispatcher()
{
}

template <class BaseClass, typename ResulT>
ResulT BasicDispatcher<BaseClass, ResulT>::defaultFn(BaseClass& arg1, BaseClass& arg2)
{
    // commented by Sylvere F.
    // TODO : search where are the errors for gettypename
    // error : operator << not found for right value type std::string
    //          << gettypename(typeid(arg1)) << ", "
    //          << gettypename(typeid(arg2)) << ")\n";
    return ResulT();
}

template <class BaseClass, typename ResulT>
ResulT BasicDispatcher<BaseClass, ResulT>::go(BaseClass &arg1,BaseClass &arg2)
{
    typename MapType::iterator itt = this->callBackMap.find(KeyType(TypeInfo(typeid(arg1)),TypeInfo(typeid(arg2))));
    if (itt==callBackMap.end())
        return defaultFn(arg1,arg2);
    else
        return (itt->second)(arg1,arg2);
}

template <class BaseClass, typename ResulT>
FnDispatcher<BaseClass, ResulT>* FnDispatcher<BaseClass, ResulT>::getInstance()
{
    static FnDispatcher<BaseClass, ResulT> instance;
    return &instance;
}

} // namespace Common

} // namespace Components

} // namepsace Sofa

#endif
