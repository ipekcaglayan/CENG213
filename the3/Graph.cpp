#include "Graph.h"
#define INF 9999999999
/*Do not add new libraries or files*/
typedef pair<int, string> p;

Graph::Graph()
{
    // TODO: IMPLEMENT THIS FUNCTION.
    adjList = HashTable<string, list<Edge>>();
}

Graph::Graph(const Graph &rhs)
{
    // TODO: IMPLEMENT THIS FUNCTION.
    adjList = HashTable<string, list<Edge>>();
    *this = rhs;
}

Graph &Graph::operator=(const Graph &rhs)
{
    // TODO: IMPLEMENT THIS FUNCTION.
    adjList = rhs.adjList;
    return *this;
}

Graph::~Graph()
{
    // TODO: IMPLEMENT THIS FUNCTION.
    //adjList.~HashTable();
}

void Graph::addNode(const Node &node)
{
    // TODO: IMPLEMENT THIS FUNCTION.
    list<Edge> edges;
    adjList.Insert(node.getCountry(), edges);
}

void Graph::addConnection(const Node &headNode, const Node &tailNode, int import)
{
    // TODO: IMPLEMENT THIS FUNCTION.
    //get val of key and then create new edge and push it to val
    list<Edge> &edges = adjList.Get(headNode.getCountry());
    edges.push_back(Edge(tailNode, import));
}

list<Node> Graph::getAdjacentNodes(const Node &node)
{
    // TODO: IMPLEMENT THIS FUNCTION.
    list<Node> result;
    list<Edge>::iterator it;
    list<Edge> edges = adjList.Get(node.getCountry());
    for (it = edges.begin(); it != edges.end(); it++)
    {
        result.push_back(it->getTailNode());
    }
    return result;
}

long Graph::getTotalImports(const Node &node)
{
    // TODO: IMPLEMENT THIS FUNCTION.
    int total = 0;
    list<Edge>::iterator it;
    list<Edge> edges = adjList.Get(node.getCountry());
    for (it = edges.begin(); it != edges.end(); it++)
    {
        total += it->getImport();
    }
    return total;
}

void Graph::deleteNode(const Node &node)
{
    // TODO: IMPLEMENT THIS FUNCTION.
    int size = adjList.Size();
    string *keys = new string[size];
    adjList.getKeys(keys);
    list<Edge>::iterator it;
    for (int i = 0; i < size; i++)
    {
        list<Edge> &edges = adjList.Get(keys[i]);
        for (it = edges.begin(); it != edges.end(); it++)
        {
            if (it->getTailNode().getCountry() == node.getCountry())
            {
                edges.erase(it);
                break;
            }
        }
    }
    delete[] keys;
    adjList.Delete(node.getCountry());
}
long Graph::distanceFind(vector<pair<string, long>> &distance, string &country)
{
    for (int i = 0; i < distance.size(); i++)
    {
        if (distance[i].first == country)
        {
            return distance[i].second;
        }
    }
}

void Graph::updateDistance(vector<pair<string, long>> &distance, string &country, long newDistance)
{
    for (int i = 0; i < distance.size(); i++)
    {
        if (distance[i].first == country)
        {
            distance[i].second = newDistance;
            return;
        }
    }
}
void Graph::updatePrevious(vector<pair<string, string>> &previous, string &country, string &updatedVal)
{
    for (int i = 0; i < previous.size(); i++)
    {
        if (previous[i].first == country)
        {
            previous[i].second = updatedVal;
            return;
        }
    }
}
string Graph::findPrevious(vector<pair<string, string>> &previous, string &country)
{
    for (int i = 0; i < previous.size(); i++)
    {
        //cout<<previous[i].first<<" "<<previous[i].second<<endl;
        if (previous[i].first == country)
        {
            return (previous[i].second);
        }
    }
}
void Graph::createPath(list<string> &path, string &country, vector<pair<string, string>> &previous)
{
    string prevCountry = findPrevious(previous, country);
    if (prevCountry == "NONE")
    {
        path.push_back(country);
        return;
    }
    createPath(path, prevCountry, previous);
    path.push_back(country);
}

list<string> Graph::findLeastCostPath(const Node &srcNode, const Node &destNode)
{
    // TODO: IMPLEMENT THIS FUNCTION.
    list<string> path;
    int size = adjList.Size();
    string *keys = new string[size];
    adjList.getKeys(keys);
    // first node itself, second previous
    vector<pair<string, string>> previous;
    vector<pair<string, long>> distance;
    priority_queue<pair<long, string>, vector<pair<long, string>>, greater<pair<long, string>>> q;
    for (int i = 0; i < size; i++)
    {
        if (keys[i] == srcNode.getCountry())
        {
            q.push(make_pair(0, keys[i]));
            previous.push_back(make_pair(srcNode.getCountry(), "NONE"));
        }
        else
        {
            q.push(make_pair(INF, keys[i]));
            distance.push_back(make_pair(keys[i], INF));
            previous.push_back(make_pair(keys[i], "NULL"));
        }
    }
    while (!q.empty())
    {
        pair<long, string> min = q.top();
        q.pop();
        long vertexDistance = min.first;
        list<Edge> edges = adjList.Get(min.second);
        list<Edge>::iterator it;
        for (it = edges.begin(); it != edges.end(); it++)
        {
            long weight = it->getImport();
            string country = it->getTailNode().getCountry();
            long prevDistance = distanceFind(distance, country);
            //cout<<"import: "<<weight<<endl;
            //cout<<"vertex dist: "<<vertexDistance<<endl;
            if (vertexDistance + weight < prevDistance)
            {
                //cout<<"new val: "<< vertexDistance+weight<<endl;
                //cout<<"Before: "<<distanceFind(distance,country)<<endl;
                updateDistance(distance, country, vertexDistance + weight);
                //cout<<"After: "<<distanceFind(distance,country)<<endl;

                updatePrevious(previous, country, min.second);
                q.push(make_pair(vertexDistance + weight, country));
            }
        }
    }
    string destCountry = destNode.getCountry();
    //    for(int i=0;i<distance.size();i++){
    //        cout<<distance[i].first<<" "<< distance[i].second<<endl;
    //    }

    createPath(path, destCountry, previous);

    //    for(string s: path){
    //        cout << s << endl;
    //    }

    delete[] keys;
    return path;
}

