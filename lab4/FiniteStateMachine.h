#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include <unordered_map>
#include <functional>

/*******************************************************************************************

	File: Finite State Machine
	Author: Ben Brenkman
	version: 1.0

	Purpose: This is a gernal purpose finite state machine, it is a template class
			 that takes in an input type, an output type and the class that the instance
			 of the fsm is in. This is used to defined the member function pointers
			 in the fsm and the State class.

*******************************************************************************************/

// T - input
// V - output
// A - class that the fsm in located in
template<typename T, typename V, class A>
class FiniteStateMachine {
public:
    // T - input
    // V - output
    // A - class that the fsm in located in
    template<typename Ta, typename Va, class Aa>
    class State {
    private:
        // This funtion is a pointer to the function that defines the logic of the State
        void (Aa::*proccessFunc)(FiniteStateMachine<Ta, Va, Aa> *fsm,
                                 Ta t); // Function that is used to determmine the next state
        // This is a function with in the fsm, it is a callback funtion currently not used
        void (FiniteStateMachine<Ta, Va, Aa>::*fsmCallback)(Va v); // trigger to the FSM, not used
        // instance of the finite state machine
        FiniteStateMachine<Ta, Va, Aa> *fsm; // Pointer to the FSM
        // Pointer to the parent class
        Aa *a;
        // This determines wether the State is an accepting State or not
        bool isStateAccepting;
    public:
        State(FiniteStateMachine<Ta, Va, Aa> *fsm, void(Aa::*proccFunc)(FiniteStateMachine<Ta, Va, Aa> *fsm, Ta t),
              Aa *a, bool isStateAccepting) {
            proccessFunc = proccFunc;
            this->fsm = fsm;
            this->isStateAccepting = isStateAccepting;
            this->a = a;
        }

        ~State() {}

        // Triggers the states logic funtion defined by the user
        void proccesEvent(Ta t, Aa *a) {
            (a->*proccessFunc)(fsm, t);
        }

        void setFSMCallback(FiniteStateMachine<Ta, Va, Aa> *fsm) {
            this->fsm = fsm;
        }

        // Triggers the event that sends the output, whatever it my be
        void triggerChangeEvent(Va v) {
            fsmCallback(v);
        }

        bool isAccepting() {
            return isStateAccepting;
        }
    };

private:
    // pointer to the current state, the fsm will only call this states logic function
    State<T, V, A> *currentState; // This is the current state, all events given to the FSM will be proccessed using this node.
    // Call back in the parent class. Triggered when there is an fsm event
    void (A::*callbackPtr)(V v); // Call back pointer to handle the outward bound events
    // Map of all the States
    std::unordered_map<std::string, State<T, V, A> *> states; // List of all the states
public:
    FiniteStateMachine() {}

    ~FiniteStateMachine() {
    }

    // Memory management, keeps it squeaky cleany ;)
    void clean() {
        for (auto &st : states) {
            delete st.second;
        }
    }

    // This is call back function, transmits events
    void setCallbackFunction(void (A::*funcptr)(V v)) {
        this->callbackPtr = funcptr;
    }

    // Calls the current states logic function
    void proccessEvent(T t, A *a) {
        this->currentState->proccesEvent(t, a);
    }

    // Called within the states logic function, triggers and event
    void triggerStateChangeEvent(V v, A *a) {
        (a->*callbackPtr)(v);
    }

    // Adds a new state to the map
    void addState(State<T, V, A> *state, std::string name) {
        states[name] = state;
        //std::cout << "FSM: Added state '" << name << "' to the fsm" << std::endl;
    }

    // Switches states, first checks whether or not the state exists
    void switchStates(std::string name) {
        //  std::cout << "Switching to state: " << name << std::endl;
        if (states.find(name) != states.end()) {
            currentState = states[name];
        } else {
            std::string message = "ERROR: State \'";
            message.append(name).append("\' does not exist");
            throw message;
        }
    }

    // Checks whether current state is an acecpting state
    bool isCurrentStateAccepting() {
        return currentState->isAccepting();
    }

    // Sets the initial state. Needed to actually run the fsm
    // This version of the function is used only if the state will not survive
    void setInitialState(State<T, V, A> *state) {
        this->currentState = state;
    }

    // Sets the initial state. Needed to actually run the fsm
    void setInitialState(std::string name) {
        switchStates(name);
    }

    // Creates a new state pointer and initializes it
    State<T, V, A> *
    createState(void(A::*proccFunc)(FiniteStateMachine<T, V, A> *fsm, T t), A *a, bool isStateAccepting) {
        State<T, V, A> *ptr = new State<T, V, A>(this, proccFunc, a, isStateAccepting);
        return ptr;
    }
};


#endif
