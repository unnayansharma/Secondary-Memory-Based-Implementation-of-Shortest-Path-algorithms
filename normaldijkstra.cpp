#include <bits/stdc++.h>
#include <fstream>
#define double long double
using namespace std;
map<int, int> nodes;
map<int, pair<double, int>> edges;
map<int, pair<int, int>> data;

int getvalint(string s) // Function to convert the input in string form to integer type
{
    int x;
    stringstream ss(s);
    ss >> x;
    return x;
}
double getvaldouble(string s)
{
    double x;
    stringstream ss(s);
    ss >> x;
    return x;
}
void insertinedges(int src, double dis)
{
    fstream fedge;
    fedge.open("edges1.txt", ios::in);

    string enode1;
    string enode2;
    string edgelength;

    int eno1;
    int eno2;
    double el;
    while (fedge.good())
    {
        getline(fedge, enode1, ' ');
        getline(fedge, enode2, ' ');
        getline(fedge, edgelength, '\n');
        eno1 = getvalint(enode1);
        eno2 = getvalint(enode2);
        el = getvaldouble(edgelength);

        if (eno1 == src && edges.find(eno2) != edges.end() && edges[eno2].first > el + dis && nodes.find(eno2) == nodes.end())
        {
            edges[eno2] = {el + dis, src};
        }
        if (eno1 == src && edges.find(eno2) == edges.end() && nodes.find(eno2) == nodes.end())
        {
            edges[eno2] = {el + dis, src};
        }
    }
}
int findmin(double &distance, int count)
{
    double min = INT_MAX;
    for (auto it : edges)
    {
        if (it.second.first < min)
        {
            min = it.second.first;
        }
    }
    int a;
    for (auto it : edges)
    {
        if (it.second.first == min)
        {
            a = it.first;
            distance = it.second.first;
            nodes[it.first] = 1;
            data[count] = {it.second.second, it.first};

            edges.erase(it.first);
            break;
        }
    }
    return a;
}
void dijkstranormal(int src, int dest)
{
    int count = 0;
    double distance = 0;
    nodes[src] = 1;
    int k = src;
    /*for(auto it : edges)
    {
        cout<<it.first<< " : "<<it.second<<"\n";
    }
    */
    int g = 0;
    while (k != dest)
    {
        //g++;
        //if (g == 600)
        //    break;
        insertinedges(k, distance);
        k = findmin(distance, count);
        if(edges.empty())
        {
            g=1;
            break;
        }
        count++;
    }
    /*for(auto it : data)
    {
        cout<<it.first<< " : "<<it.second.first<<"-->"<<it.second.second<<"\n";
    }
    */
    if (g == 1)
        cout << "Path Not Exist\n";
    else
    {
        vector<int> path;
        cout << "Distance = " << distance << "\n";
        cout << "PATH : ";
        while (dest != src)
        {
            for (auto it : data)
            {
                if (it.second.second == dest)
                {
                    path.push_back(it.second.second);
                    dest = it.second.first;
                    break;
                }
            }
        }
        path.push_back(dest);
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size() - 1; i++)
        {
            cout << path[i] << "-->";
        }
        cout << path[path.size() - 1] << "\n";
    }
}
int main()
{
    int src, dest;
    cout << "Enter source and Destination edges : \n";
    cin >> src >> dest;
    dijkstranormal(src, dest);
}