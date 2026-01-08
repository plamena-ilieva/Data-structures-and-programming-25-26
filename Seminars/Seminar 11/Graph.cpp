#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>

class Graph
{
    std::vector<std::vector<int>> adj;
    bool oriented;

    void dfs_help_rec(size_t start, size_t, std::vector<bool>& visited) const;

    void dfs_connected_comp(size_t curr,
        size_t component,
        std::vector<unsigned>& visited) const;
public:
    Graph(size_t vertexCount, bool isOriented);
    void addEdge(size_t start, size_t end);

    void BFS(size_t start) const;
    void DFS_ITER(size_t start) const;
    void DFS_REC(size_t start) const;
    int BFS_shortest_path(size_t start, size_t end) const;
    int BFS_shortest_path_vector(size_t start, size_t end) const;


    bool DFS_CONTAINS_CYCLE(int start, std::vector<bool>& visited, std::set<int>& isInStack) const;
    bool containsCycle() const;
    
    int connected_comp_count() const;
};

Graph::Graph(size_t vertexCount, bool isOriented) : adj(vertexCount), oriented(isOriented)
{
}

void Graph::addEdge(size_t start, size_t end)
{
    adj[start].push_back((int)end);
    if (!oriented)
        adj[end].push_back((int)start);
}

void Graph::BFS(size_t start) const
{
    std::vector<bool> visited(adj.size());

    std::queue<size_t> q;

    std::cout << start << std::endl;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        size_t currentVertex = q.front();
        q.pop();

        for (int i = 0; i < adj[currentVertex].size(); i++)
        {
            size_t neighbor = adj[currentVertex][i];
            if (visited[neighbor])
                continue;

            std::cout << "(" << currentVertex << ", " << neighbor << ")" << std::endl;
            visited[neighbor] = true;
            q.push(neighbor);
        }
    }
}

int Graph::BFS_shortest_path(size_t start, size_t end) const
{
    if (start == end) return 0;

    std::vector<bool> visited(adj.size(), false);
    std::queue<size_t> q;
    q.push(start);
    visited[start] = true;

    int dist = 0;

    while (!q.empty())
    {
        size_t currentLevelSize = q.size();
        for (size_t i = 0; i < currentLevelSize; i++)
        {
            size_t currentVertex = q.front();
            q.pop();

            for (auto neighbor : adj[currentVertex])
            {
                if (visited[neighbor])
                    continue;
                if (neighbor == end)
                    return dist + 1;

                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
        dist++;
    }

    return -1;
}

int Graph::BFS_shortest_path_vector(size_t start, size_t end) const
{
    std::vector<size_t> currLevel = { start };
    int dist = 0;
    std::vector<bool> visited(adj.size(), false);
    visited[start] = true;

    while (!currLevel.empty())
    {
        std::vector<size_t> nextLevel;

        for (size_t currNode : currLevel)
        {
            for (size_t currNodeChild : adj[currNode])
            {
                if (visited[currNodeChild])
                    continue;
                visited[currNodeChild] = true;
                if (currNodeChild == end)
                    return dist + 1;
                else
                    nextLevel.push_back(currNodeChild);
            }
        }
        currLevel.swap(nextLevel);
        dist++;

    }
    return -1;
}

void Graph::DFS_ITER(size_t start) const
{
    std::vector<bool> visited(adj.size(), false);

    struct edge {
        size_t origin;
        size_t dest;
    };
    std::stack<edge> s;
    s.push({start, start});

    while (!s.empty())
    {
        edge currEdge = s.top();
        size_t current = currEdge.dest;
        s.pop();

        if (visited[current])
            continue;

        visited[current] = true;
        std::cout << "( " << currEdge.origin << " " << current << " )";

        for (size_t neighbor : adj[current])
        {
            s.push(edge{ current, neighbor });
        }
    }
}

void Graph::dfs_help_rec(size_t curr,
                         size_t parent,
                         std::vector<bool>& visited) const
{
    visited[curr] = true;
    std::cout << "( " << parent << ", " << curr << ")";

    for (int neighbor : adj[curr])
    {
        if (!visited[neighbor])
            dfs_help_rec(neighbor, curr, visited);
    }
}

void Graph::dfs_connected_comp(size_t curr,
    size_t component,
    std::vector<unsigned>& components) const
{
    components[curr] = component;

    for (int neighbor : adj[curr])
    {
        if (components[neighbor] == 0)
            dfs_connected_comp(neighbor, component, components);
    }
}


void Graph::DFS_REC(size_t start) const
{
    std::vector<bool> visited(adj.size(), false);
    dfs_help_rec(start, start, visited);
}


bool Graph::DFS_CONTAINS_CYCLE(int start, std::vector<bool>& visited, std::set<int>& isInStack) const
{
    isInStack.insert(start);
    visited[start] = true;

    bool cycle = false;
    for (int neighbor : adj[start])
    {
        if (isInStack.find(neighbor) != isInStack.end())
            return true; //cycle!!!

        if (!visited[neighbor])
        {
            cycle = cycle || DFS_CONTAINS_CYCLE(neighbor, visited, isInStack);
        }
    }
    isInStack.erase(start);
    return cycle;
}

bool Graph::containsCycle() const
{   
    std::set<int> isInStack;


    for (size_t i = 0; i < adj.size(); i++)
    {
        if (!visited[i])
            if (DFS_CONTAINS_CYCLE(i, visited, isInStack))
                return true;
    }
    return false;
}

int Graph::connected_comp_count() const {
    if (oriented) {
        return -1;
    }

    std::vector<unsigned> components(adj.size(), 0);
    size_t compCounter = 0;

    for (size_t i = 0; i < adj.size(); i++)
    {
        if (components[i] == 0) {
            compCounter++;
            dfs_connected_comp(i, compCounter, components);
        }
    }

    return compCounter;
}
