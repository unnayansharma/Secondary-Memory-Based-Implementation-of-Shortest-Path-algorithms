#include <bits/stdc++.h>
#include <fstream>
#define double long double
using namespace std;
struct points
{
    double x;
    double y;
};
struct coordinates
{
    points t11;
    points t22;
};
struct nodesedge
{
    int n1;
    int n2;
    double l;
};
struct nodes_edge
{
    int n2;
    double l;
};
points min_cordinates, max_cordinates;
int B;
map<int, points> nodedata;
map<int, coordinates> celldata;
map<int, coordinates> nodecellmap;
map<int, nodesedge> edgemap;
map<int, int> eachcell;

map<int, int> record;
map<int, int> over;
map<int, int> nodesincell;
map<int, vector<int>> boundarynodesincell;
map<int, vector<nodesedge>> edgesincell;
map<int, list<pair<int, double>>> graphrep;
set<int> cellbuffer;
map<int, pair<int, double>> inputlist;
map<int, pair<int, double>> outputlist;
map<int, set<int>> buffer;
int o = 0;

points findcoordinates(double m, double n)
{
    double x = min_cordinates.x;
    double y = min_cordinates.y;
    double s = max_cordinates.x;
    double t = max_cordinates.y;
    int i = 0;
    while (y < t)
    {
        x = min_cordinates.x;
        while (x < s)
        {
            points t1 = {x, y};
            points t2 = {x + m, y + n};
            coordinates t3 = {t1, t2};
            celldata[i] = t3;
            i++;
            x = x + m;
        }
        y = y + n;
    }
    points t4 = {x, y};
    return t4;
}
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
void mapnodecell()
{
    for (auto it1 : nodedata)
    {
        for (auto it2 : celldata)
        {
            if (it1.second.x >= it2.second.t11.x && it1.second.y >= it2.second.t11.y && it1.second.x <= it2.second.t22.x && it1.second.y <= it2.second.t22.y)
            {
                points t1 = {it2.second.t11.x, it2.second.t11.y};
                points t2 = {it2.second.t22.x, it2.second.t22.y};
                coordinates t3 = {t1, t2};
                nodecellmap[it1.first] = t3;
            }
        }
    }
}
void mapedges()
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

        nodesedge n = {eno1, eno2, el};
        edgemap[o] = n;
        o++;
    }
}

