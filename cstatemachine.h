/*********
* filename: cstatemachine.h
* author: yaya
* date: 2022.4.10
**********/
#ifndef CSTATEMACHINE_H
#define CSTATEMACHINE_H

#include <map>
#include "cstate.h"

class CState;

/********
* className: CStateMachine
* description： 状态机类
*/
class CStateMachine
{
public:
    CStateMachine();
    ~CStateMachine();

    /*
     * @description：创建一个状态机管理的状态
     * @param: state 状态
     * @return：状态对象
    */
    CState* CreateState(int state);

    /*
     * @description：设置初始状态
     * @param: state 状态
     * @return：是否成功
    */
    bool SetInitState(int state);

    /*
     * @description：切换状态
     * @param: state 状态
     * @return：是否成功
    */
    bool ChangeState(int state);

private:
    /*
     * @description：自动转换
    */
    void AutoChange();

private:
    CState *m_curState;
    std::map<int, CState*> m_states;
    StatuesParam* m_curStatusParam;
};

#endif // CSTATEMACHINE_H
