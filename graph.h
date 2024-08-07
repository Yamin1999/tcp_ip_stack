#include "gluethread/glthread.h"
#include <assert.h>

#define IF_NAME_SIZE 16
#define NODE_NAME_SIZE 16
#define MAX_INTF_PER_NODE 10

typedef struct node_ node_t;
typedef struct link_ link_t;

typedef struct interface_
{
    char if_name[IF_NAME_SIZE];
    struct node_ *att_node;
    struct link_ *link;
}interface_t;

struct link_
{
    interface_t intf1;
    interface_t intf2;
    unsigned int cost;
};

struct node_
{
    char node_name[NODE_NAME_SIZE];
    interface_t *intf[MAX_INTF_PER_NODE];
    glthread_t graph_glue;
};

GLTHREAD_TO_STRUCT(graph_glue_to_node, node_t, graph_glue);

typedef struct graph_{

    char topology_name[32];
    glthread_t node_list;

}graph_t;


graph_t * create_new_graph(char *topology_name);
node_t * create_graph_node(graph_t *topo, char * node_name);
void insert_link_between_two_nodes(node_t *node1, node_t *node2, char *link1_name, char *link2_name, unsigned int cost);
int get_node_intf_empty_slot(node_t *node1);

void dump_graph(graph_t *topo);
void dump_node(node_t *node);
void dump_interface(interface_t *interface);
static inline node_t *get_nbr_node(interface_t *interface);