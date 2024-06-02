# ACM

# §1 STL

## §1.1 `<iomainip>`

众所周知，在 `algorithm` 库中有一个 `max` 函数，但你不知道的是 `ISO c++11` 中 `max` 可以接受多个参数，前提是要用中括号括起来，如：

```cpp
int a = max({9, 9, 12, 97301, 937});
```

还有，`printf` 支持输出保留小数点位数的数，但是很多人不知道 `cout` 也可以，但是需要包含头文件 `iomanip`，代码：

```cpp
cout << fixed << setprecision(位数) << 值;
```

## §1.2 `<algorithm>`

### §1.2.1 `std::sort()`

`std::sort(Iterator begin, Iterator end)`默认从小到大排序。

### §1.2.2 `std::lower_bound()`

`std::lower_bound(Iterator begin, Iterator end, T value)`要求迭代器必须从小到大排列，找到第一个大于等于`value`的位置，并返回这个位置的迭代器，



BFS板子：

```c++
    long long int x, y; std::cin >> x >> y;
    bool visited[50][50]; std::fill(visited[0], visited[0] + 50 * 50, false);
    std::queue<std::pair<long long int, long long int>> queue; queue.push({x, y});
    long long int distance = 0;

    while(!queue.empty()){
        long long int size = queue.size();
        while(size--){
            std::pair<long long int, long long int> current = queue.front(); queue.pop();
            if(isInRange(...)){ // 如果数组下标越界就退出
            	continue;
            }
            if(visited[current.first][current.second]){ // 如果已经访问过就退出
                continue;
            }
            visited[current.first][current.second] = true;
            if(current.first == 1 && current.second == 1){ // 如果找到目标点(1,1)
                std::cout << distance << '\n';
                return;
            }

			queue.push({current.first + 2, current.second + 1});
			// ......
			queue.push({current.first + 2, current.second + 1});
        }
        distance++;
    }
```

