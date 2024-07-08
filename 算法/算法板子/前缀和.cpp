#include<bits/stdc++.h>

template<typename T>
class PrefixSumArray{
    /**
     *  sum[0] = 0, sum[1], sum[2], ... , sum[a.size()]
     *           a[0]     a[1]   a[2] a[a.size() - 1]
     *  于是a[i] + ... + a[j] = sum[j + 1] - sum[i]
    */
    public:
        std::vector<T> sum;
        void resize(long long int length){
            this->sum.resize(length + 1);
        }
        PrefixSumArray(){
            resize(0);
            sum[0] = 0;
        }
        PrefixSumArray(long long int length){
            resize(length);
            sum[0] = 0;
        }
        PrefixSumArray(const std::vector<T> &a){
            resize(a.size());
            sum[0] = 0;
            for(long long int i = 1 ; i <= (long long int)a.size() ; ++i){
                sum[i] = sum[i - 1] + a[i - 1];
            }
        }
        
        T &operator[](const T index){
            assert(index >= 0);
            return sum[index + 1];
        }

        /**
         * 获取[left, right]之间的元素之和
        */
        T get_closed_sum(long long int left, long long int right){
            assert(left >= 0);
            assert(right + 1 < (long long int)this->sum.size());
            assert(left <= right);
            return this->sum[right + 1] - this->sum[left];
        }

        /**
         * 获取[left, right)之间的元素之和
        */
        T get_sum(long long int left, long long int right){
            return get_closed_sum(left, right - 1);
        }

        void push_back(T value){
            sum.push_back(sum.back() + value);
        }

        long long int length(){
            return (long long int)sum.size() - 1;
        }
};