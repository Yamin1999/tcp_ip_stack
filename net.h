
#ifndef __NET__
#define __NET__
#include <string.h> 
#include <stdbool.h>

/* Forward declaration */
typedef struct node_ node_t;

typedef struct ip_aad_
{
   unsigned char ip_addr[16];
}ip_add_t;

typedef struct mac_add_
{
   unsigned char mac[8];
}mac_add_t;

typedef struct node_net_props_
{
    bool is_loop_back_addr;
    ip_add_t loop_back_addr;

}node_net_props_t;

static inline void
init_node_nw_addr(node_net_props_t *node_nw_addr)
{
   node_nw_addr->is_loop_back_addr = false;
   memset(node_nw_addr->loop_back_addr.ip_addr,0,16);
}

typedef struct  intf_nw_props_
{
   mac_add_t mac_addr;
   bool is_ipadd_config;
   ip_add_t ip_addr;
   char mask;
}intf_nw_props_t;

static inline void
init_intf_nw_props(intf_nw_props_t *intf_nw_prop)
{
   memset(intf_nw_prop->mac_addr.mac,0,8);
   intf_nw_prop->is_ipadd_config = false;
   memset(intf_nw_prop->ip_addr.ip_addr,0,16);
   intf_nw_prop->mask = 0;
}

#define IF_MAC(intf_ptr)   ((intf_ptr)->mac_addr.mac)
#define IF_IP(intf_prt)    ((intf_prt)->ip_addr.ip_addr)

#define NODE_LO_ADDR(node_ptr) ((node_prt).loop_back_addr.ip_addr)

bool node_set_loopback_address(node_t *node,char *ip_addr);
bool node_set_intf_ip_address(node_t *node,char *local_if, char *ip_addr,char mask);
// bool node_unset_intf_ip_address(node_t *node,char *local_if);
#endif