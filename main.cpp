#include "cstate.h"
#include"cstatemachine.h"

enum STATUS
{
    INIT = 0,
    BEGIN = 1,
    RUNNING = 2,
    HOLD_ON = 3,
    EXIT = 4
};

int main()
{
    CStateMachine *stateMachine = new CStateMachine();

    CState *init =  stateMachine->CreateState(INIT);
    CState *begin = stateMachine->CreateState(BEGIN);
    CState *running = stateMachine->CreateState(RUNNING);
    CState *hold_on = stateMachine->CreateState(HOLD_ON);
    CState *exit = stateMachine->CreateState(EXIT);

    stateMachine->SetInitState(INIT);

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

    running->To(hold_on)->When([](){
        return true;
    })->Enter([](){
        printf("Enter HoldOn\n");
    })->Exit([](){
        printf("Exit HoldOn\n");
    });

    hold_on->To(exit)->When([](){
        return false;
    })->Enter([](){
        printf("Enter Exite\n");
    })->Exit([](){
        printf("Exit Exite\n");
    });

    stateMachine->ChangeState(BEGIN);
    //stateMachine->ChangeState(RUNNING);
    stateMachine->ChangeState(HOLD_ON);
    stateMachine->ChangeState(EXIT);

    getchar();
    delete stateMachine;
    return 0;
}
