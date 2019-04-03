#include "graph.h"


void FreeGraph(
        void * graph)
{
    if (graph == NULL)
        return;

    free(((Graph *)graph)->distance);
    free(((Graph *)graph)->parent);
    free(((Graph *)graph)->adjacency_matrix);

    free(graph);
}


Graph * InitGraph(
        unsigned int vertices,
        unsigned int edges,
        unsigned short vertex)
{
    Graph * graph = (Graph *) malloc(sizeof(Graph));

    if (graph == NULL)
        return NULL;

    graph->distance = malloc(vertices * sizeof(unsigned int));
    graph->parent = malloc(vertices * sizeof(short));
    graph->adjacency_matrix = (unsigned int *) malloc(vertices * (1 + vertices) / 2 * sizeof(unsigned int));

    if ((graph->distance == NULL || graph->parent == NULL ||
         graph->adjacency_matrix == NULL) && vertices)
    {
        FreeGraph(graph);
        free(graph);
        return NULL;
    }

    memset(graph->adjacency_matrix, 0xFF, (size_t) vertices * (1 + vertices) / 2 * sizeof(unsigned int));
    memset(graph->parent, 0xFF, (size_t) vertices * sizeof(short));
    memset(graph->distance, 0xFF, (size_t) vertices * sizeof(unsigned int));


    graph->distance[vertex] = 0;
    graph->vertices = vertices;
    graph->edges = edges;

    return graph;
}


void PrintDistances(
        Graph * graph,
        unsigned short start,
        unsigned short end,
        unsigned int overflow)
{
    if (graph == NULL)
        return;

    for (int k = 0; k < graph->vertices; k++) {
        if ((graph->parent[k] != NO_PARENT && graph->distance[k] != OVERFLOW) || k == start) {
            printf("%d ", graph->distance[k]);
        }
        else if (graph->parent[k] == NO_PARENT) {
            printf("oo ");
        }
        else if (graph->parent[k] != NO_PARENT && graph->distance[k] == OVERFLOW) {
            printf("INT_MAX+ ");
        }
    }

    printf("\n");

    if (graph->parent[end] != NO_PARENT && graph->distance[end] == OVERFLOW && overflow > 1) {
        printf("overflow");
    }
    else if (graph->parent[end] == NO_PARENT && end != start) {
        printf("no path");
    }
    else if (graph->parent[end] != NO_PARENT || start == end) {
        while (graph->parent[end] != NO_PARENT) {
            printf("%d ", end + 1);
            end = (unsigned short) graph->parent[end];
        }
        printf("%d", start + 1);
    }
}
