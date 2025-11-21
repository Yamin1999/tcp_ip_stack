#include "graph.h"
#include "net.h"
#include <stdio.h>
#include <memory.h>

bool node_set_loopback_address(node_t *node,char *ip_addr)
{
    assert(ip_addr);

    node->node_new_prop.is_loop_back_addr = true;
    memcpy(node->node_new_prop.loop_back_addr.ip_addr, ip_addr, 16);
    return true;
}

bool node_set_intf_ip_address(node_t *node,char *local_if, char *ip_addr,char mask)
{
    interface_t *intf = get_int_with_intf_name(node,local_if);

    memcpy(intf->intf_nw_props.ip_addr.ip_addr,ip_addr,16);

    intf->intf_nw_props.mask = mask;

    intf->intf_nw_props.is_ipadd_config = true;

    return true;
}




