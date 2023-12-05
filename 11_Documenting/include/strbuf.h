typedef struct {
    char *data;
    int len;
    int allocated;
    int realloc_step;
} strbuf;

strbuf *create_strbuf();
void delete_strbuf(strbuf *buf);
void strbuf_maybe_realloc_to_fit(strbuf *buf, const int len_to_fit);
void strbuf_append(strbuf *buf, const char *str);
void strbuf_append_substr(strbuf *buf, const char *str, const int from, const int to);
