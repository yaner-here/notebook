#include<bits/stdc++.h>

/* 大理石在哪儿 UVa 10474 */
void example_5_1(){
    long long int i = 0;
    while(true){
        long long int n, q; std::cin >> n >> q;
        if(n == 0 && q == 0){
            return;
        }
        i++;
        std::cout << "CASE# " << i << ":\n";

        std::vector<long long int> number; number.resize(n);
        for(long long int i = 0 ; i < n ; ++i){
            std::cin >> number[i];
        }
        
        std::sort(number.begin(), number.end());
        while(q--){
            long long int temp; std::cin >> temp;
            long long int index = std::lower_bound(number.begin(), number.end(), temp) - number.begin();
            if(number[index] == temp){
                std::cout << temp << " found at " << index + 1 << "\n";
            }else{
                std::cout << temp << " not found\n";
            }
        }
    }
}

/* 木块问题 UVa 101 */
// void example_5_2(){
//     long long int n; std::cin >> n;
    
//     std::vector<std::vector<long long int>> lists; lists.resize(n); 
//     std::vector<long long int> position; position.resize(n);
//     for(long long int i = 0 ; i < n ; ++i){
//         lists[i].push_back(i);
//         position[i] = i;
//     }
    
//     auto findPosition = [](std::vector<long long int> position, long long int a) -> long long int {
//         return position[a];
//     };

//     auto returnBack = [](std::vector<std::vector<long long int>> &lists, std::vector<long long int> &position, std::function<long long int(std::vector<long long int> position, long long int a)> findPosition, long long int a) -> void {
//         long long int currentPosition = findPosition(position, a);
//         auto iter = std::find(lists[currentPosition].begin(), lists[currentPosition].end(), a);
//         for(iter ; iter != lists[currentPosition].end() ; iter++){
//             // lists[value].push_back(value);
//             // position[value] = value;
//         }
//     };

//     auto moveOnto = [](std::vector<std::vector<long long int>> &lists, std::vector<long long int> position, std::function<void(std::vector<std::vector<long long int>>, std::vector<long long int>, long long int)> returnBack, long long int a, long long int b){
//         returnBack(lists, position, a);
//         returnBack(lists, position, b);
//         lists[a].push_back(b);
//         lists[a].clear();
//     };

//     auto moveOver = [](std::vector<std::vector<long long int>> &lists, std::vector<long long int> position, std::function<void(std::vector<std::vector<long long int>>, std::vector<long long int>, long long int)> returnBack, long long int a, long long int b){
//         returnBack(lists, position, a);
//         lists[a].clear();
//         lists[b].push_back(a);
//     };

//     auto pileOnto = [](std::vector<std::vector<long long int>> &lists, std::vector<long long int> position, std::function<void(std::vector<std::vector<long long int>>, std::vector<long long int>, long long int)> returnBack, long long int a, long long int b){
//         returnBack(lists, position, b);
//         lists[a].clear();
//         lists[b].push_back(a);
//     };

//     while(n--){
//         std::string action_1, action_2; long long int a, b; std::cin >> action_1 >> a >> action_2 >> b;
//         if(a == b){
//             continue;
//         }    
//         if(action_1 == "move" && action_2 == "onto"){

//         }
//     }
// }

/* 安迪的第一个字典 Uva 10815 */
void example_5_3(){
    std::string temp;
    std::set<std::string> dict;
    while(std::cin >> temp){
        for(long long int i = 0 ; i < temp.length() ; ++i){
            temp[i] = std::tolower(temp[i]);
        }
        dict.insert(temp);
    }
    for(std::string value : dict){
        std::cout << value << "\n";
    }
}

int main(){
    example_5_3();
}