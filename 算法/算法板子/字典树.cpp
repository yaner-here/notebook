#include<bits/stdc++.h>

typedef struct Trie{

    struct TrieNode {
        std::map<char, long long int> next{{}};
        long long int is_full_word{0};          // 完全匹配的单词总数
        long long int word_count{0};            // 其子树之下包含的完整单词数
    };

    std::vector<TrieNode> tree{{{}, false}};

    long long int insert(const std::string &str){
        long long int pointer = 0;
        for(long long int i = 0 ; i < (long long int)str.size() ; ++i){
            if(tree[pointer].next.find(str[i]) == tree[pointer].next.end()){
                tree[pointer].next[str[i]] = tree.size();
                tree.push_back({{}, false, 0});
            }
            tree[pointer].word_count++;
            pointer = tree[pointer].next[str[i]];
        }
        tree[pointer].word_count++;
        tree[pointer].is_full_word++;
        return pointer;
    }

    long long int insert(const char *str, long long int length){
        long long int pointer = 0;
        for(long long int i = 0 ; i < (long long int)length ; ++i){
            if(tree[pointer].next.find(str[i]) == tree[pointer].next.end()){
                tree[pointer].next[str[i]] = tree.size();
                tree.push_back({{}, false, 0});
            }
            tree[pointer].word_count++;
            pointer = tree[pointer].next[str[i]];
        }
        tree[pointer].word_count++;
        tree[pointer].is_full_word++;
        return pointer;
    }

    /**
     *  查询某个前缀的结束节点在字典树中的位置
     *  @return -1 前缀不在字典树中
     *          >=0 结束节点在字典树中的位置
    */
    long long int __get_trienode_index(const std::string &str){
        long long int pointer = 0;
        for(long long int i = 0 ; i < (long long int)str.size() ; ++i){
            if(tree[pointer].next.find(str[i]) == tree[pointer].next.end()){
                return -1;
            }
            pointer = tree[pointer].next[str[i]];
        }
        return pointer;
    }

    /**
     *  查询某个完整单词是否属于字典树的单词
     *  @return bool
     */
    bool find_full_word(const std::string &str){
        long long int pointer = 0;
        for(long long int i = 0 ; i < (long long int)str.size() ; ++i){
            if(tree[pointer].next.find(str[i]) == tree[pointer].next.end()){
                return false;
            }
            pointer = tree[pointer].next[str[i]];
        }
        return tree[pointer].is_full_word > 0;
    }

    bool find_full_word(const char *str, long long int length){
        long long int pointer = 0;
        for(long long int i = 0 ; i < (long long int)length ; ++i){
            if(tree[pointer].next.find(str[i]) == tree[pointer].next.end()){
                return false;
            }
            pointer = tree[pointer].next[str[i]];
        }
        return tree[pointer].is_full_word > 0;
    }

    /**
     *  查询某个长前缀包含了多少完整的短单词(经过了多少叶子节点)
     *  @return -1 长前缀不在字典树中
     *          >=0 该长前缀经过的叶子节点个数
     */
    long long int get_word_chain_count(const std::string &str){ 
        long long int pointer = 0, counter = 0;
        for(long long int i = 0 ; i < (long long int)str.size() ; ++i){
            if(tree[pointer].next.find(str[i]) == tree[pointer].next.end()){
                return -1;
            }
            if(tree[pointer].is_full_word > 0){
                counter++;
            }
            pointer = tree[pointer].next[str[i]];
        }
        if(tree[pointer].is_full_word > 0){
            counter++;
        }
        return counter;
    }

    /**
     *  查询某个前缀是否在字典树中
     *  @return bool
    */
    bool find_prefix(const std::string &str){
        long long int pointer = 0;
        for(long long int i = 0 ; i < (long long int)str.size() ; ++i){
            if(tree[pointer].next.find(str[i]) == tree[pointer].next.end()){
                return false;
            }
            pointer = tree[pointer].next[str[i]];
        }
        return true;
    }

    /**
     *  查询有多少个完整单词以该前缀开头
     *  @return long long int
    */
    long long int get_prefix_word_count(const std::string &str){
        long long int trienode_index = __get_trienode_index(str);
        if(trienode_index == -1){
            return 0;
        }
        return tree[trienode_index].word_count;
    }

    /**
     *  查询为了确定一个完整单词所需要的最短前缀
     *  @return std::string
    */
    std::string get_word_shortest_prefix(const std::string &str){
        long long int pointer = 0, i;
        for(i = 0 ; i < (long long int)str.length() ; ++i){
            pointer = tree[pointer].next[str[i]];
            // std::cout << str[i];
            if(tree[pointer].word_count == 1){
                break;
            }
        }
        return str.substr(0, i + 1);
    }
}Trie;