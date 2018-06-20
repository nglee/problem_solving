#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int m_ = m - 1;
    int n_ = n;
    int index[20];
    int i = 0;
    do {
        n_ /= 2;
        int q = n_ * n_;
        index[i++] = m_ / q;
        m_ %= q;
    } while (n_ > 1);

    //for (int j = 0; j < i; j++)
    //    printf("%d ", index[j]);
    //printf("\n");

    // i 개의 element in array index

    // case 1 : top -> right -> down
    //  0:    : right -> top -> left
    //  1:    : top -> right -> down
    //  2:    : top -> right -> down
    //  3:    : left -> down -> right

    // case 2 : right -> top -> left
    //  0:    : top -> right -> down
    //  1:    : right -> top -> left
    //  2:    : right -> top -> left
    //  3:    : down -> left -> top

    // case 3 : left -> down -> right
    //  0:    : down -> left -> top
    //  1:    : left -> down -> right
    //  2:    : left -> down -> right
    //  3:    : top -> right -> down

    // case 4 : down -> left -> top
    //  0:    : left -> down -> right
    //  1:    : down -> left -> top
    //  2:    : down -> left -> top
    //  3:    : right -> top -> left

    int cur_case = 1;
    int x = 1, y = 1;

    n_ = n;
    int j = 0;
    do {
        n_ = n_ / 2;

        int idx = index[j++];

        switch (cur_case) {
        case 1:
            switch (idx) {
            case 0:
                cur_case = 2;
                break;
            case 1:
                y += n_;
                cur_case = 1;
                break;
            case 2:
                x += n_;
                y += n_;
                cur_case = 1;
                break;
            case 3:
                x += n_;
                cur_case = 3;
                break;
            }
            break;
        case 2:
            switch (idx) {
            case 0:
                cur_case = 1;
                break;
            case 1:
                x += n_;
                cur_case = 2;
                break;
            case 2:
                x += n_;
                y += n_;
                cur_case = 2;
                break;
            case 3:
                y += n_;
                cur_case = 4;
                break;
            }
            break;
        case 3:
            switch (idx) {
            case 0:
                x += n_;
                y += n_;
                cur_case = 4;
                break;
            case 1:
                y += n_;
                cur_case = 3;
                break;
            case 2:
                cur_case = 3;
                break;
            case 3:
                x += n_;
                cur_case = 1;
                break;
            }
            break;
        case 4:
            switch (idx) {
            case 0:
                x += n_;
                y += n_;
                cur_case = 3;
                break;
            case 1:
                x += n_;
                cur_case = 4;
                break;
            case 2:
                cur_case = 4;
                break;
            case 3:
                y += n_;
                cur_case = 2;
                break;
            }
            break;
        }

    } while (n_ > 1);

    printf("%d %d\n", x, y);
    //scanf("%d", &n);
}