int Graph::isVisited(vector<pair<string, int>> &visitedInfo, string &country)
{
    for (int i = 0; i < visitedInfo.size(); i++)
    {
        if (visitedInfo[i].first == country)
        {
            return visitedInfo[i].second;
        }
    }
    return -1;
}
void Graph::markVisited(vector<pair<string, int>> &visitedInfo, string &country)
{
    //cout << "country: "<<country <<endl;
    for (int i = 0; i < visitedInfo.size(); i++)
    {

        if (visitedInfo[i].first == country)
        {
            visitedInfo[i].second = 1;
            // cout << country <<" is now visited: " << visitedInfo[i].second<< endl;
        }
    }
}

int Graph::index(string key)
{
    string *keys = new string[adjList.Size()];
    adjList.getKeys(keys);

    for (int i = 0; i < adjList.Size(); i++)
    {

        if (keys[i] == key)
        {
            delete[] keys;
            return i;
        }
    }

    delete[] keys;
    return -1;
}

bool Graph::dfs(vector<bool> &checkCycling, vector<bool> &visitedInfo, string country)
{
    int ind = index(country);
    if (!visitedInfo[ind])
    {
        visitedInfo[ind] = true;
        checkCycling[ind] = true;
        list<Edge> edges = adjList.Get(country);
        list<Edge>::iterator it;
        for (it = edges.begin(); it != edges.end(); ++it)
        {
            string c = it->getTailNode().getCountry();
            int indC = index(c);
            if (!visitedInfo[indC] && dfs(checkCycling, visitedInfo, c))
            {
                return true;
            }
            else if (checkCycling[indC])
            {
                return true;
            }
        }
    }
    checkCycling[ind] = false;
    return false;
}

bool Graph::isCyclic()
{
    // TODO: IMPLEMENT THIS FUNCTION.
    int size = adjList.Size();
    string *keys = new string[size];
    adjList.getKeys(keys);
    vector<bool> checkCycling(size,false);
    vector<bool> visitedInfo(size,false);

    for (int i = 0; i < size; i++)
    {
        if (dfs(checkCycling, visitedInfo, keys[i]))
        {

            delete[] keys;
            return true;
        }
    }

    delete[] keys;
    return false;
}

list<string> Graph::getBFSPath(const Node &srcNode, const Node &destNode)
{
    // TODO: IMPLEMENT THIS FUNCTION.
    list<string> path;
    string srcCountry = srcNode.getCountry();
    string dstCountry = destNode.getCountry();
    int size = adjList.Size();
    string *keys = new string[size];
    adjList.getKeys(keys);
    vector<pair<string, int>> visitedInfo;
    for (int i = 0; i < keys->size(); i++)
    {
        visitedInfo.push_back(make_pair(keys[i], 0));
    }
    queue<string> q;
    // cout<<"before marked: "<<isVisited(visitedInfo,srcCountry) <<endl;
    int visitInfo = isVisited(visitedInfo, srcCountry);
    if (visitInfo == 0)
    {
        markVisited(visitedInfo, srcCountry);
    }
    else if (visitInfo == -1)
    {
        visitedInfo.push_back(make_pair(srcCountry, 1));
    }

    //cout<<"after marked: "<< isVisited(visitedInfo,srcCountry)<<endl;

    q.push(srcCountry);
    //    markVisited(visitedInfo,visitedInfo[5].first);
    //    for(int h=0;h<visitedInfo.size();h++){
    //        cout<<"h: "<<h<<" country: "<< visitedInfo[h].first<<"---- "<<visitedInfo[h].second<<endl;
    //    }

    delete[] keys;
    while (!q.empty())
    {
        string front = q.front();
        q.pop();
        path.push_back(front);

        if (front == dstCountry)
        {
            // for(string s:path){
            //     cout<<s<<endl;
            // }
            return path;
        }

        list<Edge> edges = adjList.Get(front);
        list<Edge>::iterator it;
        for (it = edges.begin(); it != edges.end(); it++)
        {
            string c = it->getTailNode().getCountry();
            int vInfo = isVisited(visitedInfo, c);
            if (vInfo == 0)
            {
                markVisited(visitedInfo, c);
                q.push(c);
            }
            else if (vInfo == -1)
            {
                visitedInfo.push_back(make_pair(c, 1));
                q.push(c);
            }
        }
    }
}