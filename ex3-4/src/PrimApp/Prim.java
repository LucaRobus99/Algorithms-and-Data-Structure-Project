package PrimApp;

import java.text.DecimalFormat;
import java.util.*;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.BufferedWriter;

import GraphP.AbstractEdge;
import GraphP.Edge;
import GraphP.Graph;
import PriorityQueue.PriorityQueue;
import PriorityQueue.PriorityQueueException;

public class Prim {

      // metodo che restituisce una lista di archi adiacenti a un nodo specificato nel grafo.

    private static <V, L> List<AbstractEdge<V, L>> getEdgesFromNode(Graph<V, L> graph, V node) {
        List<AbstractEdge<V, L>> adjacentEdges = new ArrayList<>();

        ArrayList<V> neighbors = (ArrayList<V>) graph.getNeighbours(node);
        for (V neighbor : neighbors) {
            L label = graph.getLabel(node, neighbor);
            AbstractEdge<V, L> edge = new Edge<>(node, neighbor, label);
            adjacentEdges.add(edge);
        }

        return adjacentEdges;
    }

    /**
     * Calcola la minima foresta ricoprente del grafo utilizzando l'algoritmo di Prim.
     *
     * @param graph il grafo
     * @return una collezione di archi che compongono la minima foresta ricoprente
     * @throws PriorityQueueException se si verifica un errore nella coda prioritaria
     */
    public static <V, L extends Comparable<L>> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(
            Graph<V, L> graph) throws PriorityQueueException {
        Set<V> visitedNodes = new HashSet<V>();
        int num_nodes = 0;
        List<AbstractEdge<V, L>> forestEdges = new ArrayList<>();
        PriorityQueue<AbstractEdge<V, L>> priorityQueue = new PriorityQueue<AbstractEdge<V, L>>(
                Comparator.comparing(AbstractEdge::getLabel));
        AbstractCollection<V> nodes = new ArrayList<>();
        nodes = graph.getNodes();

        while (!nodes.isEmpty()) {
            V startNode = nodes.iterator().next(); // Partenza casuale
            visitedNodes.add(startNode);
            nodes.remove(startNode);
            num_nodes++;
            List<AbstractEdge<V, L>> edges = getEdgesFromNode(graph, startNode);

            for (AbstractEdge<V, L> edge : edges) {
                priorityQueue.push(edge);
            }

            while (!priorityQueue.empty()) {
                AbstractEdge<V, L> minEdge = priorityQueue.top();
                priorityQueue.pop();

                V nextNode = minEdge.getEnd();

                if (!visitedNodes.contains(nextNode)) {
                    visitedNodes.add(nextNode);
                    nodes.remove(nextNode);
                    forestEdges.add(minEdge);
                    num_nodes++;

                    for (AbstractEdge<V, L> edge : getEdgesFromNode(graph, nextNode)) {
                        if (!visitedNodes.contains(edge.getEnd())) {
                            priorityQueue.push(edge);
                        }
                    }
                }
            }
        }
        System.out.println("Numero Nodi dopo l'algoritmo di Prim: " + num_nodes);//stampa aggiunta da noi per visualizzare il numero di nodi dopo l'algortimo di Prim
        return forestEdges;
    }

     //funzione che Legge un grafo da un file CSV.

    private static Graph<String, Float> readGraphFromCSV(String filePath) throws IOException {
        Graph<String, Float> graph = new Graph<String, Float>(false, true);

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] fields = line.split(",");
                String place1 = fields[0];
                String place2 = fields[1];
                float distance = Float.parseFloat(fields[2]);

                graph.addNode(place1);
                graph.addNode(place2);
                graph.addEdge(place1, place2, distance);
                if (!graph.isDirected())
                    graph.addEdge(place2, place1, distance); // Aggiungi anche l'arco di ritorno
            }
        }

        return graph;
    }




    //funzione che scrive la foresta di archi su un file CSV.
    private static void writeForestToCSV(Collection<? extends AbstractEdge<String, Float>> forestEdges, String filePath)
            throws IOException {
        double sumofedgeweight = 0;

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            for (AbstractEdge<String, Float> edge : forestEdges) {
                sumofedgeweight += (double) edge.getLabel();
                String row = edge.getStart() + "," + edge.getEnd() + "," + edge.getLabel().toString();
                writer.write(row);
                writer.newLine();
            }
        }
        DecimalFormat df = new DecimalFormat("#");
        String sumofedgeweight_str = df.format(sumofedgeweight);
        System.out.println("Peso degli archi: " + sumofedgeweight_str + " Km");
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java Prim <input_csv_path> <output_csv_path>");
            return;
        }

        String inputPath = args[0];
        String outputPath = args[1];

        try {
            // Leggi i dati CSV del grafo
            Graph<String, Float> graph = readGraphFromCSV(inputPath);

            System.out.println("Numero Nodi prima dell'algoritmo di Prim: " + graph.getNodes().size() + "\n"
                    + "Numero Archi prima dell'algoritmo di Prim: " + graph.getEdges().size() + "\n");
            // Calcola la minima foresta ricoprente con l'algoritmo di Prim
            Collection<? extends AbstractEdge<String, Float>> forestEdges = minimumSpanningForest(graph);
            System.out.println("Numero Archi dopo l'algoritmo di Prim: " + forestEdges.size() + "\n");
            // Scrivi su standard output una descrizione della foresta calcolata come CSV
            writeForestToCSV(forestEdges, outputPath);
        } catch (IOException e) {
            System.out.println("Si è verificato un errore durante la lettura o la scrittura dei file.");
            e.printStackTrace();
        } catch (PriorityQueueException e) {
            System.out.println("Si è verificato un errore nell'uso della coda prioritaria.");
            e.printStackTrace();
        }
    }
}
