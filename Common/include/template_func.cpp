//
// Created by Administrator on 2019/12/26 0026.
//

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Count elements of a vector
 * @tparam T
 * @param list
 * @return
 */
template <typename T>
map<T, int> countVecEle(const vector<T> &list){
    map<T, int> resMap;
    for (auto ele : list)
    {
        if (!resMap.count(ele)){
            resMap[ele] = 1;
        } else{
            resMap[ele] += 1;
        }
    }
    return resMap;
}


template <class K, class V>
struct CmpByValue {
    bool operator()(const pair<K, V> &p1, const pair<K, V> &p2) {
        return p1.second == p2.second ? p1.first > p2.first : p1.second > p2.second;
    }
};


template <typename K, typename V>
vector<pair<K, V>> sortMapByValue(map<K, V> &m, bool reverse)
{
    vector<pair<K, V>> vec(m.begin(), m.end());
    if (reverse){
        sort(vec.begin(), vec.end(), CmpByValue<K, V>());
    } else{
        sort(vec.rbegin(), vec.rend(), CmpByValue<K, V>());
    }
    return vec;
}


template <typename K, typename V>
void printMap(const map<K, V> &m)
{
    if (m.size() > 0){
        cout << "Map {";
        for (auto &entry : m)
        {
            cout << entry.first << ":" << entry.second << ", ";
        }
        cout << "}" << endl;
    }
}

template <typename K, typename V>
void printPairVector(const vector<pair<K, V>> &vec)
{
    if (vec.size() > 0){
        cout << "Pair vector [";
        for (auto &p : vec)
        {
            cout << "[" << p.first << "," << p.second << "]" << ", ";
        }
        cout << "]" << endl;
    }
}
