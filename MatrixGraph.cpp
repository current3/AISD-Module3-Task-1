#include "MatrixGraph.h"

#include <cassert>

MatrixGraph::MatrixGraph(int size)
: adjacencyMatrix(size, std::vector<bool>(size, false))
{
}

MatrixGraph::MatrixGraph(const IGraph& graph)
: MatrixGraph(graph.VerticesCount())
{
    for (int from = 0; from < graph.VerticesCount(); ++from)
    {
        for (int to : graph.GetNextVertices(from))
        {
            AddEdge(from, to);
        }
    }
}

void MatrixGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < (int)adjacencyMatrix.size());
    assert(0 <= to && to < (int)adjacencyMatrix.size());

    adjacencyMatrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const
{
    return (int)adjacencyMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < (int)adjacencyMatrix.size());

    std::vector<int> nextVertices;
    for (int to = 0; to < (int)adjacencyMatrix.size(); ++to)
    {
        if (adjacencyMatrix[vertex][to])
        {
            nextVertices.push_back(to);
        }
    }
    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < (int)adjacencyMatrix.size());

    std::vector<int> prevVertices;
    for (int from = 0; from < (int)adjacencyMatrix.size(); ++from)
    {
        if (adjacencyMatrix[from][vertex])
        {
            prevVertices.push_back(from);
        }
    }
    return prevVertices;
}
