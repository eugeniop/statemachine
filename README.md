# Statemachine
A very simple state machine I use for my [MBED](http://mbed.org) projects.

## Sample use

The "App" class:

```cpp
class App{

private:
  StateMachine<App> appStateMachine;

  void HandleOne(char e){
    return StateMachine::EventProcessed;
  };
  
  void HandleTwo(char e){
    return StateMachine::EventProcessed;
  };

public:
  void HandleEvent(char e){
    appStateMachine.processEvent(e);
  };

  void Init(){
    appStateMachine.Init(this, Main);
  };
};
```

The `Init` method simply wires up the table (below). The you just send events to `HandleEvents` (that internally calls the state machine). The table below describes the states and transitions:


```cpp
STATE Main[] =
{
    //EVENT,    NEXT,     ACTION,                     ERRORSTATE (where to land if there's an error)
    { '1',      One,      &App::HandleOne,            NULL }, 
    { '2',      Two,      &App::HandleTwo,            NULL },
    { 0, NULL, NULL, NULL}, //End of table
};

STATE One[] = 
{
    { 'B',      Main,     NULL,      NULL },
    { 0, NULL, NULL, NULL },
};
```



