
#include "gcalc.h"

int main() {

    try {
        Gcalc g_calc = Gcalc();

/*        std::cout << "Gcalc> "; //Todo: check space
        std::string cmd_line("G1 = {v1,v2|<v1,v2>}");
        g_calc.executeCommand(cmd_line, stdout);

        std::cout << "Gcalc> "; //Todo: check space
        cmd_line = std::string("G2 = G1");
        g_calc.executeCommand(cmd_line, stdout);

        std::cout << "Gcalc> "; //Todo: check space
        cmd_line = std::string("H = G1 + G2");
        g_calc.executeCommand(cmd_line, stdout);*/

        while (g_calc.should_iterate) {
            std::cout << "Gcalc> "; //Todo: check space
            std::string cmd_line;
            std::getline(std::cin, cmd_line);
            g_calc.executeCommand(cmd_line, stdout);
        }
    }catch(const UndefinedVariable& e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}