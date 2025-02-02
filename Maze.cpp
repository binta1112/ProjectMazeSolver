#include "Maze.h"
#include <cstdlib>
#include <ctime>
#include <queue>
#include <unordered_map>
#include <limits>

#include <thread>
#include <chrono>
// Directions possibles (haut, bas, gauche, droite)
Maze::Maze( int h, int w) : height(h),width(w) 
{    
    for (int i = 0; i < height; ++i) 
    {
        vector<Cellule> row;
        for (int j = 0; j < width; ++j) {
            row.emplace_back(make_pair(i, j), wall);
        }
        grid.push_back(row);
    }
/*On marque par defaut l'entree et l sortie*/
    this->start = { 0,0 };
    this->end = { h - 1,w - 1 };
    grid[0][0].setState(CellState::start);
    grid[h - 1][w-1].setState(CellState::out);

}

void Maze::GenerateMaze()
{
    srand(time(0));

    // Choisir une cellule de départ aléatoire
    int startX = 0;// (rand() % (height / 2)) * 2 + 1;
    int startY = 0;// (rand() % (width / 2)) * 2 + 1;
    grid[startX][startY].setState(none);
    vector<pair<int, int>> directions = { {-2, 0}, {2, 0}, {0, -2}, {0, 2} };
    vector<FrontierCell> frontierCells;

    // Ajouter les voisins de la cellule de départ à la liste des frontières
    for (const auto& dir : directions) 
    {
        int nx = startX + dir.first;
        int ny = startY + dir.second;
        if (nx >= 0 && ny >= 0 && nx < height  && ny < width ) 
        {
            frontierCells.push_back({ nx, ny, startX, startY });
        }
    }

    while (!frontierCells.empty()) 
    {
        // Sélectionner une frontière au hasard
        int randIndex = rand() % frontierCells.size();
        FrontierCell cell = frontierCells[randIndex];
        frontierCells.erase(frontierCells.begin() + randIndex);

        // Vérifier si la cellule est toujours un mur
        if (grid[cell.x][cell.y].getState() == wall) 
        {
            // La marquer comme un chemin
            grid[cell.x][cell.y].setState(none);

            // on casse le mur entre cette cellule et son parent
            int wallX = (cell.x + cell.px) / 2;
            int wallY = (cell.y + cell.py) / 2;
            grid[wallX][wallY].setState(none);

            // Ajouter ses voisins à la liste des frontières
            for (const auto& dir : directions) 
            {
                int nx = cell.x + dir.first;
                int ny = cell.y + dir.second;
                if (nx > 0 && ny > 0 && nx < height - 1 && ny < width - 1) 
                {
                    if (grid[nx][ny].getState() == wall) 
                    {
                        frontierCells.push_back({ nx, ny, cell.x, cell.y });
                    }
                }
            }
        }
    }
    this->grid[this->height - 1][this->width - 2].setState(CellState::none);
    this->setStart(this->start);
    this->setEnd(this->end);
    //this_thread::sleep_for(std::chrono::seconds(1));
    
}

void Maze::setStart(pair<int, int> start)
{ 
    //on change l'ancienne entre en mur 
    this->grid[this->start.first][this->start.second].setState(CellState::wall);
    this->start = start;
    this->grid[start.first][start.second].setState(CellState::start);
}

void Maze::setEnd(pair<int, int> end)
{
    this->grid[this->end.first][this->end.second].setState(CellState::wall);
    this->end = end;
    this->grid[end.first][end.second].setState(CellState::out);
}

void Maze::displayMaze() const 
{
    for (const auto& row : grid) 
    {
        for (const auto& cell : row) 
        {
            
            char c = (cell.getState() == wall) ? '#' : '-';
            cout << c << ' ';
        }
        cout << endl;
    }
}
bool Maze::isValid(int x, int y) const
{
    return x >= 0 && y >= 0 && x < height && y < width && grid[x][y].getState() != wall;
}

