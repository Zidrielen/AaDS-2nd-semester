#pragma once

#include <vector>
#include <limits>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <functional>

template<typename Vertex, typename Distance = double>
class Graph
{
public:
    struct Edge
    {
        Vertex from;
        Vertex to;
        Distance distance;

        Edge(const Vertex& f, const Vertex& t, const Distance& d) :
            from(f), to(t), distance(d) {}

        Edge() = default;
    };

private:
    std::unordered_map<Vertex, std::vector<Edge>> data;

public:
    bool has_vertex(const Vertex& v) const { return data.count(v); }

    void add_vertex(const Vertex& v)
    {
        if (has_vertex(v)) throw std::invalid_argument("Error, such a vertex already exists in the graph");
        data[v] = std::vector<Edge>();
    }

    bool remove_vertex(const Vertex& v)
    {
        if (!data.erase(v)) return false;
        for (auto& pair : data)
        {
            auto pred = [&](const auto& edge) {return edge.to == v; };
            auto vector_iter = std::find_if(pair.second.begin(), pair.second.end(), pred);
            while (vector_iter != pair.second.end())
            {
                auto tmp_begin = pair.second.erase(vector_iter);
                vector_iter = std::find_if(tmp_begin, pair.second.end(), pred);
            }
        }
        return true;
    }

    class VertexIterator {
    private:
        typename std::unordered_map<Vertex, std::vector<Edge>>::const_iterator iter;

    public:
        VertexIterator(typename std::unordered_map<Vertex, std::vector<Edge>>::const_iterator it) :
            iter(it) {}

        VertexIterator& operator++()
        {
            ++iter;
            return *this;
        }

        VertexIterator operator++(int)
        {
            VertexIterator tmp(*this);
            ++iter;
            return tmp;
        }

        bool operator==(const VertexIterator& it) const { return iter == it.iter; }

        bool operator!=(const VertexIterator& it) const { return iter != it.iter; }

        Vertex operator*() const { return iter->first; }
    };

    VertexIterator vertices_cbegin() const { return VertexIterator(data.cbegin()); }

    VertexIterator vertices_cend() const { return VertexIterator(data.cend()); }

    auto edges_cbegin(const Vertex& vertex) const {
        if (!has_vertex(vertex))
        {
            throw std::invalid_argument("Error, there is no such vertex in the graph");
        }
        return data.at(vertex).cbegin();
    }

    auto edges_cend(const Vertex& vertex) const {
        if (!has_vertex(vertex))
        {
            throw std::invalid_argument("Error, there is no such vertex in the graph");
        }
        return data.at(vertex).cend();
    }

    bool has_edge(const Vertex& from, const Vertex& to) const
    {
        if (!has_vertex(from) || !has_vertex(to)) return false;
        auto pred = [&from, &to](const auto& edge)
        {
            return edge.from == from && edge.to == to;
        };
        return std::find_if(edges_cbegin(from), edges_cend(from), pred) != edges_cend(from);
    }

    bool has_edge(const Edge& e) const
    {
        if (!has_vertex(e.from) || !has_vertex(e.to)) return false;
        auto pred = [&e](const auto& edge)
        {
            return edge.from == e.from && edge.to == e.to && edge.distance == e.distance;
        };
        return std::find_if(edges_cbegin(e.from), edges_cend(e.from), pred) != edges_cend(e.from);
    }

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d)
    {
        if (!has_vertex(from) || !has_vertex(to))
        {
            throw std::invalid_argument("Error, there is no such vertex in the graph");
        }
        data[from].push_back(Edge(from, to, d));
    }

    bool remove_edge(const Vertex& from, const Vertex& to)
    {
        if (!has_vertex(from) || !has_vertex(to)) return false;
        auto pred = [&from, &to](const auto& edge)
        {
            return edge.from == from && edge.to == to;
        };
        bool is_removed = false;
        auto vector_iter = std::find_if(data.at(from).begin(), data.at(from).end(), pred);
        if (vector_iter != data.at(from).end())
        {
            auto next_iter = data.at(from).erase(vector_iter);
            vector_iter = std::find_if(next_iter, data.at(from).end(), pred);
            is_removed = true;
        }
        return is_removed;
    }

    bool remove_edge(const Edge& e) {
        if (!has_vertex(e.from) || !has_vertex(e.to)) return false;
        auto pred = [&e](const auto& edge)
        {
            return edge.from == e.from && edge.to == e.to && edge.distance == e.distance;
        };
        bool is_removed = false;
        auto vector_iter = std::find_if(data.at(e.from).begin(), data.at(e.from).end(), pred);
        if (vector_iter != data.at(e.from).end())
        {
            auto next_iter = data.at(e.from).erase(vector_iter);
            vector_iter = std::find_if(next_iter, data.at(e.from).end(), pred);
            is_removed = true;
        }
        return is_removed;
    }

    size_t order() const { return data.size(); }

    size_t degree() const
    {
        size_t res = 0;
        for (const auto& pair : data)
        {
            size_t cur_degree = pair.second.size();
            if (cur_degree > res) res = cur_degree;
        }
        return res;
    }

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to))
        {
            throw std::invalid_argument("Error, there is no such vertex in the graph");
        }
        std::vector<Edge> res;
        std::unordered_map<Vertex, Distance> distance;
        std::unordered_map<Vertex, Edge> prev;
        for (const auto& pair : data)
        {
            distance[pair.first] = std::numeric_limits<Distance>::max();
        }
        distance[from] = 0;
        for (size_t i = 0; i < data.size() - 1; i++)
        {
            for (const auto& pair : data)
            {
                for (const auto& edge : pair.second)
                {
                    auto new_distance = distance[edge.from] + edge.distance;
                    if (new_distance < distance[edge.to])
                    {
                        distance[edge.to] = new_distance;
                        prev[edge.to] = edge;
                    }
                }
            }
        }
        for (const auto& pair : data)
        {
            for (const auto& edge : pair.second)
            {
                auto new_distance = distance[edge.from] + edge.distance;
                if (new_distance < distance[edge.to])
                {
                    throw std::runtime_error("Error, graph has a negative cycle");
                }
            }
        }
        if (distance[to] == std::numeric_limits<Distance>::max())
        {
            throw std::invalid_argument("Error, these vertices are isolated from each other");
        }
        Vertex curr_vertex = to;
        while (curr_vertex != from)
        {
            Edge edge = prev[curr_vertex];
            res.push_back(edge);
            curr_vertex = edge.from;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }

    void walk(const Vertex& start_vertex, std::function<void(const Vertex&)> action) const
    {
        if (!has_vertex(start_vertex))
        {
            throw std::invalid_argument("Error, there is no such vertex in the graph");
        }
        std::unordered_set<Vertex> visited;
        std::queue<Vertex> queue;
        visited.insert(start_vertex);
        queue.push(start_vertex);
        action(start_vertex);
        while (!queue.empty()) {
            Vertex vertex = queue.front();
            queue.pop();
            for (auto edge_iter = edges_cbegin(vertex); edge_iter != edges_cend(vertex); ++edge_iter) {
                const Edge& edge = *edge_iter;
                if (!visited.count(edge.to)) {
                    visited.insert(edge.to);
                    queue.push(edge.to);
                    action(edge.to);
                }
            }
        }
    }
};
