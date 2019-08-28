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
        conhash_set(conhash, "192.168.10.1:10");
        conhash_set(conhash, "192.168.10.1:11");
        conhash_set(conhash, "192.168.10.1:12");
        conhash_set(conhash, "192.168.10.1:13");
        conhash_set(conhash, "192.168.10.1:14");
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
        conhash_del_node(conhash, "192.168.10.1:12");
        printf("remove node 192.168.10.1:12, virtual nodes number %d\n",conhash_get_vnodes_num(conhash));
        printf("the hashing results--------------------------------------:\n");
        for(i = 0; i < 20; i++)
        {
            sprintf(str, "James.km%03d", i);
            conhash_get(conhash, str,iden);
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
        conhash_set(conhash, "192.168.10.1:15");       
        printf("add node 192.169.10.1:15, virtual nodes number %d\n",conhash_get_vnodes_num(conhash));
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
