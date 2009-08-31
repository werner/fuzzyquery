char *translate_fuzzy_preds(char *result,const char *field,const char *value);

char *create_fuzzy_pred(const char *name,
                       const char *begin,const char *end,
                       const char *min,
                       const char *core1,const char *core2,
                       const char *max);

char *drop_fuzzy_pred(const char *name);

int ScanKeyword(const char *keyword);

typedef struct Keyword
{
    const char *name;	/* name of keyword */
    int         value;	/* value of keyword */
} Keyword;
