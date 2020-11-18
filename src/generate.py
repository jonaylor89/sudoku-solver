
import sys
import networkx as nx

def generate(filename, graph, nodes, edges):

    with open(filename,"w") as file:

        file.write(str(nodes)+" "+str(edges)+"\n")

        for i,j in graph.edges():
            file.write(str(i+1) +" " + str(j+1)+"\n")

        colors = " ".join(["0" for i in range(0, nodes)])

        file.write(colors)

def main():
    if len(sys.argv) < 3:
        print("Usage: \n\tpython3 generate.py nodes edges")
        return 

    numNodes = int(sys.argv[1])
    numEdges = int(sys.argv[2])
    G = nx.gnm_random_graph(numNodes,numEdges)
    
    generate("graph.txt", G, numNodes, numEdges)


if __name__ == "__main__":
    main()