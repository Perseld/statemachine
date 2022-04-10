#include "cstate.h"

CState::CState(int state)
    : m_state(state)
{

}

CState::~CState()
{
    auto it = m_statusParams.begin();
    for(; it != m_statusParams.end(); ++it)
    {
        if(it->second)
            delete it->second;
    }
    m_statusParams.clear();
}

CState *CState::To(CState* state)
{
    if(state == nullptr || this == state)
        return this;
    auto it = m_statusParams.find(state->GetState());
    if(it != m_statusParams.end())
        return this;
    m_param = new StatuesParam;
    m_param->state = state->GetState();
    m_param->isAuto = false;
    m_statusParams[state->GetState()] = m_param;
    return this;
}

CState *CState::IsAuto()
{
    m_param->isAuto = true;
    return this;
}

CState *CState::When(CONDITTIONFUNC func)
{
    m_param->conditionFunc = func;
    return this;
}

CState *CState::Enter(IN_OUT_FUNC func)
{
    m_param->EnterFunc = func;
    return this;
}

CState *CState::Exit(IN_OUT_FUNC func)
{
    m_param->ExitFunc = func;
    return this;
}

StatuesParam *CState::GetStatusParam(int state)
{
    auto it = m_statusParams.find(state);
    if(it == m_statusParams.end())
        return nullptr;
    return it->second;
}

StatuesParam *CState::GetAutoStatusParam()
{
    for(auto it : m_statusParams)
    {
        if(it.second->isAuto)
            return it.second;
    }
    return nullptr;
}




