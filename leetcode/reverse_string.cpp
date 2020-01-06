// https://leetcode.com/problems/reverse-string/

class Solution {
public:
    void reverseString(vector<char>& s) {
        if (s.size() == 0)
            return;
        
        int n = 0;
        while(n < s.size()-1)
        {  
            vector<char>::iterator it = s.begin();
            s.insert(it+n, s.back());
            //cout << s.back() << endl;
            s.pop_back();
            ++n;
        }
    }
};