void storenodes()
{
    for (auto it1 : nodecellmap)
    {
        for (auto it2 : celldata)
        {
            if (it1.second.t11.x == it2.second.t11.x && it1.second.t11.y == it2.second.t11.y && it1.second.t22.x == it2.second.t22.x && it1.second.t22.y == it2.second.t22.y)
            {
                eachcell[it2.first]++;
                if (record[it2.first] >= B || over[it2.first] != 0)
                {
                    if (record[it2.first] >= B)
                    {
                        record[it2.first] = 0;
                        over[it2.first]++;
                        if (over[it2.first] == 1)
                        {
                            ofstream fout;
                            fout.open(std::to_string(it2.first) + ".txt", std::ios_base::app);
                            fout << "??"
                                 << " " << it2.first << "overflow" << over[it2.first] << ".txt\n";
                        }
                        else if (over[it2.first] > 1)
                        {
                            ofstream fout;
                            fout.open(std::to_string(it2.first) + "overflow" + std::to_string(over[it2.first] - 1) + ".txt", std::ios_base::app);
                            fout << "??"
                                 << " " << it2.first << "overflow" << over[it2.first] << ".txt\n";
                        }
                    }
                    ofstream fout;
                    fout.open(std::to_string(it2.first) + "overflow" + std::to_string(over[it2.first]) + ".txt", std::ios_base::app);
                    for (auto it3 : nodedata)
                    {
                        if (it1.first == it3.first)
                        {
                            fout << it1.first << " < " << it3.second.x << "," << it3.second.y << " >\n";
                        }
                    }

                    record[it2.first]++;
                    fout.close();
                }
                else
                {
                    ofstream fout;
                    fout.open(std::to_string(it2.first) + ".txt", std::ios_base::app);
                    for (auto it3 : nodedata)
                    {
                        if (it1.first == it3.first)
                        {
                            fout << it1.first << " < " << it3.second.x << "," << it3.second.y << " >\n";
                        }
                    }
                    record[it2.first] += 1;
                    fout.close();
                }
            }
        }
    }
}
void storehash()
{
    for (auto it : eachcell)
    {
        if (record[it.first] >= B || over[it.first] != 0)
        {
            if (record[it.first] >= B)
            {
                record[it.first] = 0;
                over[it.first]++;
                if (over[it.first] == 1)
                {
                    ofstream fout;
                    fout.open(std::to_string(it.first) + ".txt", std::ios_base::app);
                    fout << "??"
                         << " " << it.first << "overflow" << over[it.first] << ".txt\n";
                }
                else if (over[it.first] > 1)
                {
                    ofstream fout;
                    fout.open(std::to_string(it.first) + "overflow" + std::to_string(over[it.first] - 1) + ".txt", std::ios_base::app);
                    fout << "??"
                         << " " << it.first << "overflow" << over[it.first] << ".txt\n";
                }
            }

            ofstream fout;
            fout.open(std::to_string(it.first) + "overflow" + std::to_string(over[it.first]) + ".txt", std::ios_base::app);
            string word;
            fstream fin;
            fin.open(std::to_string(it.first) + "overflow" + std::to_string(over[it.first]) + ".txt", ios::in);
            int f = 0;
            while (fin >> word)
            {
                if (word == "##")
                    f = 1;
            }
            fin.close();
            if (f == 0)
                fout << "##\n";
            fout.close();
        }
        else
        {
            string word;
            fstream fin;
            fin.open(std::to_string(it.first) + ".txt", ios::in);
            int f = 0;
            while (fin >> word)
            {
                if (word == "##")
                    f = 1;
            }
            fin.close();
            ofstream fout;
            fout.open(std::to_string(it.first) + ".txt", std::ios_base::app);
            if (f == 0)
                fout << "##\n";

            fout.close();
        }
    }
}
int checksamecell(int n1, int n2)
{
    for (auto it : nodecellmap)
    {
        if (it.first == n1)
        {
            for (auto it2 : nodecellmap)
            {
                if (it2.first == n2)
                {
                    if (it.second.t11.x == it2.second.t11.x && it.second.t11.y == it2.second.t11.y && it.second.t22.x == it2.second.t22.x && it.second.t22.y == it2.second.t22.y)
                    {
                        for (auto it3 : celldata)
                        {
                            if (it.second.t11.x == it3.second.t11.x && it.second.t11.y == it3.second.t11.y && it.second.t22.x == it3.second.t22.x && it.second.t22.y == it3.second.t22.y)
                                return it3.first;
                        }
                    }
                }
            }
        }
    }
    return -1;
}

