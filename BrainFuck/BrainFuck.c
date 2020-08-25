#include <stdio.h>
#include <string.h>

char program[1024], paper[1024];
int ptr = 0, stack[1024], sp = 0;

void run(char *name);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("BrainFuck: expect 2 argumentsi, found %d", argc);
	} else {
		if (strcmp(argv[1], "--help") == 0) {
			puts("BrainFuck v1.0\n");
			puts("+\t++ptr");
			puts("-\t--ptr");
			puts(">\t++*ptr");
			puts("<\t--*ptr");
			puts(".\tputchar(*ptr)");
			puts(",\t*ptr=getch()");
			puts("[\twhile(*ptr){");
			puts("]\t}");
		} else if (strcmp(argv[1], "--version") == 0) {
			puts("BrainFuck v1.0");
		} else {
			run(argv[1]);
		}
	}
	return 0;
}

void run(char *name) {
	FILE *fp = fopen(name, "r");
	if (fp == NULL) {
		printf("BrainFuck: file '%s' not found\n", name);
	} else {
		/* read file */
		for (int i = 0; i <= 1023; ++i) {
			if (!feof(fp)) {
				program[i] = fgetc(fp);
			} else {
				program[i + 1] = '\0';
			}
		}
		/* start */
		int size = 0, pc = 0;
		for (; program[size] != '\0'; ++size);
		for (;pc < size; ++pc) {
			if (!sp && program[pc] == ']') {
				puts("BrainFuck: sp is zero");
				break;
			}
			switch (program[pc]) {
				case '+' :
					++paper[ptr];
					break;
				case '-':
					--paper[ptr];
					break;
				case '[':
					stack[sp] = pc;
					++sp;
					break;
				case ']':
					pc = paper[ptr] ? stack[sp - 1] : pc;
					sp -= (!paper[ptr]);
					break;
				case ',':
					scanf("%c", &paper[ptr]);
					break;
				case '.':
					printf("%c", paper[ptr]);
					break;
			}
			if (ptr >= 1024 || ptr < 0) {
				puts("BrainFuck: paper out of range");
				break;
			}
			if (sp >= 1024) {
				puts("BrainFuck: sp out of range");
				break;
			}
		}
	}
	return;
}
