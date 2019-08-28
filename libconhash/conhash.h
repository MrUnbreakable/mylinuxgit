
/* Copyright (C) 2010. sparkling.liang@hotmail.com. All rights reserved. */

#ifndef __CON_HASH_H_
#define __CON_HASH_H_

#include "configure.h"
#include <stdlib.h>

#ifdef CONHASH_EXPORTS

/* windows platform DLL */
#if (defined (WIN32) || defined (__WIN32)) && (defined _USRDLL)
#define CONHASH_API __declspec(dllexport)
#else
#define CONHASH_API __declspec(dllimport)
#endif 

#else /* Linux, or static lib */
#define CONHASH_API  
#endif

#define NODE_FLAG_INIT  0x01 /* node is initialized */
#define NODE_FLAG_IN    0x02 /* node is added in the server */

typedef long (*conhash_cb_hashfunc)(const char *instr);
struct conhash_s;
typedef struct conhash_s *HANDLE;

/* nodes structure */
struct node_s
{
	char iden[64]; /* node name or some thing identifies the node */
	u_int replicas; /* number of replica virtual nodes */
	u_int flag;
        //node_s(){ (node_s*) malloc(sizeof(node_s)); }
};

/* 
 * callback function to calculate hash value 
 * @instr: input string
 */

/* export interfaces */
#ifdef  __cplusplus
extern "C" {
#endif
	/* initialize conhash library
	 * @pfhash : hash function, NULL to use default MD5 method
	 * return a conhash_s instance
	 */
	CONHASH_API HANDLE conhash_init();

        /*select hash function*/
        CONHASH_API int conhash_select_func(HANDLE conhash, conhash_cb_hashfunc pfhash);
        
        /* set a node 
         *default number of virtural nodes is 16
         */
        CONHASH_API int conhash_set(HANDLE *conhash, const char *iden);

        /* remove a node */
        CONHASH_API int conhash_del_node(HANDLE *conhash, struct node_s *node);

	/* 
	 * get a server which object belongs to 
	 * @object: the input string which indicates an object
	 * iden represents identity of the node, do not modify the value, or it will cause a disaster
	 */
	CONHASH_API int conhash_get(const HANDLE conhash, const char *object, const char* iden);

        /* finalize lib */
	CONHASH_API void conhash_fini(const HANDLE conhash);

	/* some utility functions export*/ 

        /* get virtual node number in the hash */
	CONHASH_API u_int conhash_get_vnodes_num(const HANDLE conhash);

        /*
	 * get virtual nodes in ascending oder
	 * @values, pointer to an array, stores all the nodes's hash value 
	 * @size, how many nodes to get, can't be less than the array size
	 */
	CONHASH_API void  conhash_get_vnodes(const HANDLE conhash, long *values, int size);

        /* set node */
	CONHASH_API void conhash_set_node(struct node_s *node, const char *iden, u_int replica);

	/* 
	 * add a new node 
	 * @node: the node to add
	 */
	CONHASH_API int conhash_add_node(HANDLE *conhash, struct node_s *node);

#ifdef  __cplusplus
}
#endif

#endif /* end __CON_HASH_H_ */