vector<pair<int, int>> Maze::solveDijkstra(vector<pair<int, int>>& steps)const
{
    priority_queue <pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    unordered_map<int, pair<int, int>> parent;
    vector<vector<int>> distance(height, vector<int>(width, numeric_limits<int>::max()));
    vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    int cost;
    pq.push({ 0, start });
    distance[start.first][start.second] = 0;
    parent[start.first * width + start.second] = { -1, -1 };

    while (!pq.empty()) 
    {
        pair<int,pair<int,int>> sommet = pq.top();
        pq.pop();
        
        cost = sommet.first;
        int x = sommet.second.first, y = sommet.second.second;
        if (sommet.second == end) break;
        if (sommet.second != start)
        {
            
            steps.push_back(sommet.second);
        }
        //on va vers les cellules voisines
        for (auto &dir : directions) 
        {
            int nx = x + dir.first, ny = y + dir.second;
            if (isValid(nx, ny) && distance[nx][ny] > cost + 1)
            {
                distance[nx][ny] = cost + 1;
                parent[nx * width + ny] = { x, y };
                pq.push({ distance[nx][ny], {nx, ny} });
            }
        }
    }

    //  Reconstruction du chemin
    vector<pair<int, int>> path;
    for (pair<int, int> at = end; at.first != -1; at = parent[at.first * width + at.second]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<pair<int, int>> Maze::solveBFS(vector<pair<int,int>>&steps) const
{
    queue<pair<int, int>> q;
    unordered_map<int, pair<int, int>> parent;
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    vector<pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    q.push(start);//on enfile la cellule de depart
    visited[start.first][start.second] = true;// on indique cette cellule est visitée
    parent[start.first * width + start.second] = { -1, -1 }; // Marquer le départ
    while (!q.empty()) 
    {
        pair<int, int> &cell = q.front(); // on considere la tete de la file
        q.pop();// on la defile
        if (cell == end) break; // Si on atteint la sortie on arrete
        if (cell != start)
        {            
            //je marque les etapes
            steps.push_back(cell);

        }
        cout << cell.first << " " << cell.second << "->";

        const int x = cell.first;
        const int y = cell.second;

        for (pair<int,int> &pos : directions) 
        {
            int nx = (int)(x + pos.first);
            int ny = (int)(y + pos.second);
            cout << "( ("<< x <<"+"<< pos.first<<")="  << nx << ", "
                 << y << "+" << pos.second << ")=" << ny << ") ";
            cout << "Direction utilisée : (" << pos.first << "," << pos.second << ") | ";

            if (isValid(nx, ny) && !visited[nx][ny]) 
            {

                visited[nx][ny] = true;
                parent[nx * width + ny] = { x, y };
                q.push({ nx, ny });
            }
        }
        cout << endl;
    } 
    // Reconstruction du chemin
    vector<pair<int, int>> path;

    for(pair<int, int> at = end; at.first != -1; at = parent[at.first * width + at.second]) 
    {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}
vector<vector<Cellule>> Maze::getGrid() const
{
    return this->grid;
}
void Maze::setGrid(vector<vector<Cellule>> newGrid)
{
    this->grid = newGrid;
    this->width = newGrid[0].size();
    this->height = newGrid.size();
}
/*
void Maze::solveDijkstraWithSteps()
{
    httplib::Server svr;

    svr.Post("/dijkstra", [&](const httplib::Request& req, httplib::Response& res) {
        // Appeler Dijkstra et obtenir les étapes
        vector<pair<int, int>> path = solveDijkstra();

        // Envoi des étapes sous forme de JSON
        Json::Value steps;
        for (const auto& step : path) {
            Json::Value stepJson;
            stepJson["x"] = step.first;
            stepJson["y"] = step.second;
            steps.append(stepJson);
        }

        // Convertir en chaîne JSON
        Json::StreamWriterBuilder writer;
        std::string output = Json::writeString(writer, steps);

        // Répondre avec les étapes
        res.set_content(output, "application/json");
        });

    svr.listen("localhost", 8080);  // Lancer le serveur
}*/
