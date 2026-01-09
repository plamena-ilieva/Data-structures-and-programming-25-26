#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>

class Graph
{
    std::vector<std::vector<int>> adj;
    bool directed;

    void DFSHelpRec(size_t start, size_t, std::vector<bool>& visited) const;

    void DFSConnectedComponents(size_t curr,
        size_t component,
        std::vector<unsigned>& visited) const;

    bool DFSContainsCycleDirectedRec(int start, std::vector<bool>& visited, std::set<int>& isInStack) const;
    bool DFSContainsCycleNotDirectedRec(int start, std::vector<bool>& visited, int parent) const;
    bool containsCycleDirected() const;
    bool containsCycleNotDirected() const;

    void topoSortRec(int start, std::vector<bool>& visited, std::stack<int>& st) const;

public:
    Graph(size_t vertexCount, bool isDirected);
    void addEdge(size_t start, size_t end);

    void BFS(size_t start) const;
    void DFS_ITER(size_t start) const;
    void DFS_REC(size_t start) const;
    int BFS_shortest_path(size_t start, size_t end) const;
    int BFS_shortest_path_vector(size_t start, size_t end) const;

    void topoSort() const;
    bool containsCycle() const;

    int connectedComponentsCount() const;
};

Graph::Graph(size_t vertexCount, bool isOriented) : adj(vertexCount), directed(isOriented)
{
}

void Graph::addEdge(size_t start, size_t end)
{
    adj[start].push_back((int)end);
    if (!directed)
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
    s.push({ start, start });

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

void Graph::DFSHelpRec(size_t curr,
    size_t parent,
    std::vector<bool>& visited) const
{
    visited[curr] = true;
    std::cout << "( " << parent << ", " << curr << ")";

    for (int neighbor : adj[curr])
    {
        if (!visited[neighbor])
            DFSHelpRec(neighbor, curr, visited);
    }    
}

void Graph::DFSConnectedComponents(size_t curr,
    size_t component,
    std::vector<unsigned>& components) const
{
    components[curr] = component;

    for (int neighbor : adj[curr])
    {
        if (components[neighbor] == 0)
            DFSConnectedComponents(neighbor, component, components);
    }
}


void Graph::DFS_REC(size_t start) const
{
    std::vector<bool> visited(adj.size(), false);
    DFSHelpRec(start, start, visited);
}


bool Graph::DFSContainsCycleDirectedRec(int start, std::vector<bool>& visited, std::set<int>& isInStack) const
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
            cycle = cycle || DFSContainsCycleDirectedRec(neighbor, visited, isInStack);
        }
    }
    isInStack.erase(start);
    return cycle;
}
bool Graph::DFSContainsCycleNotDirectedRec(int start, std::vector<bool>& visited, int parent) const {
    visited[start] = true;

    bool cycle = false;
    for (int neighbor : adj[start]) {
        if (start == neighbor || neighbor == parent) {
            continue;
        }
        if (visited[neighbor]) {
            return true;
        }
        cycle = cycle || DFSContainsCycleNotDirectedRec(neighbor, visited, start);
    }

    return cycle;
}

bool Graph::containsCycleDirected() const
{
    std::set<int> isInStack;
    std::vector<bool> visited(adj.size(), false);

    for (size_t i = 0; i < adj.size(); i++)
    {
        if (!visited[i]) {
            if (DFSContainsCycleDirectedRec(i, visited, isInStack))
                return true;
        }
    }
    return false;
}

bool Graph::containsCycleNotDirected() const
{
    std::vector<bool> visited(adj.size(), false);

    for (size_t i = 0; i < adj.size(); i++)
    {
        if (!visited[i]) {
            if (DFSContainsCycleNotDirectedRec(i, visited, i)) {
                return true;
            }
        }
    }
    return false;
}


bool Graph::containsCycle() const
{
    if (directed) {
        return containsCycleDirected();
    }

    return containsCycleNotDirected();
}

int Graph::connectedComponentsCount() const {
    if (directed) {
        return -1;
    }

    std::vector<unsigned> components(adj.size(), 0);
    size_t compCounter = 0;

    for (size_t i = 0; i < adj.size(); i++)
    {
        if (components[i] == 0) {
            compCounter++;
            DFSConnectedComponents(i, compCounter, components);
        }
    }

    return compCounter;
}

void Graph::topoSortRec(int start, std::vector<bool>& visited, std::stack<int>& st) const {
    visited[start] = true;

    for (int neighbor : adj[start])
    {
        if (!visited[neighbor])
            topoSortRec(neighbor, visited, st);
    }
    st.push(start);
}

void Graph::topoSort() const {
    std::stack<int> st;
    std::vector<bool> visited(adj.size(), false);


    for (size_t i = 0; i < adj.size(); i++)
    {
        if (!visited[i]) {
            topoSortRec(i, visited, st);
        }
    }

    while (!st.empty()) {
        std::cout << st.top() << ' ';
        st.pop();
    }
}
