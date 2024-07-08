#include<bits/stdc++.h>

template<typename T>
class BinaryTree{
    static const long long int NPOS = -1;
    struct Node{
        long long int left{NPOS}, right{NPOS}, depth{0};
        T value{0};
    };
    public:
        typedef const enum {IGNORE_EQUAL, LEFTWARD_EQUAL, RIGHTWARD_EQUAL} HEAP_INSERT_MODE;
        std::vector<Node> nodes;
        long long int node_count = 0;
        long long int depth = 0;
        explicit BinaryTree(long long int n){
            nodes.resize(n);
        }
        void preorder_traversal(long long int root, const std::function<void(T)> &lambda){
            if(root == NPOS){
                return;
            }
            lambda(nodes[root].value);
            preorder_traversal(nodes[root].left, lambda);
            preorder_traversal(nodes[root].right, lambda);
        }
        void inorder_traversal(long long int root, const std::function<void(T)> &lambda){
            if(root == NPOS){
                return;
            }
            inorder_traversal(nodes[root].left, lambda);
            lambda(nodes[root].value);
            inorder_traversal(nodes[root].right, lambda);
        }
        void postorder_traversal(long long int root, const std::function<void(T)> &lambda){
            if(root == NPOS){
                return;
            }
            postorder_traversal(nodes[root].left, lambda);
            postorder_traversal(nodes[root].right, lambda);
            lambda(nodes[root].value);
        }
        void make_heap(T value, HEAP_INSERT_MODE mode = IGNORE_EQUAL){
            long long int depth = 1;
            if(node_count <= 0){
                node_count++;
                nodes[0].value = value;
                nodes[0].depth = depth; this->depth = std::max(this->depth, depth);
                return;
            }
            long long int root_index = 0;
            while(true){
                bool is_equal = (nodes[root_index].value == value);
                bool is_greater = (nodes[root_index].value < value);
                bool is_less = (nodes[root_index].value > value);
                depth++;
                if(mode == IGNORE_EQUAL && is_equal){
                    return;
                }else if((mode == RIGHTWARD_EQUAL && is_equal) || (is_greater)){
                    if(nodes[root_index].right == NPOS){
                        nodes[root_index].right = node_count;
                        root_index = node_count;
                        nodes[root_index].value = value;
                        nodes[root_index].depth = depth; this->depth = std::max(this->depth, depth);
                        node_count++;
                        break;
                    }else{
                        root_index = nodes[root_index].right;
                    }
                }else if((mode == LEFTWARD_EQUAL && is_equal) || (is_less)){
                    if(nodes[root_index].left == NPOS){
                        nodes[root_index].left = node_count;
                        root_index = node_count;
                        nodes[root_index].value = value;
                        nodes[root_index].depth = depth; this->depth = std::max(this->depth, depth);
                        node_count++;
                        break;
                    }else{
                        root_index = nodes[root_index].left;
                    }
                }
            }
        }
};