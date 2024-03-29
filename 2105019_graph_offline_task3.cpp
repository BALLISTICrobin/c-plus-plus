#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <climits>
#include <algorithm>
#include <cmath>
using namespace std;

int shortestPath(pair<int, int> source, pair<int, int> destination)
{
    vector<vector<int>> distance(101, vector<int>(101, INT_MAX));
    map<pair<int, int>, bool> visited;
    if (source == destination)
    {
        return 0;
    }
    queue<pair<int, int>> q;
    q.push(source);
    visited[source] = true;
    distance[source.first][source.second] = 0;

    while (!q.empty())
    {
        pair<int, int> current = q.front();
        q.pop();
        int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

        for (int i = 0; i < 8; ++i)
        {
            int x = current.first + dx[i];
            int y = current.second + dy[i];

            if (x >= 0 && x < 8 && y >= 0 && y < 8 && !visited[{x, y}])
            {
                visited[{x, y}] = true;
                distance[x][y] = distance[current.first][current.second] + 1;
                q.push({x, y});
            }
        }
        if (distance[destination.first][destination.second] != INT_MAX)
            return distance[destination.first][destination.second];
    }

    return distance[destination.first][destination.second];
}

int main(int argc, char const *argv[])
{
    freopen("graphinput.txt", "r", stdin);
    freopen("graphOutput.txt", "w", stdout);
    int test =3;
    while(test--){
    int n, m, q,c=0;
    cin >> n >> m >> q;
    vector<pair<pair<int, int>, int>> knights;
    for (int i = 0; i < q; i++)
    {
        int riderPos_x, riderPos_y, k;
        cin >> riderPos_x >> riderPos_y >> k;
        if(k!=1){
            c++;
        }
        if (riderPos_x >= m || riderPos_y >= n)
        {
            cout << -1 << endl;
            return 1;
        }
        knights.push_back({{riderPos_x, riderPos_y}, k});
    }

    int sumOfMove = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            vector<int> move;

            for (int k = 0; k < q; k++)
            {
                int numOfMoves = shortestPath(knights[k].first, {j, i});
                if (numOfMoves != INT_MAX)
                    move.push_back(ceil(numOfMoves * 1.0 / knights[k].second));
                // if(knights[k].second!=1)
                // move.push_back(1);
            }
            int sum = 0;

            if(c!=0 && move.size()+1==q){
                while (!move.empty())
            {
                sum += move.back();
                move.pop_back();
            }
            sum++;
            }
            else{
                while (!move.empty())
            {
                sum += move.back();
                move.pop_back();
            }
            }
            

            if (sum != 0)
                sumOfMove = min(sumOfMove, sum);
        }
    }

    if (sumOfMove != INT_MAX)
        cout << sumOfMove << endl;
    else
        cout << -1 << endl;
    }
    return 0;
}
