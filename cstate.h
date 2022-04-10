/*********
* filename: cstate.h
* author: yaya
* date: 2022.4.10
**********/
#ifndef CSTATE_H
#define CSTATE_H
#include <functional>
#include <map>

typedef std::function<bool()> CONDITTIONFUNC;
typedef std::function<void()> IN_OUT_FUNC;

/********
* className: StatuesParam
* description： 状态转换条件结构体
*/
struct StatuesParam
{
    int state;              //状态
    bool isAuto = false;    //是否自动转换
    CONDITTIONFUNC conditionFunc = [&]() //转换条件
    {
        return true;
    };
    IN_OUT_FUNC EnterFunc;  //进入该状态时执行的回调
    IN_OUT_FUNC ExitFunc;   //离开该状态时执行的回调
    //执行条件回调
    void ExcuteCondition()
    {
        if(conditionFunc)
            conditionFunc();
    }
    //执行进入状态回调
    void Enter()
    {
        if(EnterFunc)
            EnterFunc();
    }
    //执行退出状态回调
    void Exit()
    {
        if(ExitFunc != nullptr)
            ExitFunc();
    }
};

/********
* className: CState
* description： 状态类
*/
class CState
{
public:
    CState(int state);
    ~CState();

    /*
     * @description：该状态转换至下一个状态
     * @param: state 可转换状态
     * @return：this指针
    */
    CState* To(CState* state);

    /*
     * @description：是否自动转换
     * @return：this指针
    */
    CState* IsAuto();

    /*
     * @description：设置转换条件
     * @param: func 转换条件函数
     * @return：this指针
    */
    CState* When(CONDITTIONFUNC func);

    /*
     * @description：设置进入下一状态的回调函数
     * @param: func 进入函数
     * @return：this指针
    */
    CState* Enter(IN_OUT_FUNC func);

    /*
     * @description：设置离开下一状态的回调函数
     * @param: func 离开函数
     * @return：this指针
    */
    CState* Exit(IN_OUT_FUNC func);

    /*
     * @description：获取对应的状态枚举值
     * @return：状态枚举值
    */
    int GetState() {return m_state;}

    /*
     * @description：获取该状态转换至目标状态的转换结构体
     * @param: state 目标状态
     * @return：转换内容
    */
    StatuesParam* GetStatusParam(int state);

    /*
     * @description：获取该状态的下一个自动状态结构体
     * @return：转换内容，没有自动转换时为nullptr
    */
    StatuesParam* GetAutoStatusParam();

private:
    int m_state; //状态枚举
    std::map<int, StatuesParam*> m_statusParams; //该状态可转换的目标状态及条件结构体
    StatuesParam *m_param; //当前设置转换状态的参数
};

#endif // CSTATE_H
