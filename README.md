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

