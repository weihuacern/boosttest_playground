#include<algorithm> 
#include<vector>

#include "solution.hpp"

Solution::Solution() {
}

Solution::~Solution() {
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
