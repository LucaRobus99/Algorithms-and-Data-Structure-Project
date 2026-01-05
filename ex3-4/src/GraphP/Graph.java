/**
 * Questa classe rappresenta un grafo generico.
 * Un grafo può essere diretto o non diretto e può essere etichettato o non etichettato.
 *
 * @param <V> il tipo di dati per i nodi del grafo
 * @param <L> il tipo di dati per le etichette degli archi del grafo
 */
package GraphP;

import java.util.*;

public class Graph<V, L> implements AbstractGraph<V, L> {
    private boolean directed;
    private boolean labelled;
    private HashMap<V, List<AbstractEdge<V, L>>> adjacencyMap;
    private int numEdges;

    /**
     * Crea un nuovo grafo.
     *
     * @param directed true se il grafo è diretto, false altrimenti
     * @param labelled true se il grafo è etichettato, false altrimenti
     */
    public Graph(boolean directed, boolean labelled) {
        this.directed = directed;
        this.labelled = labelled;
        this.adjacencyMap = new HashMap<>();
        this.numEdges = 0;
    }

    /**
     * Restituisce true se il grafo è diretto, false altrimenti.
     *
     * @return true se il grafo è diretto, false altrimenti
     */
    @Override
    public boolean isDirected() {
        return directed;
    }

    /**
     * Restituisce true se il grafo è etichettato, false altrimenti.
     *
     * @return true se il grafo è etichettato, false altrimenti
     */
    @Override
    public boolean isLabelled() {
        return labelled;
    }

    /**
     * Aggiunge un nodo al grafo.
     *
     * @param a il nodo da aggiungere
     * @return true se il nodo è stato aggiunto con successo, false se il nodo esiste già nel grafo
     */
    @Override
    public boolean addNode(V a) {
        if (containsNode(a)) {
            return false; // Nodo già presente
        }
        adjacencyMap.put(a, new ArrayList<>());
        return true;
    }

    /**
     * Aggiunge un arco al grafo.
     *
     * @param a il nodo di partenza dell'arco
     * @param b il nodo di arrivo dell'arco
     * @param l l'etichetta dell'arco
     * @return true se l'arco è stato aggiunto con successo, false se i nodi non esistono o se l'arco già esiste nel grafo
     */
    @Override
    public boolean addEdge(V a, V b, L l) {
        if (!containsNode(a) || !containsNode(b)) {
            return false; // Nodi non esistenti
        }
        if (labelled && l == null) {
            return false; // Il grafo è etichettato, ma non viene fornita un'etichetta
        }
        if (!containsEdge(a, b)) {
            adjacencyMap.get(a).add(new Edge<V, L>(a, b, l));
            if (!directed) {
                adjacencyMap.get(b).add(new Edge<V, L>(b, a, l));
            }
            numEdges++;
            return true;
        }
        return false; // Arco già presente
    }

    /**
     * Verifica se un nodo esiste nel grafo.
     *
     * @param a il nodo da cercare
     * @return true se il nodo esiste nel grafo, false altrimenti
     */
    @Override
    public boolean containsNode(V a) {
        return adjacencyMap.containsKey(a);
    }

