# include <stdio.h>
# include <string.h>
# include <stdlib.h>

#define bool char
#define true 1
#define false 0


char stack[1000];

bool isValid(char* s) {
	// char* stack = (char*)malloc(sizeof(s));
	// initial -1
	int top_stack = -1;
	for (int i = 0; s[i] != '\0'; i++) {
		printf("%c %d\n", s[i], top_stack);
		switch (s[i]) {
		case ']':
			// stack is NOT empty && stack[top] == sth.
			if (top_stack >= 0 && stack[top_stack] == '[') {
				top_stack--;
				break;
			}
			else
				return false;
		case ')':
			if (top_stack >= 0 && stack[top_stack] == '(') {
				top_stack--;
				break;
			}
			else
				return false;
		case '}':
			if (top_stack >= 0 && stack[top_stack] == '{') {
				top_stack--;
				break;
			}
			else
				return false;

		case '[':
		case '(':
		case '{':
			stack[++top_stack] = s[i];
			break;

		}
	}
	printf("????%c %d\n", s[0], top_stack);
	if (top_stack == -1)
		return true;
	return false;
}


int main() {
	char a[] = "0123456789";
	a[7] = '\0';
	char* b = (char*)malloc(sizeof(a));
	strcpy(b, a);
	printf("Hello World %d|%s|     |%d|%s|", sizeof(a), a, sizeof(*b), b);
	printf("\n\n");

	char s[] = "[]";
	printf("isValid: %d", isValid(s));

}