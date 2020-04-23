#include <boost/mpl/list.hpp>

#include "solution.hpp"

Solution::Solution() {
}

Solution::~Solution() {
}

std::vector<std::string> Solution::AlmostEquivalentStrings(std::vector<std::string>& s, std::vector<std::string>& t) {
    std::vector<std::string> res;

    int n = s.size();
    if(n != t.size()) {
        return res;
    }

    for(int i=0; i<n; i++) {
        std::map<char, int> dict;

        for (char const &c: s.at(i)) {
            dict[c] += 1;
        }

        for (char const &c: t.at(i)) {
            dict[c] -= 1;
        }

        bool flag = true;
        for(std::map<char, int>::value_type& x : dict) {
            if (std::abs(x.second) > 3) {
                flag = false;
                break;
            }
        }

        if (flag) {
            res.push_back("YES");
        } else {
            res.push_back("NO");
        }
    }

    return res;
}

int Solution::IdenticalDistribution(int n, std::vector<int>& snacks) {
    int i, d, ans=n, M=*std::max_element(snacks.begin(),snacks.end());
    std::vector<int>cnt(M+1,0);
    for(i=0; i<n; i++) {
        cnt[snacks[i]]++;
    }

    for(d=2; d<=M; d++)
    {
        int s=0;
        for(i=0; i<=M&&s<ans; i++) {
            s+=cnt[i]*((d-(i%d))%d);
        }
        ans=std::min(ans, s);
    }
    return ans;
}

int Solution::AutoscalePolicy(int ins, int n, std::vector<int>& ticks) {
    int cur = 0;
    while(cur < n) {
        int tick = ticks.at(cur);
        if(tick > 60 && ins <= 2e8){
            ins *= 2;
            cur += 10;
        }else if(tick < 25 && ins > 1) {
            ins /= 2;
            cur += 10;
        }else {
            cur += 1;
            continue;
        }
        cur += 1;
    }
    return ins;
}

int Solution::FactorOf3And5(int l, int r) {
    const float log3 = std::log(3), log5 = std::log(5) ;
    int cnt = 0;
    int xlo = 0, xup = int(std::log(r)/log3);

    for(int x=xlo; x<=xup; x++) {
        int ylo = int((std::log(r)-x*log3)/log5);
        int yup = int((std::log(r)-x*log3)/log5)+1;
        for(int y=ylo; y<=yup; y++) {
            float calc = std::pow(3, x) * std::pow(5, y);
            if(calc <= r && calc >= l) {
                cnt += 1;
            }
        }
    }
    return cnt;
}

namespace AscendingBinarySorting {
    int _getBitCount(int num) {
        int cnt = 0;
        while(num) {
            if(num & 1 == 1) { cnt++; }
            num = num >> 1;
        }
        return cnt;
    }

