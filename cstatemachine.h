#ifndef CSTATEMACHINE_H
#define CSTATEMACHINE_H

#include <map>
#include "cstate.h"

class CState;
class CStateMachine
{
public:
    CStateMachine();
    ~CStateMachine();

    CState* CreateState(int state);

    bool SetInitState(int state);

    bool ChangeState(int state);

    void AutoChange();

private:
    CState *m_curState;
    std::map<int, CState*> m_states;
    StatuesParam* m_curStatusParam;
};

#endif // CSTATEMACHINE_H
