

status_t Initialize_single_source(graph_t* g, vertex_t v)
{
    vnode_t* pv_run = NULL;
    vnode_t* pv_source_node = NULL;

    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run  = pv_run)
    {
        pv_run.prev_vertex = NULL;
        pv_run.d =INFINITY;
    }
    pv_source_node = V_search_node(g->pv_list, v);
    if(pv_source_node == NULL)
        return (G_INALID_VERTEX);
    return (SUCCESS);
}

void Releax(graph_t* g, weight_t w, vnode_t* u, vnode_t* v)
{
    if(v.d>(u.d+get_weight())
    {

    }
}