    int _compare(int num1, int num2) {
        int cnt1 = _getBitCount(num1);
        int cnt2 = _getBitCount(num2);
        if(cnt1 < cnt2) {
            return 1;
        } else if (cnt1 == cnt2) {
            if (num1 <= num2) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}

std::vector<int> Solution::AscendingBinarySorting(std::vector<int>& nums) {
    using namespace AscendingBinarySorting;
    std::vector<int> res(nums);;
    std::sort(res.begin(), res.end(), _compare);
    return res;
}

namespace ConnectingComputers {
    int _find(std::unordered_map<int, std::pair<int, int>>& parents, int node) {
        // If not in parend yet, set it
        if (parents.find(node) == parents.end()) {
            parents[node] = {node, 1};
            return node;
        }

        while (node != parents.at(node).first) {
            node = parents.at(node).first;
        }
        return node;
    }
    
    void _union(std::unordered_map<int, std::pair<int, int>>& parents, int nodeA, int nodeB, int& redundantConns) {
        int parentA = _find(parents, nodeA);
        int parentB = _find(parents, nodeB);
        // If same parent, no need to union, count redundant connections
        if (parentA == parentB) {
            ++redundantConns;
            return;
        }

        // Union
        if (parents.at(parentA).second >= parents.at(parentB).second) {
            parents.at(parentB).first = parentA;
            parents.at(parentA).second += parents.at(parentB).second;
        } else {
            parents.at(parentA).first = parentB;
            parents.at(parentB).second += parents.at(parentA).second;
        }
    }
}

int Solution::ConnectingComputers(int nNodes, int nEdges, std::vector<int>& nodeF, std::vector<int>& nodeT) {
    using namespace ConnectingComputers; 
    int redundantConns = 0;
    // Parents, key is child node ID, value is a pair of (parent node ID, number of children of this parent)
    std::unordered_map<int, std::pair<int, int>> parents;
    for (int i=1; i<=nNodes; i++) {
        parents[i] = {i, 1};
    }
    
    for (int i=0; i<nEdges; i++) {
        _union(parents, nodeF.at(i), nodeT.at(i), redundantConns);
    }

    std::set<int> indParts;
    for (auto& p : parents) {
        indParts.insert(_find(parents, p.second.first));
    }

    if (redundantConns >= indParts.size() - 1) {
        return (indParts.size() - 1);
    }
    return -1;
}

namespace CircularArray {
    void _increment_counter(int prev, int post, std::vector<int>& counter) {
        if (prev < post) {
            for (int i=prev; i<=post; i++) {
                counter[i] += 1;
            }
        } else if (prev > post) {
            for (int i=0; i<=prev; i++) {
                counter[i] += 1;
            }
            for (int i=post; i<counter.size(); i++) {
                counter[i] += 1;
            }
        } else {
            return;
        }
        return;
    }
}

int Solution::CircularArray(int n, int m, std::vector<int>& endNode) {
    using namespace CircularArray;
    std::vector<int> cnt(n, 0);
    for (int i=0; i<m-2; i++) {
        _increment_counter(endNode.at(i), endNode.at(i+1), cnt);
    }

    int res = 1, tmpcnt = 0;
    for (int i=0; i<cnt.size(); i++) {
        if (cnt.at(i) > tmpcnt) {
            tmpcnt = cnt.at(i);
            res = i;
        } else if (cnt.at(i) == tmpcnt) {
            if (res > i) {
                res = i;
            }
        } else {
            continue;
        }
    }
    return res;
}

namespace BucketFill {
    int _find(std::unordered_map<int, int>& parents, int point) {
        // If not in parend yet, set it
        if (parents.find(point) == parents.end()) {
            parents[point] = point;
            return point;
        }

        while (point != parents.at(point)) {
            point = parents.at(point);
        }
        return point;
    }

    void _union(std::unordered_map<int, int>& parents, int pointA, int pointB) {
        int parentA = _find(parents, pointA);
        int parentB = _find(parents, pointB);
        // If same parent, no need to union
        if (parentA == parentB) { return; }

        // Union
        if (parentA <= parentB) {
            parents.at(parentB) = parentA;
        } else {
            parents.at(parentA) = parentB;
        }
    }

    int _getPointFromRowCol(int row, int col, int ncol) {
        return row*ncol+col;
    }

    std::pair<int, int> _getRowColFromPoint(int point, int ncol) {
        int row = point/ncol, col = point%ncol;
        std::pair<int, int> rcPair = {row, col};
        return rcPair;
    }
}

int Solution::BucketFill(std::vector<std::string>& picture) {
    using namespace BucketFill;
    int nrow = picture.size();
    if (nrow == 0) {
        return 0;
    }
    int ncol = picture.at(0).size();
    // Parents, key is point ID from row and col, value is point ID for its parent point
    std::unordered_map<int, int> parents;
    for (int i=0; i<nrow; i++) {
        for (int j=0; j<ncol; j++) {
            int point = _getPointFromRowCol(i, j, ncol);
            parents[point] = point;
        }
    }
    
    for (int i=0; i<nrow; i++) {
        for (int j=0; j<ncol; j++) {
            int u=i-1, d=i+1, l=j-1, r=j+1;
            int point = _getPointFromRowCol(i, j, ncol);
            if (u>=0 && picture.at(i).at(j) == picture.at(u).at(j)) {
                int otherPoint = _getPointFromRowCol(u, j, ncol);
                _union(parents, point, otherPoint);
            }
            if (d<nrow && picture.at(i).at(j) == picture.at(d).at(j)) {
                int otherPoint = _getPointFromRowCol(d, j, ncol);
                _union(parents, point, otherPoint);
            }
            if (l>=0 && picture.at(i).at(j) == picture.at(i).at(l)) {
                int otherPoint = _getPointFromRowCol(i, l, ncol);
                _union(parents, point, otherPoint);
            }
            if (r<ncol && picture.at(i).at(j) == picture.at(i).at(r)) {
                int otherPoint = _getPointFromRowCol(i, r, ncol);
                _union(parents, point, otherPoint);
            }
        }
    }

    std::set<int> colorSet;
    for (auto& p : parents) {
        colorSet.insert(_find(parents, p.second));
    }

    return colorSet.size();
}

int Solution::Enigma(int rotorCount, int minRotorValue, int maxRotorValue) {
    long long int cnt = 0;
    std::unordered_map<int, int> gcdMap;
    for (int i=minRotorValue; i<=maxRotorValue; i++)
    {
        for (int j = minRotorValue; j <= maxRotorValue; j++)
        {
            if (std::__gcd(i, j) == 1)
                gcdMap[i]++;
        }
    }

    for (auto it=gcdMap.begin(); it!=gcdMap.end(); it++) {
        cnt += pow(it->second, rotorCount-1);
    }
    return cnt;
}

std::string Solution::OscillatingString(std::string s) {
    std::string res;
    std::unordered_map<char, int> cntMap;
    for (auto c: s) {
        cntMap[c] += 1;
    }

    std::vector<std::pair<char, int>> charVec;
    for (auto &e: cntMap) {
        charVec.push_back({e.first, e.second});
    }
    std::sort(charVec.begin(), charVec.end());

    bool flag = true;
    while (res.size() != s.size()) {
        if (flag) {
            for (auto it=charVec.begin(); it != charVec.end(); it++) {
                if ((*it).second > 0) {
                    res.push_back((*it).first);
                    (*it).second -= 1; 
                }
            }
        } else {
            for (auto it=charVec.rbegin(); it != charVec.rend(); it++) {
                if ((*it).second > 0) {
                    res.push_back((*it).first);
                    (*it).second -= 1; 
                }
            }
        }
        flag = !flag;
    }
    return res;
}

namespace QuickSort {
    template <typename T> int _partition(std::vector<T>& nums, int lo, int hi) {
        int pivot = nums[hi];
        int mid = lo - 1;
        for (int i = lo; i <= hi - 1; i++) {
            if (nums[i] < pivot) {
                mid++;
                std::swap(nums[mid], nums[i]);
                }
        }
        std::swap(nums[mid+1], nums[hi]);
        return (mid+1);
    }

    template <typename T> void _quickSort(std::vector<T>& nums, int lo, int hi) {
        if (lo < hi) {
            int mid = _partition<T>(nums, lo, hi);
            _quickSort<T>(nums, lo, mid-1);
            _quickSort<T>(nums, mid+1, hi);
        }
    }
}

template <typename T> void Solution::QuickSort(std::vector<T>& nums) {
    int n = nums.size();
    QuickSort::_quickSort<T>(nums, 0, n-1);
}
