// ThreatGraph.h
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include "Queue.h"

// Undirected Threat Syndicate Graph (Adjacency List)
// Unmasks coordinated scam rings by linking phone numbers, sender IDs, and malicious URLs
class ThreatGraph {
private:
    std::unordered_map<std::string, std::vector<std::string>> adjList;

public:
    ThreatGraph() = default;

    // Add a threat entity node (Phone, URL, or Sender ID)
    void addEntity(const std::string& entity) {
        if (adjList.find(entity) == adjList.end()) {
            adjList[entity] = std::vector<std::string>();
        }
    }

    // Add undirected edge: entities appeared together in the same suspicious message
    void addLink(const std::string& entityA, const std::string& entityB) {
        addEntity(entityA);
        addEntity(entityB);
        adjList[entityA].push_back(entityB);
        adjList[entityB].push_back(entityA);
    }

    // ====================================================================
    // DSA FEATURE: BREADTH-FIRST SEARCH (BFS) USING OUR CUSTOM QUEUE<T>
    // Discovers the full connected scam cluster for an entity in O(V + E)
    // ====================================================================
    std::vector<std::string> bfsCluster(const std::string& startEntity) {
        std::vector<std::string> cluster;
        if (adjList.find(startEntity) == adjList.end()) {
            return cluster;
        }

        std::unordered_set<std::string> visited;
        Queue<std::string> q; // Reusing our own Custom Queue<T> from Phase 1!

        visited.insert(startEntity);
        q.enqueue(startEntity);

        while (!q.isEmpty()) {
            std::string current = q.dequeue();
            cluster.push_back(current);

            for (const auto& neighbor : adjList[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.enqueue(neighbor);
                }
            }
        }

        return cluster;
    }

    // Finds all distinct scam syndicates (Connected Components)
    std::vector<std::vector<std::string>> findAllSyndicates() {
        std::vector<std::vector<std::string>> syndicates;
        std::unordered_set<std::string> visited;

        for (const auto& pair : adjList) {
            const std::string& node = pair.first;
            if (visited.find(node) == visited.end()) {
                std::vector<std::string> component;
                Queue<std::string> q;

                visited.insert(node);
                q.enqueue(node);

                while (!q.isEmpty()) {
                    std::string curr = q.dequeue();
                    component.push_back(curr);

                    for (const auto& neighbor : adjList[curr]) {
                        if (visited.find(neighbor) == visited.end()) {
                            visited.insert(neighbor);
                            q.enqueue(neighbor);
                        }
                    }
                }
                syndicates.push_back(component);
            }
        }

        return syndicates;
    }

    int vertexCount() const { return (int)adjList.size(); }
};
