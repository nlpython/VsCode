#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int main()
{
    // double cost[10][4] = {
    //     13.28403, 14.9621, 19.846, 20.012922,
    //     9.87088, 19.9075, 17.9282, 18.942358,
    //     20.0584, 15.9726, 14.9704, 15.116388,
    //     7.98865, 9.93665, 5.93587, 18.128398,
    //     8.77006, 13.722, 13.0052, 11.24949,
    //     19.0741, 20.0944, 14.1485, 13.883878,
    //     11.1601, 16.4961, 12.0137, 19.087604,
    //     16.0201, 8.82748, 18.1144, 16.831394,
    //     15.0146, 12.0351, 7.04191, 8.949654,
    //     12.9524, 7.01098, 9.04917, 16.052406};
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
    vector<int> signs;
    vector<double> outTimes(10);
    int sort[10] = {4, 7, 8, 1, 2, 6, 3, 5, 9, 10};

    double process[4];
    process[0] = cost[sort[0] - 1][0];
    for (int i = 1; i < 4; i++) {
        process[i] = process[i - 1] + cost[sort[0] - 1][i];
    }
    outTimes[0] = process[3];
    for (int i = 1; i < 10; i++)
    {
        int now = sort[i] - 1;
        // 前缀和
        double preSum[4];
        preSum[0] = cost[now][0];
        for (int j = 1; j < 4; j++) {
            preSum[j] = preSum[j - 1] + cost[now][j];
        }

        double distance[4] = {10000.0, 10000.0, 10000.0, 10000.0};
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
        signs.push_back(sign);
        process[sign] += cost[now][sign];
        // 各过程时间累加
        for (int j = 0; j < 4; j++) {
            if (j == sign) {
                continue;
            }
            process[j] = process[sign] + (preSum[j] - preSum[sign]);
            if (j == 3 && i == 9) {
                cout << process[3] << " ";
                cout << process[sign] << " " << (preSum[j] - preSum[sign]) << endl;
            }
        }
        outTimes[i] = process[3];
    }
    for (int i = 0; i < 10; i++) {
        resSort[i] = sort[i];
    }
    res = process[3];
    // 计算进入CJ1的时间和离开CJ4的时间
    vector<double> inTimes(10);
    inTimes[0] = 0;
    for (int i = 1; i < 10; i++)
    {
        inTimes[i] = inTimes[i - 1] + cost[resSort[i - 1] - 1][0];
    }
    cout << "最短总耗时: " << res << endl;
    cout << "顺序\t" << "CJ1\t" << "CJ4\n";
    for (int i = 0; i < 10; i++) {
        cout << resSort[i] << "\t" << inTimes[i] << "\t" << outTimes[i] << endl;
    }
    for (auto n : signs) {
        cout << n << " ";
    }
    return 0;
}
