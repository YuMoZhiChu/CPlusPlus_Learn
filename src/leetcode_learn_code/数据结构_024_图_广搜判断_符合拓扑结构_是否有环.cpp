// 力扣
// https://leetcode-cn.com/problems/course-schedule/
// 图相关
// 广搜和深搜 2 种做法
// 使用出度和入度的两种做法

#include<vector>
using std::vector;

#include<stack>
using std::stack;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> edges(numCourses, vector<int>());
        vector<int> in_record(numCourses, 0);
        for (auto &pq:prerequisites)
        {
            edges[pq[1]].push_back(pq[0]); // 记录 a -> b
            ++in_record[pq[0]]; // 入度+1
        }
        stack<int> can_visit;
        for (int i = 0; i < numCourses; ++i)
        {
            if (in_record[i] == 0) can_visit.push(i);
        }

        // 广搜做法
        int has_visited = 0;
        while(!can_visit.empty())
        {
            ++has_visited;
            int it = can_visit.top();
            can_visit.pop();
            for (int unlock:edges[it])
            {
                --in_record[unlock];
                if (in_record[unlock] == 0)
                {
                    can_visit.push(unlock);
                }
            }
        }

        return has_visited == numCourses;
    }
};