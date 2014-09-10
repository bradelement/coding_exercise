#include "cstdio"
#include "cstring"

char input[32][16];
unsigned int pc;
unsigned char accu;
unsigned char memory[32];

unsigned char get_num(char *s) {
    unsigned char ret = 0;
    while (*s) {
        ret = ret * 2 + *s - '0';
        s++;
    }
    return ret;
}

bool init() {
    if (!gets(input[0])) return false;
    for (int i=1; i<32; i++) {
        gets(input[i]);
    }
    for (int i=0; i<32; i++) {
        memory[i] = get_num(input[i]);
    }
    pc = 0;
    accu = 0;
    return true;
}

int t(unsigned char c) {
    return c >> 5;
}

bool execute() {
    bool halt = false;
    int cur = pc;
    pc++;
    pc &= 0x1F;
    if (t(memory[cur]) == 0) {
        memory[memory[cur] & 0x1F] = accu;
    }
    else if (t(memory[cur]) == 1) {
        accu = memory[memory[cur] & 0x1F];
    }
    else if (t(memory[cur]) == 2) {
        if (accu == 0) {
            pc = memory[cur] & 0x1F;
        }
    }
    else if (t(memory[cur]) == 3) {
        ;
    }
    else if (t(memory[cur]) == 4) {
        accu--;
    }
    else if (t(memory[cur]) == 5) {
        accu++;
    }
    else if (t(memory[cur]) == 6) {
        pc = memory[cur] & 0x1F;
    }
    else if (t(memory[cur]) == 7) {
        halt = true;
    }

    return halt;
}

void gao() {
    while (1) {
        bool halt = execute();
        if (halt) break;
    }
}

void print(unsigned char accu) {
    for (int i=0; i<8; i++) {
        printf("%c", (accu & (1<<(7-i))) ? '1' : '0');
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    while (1) {
        bool ret = init();
        if (!ret) break;
        gao();
        print(accu);
    }
    return 0;
}