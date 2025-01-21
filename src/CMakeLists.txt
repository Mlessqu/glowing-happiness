add_executable(tic-tac main.cpp states.hpp states.cpp utility.hpp utility.cpp
 button.hpp button.cpp resources.hpp resources.cpp ai.cpp
        StateMachine.cpp
        StateMachine.h
        State.cpp
        State.h
        Application.cpp
        Application.h
        MenuState.cpp
        MenuState.h
        ResourceManager.cpp
        ResourceManager.h
        LocalGameState.cpp
        LocalGameState.h
        AiGameState.cpp
        AiGameState.h
        OnlineHostState.cpp
        OnlineHostState.h
        OnlineClientState.cpp
        OnlineClientState.h
)
