#ifndef Ta3_TOKENIZER_H
#define Ta3_TOKENIZER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"

/* Tokenizer interface */

#include "../Include/token.h"

#define MAXINDENT 100   /* Max indentation level */

enum decoding_state {
    STATE_INIT,
    STATE_RAW,
    STATE_NORMAL        /* have a codec associated with input */
};

/* Tokenizer state */
struct tok_state {
    /* Input state; buf <= cur <= inp <= end */
    /* NB an entire line is held in the buffer */
    char *buf;          /* Input buffer, or NULL; malloc'ed if fp != NULL */
    char *cur;          /* Next character in buffer */
    char *inp;          /* End of data in buffer */
    char *end;          /* End of input buffer if buf != NULL */
    char *start;        /* Start of current token if not NULL */
    int done;           /* E_OK normally, E_EOF at EOF, otherwise error code */
    /* NB If done != E_OK, cur must be == inp!!! */
    FILE *fp;           /* Rest of input; NULL if tokenizing a string */
    int tabsize;        /* Tab spacing */
    int indent;         /* Current indentation index */
    int indstack[MAXINDENT];            /* Stack of indents */
    int atbol;          /* Nonzero if at begin of new line */
    int pendin;         /* Pending indents (if > 0) or dedents (if < 0) */
    const char *prompt, *nextprompt;          /* For interactive prompting */
    int lineno;         /* Current line number */
    int level;          /* () [] {} Parentheses nesting level */
            /* Used to allow free continuations inside them */
    /* Stuff for checking on different tab sizes */
#ifndef PGEN
    /* pgen doesn't have access to Python codecs, it cannot decode the input
       filename. The bytes filename might be kept, but it is only used by
       indenterror() and it is not really needed: pgen only compiles one file
       (Grammar/Grammar). */
    PyObject *filename;
#endif
    int altindstack[MAXINDENT];         /* Stack of alternate indents */
    /* Stuff for PEP 0263 */
    enum decoding_state decoding_state;
    int decoding_erred;         /* whether erred in decoding  */
    int read_coding_spec;       /* whether 'coding:...' has been read  */
    char *encoding;         /* Source encoding. */
    int cont_line;          /* whether we are in a continuation line. */
    const char* line_start;     /* pointer to start of current line */
#ifndef PGEN
    PyObject *decoding_readline; /* open(...).readline */
    PyObject *decoding_buffer;
#endif
    const char* enc;        /* Encoding for the current str. */
    const char* str;
    const char* input; /* Tokenizer's newline translated copy of the string. */

    /* async/await related fields; can be removed in 3.7 when async and await
       become normal keywords. */
    int async_def;        /* =1 if tokens are inside an 'async def' body. */
    int async_def_indent; /* Indentation level of the outermost 'async def'. */
    int async_def_nl;     /* =1 if the outermost 'async def' had at least one
                             NEWLINE token after it. */
    int async_always;     /* =1 if async/await are always keywords */
};

extern struct tok_state *Ta3Tokenizer_FromString(const char *, int);
extern struct tok_state *Ta3Tokenizer_FromUTF8(const char *, int);
extern struct tok_state *Ta3Tokenizer_FromFile(FILE *, const char*,
                                              const char *, const char *);
extern void Ta3Tokenizer_Free(struct tok_state *);
extern int Ta3Tokenizer_Get(struct tok_state *, char **, char **);

#ifdef __cplusplus
}
#endif
#endif /* !Ta3_TOKENIZER_H */
