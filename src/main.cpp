#include "App.cpp"

int main(int argc, char * argv[])
{
    App app;

    if (argc > 0) {
        app.setPath(argv[0]);
    }
    
    if (argc > 1) {
        app.setAction(argv[1]);
    }
    
    if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            app.addArg(argv[i]);
        }
    }
    
    app.run();
        
    return 0;
}

