//
// Created by salih on 06/08/2020.
//

#include "gcalc.h"

int main() {

    try {
        Gcalc g_calc = Gcalc();
        while (1) {
            std::cout << "Gcalc> "; //Todo: check space
            std::string cmd_line;
            std::getline(std::cin, cmd_line);
            g_calc.executeCommand(cmd_line);
        }
    }catch(const UndefinedVariable& e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}