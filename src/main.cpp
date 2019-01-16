#include <iostream>
#include "coreEngine.h"

//main program
int main(int argc, char* argv[]) {
    CoreEngine game (TITLE, WIDTH, HEIGHT);

    if (argc == 1) {
        std::cerr << "Usage: ./GameEngine path_to_model_files file_name1 file_name2 ...)" << std::endl;

        for (int i = 1; i < argc; i++) {
            game.loadMesh (std::string(argv[0], argv[i]));
        }
    }
    //main loop
    game.start();

    return 0;
}
