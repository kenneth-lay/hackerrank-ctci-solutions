#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int n;
int m;
int count_connected_cells = 0;
int max_connected_cells = 0;

void dfs_trace(vector< vector<int> >& grid, int py, int px) {
	if (py < 0 || px < 0 || py > n - 1 || px > m - 1 || grid[py][px] == 0) return;
	else {
		grid[py][px] = 0;	// sub-root
		count_connected_cells = count_connected_cells + 1;
		dfs_trace(grid, py, px - 1);
		dfs_trace(grid, py + 1, px - 1);
		dfs_trace(grid, py + 1, px);
		dfs_trace(grid, py + 1, px + 1);
		dfs_trace(grid, py, px + 1);
		dfs_trace(grid, py - 1, px + 1);
		dfs_trace(grid, py - 1, px);
		dfs_trace(grid, py - 1, px - 1);
	}
}

int get_biggest_region(vector< vector<int> >& grid) {
	for (int py = 0; py < n; py++) {
		for (int px = 0; px < m;) {
			if (grid[py][px] == 0) px++;
			else {
				grid[py][px] = 0;	// root
				count_connected_cells = count_connected_cells + 1;
				dfs_trace(grid, py, px - 1);
				dfs_trace(grid, py + 1, px - 1);
				dfs_trace(grid, py + 1, px);
				dfs_trace(grid, py + 1, px + 1);
				dfs_trace(grid, py, px + 1);
				dfs_trace(grid, py - 1, px + 1);
				dfs_trace(grid, py - 1, px);
				dfs_trace(grid, py - 1, px - 1);
				if (count_connected_cells > max_connected_cells) {
					max_connected_cells = count_connected_cells;
				}
				count_connected_cells = 0;
			}
		}
	}
	return max_connected_cells;
}

int main(){
    cin >> n;
    cin >> m;
    vector< vector<int> > grid(n,vector<int>(m));
    for(int grid_i = 0;grid_i < n;grid_i++){
       for(int grid_j = 0;grid_j < m;grid_j++){
          cin >> grid[grid_i][grid_j];
       }
    }
    cout << get_biggest_region(grid) << endl;
    return 0;
}
