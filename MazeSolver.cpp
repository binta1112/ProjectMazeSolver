#include <iostream>
#include "httplib.hpp"
#include <json/json.h>
#include "Maze.h" // Ton générateur de labyrinthe

using namespace httplib;

 
int main() {
   
    Server svr;
    // Middleware pour gérer les requêtes OPTIONS (prévols CORS)
    svr.Options(".*", [](const Request& req, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Access-Control-Allow-Credentials", "true");  // Optionnel
        res.status = 200;
        });
    // Générer un labyrinthe
    svr.Get("/generate", [](const Request& req, Response& res) {       
        Maze maze(20, 30);
        maze.GenerateMaze(); // Fonction qui génère le labyrinthe
       
       
        Json::Value response;
        vector<vector<Cellule>> grid = maze.getGrid();

        for (auto& row : grid)
        {
            Json::Value line;
            for (auto& cell : row)
            {
                line.append(cell.getState());
            }
            response["maze"].append(line);
        }


        Json::StreamWriterBuilder writer;
        std::string json_str = Json::writeString(writer, response);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(json_str, "application/json");
        });


    svr.Post("/solve", [](const Request& req, Response& res) {
        Json::Value response;
        Maze maze(20, 30);

        try {
            // Parser le corps JSON de la requête
            Json::CharReaderBuilder reader;
            Json::Value requestBody;
            std::string errors;

            // Lire le JSON du corps
            std::istringstream reqBodyStream(req.body);
            if (!Json::parseFromStream(reader, reqBodyStream, &requestBody, &errors)) 
            {
                res.status = 400; // Bad Request
                res.set_content("Invalid JSON format", "text/plain");
                return;
            }
            std::vector<std::vector<Cellule>> grid = maze.getGrid();
            for (int i=0;i< requestBody["grid"].size();i++)
            {
                
                for (int j=0;j< requestBody["grid"][i].size(); j++)
                {
                    grid[i][j].setState((CellState)requestBody["grid"][i][j].asInt());
                    if (requestBody["grid"][i][j].asInt() == 2)
                        maze.setStart({ i,j });
                    if (requestBody["grid"][i][j].asInt() == 3)
                        maze.setEnd({ i,j });
                }
                
            }

            vector<pair<int, int>> steps;
            vector<pair<int, int>> path;
            maze.setGrid(grid);
            if(requestBody["algo"].asInt()==1) 
            {
                path = maze.solveDijkstra(steps);
            }
            else   
            {
              //  cout << "hello" << requestBody["algo"].asInt() << endl;
                path = maze.solveBFS(steps);
            }
            

             /*steps*/
            for (auto& Case : steps)
            {
                Json::Value pos;
                pos.append(Case.first);
                pos.append(Case.second);
                response["steps"].append(pos);

                //cout << Case.first << " "<<Case.second << endl;
            }
            /********************************************/
            for (auto& pos : path)
            {
                Json::Value line;
                line.append(pos.first);
                line.append(pos.second);
                response["path"].append(line);
            }
        }
        catch (const std::exception& e) 
        {
            res.status = 500; // Internal Server Error
            res.set_content(std::string("Error: ") + e.what(), "text/plain");
            cout << "hello" << endl;

        }
        Json::StreamWriterBuilder writer;
        std::string json_str = Json::writeString(writer, response);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(json_str, "application/json");
        });
    std::cout << "Serveur démarré sur http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
}
