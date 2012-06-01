#include "App.cpp"

int main(int argc, char * argv[])
{
    App app;

    if (argc > 1) {
        app.setAction(argv[1]);
    }
    
    if (argc > 2) {
        app.setPath(argv[2]);
    }
    
    if (argc > 3) {
        for (int i = 3; i < argc; i++) {
            app.addArg(argv[i]);
        }
    }
    
    app.run();
        
    return 0;
}

