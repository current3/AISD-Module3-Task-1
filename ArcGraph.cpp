#include "ArcGraph.h"

#include <cassert>

ArcGraph::ArcGraph(int size)
: verticesCount(size)
{
}

ArcGraph::ArcGraph(const IGraph& graph)
: ArcGraph(graph.VerticesCount())
{
    for (int from = 0; from < graph.VerticesCount(); ++from)
    {
        for (int to : graph.GetNextVertices(from))
        {
            AddEdge(from, to);
        }
    }
}

void ArcGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < verticesCount);
    assert(0 <= to && to < verticesCount);

    edges.push_back({from, to});
}

int ArcGraph::VerticesCount() const
{
    return verticesCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < verticesCount);

    std::vector<int> nextVertices;
    for (const auto& e : edges)
    {
        if (e.first == vertex)
        {
            nextVertices.push_back(e.second);
        }
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < verticesCount);

    std::vector<int> prevVertices;
    for (const auto& e : edges)
    {
        if (e.second == vertex)
        {
            prevVertices.push_back(e.first);
        }
    }
    return prevVertices;
}
