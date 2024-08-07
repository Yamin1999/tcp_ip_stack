#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

graph_t * create_new_graph(char *topology_name)
{
    graph_t *new_graph;

    new_graph = (graph_t *) malloc (sizeof(graph_t));

    memset(new_graph,0,sizeof(new_graph));

    strcpy(new_graph->topology_name,topology_name);

    init_glthread(&new_graph->node_list);

    return new_graph;
} 

node_t * create_graph_node(graph_t *topo, char * node_name)
{
    node_t *new_node;
    new_node = (node_t *) malloc (sizeof(node_t));

    memset(new_node,0,sizeof(node_t));

    strcpy(new_node->node_name,node_name);

    glthread_add_next(&topo->node_list,&new_node->graph_glue);

    return new_node;
}

void insert_link_between_two_nodes(node_t *node1, node_t *node2,
char *link1_name, char *link2_name, unsigned int cost)
{
    link_t *new_link;
    int empty_intf_slot;

    new_link = (link_t *)malloc(sizeof(link_t));

    memset(new_link,0,sizeof(new_link));

    strcpy(new_link->intf1.if_name,link1_name);
    strcpy(new_link->intf2.if_name,link2_name);                                                            

    new_link->intf1.att_node = node1;
    new_link->intf2.att_node = node2;

    new_link->intf1.link = new_link;

    new_link->intf2.link = new_link;

    new_link->cost = cost;

    empty_intf_slot = get_node_intf_empty_slot(node1);
    node1->intf[empty_intf_slot] = &new_link->intf1;

    empty_intf_slot = get_node_intf_empty_slot(node2);

    node2->intf[empty_intf_slot] = &new_link->intf2;
}

int  
get_node_intf_empty_slot(node_t *node1)
{
    for(int i=0;i<MAX_INTF_PER_NODE;i++)
    {
        if(node1->intf[i] == NULL)
        return i;
    }

    return -1;
}


void dump_graph(graph_t *graph){

    glthread_t *curr;
    node_t *node;
    
    printf("Topology Name = %s\n", graph->topology_name);

    ITERATE_GLTHREAD_BEGIN(&graph->node_list, curr){

        node = graph_glue_to_node(curr);
        dump_node(node);    
    } ITERATE_GLTHREAD_END(&graph->node_list, curr);
}

void dump_node(node_t *node){

    unsigned int i = 0;
    interface_t *intf;

    printf("Node Name = %s : \n", node->node_name);
    for( ; i < MAX_INTF_PER_NODE; i++){
        
        intf = node->intf[i];
        if(!intf) break;
        dump_interface(intf);
    }
}

void dump_interface(interface_t *interface){

   link_t *link = interface->link;
   node_t *nbr_node = get_nbr_node(interface);

   printf(" Local Node : %s, Interface Name = %s, Nbr Node %s, cost = %u\n", 
            interface->att_node->node_name, 
            interface->if_name, nbr_node->node_name, link->cost); 
}

static inline node_t *
get_nbr_node(interface_t *interface){

    assert(interface->att_node);
    assert(interface->link);
    
    link_t *link = interface->link;
    if(&link->intf1 == interface)
        return link->intf2.att_node;
    else
        return link->intf1.att_node;
}