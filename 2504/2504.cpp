#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <stack>
#include <climits>
#include <cstring>

using namespace std;

#define lp UINT_MAX      // '('
#define lb UINT_MAX - 1U // '['

std::stack<unsigned int> st;

bool is_number(unsigned int val)
{
    return val != lp && val != lb;
}

bool pop_until_lp()
{
    bool ret = true;

    bool loop = true;
    unsigned int cur_val = 0U;
    while (loop) {
        if (st.empty()) {
            ret = false;
            break;
        }
        unsigned int top = st.top();
        switch (top) {
        case lb:
            ret = false;
            loop = false;
            break;
        case lp:
            st.pop();
            if (cur_val)
                st.push(cur_val * 2U);
            else
                st.push(2U);
            loop = false;
            break;
        default:
            st.pop();
            cur_val += top;
        }
    }
    return ret;
}

bool pop_until_lb()
{
    bool ret = true;

    bool loop = true;
    unsigned int cur_val = 0U;
    while (loop) {
        if (st.empty()) {
            ret = false;
            break;
        }
        unsigned int top = st.top();
        switch (top) {
        case lp:
            ret = false;
            loop = false;
            break;
        case lb:
            st.pop();
            if (cur_val)
                st.push(cur_val * 3U);
            else
                st.push(3U);
            loop = false;
            break;
        default:
            st.pop();
            cur_val += top;
        }
    }

    return ret;
} 

int main()
{
    bool valid = true;

    char in[31];
    memset(in, 0, 31);
    scanf("%30s", in);
    char *c = in; // 문자열의 길이는 1 이상

    do {
        switch (*c) {
        case '(':
            st.push(lp);
            break;
        case '[':
            st.push(lb);
            break;
        case ')':
            valid = pop_until_lp();
            break;
        case ']':
            valid = pop_until_lb();
            break;
        default:
            valid = false;
        }
    } while (valid && *++c);

    unsigned int ans = 0U;
    while (!st.empty()) {
        unsigned int top = st.top();
        if (!is_number(top)) {
            valid = false;
            break;
        }
        ans += top;
        st.pop();
    }

    if (valid)
        printf("%u\n", ans);
    else
        printf("0\n");
}