#ifndef CSTATE_H
#define CSTATE_H
#include <functional>
#include <map>

typedef std::function<bool()> CONDITTIONFUNC;
typedef std::function<void()> IN_OUT_FUNC;

struct StatuesParam
{
    int state;
    bool isAuto = false;
    CONDITTIONFUNC conditionFunc = [&]()
    {
        return true;
    };
    IN_OUT_FUNC EnterFunc;
    IN_OUT_FUNC ExitFunc;

    void ExcuteCondition()
    {
        if(conditionFunc)
            conditionFunc();
    }

    void Enter()
    {
        if(EnterFunc)
            EnterFunc();
    }

    void Exit()
    {
        if(ExitFunc != nullptr)
            ExitFunc();
    }
};

class CState
{
public:
    CState(int state);
    ~CState();

    CState* To(CState* state);

    CState* IsAuto();

    CState* When(CONDITTIONFUNC func);

    CState* Enter(IN_OUT_FUNC func);

    CState* Exit(IN_OUT_FUNC func);

    int GetState() {return m_state;}

    StatuesParam* GetStatusParam(int state);

    StatuesParam* GetAutoStatusParam();

private:
    int m_state;
    std::map<int, StatuesParam*> m_statusParams;
    StatuesParam *m_param; //当前设置转换状态的参数
};

#endif // CSTATE_H
