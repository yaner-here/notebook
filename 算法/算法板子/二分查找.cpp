bool valid(int x){
	return ...;
}

int left = 0, right = 9;
int left_pointer = left - 1, right_pointer = right + 1; // 若while()不满足，则直接返回区间外的数，表示查找失败
while(left <= right) {
    int mid = (left + right) / 2;
    if(valid(mid)) {
        left_pointer = mid;
        left = mid + 1;
    } else {
        right_pointer = mid;
        right = mid - 1;
    }
}
std::cout << left_pointer << '\n';
std::cout << right_pointer << '\n';