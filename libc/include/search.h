/*-
 * Written by J.T. Conklin <jtc@netbsd.org>
 * Public domain.
 */

#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <sys/cdefs.h>
#include <sys/types.h>

typedef enum {
  preorder,
  postorder,
  endorder,
  leaf
} VISIT;

#ifdef _SEARCH_PRIVATE
typedef struct node {
  char* key;
  struct node* llink;
  struct node* rlink;
} node_t;
#endif

struct qelem {
	struct qelem *q_forw;
	struct qelem *q_back;
	char          q_data[1];
};


__BEGIN_DECLS

void insque(void *elem, void *prev);
void remque(void *elem);

void* lfind(const void*, const void*, size_t*, size_t, int (*)(const void*, const void*));
void* lsearch(const void*, void*, size_t*, size_t, int (*)(const void*, const void*));

void* tdelete(const void* __restrict, void** __restrict, int (*)(const void*, const void*));
void tdestroy(void*, void (*)(void*));
void* tfind(const void*, void* const*, int (*)(const void*, const void*));
void* tsearch(const void*, void**, int (*)(const void*, const void*));
void twalk(const void*, void (*)(const void*, VISIT, int));

__END_DECLS

#endif /* !_SEARCH_H_ */
