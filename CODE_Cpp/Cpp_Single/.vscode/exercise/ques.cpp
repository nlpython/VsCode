#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<double> head({66.972699, 65.718154, 65.246949, 41.231134, 45.809782, 66.216707, 57.886455, 58.948118, 42.366238, 44.601401}); 
    vector<double> every({19.686986, 19.642140, 19.840489, 17.876612, 13.468906, 19.840489, 18.895515, 17.869124, 14.780628, 15.930722});
    vector<int> need({10, 5, 6, 10, 12, 16, 18, 8, 6, 9});
    double times = 0;  //单位:分钟
    for (int i = 0; i < 10; i++) {
        double first = head[i];
        double others = (need[i] * 100 - 1) * every[i];
        times += (first + others);
    }
    // 化为小时
    double hours = times / 60.0;
    // 化为天
    double days = hours / 16;
    cout << days;
    return 0;
}