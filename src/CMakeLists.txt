add_executable(tic-tac main.cpp states.cpp Utility.h Utility.cpp
        gui/Button.h gui/Button.cpp
        StateMachine.cpp
        StateMachine.h
        Application.cpp
        Application.h
        states/MenuState.cpp
        states/MenuState.h
        ResourceManager.cpp
        ResourceManager.h
        states/LocalGameState.cpp
        states/LocalGameState.h
        states/AiGameState.cpp
        states/AiGameState.h
        states/OnlineHostState.cpp
        states/OnlineHostState.h
        states/OnlineClientState.cpp
        states/OnlineClientState.h
        Game.cpp
        Game.h
        states/State.h
        states/State.cpp
        EventHandle.cpp
        EventHandle.h
)
