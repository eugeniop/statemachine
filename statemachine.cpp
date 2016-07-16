#ifndef STM
#define STM

template<class T>
class State
{
    public:
        char InputEvent;
        State<T> * NextState;
        EventActionResult (T::*Action)( char event );
        State<T> * ErrorState;
};

#define ANY        '*'
    
template<class T>
class StateMachine
{
    private:
        State<T> * init;
        State<T> * current;
        T * target;

    public:
      
        enum EventActionResult { EventFailed, EventProcessed };
    
        StateMachine()
        {}

        void Init( T * _target, State<T> * initialState )
        {
            init = current = initialState;
            target = _target;
        }

        void Reset()
        {
            current = init;
        }
    
        void ProcessEvent( char event )
        {
            for( State<T> * p = this->current; p->NextState != NULL; p++ )
            {
                if( p->InputEvent == event || p->InputEvent == ANY )
                {
                    if( p->Action != NULL )
                    {
                        if( EventFailed == (this->target->*(p->Action))( event ) )
                        {
                            if( p->ErrorState != NULL )
                            {
                                //Only if there's an errorstate defined. Otherwise, just do nothing
                                this->current = p->ErrorState;
                            }
                            return;
                        }
                    }
                    this->current = p->NextState;
                    return;
                }
            }

            //Event not found. Do nothing
            return;
        }        
};

#endif
