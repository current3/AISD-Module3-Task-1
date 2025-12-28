#include "SetGraph.h"

#include <cassert>

SetGraph::SetGraph(int size)
: adjacencySets(size)
{
}

SetGraph::SetGraph(const IGraph& graph)
: SetGraph(graph.VerticesCount())
{
    for (int from = 0; from < graph.VerticesCount(); ++from)
    {
        for (int to : graph.GetNextVertices(from))
        {
            AddEdge(from, to);
        }
    }
}

void SetGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < (int)adjacencySets.size());
    assert(0 <= to && to < (int)adjacencySets.size());

    adjacencySets[from].insert(to);
}

int SetGraph::VerticesCount() const
{
    return (int)adjacencySets.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < (int)adjacencySets.size());

    std::vector<int> nextVertices;
    nextVertices.reserve(adjacencySets[vertex].size());
    for (int to : adjacencySets[vertex])
    {
        nextVertices.push_back(to);
    }
    return nextVertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < (int)adjacencySets.size());

    std::vector<int> prevVertices;
    for (int from = 0; from < (int)adjacencySets.size(); ++from)
    {
        if (adjacencySets[from].find(vertex) != adjacencySets[from].end())
        {
            prevVertices.push_back(from);
        }
    }
    return prevVertices;
}