void storeedgesn1n2()
{
    for (auto it2 : edgemap)
    {
        int cell = checksamecell(it2.second.n1, it2.second.n2);
        if (cell != -1)
        {
            if (record[cell] >= B || over[cell] != 0)
            {
                if (record[cell] >= B)
                {
                    record[cell] = 0;
                    over[cell]++;
                    if (over[cell] == 1)
                    {
                        ofstream fout;
                        fout.open(std::to_string(cell) + ".txt", std::ios_base::app);
                        fout << "??"
                             << " " << cell << "overflow" << over[cell] << ".txt\n";
                    }
                    else if (over[cell] > 1)
                    {
                        ofstream fout;
                        fout.open(std::to_string(cell) + "overflow" + std::to_string(over[cell] - 1) + ".txt", std::ios_base::app);
                        fout << "??"
                             << " " << cell << "overflow" << over[cell] << ".txt\n";
                    }
                }

                ofstream fout;
                fout.open(std::to_string(cell) + "overflow" + std::to_string(over[cell]) + ".txt", std::ios_base::app);

                fout << it2.second.n1 << " " << it2.second.n2 << " < " << it2.second.l << " > \n";
                edgesincell[cell].push_back({it2.second.n1, it2.second.n2, it2.second.l});
                record[cell]++;

                fout.close();
            }
            else
            {
                ofstream fout;
                fout.open(std::to_string(cell) + ".txt", std::ios_base::app);

                fout << it2.second.n1 << " " << it2.second.n2 << " < " << it2.second.l << " > \n";
                edgesincell[cell].push_back({it2.second.n1, it2.second.n2, it2.second.l});
                record[cell]++;

                fout.close();
            }
        }
    }
}
void storestar()
{
    for (auto it : eachcell)
    {
        if (record[it.first] >= B || over[it.first] != 0)
        {
            if (record[it.first] >= B)
            {
                record[it.first] = 0;
                over[it.first]++;
                if (over[it.first] == 1)
                {
                    ofstream fout;
                    fout.open(std::to_string(it.first) + ".txt", std::ios_base::app);
                    fout << "??"
                         << " " << it.first << "overflow" << over[it.first] << ".txt\n";
                }
                else if (over[it.first] > 1)
                {
                    ofstream fout;
                    fout.open(std::to_string(it.first) + "overflow" + std::to_string(over[it.first] - 1) + ".txt", std::ios_base::app);
                    fout << "??"
                         << " " << it.first << "overflow" << over[it.first] << ".txt\n";
                }
            }

            ofstream fout;
            fout.open(std::to_string(it.first) + "overflow" + std::to_string(over[it.first]) + ".txt", std::ios_base::app);
            string word;
            fstream fin;
            fin.open(std::to_string(it.first) + "overflow" + std::to_string(over[it.first]) + ".txt", ios::in);
            int f = 0;
            while (fin >> word)
            {
                if (word == "**")
                    f = 1;
            }
            fin.close();
            if (f == 0)
                fout << "**\n";
            fout.close();
        }
        else
        {
            string word;
            fstream fin;
            fin.open(std::to_string(it.first) + ".txt", ios::in);
            int f = 0;
            while (fin >> word)
            {
                if (word == "**")
                    f = 1;
            }
            fin.close();
            ofstream fout;
            fout.open(std::to_string(it.first) + ".txt", std::ios_base::app);
            if (f == 0)
                fout << "**\n";

            fout.close();
        }
    }
}
bool truecell(int n, int c)
{
    for (auto it : nodecellmap)
    {
        if (it.first == n)
        {
            for (auto it2 : celldata)
            {
                if (it.second.t11.x == it2.second.t11.x && it.second.t11.y == it2.second.t11.y && it.second.t22.x == it2.second.t22.x && it.second.t22.y == it2.second.t22.y)
                {
                    if (it2.first == c)
                        return true;
                }
            }
        }
    }
    return false;
}
int findcellofnode(int n)
{
    for (auto it : nodecellmap)
    {
        if (it.first == n)
        {
            for (auto it2 : celldata)
            {
                if (it.second.t11.x == it2.second.t11.x && it.second.t11.y == it2.second.t11.y && it.second.t22.x == it2.second.t22.x && it.second.t22.y == it2.second.t22.y)
                {
                    return it2.first;
                }
            }
        }
    }
    return -1;
}
void storeboundarynodes1()
{
    for (auto it2 : edgemap)
    {

        int flag = 0;
        int cell1;
        int cell2;
        int xco;
        int yco;
        cell1 = findcellofnode(it2.second.n1);
        cell2 = findcellofnode(it2.second.n2);
        if (cell1 != cell2 && cell1 != -1)
        {
            for (auto it1 : nodedata)
            {
                if (it2.second.n2 == it1.first)
                {
                    if (buffer[cell1].find(it1.first) == buffer[cell1].end())
                        buffer[cell1].insert(it1.first);
                    else
                        flag = 1;
                    xco = it1.second.x;
                    yco = it1.second.y;
                }
            }
            if (flag == 1)
                continue;
            if (record[cell1] >= B || over[cell1] != 0)
            {

                if (record[cell1] >= B)
                {

                    record[cell1] = 0;
                    over[cell1]++;
                    if (over[cell1] == 1)
                    {
                        ofstream fout;
                        fout.open(std::to_string(cell1) + ".txt", std::ios_base::app);
                        fout << "??"
                             << " " << cell1 << "overflow" << over[cell1] << ".txt\n";
                    }
                    else if (over[cell1] > 1)
                    {
                        ofstream fout;
                        fout.open(std::to_string(cell1) + "overflow" + std::to_string(over[cell1] - 1) + ".txt", std::ios_base::app);
                        fout << "??"
                             << " " << cell1 << "overflow" << over[cell1] << ".txt\n";
                    }
                }

                ofstream fout;
                fout.open(std::to_string(cell1) + "overflow" + std::to_string(over[cell1]) + ".txt", std::ios_base::app);

                fout << it2.second.n2 << " "
                     << " < " << xco << "," << yco << " > \n";
                boundarynodesincell[cell1].push_back(it2.second.n2);
                record[cell1]++;

                fout.close();
            }
            else
            {

                ofstream fout;
                fout.open(std::to_string(cell1) + ".txt", std::ios_base::app);

                fout << it2.second.n2 << " "
                     << " < " << xco << "," << yco << " > \n";
                boundarynodesincell[cell1].push_back(it2.second.n2);
                record[cell1]++;

                fout.close();
            }
        }
    }
}
void storeboundarynodes2()
{

    for (auto it2 : edgemap)
    {

        int flag = 0;
        int cell1;
        int cell2;
        int xco;
        int yco;
        cell1 = findcellofnode(it2.second.n1);
        cell2 = findcellofnode(it2.second.n2);
        if (cell1 != cell2 && cell2 != -1)
        {
            for (auto it1 : nodedata)
            {
                if (it2.second.n1 == it1.first)
                {
                    if (buffer[cell2].find(it1.first) == buffer[cell2].end())
                        buffer[cell2].insert(it1.first);
                    else
                        flag = 1;
                    xco = it1.second.x;
                    yco = it1.second.y;
                }
            }
            if (flag == 1)
                continue;
            if (record[cell2] >= B || over[cell2] != 0)
            {

                if (record[cell2] >= B)
                {

                    record[cell2] = 0;
                    over[cell2]++;
                    if (over[cell2] == 1)
                    {
                        ofstream fout;
                        fout.open(std::to_string(cell2) + ".txt", std::ios_base::app);
                        fout << "??"
                             << " " << cell2 << "overflow" << over[cell2] << ".txt\n";
                    }
                    else if (over[cell2] > 1)
                    {
                        ofstream fout;
                        fout.open(std::to_string(cell2) + "overflow" + std::to_string(over[cell2] - 1) + ".txt", std::ios_base::app);
                        fout << "??"
                             << " " << cell2 << "overflow" << over[cell2] << ".txt\n";
                    }
                }

                ofstream fout;
                fout.open(std::to_string(cell2) + "overflow" + std::to_string(over[cell2]) + ".txt", std::ios_base::app);

                fout << it2.second.n1 << " "
                     << " < " << xco << "," << yco << " > \n";
                boundarynodesincell[cell2].push_back(it2.second.n1);
                record[cell2]++;

                fout.close();
            }
            else
            {

                ofstream fout;
                fout.open(std::to_string(cell2) + ".txt", std::ios_base::app);

                fout << it2.second.n1 << " "
                     << " < " << xco << "," << yco << " > \n";
                boundarynodesincell[cell2].push_back(it2.second.n1);
                record[cell2]++;

                fout.close();
            }
        }
    }
}
void storepercent()
{
    for (auto it : eachcell)
    {

        if (record[it.first] >= B || over[it.first] != 0)
        {
            if (record[it.first] >= B)
            {
                record[it.first] = 0;
                over[it.first]++;
                if (over[it.first] == 1)
                {
                    ofstream fout;
                    fout.open(std::to_string(it.first) + ".txt", std::ios_base::app);
                    fout << "??"
                         << " " << it.first << "overflow" << over[it.first] << ".txt\n";
                }
                else if (over[it.first] > 1)
                {
                    ofstream fout;
                    fout.open(std::to_string(it.first) + "overflow" + std::to_string(over[it.first] - 1) + ".txt", std::ios_base::app);
                    fout << "??"
                         << " " << it.first << "overflow" << over[it.first] << ".txt\n";
                }
            }

            ofstream fout;
            fout.open(std::to_string(it.first) + "overflow" + std::to_string(over[it.first]) + ".txt", std::ios_base::app);
            string word;
            fstream fin;
            fin.open(std::to_string(it.first) + "overflow" + std::to_string(over[it.first]) + ".txt", ios::in);
            int f = 0;
            while (fin >> word)
            {
                if (word == "%%")
                    f = 1;
            }
            fin.close();
            if (f == 0)
                fout << "%%\n";
            fout.close();
        }
        else
        {
            string word;
            fstream fin;
            fin.open(std::to_string(it.first) + ".txt", ios::in);
            int f = 0;
            while (fin >> word)
            {
                if (word == "%%")
                    f = 1;
            }
            fin.close();
            ofstream fout;
            fout.open(std::to_string(it.first) + ".txt", std::ios_base::app);
            if (f == 0)
                fout << "%%\n";

            fout.close();
        }
    }
}
void storeboundaryedge()
{
    map<int, set<pair<int, int>>> buffer;
    for (auto it2 : edgemap)
    {

        int flag = 0;
        int cell1;
        int cell2;
        cell1 = findcellofnode(it2.second.n1);
        cell2 = findcellofnode(it2.second.n2);
        if (cell1 != cell2 && cell1 != -1)
        {

            if (buffer[cell1].find({it2.second.n1, it2.second.n2}) == buffer[cell1].end())
                buffer[cell1].insert({it2.second.n1, it2.second.n2});
            else
                flag = 1;

            if (flag == 1)
                continue;
            if (record[cell1] >= B || over[cell1] != 0)
            {

                if (record[cell1] >= B)
                {

                    record[cell1] = 0;
                    over[cell1]++;
                    if (over[cell1] == 1)
                    {
                        ofstream fout;
                        fout.open(std::to_string(cell1) + ".txt", std::ios_base::app);
                        fout << "??"
                             << " " << cell1 << "overflow" << over[cell1] << ".txt\n";
                    }
                    else if (over[cell1] > 1)
                    {
                        ofstream fout;
                        fout.open(std::to_string(cell1) + "overflow" + std::to_string(over[cell1] - 1) + ".txt", std::ios_base::app);
                        fout << "??"
                             << " " << cell1 << "overflow" << over[cell1] << ".txt\n";
                    }
                }

                ofstream fout;
                fout.open(std::to_string(cell1) + "overflow" + std::to_string(over[cell1]) + ".txt", std::ios_base::app);

                fout << it2.second.n1 << " " << it2.second.n2
                     << " < " << it2.second.l << " > \n";
                edgesincell[cell1].push_back({it2.second.n1, it2.second.n2, it2.second.l});
                record[cell1]++;

                fout.close();
            }
            else
            {

                ofstream fout;
                fout.open(std::to_string(cell1) + ".txt", std::ios_base::app);

                fout << it2.second.n1 << " " << it2.second.n2
                     << " < " << it2.second.l << " > \n";
                edgesincell[cell1].push_back({it2.second.n1, it2.second.n2, it2.second.l});
                record[cell1]++;

                fout.close();
            }
            if (record[cell2] >= B || over[cell2] != 0)
            {

                if (record[cell2] >= B)
                {

                    record[cell2] = 0;
                    over[cell2]++;
                    if (over[cell2] == 1)
                    {
                        ofstream fout;
                        fout.open(std::to_string(cell2) + ".txt", std::ios_base::app);
                        fout << "??"
                             << " " << cell2 << "overflow" << over[cell2] << ".txt\n";
                    }
                    else if (over[cell2] > 1)
                    {
                        ofstream fout;
                        fout.open(std::to_string(cell2) + "overflow" + std::to_string(over[cell2] - 1) + ".txt", std::ios_base::app);
                        fout << "??"
                             << " " << cell2 << "overflow" << over[cell2] << ".txt\n";
                    }
                }

                ofstream fout;
                fout.open(std::to_string(cell2) + "overflow" + std::to_string(over[cell2]) + ".txt", std::ios_base::app);

                fout << it2.second.n1 << " " << it2.second.n2
                     << " < " << it2.second.l << " > \n";
                record[cell2]++;

                fout.close();
            }
            else
            {

                ofstream fout;
                fout.open(std::to_string(cell2) + ".txt", std::ios_base::app);

                fout << it2.second.n1 << " " << it2.second.n2
                     << " < " << it2.second.l << " > \n";
                record[cell2]++;

                fout.close();
            }
        }
    }
}
void visualizer(int n)
{
    int cell;
    for (auto it1 : nodecellmap)
    {
        if (it1.first == n)
        {
            for (auto it2 : celldata)
            {
                if (it1.second.t11.x == it2.second.t11.x && it1.second.t11.y == it2.second.t11.y && it1.second.t22.x == it2.second.t22.x && it1.second.t22.y == it2.second.t22.y)
                    cell = it2.first;
            }
        }
    }
    fstream fin;
    fin.open(std::to_string(cell) + ".txt", ios::in);
    if (fin.is_open())
        std::cout << fin.rdbuf();
    cout << "\n";
    fin.close();
    fstream fin2;
    fin2.open(std::to_string(cell) + ".txt", ios::in);
    int k = 0;
    string word;
    while (fin2 >> word)
    {

        if (word == "??")
            k++;
    }
    fin2.close();
    while (k != 0)
    {
        int k1 = 0;
        fstream fin1;
        cout << k << "\n";
        fin1.open(std::to_string(cell) + "overflow" + std::to_string(k) + ".txt", ios::in);
        if (fin1.is_open())
            std::cout << fin1.rdbuf();
        cout << "\n";
        fin1.close();
        fstream fin2;
        fin2.open(std::to_string(cell) + "overflow" + std::to_string(k) + ".txt", ios::in);
        string word1;
        while (fin2 >> word1)
        {
            if (word1 == "??")
            {
                k++;
                k1 = 1;
            }
        }
        fin2.close();
        if (k1 == 0)
            k = 0;
    }
}
int nodecelldata(int node)
{
    for (auto it : nodecellmap)
    {
        if (it.first == node)
        {
            for (auto it2 : celldata)
            {
                if (it.second.t11.x == it2.second.t11.x && it.second.t11.y == it2.second.t11.y)
                {
                    return it2.first;
                }
            }
        }
    }
}
void nodesincellfunction()
{
    for (auto it : nodecellmap)
    {
        for (auto it2 : celldata)
        {
            if (it.second.t11.x == it2.second.t11.x && it.second.t11.y == it2.second.t11.y)
            {
                nodesincell[it.first] = it2.first;
                break;
            }
        }
    }
}
/*void boundarynodesincellfunction()
{

    for (auto it : eachcell)
    {
        vector<int> nodes;
        for (auto it2 : edgemap)
        {
            if (truecell(it2.second.n1, it.first))
            {
                if (!truecell(it2.second.n2, it.first))
                {
                    nodes.push_back(it2.second.n2);
                }
            }
        }
        boundarynodesincell[it.first] = nodes;
    }
}
*/
/*void edgesincellfunction()
{
    for (auto it : eachcell)
    {
        vector<nodesedge> edges;
        for (auto it2 : edgemap)
        {
            if (truecell(it2.second.n1, it.first))
            {
                nodesedge n1 = {it2.second.n1, it2.second.n2, it2.second.l};
                edges.push_back(n1);
            }
        }
        edgesincell[it.first] = edges;
    }
}
*/
void makegraph(int srccell, int srcnode)
{
    map<int, int> nodes;
    for (auto it : nodesincell)
    {
        if (it.second == srccell)
        {
            nodes[it.first]++;
        }
    }
    for (auto it : boundarynodesincell)
    {
        if (it.first == srcnode)
        {
            for (auto it2 : it.second)
            {
                nodes[it2]++;
            }
        }
    }
    /*for (auto it : nodes)
    {
        cout << it.first << ",";
    }
    cout << "\n";
    for (auto it : edgesincell)
    {
        if (it.first == srccell)
        {
            for (auto it2 : it.second)
            {
                cout << it2.n1 << " , " << it2.n2 << " --> " << it2.l << endl;
            }
        }
    }
    */
    for (auto it : nodes)
    {
        for (auto it2 : edgesincell)
        {
            if (it2.first == srccell)
            {
                for (auto it3 : it2.second)
                {
                    if (it3.n1 == it.first)
                        graphrep[it.first].push_back(make_pair(it3.n2, it3.l));
                }
            }
        }
    }
    /*cout << "----------------------------------------------\n";
    for (auto it : graphrep)
    {
        cout << it.first << "-->";
        for (auto it2 : it.second)
        {
            cout << "(" << it2.first << "," << it2.second << ") ";
        }
        cout << endl;
    }
    cout << "----------------------------------------------\n";
    */
}
void adjacencylist()
{
    cout << "----------------------------------------------\n";
    cout << "Adjacency List Formed is :\n";
    for (auto it : graphrep)
    {
        cout << it.first << "-->";
        for (auto it2 : it.second)
        {
            cout << "(" << it2.first << "," << it2.second << ") ";
        }
        cout << endl;
    }
    cout << "----------------------------------------------\n";
}
bool cmp(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b)
{
    return a.second.second < b.second.second;
}
void dijkstra(int srcnode, int destnode)
{
    inputlist.clear();
    outputlist.clear();
    graphrep.clear();
    cellbuffer.clear();
    int k = srcnode;
    double l;
    /*int srccell = nodecelldata(srcnode);

    makegraph(srccell, srcnode);
    cellbuffer.insert(srccell);
    */
    outputlist[srcnode] = {0, -1};

    l = 0;
    int g = 0;
    while (k != destnode)
    {
        
        double min = INT_MAX;
        int srccell = nodecelldata(k);
        if (cellbuffer.find(srccell) == cellbuffer.end() && k != -1)
        {
            makegraph(srccell, k);
            //cout<<k<<" : "<<srccell<<endl;

            cellbuffer.insert(srccell);
        }

        for (auto it : graphrep)
        {
            if (it.first == k)
            {
                for (auto it2 : it.second)
                {
                    int flag = 0;
                    for (auto it3 : inputlist)
                    {
                        if (it3.first == it2.first && it3.second.second <= it2.second + l)
                            flag = 1;
                    }
                    if (flag == 0)
                        inputlist[it2.first] = {it.first, it2.second + l};
                }
            }
        }
        if(inputlist.empty())
        {
            g=1;
            break;
        }
        //cout<<"InputList--------------\n";
        for (auto it : inputlist)
        {
            if (it.second.second < min)
                min = it.second.second;

            //cout<<it.first<<"--> ("<<it.second.first<<","<<it.second.second<<")\n";
        }

        for (auto it : inputlist)
        {
            if (it.second.second == min)
            {
                int flag = 0;
                for (auto it2 : outputlist)
                {
                    //if (it2.first == it.first && it2.second.second > it.second.second)
                    //    flag = 1;
                    if (it2.first == it.first && it2.second.second <= it.second.second)
                        flag = 1;
                }
                if (flag == 0)
                {
                    outputlist[it.first] = {it.second.first, it.second.second};
                    k = it.first;
                    l = it.second.second;
                    inputlist.erase(it.first);
                }
                else if (flag == 1)
                {
                    k = -1;
                    l = 0;
                    inputlist.erase(it.first);
                }

                break;
            }
        }
        /*cout<<"Output List--------------------\n";
        for (auto it : outputlist)
                {
                    cout<<it.first<<"--> ("<<it.second.first<<","<<it.second.second<<")\n";
                }
                */
    }
    if (g == 1)
    {
        cout << "No Path Exist\n";
    }
    else
    {
        
        adjacencylist();
        cout << "Length Of The Path Is = " << l << endl;
        vector<int> path;
        while (k != srcnode)
        {
            path.push_back(k);
            for (auto it : outputlist)
            {
                if (it.first == k)
                {
                    k = it.second.first;
                    break;
                }
            }
        }
        path.push_back(k);
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size() - 1; i++)
        {
            cout << path[i] << "-->";
        }
        cout << path[path.size() - 1] << "\n";
        cout << "Number Of Cells Brought From Secondary Memory to Main Memory are : ";
        int number = 0;
        for (auto it : cellbuffer)
        {
            cout << it << " ";
            number++;
        }
        cout << endl;
        cout << "Total : " << number << "\n";
        
    }
}
int main()
{
    cout << "Enter size of one block (B)\n";
    cin >> B;
    min_cordinates.x = INT_MAX;
    min_cordinates.y = INT_MAX;
    max_cordinates.x = INT_MIN;
    max_cordinates.y = INT_MIN;
    fstream fin1;
    fin1.open("nodes1.txt", ios::in);
    string node1;
    string x_coordinate1;
    string y_coordinate1;
    int no1;
    double x_co1, y_co1;
    if (!fin1.good())
    {
        cout << "Error\n";
        exit(1);
    }

    while (fin1.good())
    {

        getline(fin1, node1, ' ');
        getline(fin1, x_coordinate1, ' ');
        getline(fin1, y_coordinate1, '\n');
        no1 = getvalint(node1);
        x_co1 = getvaldouble(x_coordinate1);
        y_co1 = getvaldouble(y_coordinate1);
        points t9 = {x_co1, y_co1};
        nodedata[no1] = t9;

        if (x_co1 < min_cordinates.x)
            min_cordinates.x = x_co1;
        if (y_co1 < min_cordinates.y)
            min_cordinates.y = y_co1;
        if (x_co1 > max_cordinates.x)
            max_cordinates.x = x_co1;
        if (y_co1 > max_cordinates.y)
            max_cordinates.y = y_co1;
    }
    cout << "min cordinates : {" << setprecision(15) << min_cordinates.x << "," << min_cordinates.y << "}\n";
    cout << "max cordinates : {" << setprecision(15) << max_cordinates.x << "," << max_cordinates.y << "}\n";
    fin1.close();
    double k;
    cout << "Enter the value of k\n";
    cin >> k;

    points t7 = findcoordinates(k, k);
    cout << "After Extension..............\n";
    cout << "min cordinates : {" << setprecision(15) << min_cordinates.x << "," << min_cordinates.y << "}\n";
    cout << "max cordinates : {" << setprecision(15) << t7.x << "," << t7.y << "}\n";

    mapnodecell();
    mapedges();

    storenodes();

    storehash();

    storeedgesn1n2();
    //storeedgesn2n1();

    storestar();

    storeboundarynodes1();
    storeboundarynodes2();

    storepercent();
    storeboundaryedge();
    nodesincellfunction();
    //boundarynodesincellfunction();
    //edgesincellfunction();
    char choice;
    cout << "Do you want to view any file ( Y/N )\n";
    cin >> choice;
    while (choice != 'N')
    {

        int n;
        cout << "Enter node to view it's file\n";
        cin >> n;
        visualizer(n);
        cout << "Do you want to view any file ( Y/N )\n";
        cin >> choice;
    }
    char choice2;
    cout << "Do you want to run Dijkstra (Y/N)\n";
    cin >> choice2;
    while (choice2 != 'N')
    {
        cout << "Enter Src Node and Dest Node\n";
        int srcnode, destnode;
        cin >> srcnode >> destnode;

        dijkstra(srcnode, destnode);

        cout << "Do you want to again run Dijkstra (Y/N)\n";
        cin >> choice2;
    }
}
