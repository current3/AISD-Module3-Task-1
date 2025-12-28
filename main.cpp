/*
Задача 1. Представление графа.
Дан базовый интерфейс для представления ориентированного графа:
struct IGraph {
virtual ~IGraph() {}
	
	// Добавление ребра от from к to.
virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

Необходимо написать несколько реализаций интерфейса:
ListGraph, хранящий граф в виде массива списков смежности,
MatrixGraph, хранящий граф в виде матрицы смежности,
SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
ArcGraph, хранящий граф в виде одного массива пар {from, to}.
Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>
#include <algorithm>

#include "IGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "ArcGraph.h"
#include "SetGraph.h"

int EdgesCount(const IGraph& graph)
{
    int edges = 0;
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        edges += (int)graph.GetNextVertices(i).size();
    }
    return edges;
}

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty())
    {
        int currentVertex = qu.front();
        qu.pop();

        func(currentVertex);

        std::vector<int> next = graph.GetNextVertices(currentVertex);
        std::sort(next.begin(), next.end());

        for (int nextVertex : next)
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph& graph, const std::function<void(int)>& func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            BFS(graph, i, visited, func);
        }
    }
}

void DFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func)
{
    visited[vertex] = true;
    func(vertex);

    std::vector<int> next = graph.GetNextVertices(vertex);
    std::sort(next.begin(), next.end());

    for (int nextVertex : next)
    {
        if (!visited[nextVertex])
        {
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void mainDFS(const IGraph& graph, const std::function<void(int)>& func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, func);
        }
    }
}

void PrintTraversals(const IGraph& graph, const char* name)
{
    std::cout << name << "\n";
    std::cout << "V = " << graph.VerticesCount() << ", E = " << EdgesCount(graph) << "\n";

    std::cout << "BFS: ";
    mainBFS(graph, [](int v){ std::cout << v << " "; });
    std::cout << "\n";

    std::cout << "DFS: ";
    mainDFS(graph, [](int v){ std::cout << v << " "; });
    std::cout << "\n\n";
}

int main()
{
    ListGraph listGraph(7);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);

    MatrixGraph matrixGraph(listGraph);
    ArcGraph arcGraph(matrixGraph);
    SetGraph setGraph(arcGraph);

    assert(listGraph.VerticesCount() == matrixGraph.VerticesCount());
    assert(matrixGraph.VerticesCount() == arcGraph.VerticesCount());
    assert(arcGraph.VerticesCount() == setGraph.VerticesCount());

    assert(EdgesCount(listGraph) == EdgesCount(matrixGraph));
    assert(EdgesCount(matrixGraph) == EdgesCount(arcGraph));
    assert(EdgesCount(arcGraph) == EdgesCount(setGraph));

    PrintTraversals(listGraph,   "ListGraph");
    PrintTraversals(matrixGraph, "MatrixGraph");
    PrintTraversals(arcGraph,    "ArcGraph");
    PrintTraversals(setGraph,    "SetGraph");

    return 0;
}
