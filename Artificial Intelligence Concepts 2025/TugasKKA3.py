from collections import deque
import heapq

class Graph:
    def __init__(self):
        self.adj = {}

    def add_edge(self, u, v, weight):
        self.adj.setdefault(u, []).append((v, weight))
        self.adj.setdefault(v, []).append((u, weight))

    def dfs(self, start_node):
        visited = set()
        path = []

        def _dfs_util(node):
            if node not in visited:
                visited.add(node)
                path.append(node)	
                if node in self.adj:
                    for child, _ in self.adj[node]:
                        _dfs_util(child)
        
        _dfs_util(start_node)
        print(" -> ".join(path))

    def bfs(self, start_node):
        if start_node not in self.adj:
            print(start_node)
            return

        visited = {start_node}
        queue = deque([start_node])
        path = []

        while queue:
            node = queue.popleft()
            path.append(node)

            if node in self.adj:
                for child, _ in self.adj[node]:
                    if child not in visited:
                        visited.add(child)
                        queue.append(child)
        
        print(" -> ".join(path))
    
    def ucs(self, start_node, end_node):
        priority_queue = [(0, start_node)]
        cost = {start_node: 0}
        parent = {start_node: None}

        while priority_queue:
            _, curnode = heapq.heappop(priority_queue)

            if curnode == end_node:
                break
            
            if curnode not in self.adj:
                continue

            for child, weight in self.adj[curnode]:
                newcost = cost[curnode] + weight
                if child not in cost or newcost < cost[child]:
                    cost[child] = newcost
                    heapq.heappush(priority_queue, (newcost, child))
                    parent[child] = curnode
        
        if end_node not in parent:
            print(f"Jalur dari {start_node} ke {end_node} tidak ditemukan.")
            return

        path = []
        node = end_node
        while node is not None:
            path.append(node)
            node = parent[node]
        path.reverse()

        print(f"{' -> '.join(path)}")
        print(f"Total Biaya: {cost[end_node]}")


if __name__ == "__main__":
    g = Graph()
    
    g.add_edge("Arad", "Zerind", 75)
    g.add_edge("Arad", "Timisoara", 118)
    g.add_edge("Arad", "Sibiu", 140)
    g.add_edge("Zerind", "Oradea", 71)
    g.add_edge("Oradea", "Sibiu", 151)
    g.add_edge("Timisoara", "Lugoj", 111)
    g.add_edge("Lugoj", "Mehadia", 70)
    g.add_edge("Mehadia", "Dobreta", 75)
    g.add_edge("Dobreta", "Craiova", 120)
    g.add_edge("Sibiu", "Fagaras", 99)
    g.add_edge("Sibiu", "Rimnicu Vilcea", 80)
    g.add_edge("Rimnicu Vilcea", "Craiova", 146)
    g.add_edge("Rimnicu Vilcea", "Pitesti", 97)
    g.add_edge("Craiova", "Pitesti", 138)
    g.add_edge("Fagaras", "Bucharest", 211)
    g.add_edge("Pitesti", "Bucharest", 101)
    g.add_edge("Bucharest", "Giurgiu", 90)
    g.add_edge("Bucharest", "Urziceni", 85)
    g.add_edge("Urziceni", "Hirsova", 98)
    g.add_edge("Urziceni", "Vaslui", 142)
    g.add_edge("Hirsova", "Eforie", 86)
    g.add_edge("Vaslui", "Iasi", 92)
    g.add_edge("Iasi", "Neamt", 87)
    
    start_node = "Arad"
    goal_node = "Bucharest"

    print(f"Traversal & Pencarian dimulai dari '{start_node}'")
    print("-" * 40)

    print("Hasil DFS (Traversal):")
    g.dfs(start_node)
    print("-" * 40)
    
    print("Hasil BFS (Traversal):")
    g.bfs(start_node)
    print("-" * 40)

    print(f"Hasil UCS (Pencarian Jalur Termurah ke '{goal_node}'):")
    g.ucs(start_node, goal_node)
    print("-" * 40)