#include <stdio.h>
#include <stdlib.h>

#include "conhash.h"

struct node_s g_nodes[64];
int main()
{
    int i;
    const struct node_s *node;
    char str[128];
    char iden[64];
    long hashes[128] = {0};

    /* init conhash instance */
    HANDLE *conhash = conhash_init();
    if(conhash)
    {
        conhash_set(conhash, &g_nodes[0], "192.168.10.1:10");
        conhash_set(conhash, &g_nodes[1], "192.168.10.1:11");
        conhash_set(conhash, &g_nodes[2], "192.168.10.1:12");
        conhash_set(conhash, &g_nodes[3], "192.168.10.1:13");
        conhash_set(conhash, &g_nodes[4], "192.168.10.1:14");
        printf("virtual nodes number %d\n", conhash_get_vnodes_num(conhash));
        printf("the hashing results--------------------------------------:\n");

        /* try object */
        for(i = 0; i < 20; i++)
        {
            sprintf(str, "James.km%03d", i);
            conhash_get(conhash, str,iden);
            printf("[%16s] is in node:[%16s]\n", str,iden);
        }        
        conhash_get_vnodes(conhash, hashes, sizeof(hashes)/sizeof(hashes[0]));
        for(i = 0; i < sizeof(hashes)/sizeof(hashes[0]);i++)
        {   if(hashes[i] != 0)
            {
                printf("hash[%d] is : %ld\n", i ,hashes[i]);
            }
        }
        /*test delete node*/
        conhash_del_node(conhash, &g_nodes[2]);
        printf("remove node[%s], virtual nodes number %d\n", g_nodes[2].iden, conhash_get_vnodes_num(conhash));
        printf("the hashing results--------------------------------------:\n");
        for(i = 0; i < 20; i++)
        {
            sprintf(str, "James.km%03d", i);
            conhash_get(conhash, str,iden);
            printf("[%16s] is in node: [%16s]\n", str,iden);
        }
        /*test add node*/
        conhash_add_node(conhash, &g_nodes[2]);
        printf("add node[%s], virtual nodes number %d\n", g_nodes[2].iden, conhash_get_vnodes_num(conhash));
        /*test set hash*/
        conhash_set(conhash, &g_nodes[5], "192.168.10.1:15");       
        //conhash_add_node(conhash, &g_nodes[5]);
        printf("add node[%s], virtual nodes number %d\n", g_nodes[5].iden, conhash_get_vnodes_num(conhash));
	printf("the hashing results--------------------------------------:\n");
	for(i = 0; i < 20; i++)
	{
            sprintf(str, "James.km%03d", i);
            conhash_get(conhash, str, iden);
            printf("[%16s] is in node: [%16s]\n", str,iden);
        }
        memset(hashes , 0 ,sizeof hashes);
        conhash_get_vnodes(conhash, hashes, sizeof(hashes)/sizeof(hashes[0]));
        for(i = 0; i < sizeof(hashes)/sizeof(hashes[0]);i++)
        {   if(hashes[i] != 0)
            {
                printf("hash[%d] is : %ld\n", i ,hashes[i]);
            }
        }
    }
    conhash_fini(conhash);
    return 0;
}
