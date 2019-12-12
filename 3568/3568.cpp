#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

int main()
{
	char base[120];
	char part[120];

	scanf("%119s", base);

	bool cont = true;
	while (cont) {
		scanf("%119s", part);
		size_t l = strlen(part);
		if (part[l - 1] == ';') {
			cont = false;
		}
		l--; // , 와 ; 필요 없음

		int outidx = 0;
		char out[120];
		while (l--) {
			char c = part[l];

			if ('A' <= c && c <= 'Z' || 'a' <= c && c <= 'z') {
				part[l + 1] = 0;
				out[outidx++] = ' ';
				strcpy(&out[outidx], part);
				break;
			}

			out[outidx++] = c;
			if (c == '[') {
				out[outidx - 1] = ']';
				out[outidx - 2] = '[';
			}
		}

		printf("%s%s;\n", base, out);
	}
}