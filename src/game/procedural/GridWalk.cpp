#include <queue>
#include <iostream>
#include "GridWalk.hpp"

using std::vector;

void GridWalk::generateDistanceField(vector<vector<int>> &base, vector<vector<int>> &field, int x, int y)
{
	int nx = base.size(), ny = base[0].size();
	for(auto &i : field) for(int &j : i) j = -1;
	std::queue<std::pair<int, int>> q;
	q.push(std::make_pair(x, y));
	field[x][y] = 0;

	while(!q.empty())
	{
		auto curCheck = q.front();
		int cx = curCheck.first, cy = curCheck.second;
		q.pop();

		for(int dx = -1; dx < 2; dx++) for(int dy = -1; dy < 2; dy++) if(dx != 0 || dy != 0)
		{
			int fx = cx + dx, fy = cy + dy;
			if(fx >= 0 && fy >= 0 && fx < nx && fy < ny && base[fx][fy] != 15)
			{
				if(field[fx][fy] == -1 || field[fx][fy] > field[cx][cy] + 1)
				{
					field[fx][fy] = field[cx][cy] + 1;
					q.push(std::make_pair(fx, fy));
				}
			}
		}
	}
}

void GridWalk::createRegions(vector<vector<int>> &field, vector<vector<int>> &regions,
							 vector<vector<std::pair<int, int>>> regionList)
{
	int nx = field.size(), ny = field[0].size();
	for(auto &i : regions) for(int &j : i) j = -1;

	int nRegions = 0;
	std::queue<std::pair<int, int>> q;

	for(int i = 0; i < nx; i++) for(int j = 0; j < ny; j++) if(field[i][j] != -1 && regions[i][j] == -1)
	{
		int curRegion = field[i][j];
		q.push(std::make_pair(i, j));
		regionList.push_back(vector<std::pair<int, int>>());
		regions[i][j] = nRegions;

		while(!q.empty())
		{
			auto curCoords = q.front();
			q.pop();
			int x = curCoords.first, y = curCoords.second;
			regionList[nRegions].push_back(std::make_pair(x, y));

			for(int dx = -1; dx < 2; dx++) for(int dy = -1; dy < 2; dy++) if(dx != 0 || dy != 0)
			{
				int fx = x + dx, fy = y + dy;
				if(fx >= 0 && fy >= 0 && fx < nx && fy < ny && field[fx][fy] == curRegion && regions[fx][fy] == -1)
				{
					q.push(std::make_pair(fx, fy));
					regions[fx][fy] = nRegions;
				}
			}
		}

		nRegions++;
	}
}