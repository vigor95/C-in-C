#include "util.h"

char* scan_for_out(int argc, char *argv[]) {
    int i;
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0)
            return argv[i + 1];
    }
    return NULL;
}

char** get_files_from_argv(int argc, char *argv[]) {
    return NULL;
}

int get_filesize(char *filename) {
    FILE *f = fopen(filename, "r");
    fseek(f, 0, SEEK_END);
    return ftell(f);
}

void* xmalloc(int size) {
    register void *value = malloc(size);
    if (value == NULL) {
        fprintf(stderr, "Virtual memory exhausted!\n");
        exit(1);
    }
    return value;
}

char fcpeek(FILE *f) {
    char c = getc(f);
    ungetc(c, f);
    return c;
}

char* getword(FILE *f) {
    int i = 0;
    char c;
    char *word;
    int pos;
    size_t size = 0;

    if (fcpeek(f) == EOF) {
        return NULL;
    }

    pos = ftell(f);
    c = getc(f);
    if (c == '\n') {
        total_newlines++;
    }

    while (c != EOF && !isspace(c)) {
        if (c == '\"') {
            size++;
            c = getc(f);
            while (c != '\"') {
                if (c == '\n') {
                    error("file-not-known(feature-incomplete)", total_newlines, 0, "Badly formatted string!\n");
                }
                size++;
                c = getc(f);
            }
        }
        size++;
        c = getc(f);
        if (c == '\n') {
            total_newlines++;
        }
    }
    fseek(f, -(ftell(f) - pos), SEEK_CUR);
    word = (char*)xmalloc(sizeof(char) * size + 1);
    c = getc(f);

    while (c != EOF && !isspace(c) && i < size) {
        if (c == '\"') {
            word[i++] = c;
            c = getc(f);
            word[i] = c;
            while (c != '\"' && i < size) {
                word[i++] = c;
                c = getc(f);
            }
        }
        word[i++] = c;
        c = getc(f);
    }
    word[size] = '\0';

    return word;
}

char* wordpeek(FILE *f) {
    return NULL;
}

void file_error(char *prog, char *do_this, char *ifilename, char *specifics, char *msg) {
    fprintf(stderr, "%s: cannot %s %s (%s):\n""%s.\n", prog, do_this, ifilename, specifics, msg);
    exit(EXIT_FAILURE);
}

char* strip_whitesp(char *str) {
    return 0;
}

char* copy_alloced(char *s) {
    char *t = (char*)xmalloc(sizeof(char) * strlen(s));
    strcpy(t, s);
    return t;
}

int get_column(FILE *f) {
    int cur_pos = ftell(f);
    int offset = 0;
    char c = fcpeek(f);

    while (c != '\n' && ftell(f) > 0 && c != EOF) {
        fseek(f, -1, SEEK_CUR);
        offset++;
        c = fcpeek(f);
    }
    fseek(f, cur_pos, SEEK_CUR);
    return offset;
}

int intlit_comp(const void *a, const void *b) {
    if (*(int*)a > *(int*)b) return 1;
    if (*(int*)a < *(int*)b) return -1;
    return 0;
}

int floatlit_comp(const void *a, const void *b) {
    if (*(double*)a > *(double*)b) return 1;
    if (*(double*)a < *(double*)b) return -1;
    return 0;
}

char* cstr(char *s) {
    char *tmp = (char*)xmalloc(sizeof(char) * strlen(s) + 1);
    strcpy(tmp, s);
    return tmp;
}

int token_num(char *token) {
    int i;
    for (i = 0; i < strlen(token); i++) {
        if (token[i] == ',')
            return 2;
    }
    return 1;
}
