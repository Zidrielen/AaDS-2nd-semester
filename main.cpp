#include <iostream>
#include <string>

#include "class_graph.h"


void menu()
{
	std::cout << "1. Add a vertex to a graph" << std::endl;
	std::cout << "2. Remove a vertex from a graph" << std::endl;
	std::cout << "3. Check if a vertex exists in a graph" << std::endl;
	std::cout << "4. Connect the vertices of the graph with an edge" << std::endl;
	std::cout << "5. Remove an edge associated with graph vertices" << std::endl;
	std::cout << "6. Check for an edge between graph edges" << std::endl;
	std::cout << "7. Find out the order of the graph" << std::endl;
	std::cout << "8. Find out the degree of the graph" << std::endl;
	std::cout << "9. Find the shortest path from one vertex to another" << std::endl;
	std::cout << "10. Walk through the graph (print the result of the walkthrough)" << std::endl;
	std::cout << "11. Complete the lab assignment" << std::endl;
	std::cout << "12. Exit" << std::endl << std::endl;
	std::cout << "Enter the number: ";
}


template<typename Vertex, typename Distance = double>
const Vertex find_farthest_hospital(const Graph<Vertex, double>& graph)
{
	if (graph.degree() == 0) { throw std::invalid_argument("Transferred graph without edges"); }
	Distance max_average_distance = std::numeric_limits<Distance>::min();
	Vertex farthest_hospital;
	std::unordered_set<Vertex> visited;
	auto action = [&max_average_distance, &farthest_hospital, &graph, &visited](const Vertex& vertex)
	{
		visited.insert(vertex);
		if (graph.edges_cbegin(vertex) == graph.edges_cend(vertex)) return;
		Distance total_distance = 0;
		size_t num_edges = 0;
		bool is_first = true;
		for (auto edge_iter = graph.edges_cbegin(vertex); edge_iter != graph.edges_cend(vertex); ++edge_iter)
		{
			if (is_first)
			{
				total_distance = edge_iter->distance;
				is_first = false;
			}
			else total_distance += edge_iter->distance;
			num_edges += 1;
		}
		Distance average_distance = total_distance / num_edges;
		if (average_distance > max_average_distance)
		{
			max_average_distance = average_distance;
			farthest_hospital = vertex;
		}
	};
	if (graph.vertices_cbegin() == graph.vertices_cend())
	{
		throw std::invalid_argument("An empty graph was passed");
	}
	for (auto vertex_iter = graph.vertices_cbegin(); vertex_iter != graph.vertices_cend(); ++vertex_iter)
	{
		if (!visited.count(*vertex_iter)) graph.walk(*vertex_iter, action);
	}
	return farthest_hospital;
}


template<typename Vertex>
void print(const Vertex& vertex) { std::cout << vertex << " "; }


int main()
{
	size_t n = 0;
	Graph<std::string> graph;
	std::string str1, str2;
	double dist = 0;
	while (1)
	{
		menu();
		std::cin >> n;
		try
		{
			if (n == 1)
			{
				std::cout << std::endl << "Enter a unique vertex name: ";
				std::cin >> str1;
				graph.add_vertex(str1);
			}
			if (n == 2)
			{
				std::cout << std::endl << "Enter the name of the vertex to be deleted: ";
				std::cin >> str1;
				if (graph.remove_vertex(str1))
					std::cout << "The vertex named " << str1 << " was deleted successfully";
				else std::cout << "The vertex named " << str1 << " was not deleted";
			}
			if (n == 3)
			{
				std::cout << std::endl << "Enter the name of the vertex to be found: ";
				std::cin >> str1;
				if (graph.has_vertex(str1))
					std::cout << "The vertex named " << str1 << " was found";
				else std::cout << "The vertex named " << str1 << " was not found";
			}
			if (n == 4)
			{
				std::cout << std::endl << "Enter vertex name FROM: ";
				std::cin >> str1;
				std::cout << std::endl << "Enter vertex name TO: ";
				std::cin >> str2;
				std::cout << std::endl << "Enter edge weight: ";
				std::cin >> dist;
				graph.add_edge(str1, str2, dist);
			}
			if (n == 5)
			{
				std::cout << std::endl << "Enter vertex name FROM: ";
				std::cin >> str1;
				std::cout << std::endl << "Enter vertex name TO: ";
				std::cin >> str2;
				if (graph.remove_edge(str1, str2))
					std::cout << "The edge was deleted successfully";
				else std::cout << "The edge was not deleted";
			}
			if (n == 6)
			{
				std::cout << std::endl << "Enter vertex name FROM: ";
				std::cin >> str1;
				std::cout << std::endl << "Enter vertex name TO: ";
				std::cin >> str2;
				if (graph.has_edge(str1, str2))
					std::cout << "The edge was found";
				else std::cout << "The edge was not found";
			}
			if (n == 7)
			{
				std::cout << std::endl << "The order of the graph is ";
				std::cout << graph.order();
			}
			if (n == 8)
			{
				std::cout << std::endl << "The degree of the graph is ";
				std::cout << graph.degree();
			}
			if (n == 9)
			{
				std::cout << std::endl << "Enter vertex name FROM: ";
				std::cin >> str1;
				std::cout << std::endl << "Enter vertex name TO: ";
				std::cin >> str2;
				auto short_path = graph.shortest_path(str1, str2);
				for (const auto& edge : short_path)
				{
					std::cout << edge.from << " -> " << edge.to;
					std::cout << " (distance: " << edge.distance << ")" << std::endl;
				}
			}
			if (n == 10)
			{
				std::cout << "Enter the name of the vertex from which to start walking along the graph: ";
				std::cin >> str1;
				std::cout << "The result of the walk: ";
				graph.walk(str1, print<std::string>);
			}
			if (n == 11)
			{
				std::cout << "Result: ";
				std::cout << find_farthest_hospital(graph);
			}
			if(n == 12) return 0;
		}
		catch (const std::exception& err) { std::cout << err.what(); }
		std::cout << std::endl << std::endl;
	}
}
