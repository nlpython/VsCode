#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int main()
{
    double sum = 0;
    double cost[10][4];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> cost[i][j];
            if (j == 0) {
                sum += cost[i][j];
            }
        }

    }
    // 最短时间
    double res = INT_MAX;
    // 最短时间对应的顺序
    vector<int> resSort(10);
    int sort[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    do{
        double process[4];
        process[0] = cost[sort[0]][0];
        for (int i = 1; i < 4; i++) {
            process[i] = process[i - 1] + cost[sort[0]][i];
        }

        for (int i = 1; i < 10; i++)
        {
            int now = sort[i];
            // 前缀和
            double preSum[4];
            preSum[0] = cost[now][0];
            for (int j = 1; j < 4; j++) {
                preSum[j] = preSum[j - 1] + cost[now][j];
            }

            double distance[4] = {100000.0, 0.0, 0.0, 0.0};
            for (int j = 1; j < 4; j++) {
                distance[j] = distance[j - 1] + cost[now][j - 1];
            }
            // for (int j = 0; j < 4; j++) {
            //     distance[j] += preSum[j];
            // }
            // 找最小值
            double minDis = distance[0] - process[0];
            // 标志位
            int sign = 0;
            for (int j = 1; j < 4; j++) {
                if (distance[j] - process[j] < minDis) {
                    minDis = distance[j] - process[j];
                    sign = j;
                }
            }
            process[sign] += cost[now][sign];
            // 各过程时间累加
            for (int j = 0; j < 4; j++) {
                if (j == sign) {
                    continue;
                }
                process[j] = process[sign] + (preSum[j] - preSum[sign]);
            }
        }
        // 更新结果
        if (process[3] < res) {
            res = process[3];
            for (int k = 0; k < 10; k++) {
                resSort[k] = sort[k] + 1;
            }

        }

    } while (next_permutation(sort, sort + 10));

    cout << "最短总耗时: " << res << endl;
    cout << "顺序:\n";
    for (int i = 0; i < 10; i++) {
        cout << resSort[i] << " ";
    }
    return 0;
    
}