#include "graph.h"


static inline unsigned short closest_vertex(
        Graph * graph)
{
    unsigned short v = 0;

    unsigned int min_distance = UINT_MAX;

    for (unsigned short t = 0; t < graph->vertices; t++) {
        if (graph->distance[t] <= min_distance && graph->adjacency_matrix[offset(t, t)] != PROCESSED) {
            min_distance = graph->distance[t];
            v = t;
        }
    }

    return v;
}


int FindDistance(
        Graph * graph,
        unsigned short end)
{
    if (graph == NULL)
        return -1;

    unsigned short v = 0;

    unsigned long long int current_distance = 0;
    unsigned int overflow_counter = 0;

    if (graph->vertices && graph->edges)
    {
        for (unsigned int k = 0; k < graph->vertices; k++)
        {
            v = closest_vertex(graph);

            graph->adjacency_matrix[offset(v, v)] = PROCESSED;

            for (unsigned short u = 0; u < graph->vertices; u++)
            {
                if (graph->adjacency_matrix[offset(v,  u)] != UINT_MAX
                    && graph->adjacency_matrix[offset(u, u)] != PROCESSED)
                {
                    current_distance = graph->adjacency_matrix[offset(v,  u)] + graph->distance[v];

                    if (current_distance >= OVERFLOW || graph->distance[v] >= OVERFLOW)
                    {
                        current_distance = OVERFLOW;

                        if (u == end)
                            overflow_counter += 1;
                    }

                    if (current_distance < graph->distance[u])
                    {
                        graph->distance[u] = (unsigned int) current_distance;
                        graph->parent[u] = (short) v;
                    }
                }
            }
        }
    }

    return overflow_counter;
}
