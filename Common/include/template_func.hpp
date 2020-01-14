//
// Created by Administrator on 2019/12/26 0026.
//

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

#define DEFAULT_SEP "-"

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
vector<pair<K, V>> sortMapByValue(const map<K, V> &m, bool reverse)
{
    vector<pair<K, V>> vec(m.begin(), m.end());
    if (reverse){
        sort(vec.begin(), vec.end(), CmpByValue<K, V>());
    } else{
        sort(vec.rbegin(), vec.rend(), CmpByValue<K, V>());
    }
    return vec;
}

template <unsigned long N, typename T>
string arrayToString(const array<T, N> &arr, const string& separator=DEFAULT_SEP)
{
    string res;
    ostringstream oss;
    if (!arr.empty())
    {
        for (auto &ele: arr)
        {
            oss.str("");
            oss << ele;
            res.append(oss.str()).append(separator);
        }
        res.erase(res.size() - 1);
    }
    return res;
}

template <typename T>
string vecToString(const vector<T>& vec, const string& separator="-")
{
    string res;
    ostringstream oss;
    if (!vec.empty())
    {
        for (auto &ele: vec)
        {
            oss.str("");
            oss << ele;
            res.append(oss.str()).append(separator);
        }
        res.erase(res.size() - 1);
    }
    return res;
}


template <typename T>
int compareEleOneByOne(const vector<T> &vec0, const vector<T> &vec1)
{
    int size0 = vec0.size();
    int size1 = vec1.size();
    int size = min(size0, size1);
    for (int i = 0; i < size;  i++)
    {
        if (vec0.at(i) > vec1.at(i))
        {
            return 1;
        } else if (vec0.at(i) < vec1.at(i)){
            return -1;
        }
    }
    return 0;
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