    /**
     * Verifica se un arco esiste nel grafo.
     *
     * @param a il nodo di partenza dell'arco
     * @param b il nodo di arrivo dell'arco
     * @return true se l'arco esiste nel grafo, false altrimenti
     */
    @Override
    public boolean containsEdge(V a, V b) {
        if (!containsNode(a) || !containsNode(b)) {
            return false; // Nodi non esistenti
        }
        List<AbstractEdge<V, L>> edges = adjacencyMap.get(a);
        for (AbstractEdge<V, L> edge : edges) {
            if (edge.getEnd().equals(b)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Rimuove un nodo dal grafo.
     *
     * @param a il nodo da rimuovere
     * @return true se il nodo è stato rimosso con successo, false se il nodo non esiste nel grafo
     */
    @Override
    public boolean removeNode(V a) {
        if (!containsNode(a)) {
            return false; // Nodo non presente
        }
        List<AbstractEdge<V, L>> edgesToRemove = adjacencyMap.get(a);
        for (V node : adjacencyMap.keySet()) {
            List<AbstractEdge<V, L>> edges = adjacencyMap.get(node);
            edges.removeAll(edgesToRemove);
        }
        adjacencyMap.remove(a);
        numEdges -= edgesToRemove.size();
        return true;
    }

    /**
     * Rimuove un arco dal grafo.
     *
     * @param a il nodo di partenza dell'arco
     * @param b il nodo di arrivo dell'arco
     * @return true se l'arco è stato rimosso con successo, false se i nodi non esistono o se l'arco non esiste nel grafo
     */
    @Override
    public boolean removeEdge(V a, V b) {
        if (!containsNode(a) || !containsNode(b)) {
            return false; // Nodi non esistenti
        }
        List<AbstractEdge<V, L>> edges = adjacencyMap.get(a);
        for (AbstractEdge<V, L> edge : edges) {
            if (edge.getEnd().equals(b)) {
                edges.remove(edge);
                if (!directed) {
                    adjacencyMap.get(b).removeIf(e -> e.getEnd().equals(a));
                }
                numEdges--;
                return true;
            }
        }
        return false; // Arco non presente
    }

    /**
     * Restituisce il numero di nodi nel grafo.
     *
     * @return il numero di nodi nel grafo
     */
    @Override
    public int numNodes() {
        return adjacencyMap.size();
    }

    /**
     * Restituisce il numero di archi nel grafo.
     *
     * @return il numero di archi nel grafo
     */
    @Override
    public int numEdges() {
        return numEdges;
    }

    /**
     * Restituisce una collezione di nodi presenti nel grafo.
     *
     * @return una collezione di nodi presenti nel grafo
     */
    @Override
    public AbstractCollection<V> getNodes() {
        AbstractCollection<V> nodes = new ArrayList<>();
        nodes.addAll(adjacencyMap.keySet());
        return nodes;
    }

    /**
     * Restituisce una collezione di archi presenti nel grafo.
     *
     * @return una collezione di archi presenti nel grafo
     */
    @Override
    public AbstractCollection<AbstractEdge<V, L>> getEdges() {
        AbstractCollection<AbstractEdge<V, L>> edges = new ArrayList<>();
        for (List<AbstractEdge<V, L>> edgeList : adjacencyMap.values()) {
            edges.addAll(edgeList);
        }
        return edges;
    }

    /**
     * Restituisce una collezione di nodi adiacenti al nodo specificato.
     *
     * @param a il nodo di cui si vogliono ottenere i nodi adiacenti
     * @return una collezione di nodi adiacenti al nodo specificato
     */
    @Override
    public AbstractCollection<V> getNeighbours(V a) {
        if (!containsNode(a)) {
            return null; // Nodo non presente
        }
        List<AbstractEdge<V, L>> edges = adjacencyMap.get(a);
        AbstractCollection<V> neighbours = new ArrayList<>();
        for (AbstractEdge<V, L> edge : edges) {
            neighbours.add(edge.getEnd());
        }
        return neighbours;
    }

    /**
     * Restituisce l'etichetta dell'arco tra i due nodi specificati.
     *
     * @param a il nodo di partenza dell'arco
     * @param b il nodo di arrivo dell'arco
     * @return l'etichetta dell'arco tra i due nodi specificati
     */
    @Override
    public L getLabel(V a, V b) {
        if (!containsEdge(a, b)) {
            return null; // Arco non presente
        }
        List<AbstractEdge<V, L>> edges = adjacencyMap.get(a);
        for (AbstractEdge<V, L> edge : edges) {
            if (edge.getEnd().equals(b)) {
                return edge.getLabel();
            }
        }
        return null;
    }
}
