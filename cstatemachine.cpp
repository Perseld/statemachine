#include "cstatemachine.h"

CStateMachine::CStateMachine()
    : m_curState(nullptr)
    , m_curStatusParam(nullptr)
{

}

CStateMachine::~CStateMachine()
{
    auto it = m_states.begin();
    for(; it != m_states.end(); ++it)
    {
        if(it->second)
            delete it->second;
    }
    m_states.clear();
    if (m_curStatusParam)
        delete m_curStatusParam;

}

CState *CStateMachine::CreateState(int state)
{
    auto it = m_states.find(state);
    if(it != m_states.end())
        return it->second;
    CState *newState = new CState(state);
    m_states[state] = newState;
    return newState;
}

bool CStateMachine::SetInitState(int state)
{
    auto it = m_states.find(state);
    if(it == m_states.end())
    {
        m_curState = nullptr;
        return false;
    }
    m_curState = it->second;
    return true;
}

bool CStateMachine::ChangeState(int state)
{
    if(m_curState == nullptr)
        return SetInitState(state);

    auto it = m_states.find(state);
    if(it == m_states.end())
        return false;

    StatuesParam* param = m_curState->GetStatusParam(state);
    //当前状态是否可以转换到下一个状态
    if(param == nullptr)
        return false;
    //如果可以
    //转换条件是否为真
    if(!param->conditionFunc || !param->conditionFunc())
        return false;
    //如果为真
    //执行当前状态的退出方法
    if(m_curStatusParam)
        m_curStatusParam->Exit();
    m_curStatusParam = param;
    m_curState = it->second;
    //执行下一个状态的进入方法
    m_curStatusParam->Enter();
    //执行转换后状态的自动转换
    AutoChange();
    return true;
}

void CStateMachine::AutoChange()
{
    StatuesParam* tempParam = m_curState->GetAutoStatusParam();
    while(tempParam)
    {
        if(m_curStatusParam)
            m_curStatusParam->Exit();
        m_curStatusParam = tempParam;
        m_curStatusParam->Enter();
        m_curState = m_states[m_curStatusParam->state];
        tempParam = m_curState->GetAutoStatusParam();
    }
}
