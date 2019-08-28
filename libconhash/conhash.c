
/* Copyright (C) 2010. sparkling.liang@hotmail.com. All rights reserved. */

#include "conhash.h"
#include "conhash_inter.h"

struct node_s *node[64];
int num = 0;
struct conhash_s* conhash_init()
{
    /* alloc memory and set to zero */
    struct conhash_s *conhash = (struct conhash_s*)calloc(1, sizeof(struct conhash_s));
    if(conhash == NULL)
    {
        return NULL;
    }
    do
	{
        /* setup callback functions */
            conhash->cb_hashfunc = __conhash_hash_def;
            util_rbtree_init(&conhash->vnode_tree);
            return conhash;
	}while(0);
    free(conhash);
    return NULL;
}

int conhash_select_func(HANDLE conhash, conhash_cb_hashfunc pfhash)
{
    conhash->cb_hashfunc = pfhash;
    return 0;
}

void conhash_fini(const HANDLE conhash)
{
	if(conhash != NULL)
	{
		/* free rb tree */
        while(!util_rbtree_isempty(&(conhash->vnode_tree)))
        {
            util_rbtree_node_t *rbnode = conhash->vnode_tree.root;
            util_rbtree_delete(&(conhash->vnode_tree), rbnode);
            __conhash_del_rbnode(rbnode);
        }
		free(conhash);
	}
}

int conhash_set(HANDLE *conhash, const char *iden)
{
    u_int replica = 16;
    node[num] = (struct node_s*)malloc(sizeof(struct node_s));
    conhash_set_node(node[num],iden, replica);
    conhash_add_node(conhash, node[num]);
    num++;
    return 0;
}

void conhash_set_node(struct node_s *node, const char *iden, u_int replica)
{
    strncpy(node->iden, iden, sizeof(node->iden)-1);
    node->replicas = replica;
    node->flag = NODE_FLAG_INIT;
}

int conhash_add_node(HANDLE *conhash, struct node_s *node)
{
    if((conhash==NULL) || (node==NULL)) 
    {
        return -1;
    }
    /* check node fisrt */
    if(!(node->flag&NODE_FLAG_INIT) || (node->flag&NODE_FLAG_IN))
    {
        return -1;
    }
    node->flag |= NODE_FLAG_IN;
    /* add replicas of server */
    __conhash_add_replicas(conhash, node);
 
    return 0;
}

int conhash_del_node(HANDLE *conhash, struct node_s *node)
{
   if((conhash==NULL) || (node==NULL)) 
    {
        return -1;
    }
    /* check node first */
    if(!(node->flag&NODE_FLAG_INIT) || !(node->flag&NODE_FLAG_IN))
    {
        return -1;
    }
    node->flag &= (~NODE_FLAG_IN);
    /* add replicas of server */
    __conhash_del_replicas(conhash, node);

    return 0;
}

int conhash_get(const HANDLE conhash, const char *object,const char* iden)
{
    long hash;
    const util_rbtree_node_t *rbnode;
    if((conhash==NULL) || (conhash->ivnodes==0) || (object==NULL)) 
    {
        return -1;
    }
    /* calc hash value */
    hash = conhash->cb_hashfunc(object);
    //printf("hash of text is : %ld\n",hash);
    rbnode = util_rbtree_lookup(&(conhash->vnode_tree), hash);
    if(rbnode != NULL)
    {
        struct virtual_node_s *vnode = rbnode->data;
        strcpy(iden,vnode->node->iden);
    }
    return 0;
}
