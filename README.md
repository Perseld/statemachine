# statemachine
c++状态机，状态之间的跳转管理
## CState
状态类，记录了从该状态跳转到其它状态的条件和信息。
## CStateMachine
状态机类，实现状态与状态之间的跳转逻辑
## 使用
```
//创建状态机
CStateMachine *stateMachine = new CStateMachine();
```

```
\\创建状态
CState *init =  stateMachine->CreateState(INIT);
```

```
\\设置初始状态
stateMachine->SetInitState(INIT);
```

```
\\设置状态转换的条件等
init->To(begin)->When([](){
        return true;
    })->Enter([](){
        printf("Enter Begin\n");
    })->Exit([](){
        printf("Exit Begin\n");
    });

    begin->To(running)->IsAuto()->Enter([](){
        printf("Enter Running\n");
    })->Exit([](){
        printf("Exit Running\n");
    });
```

```
\\切换状态
stateMachine->ChangeState(BEGIN);
```
