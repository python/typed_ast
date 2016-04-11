
/* Parse tree node interface */

#ifndef Ta35_NODE_H
#define Ta35_NODE_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _node {
    short		n_type;
    char		*n_str;
    int			n_lineno;
    int			n_col_offset;
    int			n_nchildren;
    struct _node	*n_child;
} node;

PyAPI_FUNC(node *) Ta35Node_New(int type);
PyAPI_FUNC(int) Ta35Node_AddChild(node *n, int type,
                                      char *str, int lineno, int col_offset);
PyAPI_FUNC(void) Ta35Node_Free(node *n);
#ifndef Py_LIMITED_API
PyAPI_FUNC(Py_ssize_t) _Ta35Node_SizeOf(node *n);
#endif

/* Node access functions */
#define NCH(n)		((n)->n_nchildren)

#define CHILD(n, i)	(&(n)->n_child[i])
#define RCHILD(n, i)	(CHILD(n, NCH(n) + i))
#define TYPE(n)		((n)->n_type)
#define STR(n)		((n)->n_str)
#define LINENO(n)       ((n)->n_lineno)

/* Assert that the type of a node is what we expect */
#define REQ(n, type) assert(TYPE(n) == (type))

PyAPI_FUNC(void) Ta35Node_ListTree(node *);

#ifdef __cplusplus
}
#endif
#endif /* !Ta35_NODE_H */
