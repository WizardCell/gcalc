
#include "gcalc.h"

int main(int argc, char *argv[]) {
    try {
        if (argc == 1) {
            Gcalc g_calc = Gcalc();
            while (g_calc.should_iterate) {
                std::cout << "Gcalc> ";
                std::string cmd_line;
                std::getline(std::cin, cmd_line);
                if(std::cin.eof()){
                    break;
                }
                g_calc.executeCommand(cmd_line, std::cout);
            }
        } else if (argc == 3) {
            ///Get "input.txt"
            std::string input_name = argv[1];

            ///Get "output.txt"
            std::string output_name = argv[2];

            ///open "input.txt"
            std::ifstream in_stream(input_name);
            if (!in_stream) {
                throw FileDidntOpen();
            }


            std::ofstream out_stream(output_name);
            if (!out_stream) {
                throw FileDidntOpen();
            }


            ///Define inner Gcalc (in order to run to redirected IO)
            Gcalc g_calc_inner = Gcalc();
            std::string cmd_line;
            while (g_calc_inner.should_iterate && std::getline(in_stream, cmd_line)) {
                g_calc_inner.executeCommand(cmd_line, out_stream);
            }
        } else {
            std::cerr << "Error: Invalid number of arguments" << std::endl;
        }
    } catch (const FileDidntOpen &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

bool isInsideParentheses(std::string& param){
    param = trim(param);
    if ((param[0]=='(') && (param[param.length()-1])==')'){
        param = param.substr(1,param.length()-2);
        return true;
    }
    else return false;
}

Graph executeOperation(const Graph &G2, const Graph &G3, const char operation) {
    switch (operation) {
        case ('+'):
            return G2 + G3;
        case ('^'):
            return G2 ^ G3;
        case ('-'):
            return G2 - G3;
        case ('*'):
            return G2 * G3;
        default:
            return G2;
    }
}

std::string ltrim(const std::string &s) {
    const std::string WHITESPACE = " \n\v\f\r\t";
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s) {
    const std::string WHITESPACE = " \n\v\f\r\t";
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

bool isAlphanumeric(const std::string &s) {
    if(s.empty()){
        return false; //todo check
    }
    for (auto &character : s) {
        if (!isalnum(character) || !isalpha(s[0])) {
            return false;
        }
    }
    return true;
}

void splitVertices(std::set<Vertex> &Vertex_set, const std::string &str) {
    ///This deals with the case of "a,b,"
    if (str.empty()) {
        throw IllegalName();
    }
    size_t comma_place = str.find_first_of(',');
    ///Get current vertex's name
    std::string curr_vertex_name = str.substr(0, comma_place);
    curr_vertex_name = trim(curr_vertex_name);

    ///Get vertex given name
    Vertex curr_vertex(curr_vertex_name);

    ///Check if vertex already exists
    if (Vertex_set.count(curr_vertex) > 0) {
        throw RedefinedVertex();
    }

    ///Insert vertex
    Vertex_set.insert(curr_vertex);

    ///Recursion
    if (comma_place != std::string::npos) {
        splitVertices(Vertex_set, str.substr(comma_place + 1, std::string::npos));
    }

}

std::set<Edge> splitEdges(const std::string &str, std::set<Vertex> &Vertex_set) {
    if (str.empty()) {
        return std::set<Edge>();
    }
    int brackets_counter = 0, comma_counter = 1;
    std::set<Edge> tokens;
    //int opener = -1, comma = -1;
    size_t opener = std::string::npos;
    size_t comma = std::string::npos;
    size_t ite_number = 0;


    if (str[0] != '<') {
        throw IllegalName();
    }
    if (str[str.length() - 1] != '>') {
        throw IllegalName();
    }

    for (auto &character : str) {

        if (character == '<') {
            if (comma_counter != 1) {
                throw IllegalName();
            }
            comma_counter = 0;
            brackets_counter++;
            if (brackets_counter > 1) {
                throw IllegalName();
            }
            opener = ite_number;
        } else if (character == '>') {

            ///Check if indeed there's an opener to this closer
            if (brackets_counter == 0) {
                throw IllegalName();
            }
            brackets_counter--;

            size_t closer = ite_number;

            if ((opener == std::string::npos) || (comma == std::string::npos)) {
                throw IllegalName();
            }

            ///Get the src,dst vertices' names
            std::string src_vertex_name(str.substr(opener + 1, comma - opener - 1));
            std::string dst_vertex_name(str.substr(comma + 1, closer - comma - 1));
            src_vertex_name = trim(src_vertex_name);
            dst_vertex_name = trim(dst_vertex_name);

            ///Case <,v> or <v,>
            if ((src_vertex_name.empty()) || (dst_vertex_name.empty())) {
                throw IllegalName();
            }

            Edge edge;
            Vertex src_vertex;
            Vertex dst_vertex;

            ///Define the vertices
            src_vertex = Vertex(src_vertex_name);
            dst_vertex = Vertex(dst_vertex_name);

            ///Check if the vertices are defined in the set
            if (Vertex_set.find(src_vertex) == Vertex_set.end()) {
                throw EdgeMissingBeginPoint(src_vertex_name, dst_vertex_name);
            }
            if (Vertex_set.find(dst_vertex) == Vertex_set.end()) {
                throw EdgeMissingEndPoint(src_vertex_name, dst_vertex_name);
            }

            ///Define the edge
            edge = Edge(src_vertex, dst_vertex);
            ///Check parallel edges
            if (tokens.count(edge) != 0) {
                throw ParallelEdges();
            }

            ///Add edge to set
            tokens.insert(edge);

            comma_counter = 0;
            opener = std::string::npos;
            comma = std::string::npos;
        } else if (character == ',') {
            if (comma_counter != 0) {
                throw IllegalName();
            }
            comma_counter++;
            if (brackets_counter == 1) {///This means this is an inner comma
                comma = ite_number;
            }
        }
        ite_number++;
    }
    return tokens;
}

char returnLastDominantOperation(const std::string &s) {
    char last_op = NULLCHAR;
    size_t parentheses_count = 0;
    for (auto &character : s) {
        if ((character == '+') || (character == '^') || (character == '-') || (character == '*')) {
            if (parentheses_count == 0) {
                last_op = character;
            }
        }
        if (character == '(') {
            parentheses_count++;
        }
        if (character == ')') {
            parentheses_count--;
        }
    }
    return last_op;
}

size_t findLastDominantOperation(const std::string &s) {
    size_t count = 0;
    size_t operation_index = std::string::npos;
    size_t parentheses_count = 0;
    for (auto &character : s) {
        if ((character == '+') || (character == '^') || (character == '-') || (character == '*')) {
            if (parentheses_count == 0) {
                operation_index = count;
            }
        }
        if (character == '(') {
            parentheses_count++;
        }
        if (character == ')') {
            parentheses_count--;
        }
        count++;
    }
    return operation_index;
}

Graph defineGraph(std::string &rhs) {
    const std::string Comma = ",";

    ///Remove the '{' and '}'
    rhs = rhs.substr(1, rhs.length() - 2);
    rhs = trim(rhs);

    ///Find the separator '|'
    size_t separator = rhs.find_first_of('|');

    ///Split string into vertices and edges
    std::string vertices = rhs.substr(0, separator);
    std::string edges = std::string();
    if (separator != std::string::npos) {
        edges = rhs.substr(separator + 1, std::string::npos);
    }
    vertices = trim(vertices);
    edges = trim(edges);

    std::set<Vertex> Vertex_set;
    ///Convert the string of vertices to vertices set
    if (!vertices.empty()) {
        splitVertices(Vertex_set, vertices);
    }

    ///Convert the string of edges to edges set
    std::set<Edge> Edge_set = splitEdges(edges, Vertex_set);

    return Graph(Vertex_set, Edge_set);
}

void printGraph(const Graph &graph, std::ostream &output) {

    ///Print the vertices
    for (const auto &v : graph.getVertices()) {
        output << v.getName() << std::endl;
    }

    ///Print the '$' sign
    output << "$" << std::endl;

    ///Print the edges
    for (const auto &e : graph.getEdges()) {
        output << e.getSourceVertex().getName() << " " << e.getDestinationVertex().getName() << std::endl;
    }
}

std::set<Vertex> readVertices(std::ifstream &infile, unsigned int Vertex_num) {
    std::set<Vertex> Vertex_set = std::set<Vertex>();
    for (unsigned int i = 0; i < Vertex_num; i++) {
        ///Read the current vertex's length
        unsigned int Vertex_length;
        infile.read((char *) &Vertex_length, sizeof(int));
        if(!infile){
            throw ReadFailed();
        }


        ///Get a char* to read into
        char *temp = (char *) malloc(sizeof(char) * Vertex_length + 1);
        if(temp == nullptr){
            throw std::bad_alloc();
        }
        temp[Vertex_length] = '\0';

        ///Read the vertex
        infile.read((char *) temp, sizeof(char) * Vertex_length);
        if(!infile){
            throw ReadFailed();
        }

        ///Define the string
        std::string Vertex_name(temp);
        free(temp);

        ///Define vertex
        Vertex vertex(Vertex_name);
        if (Vertex_set.count(vertex) > 0) {
            throw RedefinedVertex();
        }

        Vertex_set.insert(vertex);
    }
    return Vertex_set;
}

std::set<Edge> readEdges(std::ifstream &infile, unsigned int Edge_num, const std::set<Vertex> &Vertex_set) {
    std::set<Edge> Edge_set = std::set<Edge>();

    for (unsigned int i = 0; i < Edge_num; i++) {
        ///Read the source vertex length
        unsigned int v1_length;
        infile.read((char *) &v1_length, sizeof(int));
        if(!infile){
            throw ReadFailed();
        }

        ///Get a char* to read src vertex
        char *v1_temp = (char *) malloc(sizeof(char) * v1_length + 1);
        if(v1_temp == nullptr){
            throw std::bad_alloc();
        }
        v1_temp[v1_length] = '\0';

        ///Read the src vertex
        infile.read((char *) v1_temp, sizeof(char) * v1_length);
        if(!infile){
            throw ReadFailed();
        }

        ///Define the src string
        std::string v1_name(v1_temp);
        free(v1_temp);


        ///Read the destination vertex length
        unsigned int v2_length;
        infile.read((char *) &v2_length, sizeof(int));
        if(!infile){
            throw ReadFailed();
        }

        ///Get a char* to read src vertex
        char *v2_temp = (char *) malloc(sizeof(char) * v2_length + 1);
        if(v2_temp == nullptr){
            throw std::bad_alloc();
        }
        v2_temp[v2_length] = '\0';

        ///Read the src vertex
        infile.read((char *) v2_temp, sizeof(char) * v2_length);
        if(!infile){
            throw ReadFailed();
        }

        ///Define the src string
        std::string v2_name(v2_temp);
        free(v2_temp);



        ///Define the src vertex
        Vertex v1(v1_name);

        ///Check if the src vertex exists
        if (Vertex_set.count(v1) == 0) {
            throw EdgeMissingBeginPoint(v1_name, v2_name);
        }

        ///Define the dst vertex
        Vertex v2(v2_name);

        ///Check if the dst vertex exists
        if (Vertex_set.count(v2) == 0) {
            throw EdgeMissingEndPoint(v1_name, v2_name);
        }

        ///Define and insert edge
        Edge edge(v1, v2);
        Edge_set.insert(edge);
    }
    return Edge_set;

}

Graph executeLoad(std::map<std::string, Graph> &graphs_map, const std::string &parameter) {

    ///Get the filename
    std::string filename = parameter;
    filename = trim(filename);

    ///Open the file as input
    std::ifstream infile(filename, std::ios_base::binary);
    if (!infile) {
        throw FileDidntOpen();
    }
    unsigned int Vertex_num = 0, Edge_num = 0;

    std::set<Vertex> Vertex_set;
    std::set<Edge> Edge_set;

    ///Read Vertex&Edge counts
    infile.read((char *) &Vertex_num, sizeof(int));
    if(!infile){
        throw ReadFailed();
    }
    infile.read((char *) &Edge_num, sizeof(int));
    if(!infile){
        throw ReadFailed();
    }

    ///Read the Vertices
    Vertex_set = readVertices(infile, Vertex_num);

    ///Read the Edges
    Edge_set = readEdges(infile, Edge_num, Vertex_set);


    return Graph(Vertex_set, Edge_set);
}


void removeParentheses(std::string &to_interpret) {
    to_interpret = trim(to_interpret);
    while ((to_interpret[0] == '(') && (to_interpret[to_interpret.length() - 1] == ')')) {
        int counter = 0;
        unsigned int ite = 0;
        bool flag = true;
        for (const char &c : to_interpret) {
            if (c == '(') {
                counter++;
            } else if (c == ')') {
                counter--;
                if (counter == 0 && ite != to_interpret.length() - 1) {
                    flag = false;
                    break;
                }
            }
            ite++;
        }
        if (counter == 0 && flag) {
            to_interpret = to_interpret.substr(1, to_interpret.length() - 2);
            to_interpret = trim(to_interpret);
        } else {
            break;
        }
    }
}

Graph stringToGraph(std::map<std::string, Graph> &graphs_map, std::string to_interpret) {

    ///Remove additional parentheses
    removeParentheses(to_interpret);

    ///Returns last operation not inside parentheses
    char op = returnLastDominantOperation(to_interpret);

    if (op == NULLCHAR) {
        ///case "load(...)"
        if (to_interpret.substr(0, 4) == "load") {
            std::string parameter = to_interpret.substr(4, std::string::npos);
            if( isInsideParentheses(parameter) ) {
                return executeLoad(graphs_map, parameter);
            }
        }

        if ((to_interpret.find_first_of('{') == 0) &&
            (to_interpret.find_last_of('}') == to_interpret.length() - 1)) {
            ///case " { ... | ... } "
            return defineGraph(to_interpret);
        }
        ///case " G2 " or " !G2 "
        if (to_interpret[0] == '!') {
            Graph G = stringToGraph(graphs_map, to_interpret.substr(1, std::string::npos));
            return !G;
        }
        ///case " G2 "
        if (!isAlphanumeric(to_interpret)) {
            throw IllegalName();
        } else {
            ///Find G2
            auto G2 = graphs_map.find(to_interpret);
            ///Check if G2 exists
            if (G2 == graphs_map.end()) {     ///G2 is not defined -> Error
                throw UndefinedVariable(to_interpret);
            } else {
                return G2->second;
            }
        }
    } else {
        ///Here we have "left *op* right"

        ///find the op
        size_t op_place = findLastDominantOperation(to_interpret);

        ///Get "left *op* right"
        std::string left = to_interpret.substr(0, op_place);
        std::string right = to_interpret.substr(op_place + 1, std::string::npos);
        left = trim(left);
        right = trim(right);


        ///find G2, G3 in the set
        Graph G2 = stringToGraph(graphs_map, left);
        Graph G3 = stringToGraph(graphs_map, right);

        ///Execute the operation on G2 G3.
        return executeOperation(G2, G3, op);
    }
}

bool isBuiltInName(const std::string &graph_name) {
    return (graph_name == "print") || (graph_name == "who") || (graph_name == "reset") || (graph_name == "quit")
           || (graph_name == "save") || (graph_name == "load");
}


void Gcalc::executeCommand(const std::string &cmd_line, std::ostream &output) {
    try {
        std::string trimmed_cmd_line = trim(cmd_line);
        std::string lhs, rhs;

        /*///Removes the parentheses
        removeParentheses(trimmed_cmd_line);*/

        ///Find the '=' sign
        size_t eq_sign_index = trimmed_cmd_line.find('=');

        ///Case "LHS = RHS"
        if (eq_sign_index != std::string::npos) {

            ///Define LHS
            lhs = trimmed_cmd_line.substr(0, eq_sign_index);
            lhs = trim(lhs);

            ///Check if LHS is " G1 "

            if (!isAlphanumeric(lhs)) {
                throw IllegalName();
            }
            if (isBuiltInName(lhs)) {
                throw IllegalName();
            }

            ///Define RHS
            rhs = trimmed_cmd_line.substr(eq_sign_index + 1, std::string::npos);
            rhs = trim(rhs);


            ///Define G1 = RHS and add to map
            graphs_map[lhs] = stringToGraph(graphs_map, rhs);

        } else if (trimmed_cmd_line == "who") {
            for (const auto &graph : graphs_map) {
                output << graph.first.c_str() << std::endl;
            }
        } else if (trimmed_cmd_line == "reset") {
            graphs_map.clear();
        } else if (trimmed_cmd_line == "quit") {
            should_iterate = false;
        } else if (trimmed_cmd_line.substr(0, 5) == "print") {
            ///Checks if "print   PARAM == print (...)"
            std::string parameter = trimmed_cmd_line.substr(5, std::string::npos);
            if( !isInsideParentheses(parameter) ){
                throw UnrecognizedCommand(cmd_line);
            }

            ///Gets the parameter inside the parentheses.
            std::string G = parameter;
            G = trim(G);

            ///convert the parameter to graph
            Graph G_graph = stringToGraph(graphs_map, G);

            ///You're okay to print
            printGraph(G_graph, output);
        } else if (trimmed_cmd_line.substr(0, 6) == "delete") {
            ///Checks if "delete(...)"
            std::string parameter = trimmed_cmd_line.substr(6, std::string::npos);
            if( !isInsideParentheses(parameter) ){
                throw UnrecognizedCommand(cmd_line);
            }

            ///Gets the parameter inside the parentheses
            std::string G = parameter;
            G = trim(G);

            ///Checks validity of G
            if (!isAlphanumeric(G)) {
                throw IllegalName();
            }
            if (graphs_map.count(G) == 0) {
                throw UndefinedVariable(G);
            }

            graphs_map.erase(G);
        } else if (trimmed_cmd_line.substr(0, 4) == "save") {
            ///Check if save(...)
            std::string parameter = trimmed_cmd_line.substr(4, std::string::npos);
            if( !isInsideParentheses(parameter) ){
                throw UnrecognizedCommand(cmd_line);
            }

            ///get the inner parameter
            std::string G_and_Filename = parameter;

            ///Find comma
            size_t comma_index = G_and_Filename.find_last_of(',');
            if (comma_index == std::string::npos) {
                throw UnrecognizedCommand(cmd_line);
            }

            std::string G_name = G_and_Filename.substr(0, comma_index);
            std::string filename = G_and_Filename.substr(comma_index + 1, std::string::npos);
            G_name = trim(G_name);
            filename = trim(filename);

            if ((filename.find('(') != std::string::npos) || (filename.find(')') != std::string::npos)) {
                throw FileDidntOpen();
            }
            ///Get the Graph
            Graph G = stringToGraph(graphs_map, G_name);

            ///Open file
            std::ofstream outfile(filename, std::ios_base::binary);
            if (!outfile) {
                throw FileDidntOpen();
            }


            ///Define Vertex & Edge sets
            const std::set<Vertex> &Vertex_set = G.getVertices();
            const std::set<Edge> &Edge_set = G.getEdges();

            ///Get the size
            unsigned int Vertex_num = Vertex_set.size();
            unsigned int Edge_num = Edge_set.size();

            ///Insert sizes to file
            outfile.write((const char *) &Vertex_num, sizeof(int));
            if(!outfile){
                throw WriteFailed();
            }
            outfile.write((const char *) &Edge_num, sizeof(int));
            if(!outfile){
                throw WriteFailed();
            }

            ///Add Vertices
            auto Vertex_iterator = Vertex_set.begin();
            while (Vertex_iterator != Vertex_set.end()) {

                unsigned int vertex_length = Vertex_iterator->getName().length();
                outfile.write((const char *) &vertex_length, sizeof(int));
                if(!outfile){
                    throw WriteFailed();
                }
                const char *vertex_name = Vertex_iterator->getName().c_str();
                outfile.write((const char *) vertex_name, sizeof(char) * vertex_length);
                if(!outfile){
                    throw WriteFailed();
                }

                Vertex_iterator++;
            }

            ///Add Edges
            auto Edge_iterator = Edge_set.begin();
            while (Edge_iterator != Edge_set.end()) {

                ///Get src vertex's name
                const char *v1_name = Edge_iterator->getSourceVertex().getName().c_str();
                unsigned int v1_length = Edge_iterator->getSourceVertex().getName().length();
                ///Insert length & name
                outfile.write((const char *) &v1_length, sizeof(int));
                if(!outfile){
                    throw WriteFailed();
                }
                outfile.write((const char *) v1_name, v1_length * sizeof(char));
                if(!outfile){
                    throw WriteFailed();
                }

                ///Get dst vertex's name
                const char *v2_name = Edge_iterator->getDestinationVertex().getName().c_str();
                unsigned int v2_length = Edge_iterator->getDestinationVertex().getName().length();
                ///Insert length & name
                outfile.write((const char *) &v2_length, sizeof(int));
                if(!outfile){
                    throw WriteFailed();
                }
                outfile.write((const char *) v2_name, v2_length * sizeof(char));
                if(!outfile){
                    throw WriteFailed();
                }

                Edge_iterator++;
            }

        } else {
            throw UnrecognizedCommand(cmd_line);
        }


    } catch (const IllegalName &e) {
        output << e.what() << std::endl;
    } catch (const UndefinedVariable &e) {
        output << e.what() << std::endl;
    } catch (const UnrecognizedCommand &e) {
        output << e.what() << std::endl;
    } catch (const EdgeMissingBeginPoint &e) {
        output << e.what() << std::endl;
    } catch (const EdgeMissingEndPoint &e) {
        output << e.what() << std::endl;
    } catch (const SelfEdge &e) {
        output << e.what() << std::endl;
    } catch (const ParallelEdges &e) {
        output << e.what() << std::endl;
    } catch (const RedefinedVertex &e) {
        output << e.what() << std::endl;
    } catch (const FileDidntOpen &e) {
        output << e.what() << std::endl;
    } catch (const ReadFailed &e) {
        output << e.what() << std::endl;
    } catch (const WriteFailed &e) {
        output << e.what() << std::endl;
    } catch (const std::bad_alloc &e) {
        output << "Error: bad allocation" << std::endl;
    }
}

Gcalc::Gcalc() : graphs_map(), should_iterate(true) {}
