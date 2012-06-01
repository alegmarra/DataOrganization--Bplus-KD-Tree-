#include "App.cpp"

int main(int argc, char * argv[])
{
    App app();

    if (argc > 0) {
        app.setPath(argv[0]);
    }
    
    if (argc > 1) {
        app.setAction(argv[1]);
    }
    
    if (argc > 2) {
        // Aca saco los primeros 2 argumentos con alguna logica de arrays
        app.setArgs(argv);
    }
    
    app.run();
        
    return 0;
}

