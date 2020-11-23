
from collections import defaultdict

def main():
    num_nodes, num_edges = list(map(int, input().strip().split(" ")))
    edges = [tuple(map(int, input().strip().split(" "))) for _ in range(num_edges)]
    colors = list(map(int, input().strip().split(" ")))

    graph = defaultdict(list)
    for edge in edges:
        _to = edge[0]
        _from = edge[1]

        graph[_to].append(_from)
        graph[_from].append(_to)

    degrees = [len(x) for x in graph.values()]
    max_degree = max(degrees)

    print(max_degree)

if __name__ == "__main__":
    main()