# Statemachine
A very simple state machine I often use for my [MBED](http://mbed.org) projects.

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
  
  void Start(){
    while(1){
      char event = getchar();
      this->HandleEvent(event);
    }
  }
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

Of course you can have multiple co-existing state machines. I often use one for the main app that handles main devices: keyboard, display, etc.). The I use another machine for serial communications protocols.

The man `main` typcially looks like this:

```cpp
int main(void)
{
    App app();
    
    app.Init();
    
    app.Start();
}
```
