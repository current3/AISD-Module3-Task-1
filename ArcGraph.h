#ifndef ARCGRAPH_H
#define ARCGRAPH_H

#include "IGraph.h"

#include <utility>
#include <vector>

struct ArcGraph : public IGraph
{
public:
    explicit ArcGraph(int size);
    ArcGraph(const IGraph& graph);
    ~ArcGraph() override {}

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    int verticesCount;
    std::vector<std::pair<int, int>> edges;
};

#endif
