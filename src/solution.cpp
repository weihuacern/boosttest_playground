#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

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

// Helper function
int getBitCount(int num) {
    int cnt = 0;
    while(num) {
        if(num & 1 == 1) {
            cnt++;}
        num = num >> 1;
    }
    return cnt;
}

// Helper function
int compare(int num1, int num2) {
    int cnt1 = getBitCount(num1);
    int cnt2 = getBitCount(num2);
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

std::vector<int> Solution::AscendingBinarySorting(std::vector<int>& nums) {
    std::vector<int> res(nums);;
    std::sort(res.begin(), res.end(), compare);
    return res;
}

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

int Solution::ConnectingComputers(int nNodes, int nEdges, std::vector<int>& nodeF, std::vector<int>& nodeT) {
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

void increment_counter(int prev, int post, std::vector<int>& counter) {
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

int Solution::CircularArray(int n, int m, std::vector<int>& endNode) {
    std::vector<int> cnt(n, 0);
    for (int i=0; i<m-2; i++) {
        increment_counter(endNode.at(i), endNode.at(i+1), cnt);
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

int Solution::BucketFill(std::vector<std::string>& picture) {
    return 1;
}