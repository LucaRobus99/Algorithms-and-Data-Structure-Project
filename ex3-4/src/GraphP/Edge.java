package GraphP;

/**
 * Rappresenta un arco in un grafo generico.
 *
 * @param <V> il tipo di dato per i vertici dell'arco
 * @param <L> il tipo di dato per l'etichetta dell'arco
 */
public class Edge<V, L> implements AbstractEdge<V, L> {

    private V start;
    private V end;
    private L label;

    /**
     * Crea un nuovo oggetto Edge con i vertici e l'etichetta specificati.
     *
     * @param start il vertice di partenza dell'arco
     * @param end il vertice di arrivo dell'arco
     * @param label l'etichetta associata all'arco
     */
    public Edge(V start, V end, L label) {
        this.start = start;
        this.end = end;
        this.label = label;
    }

    /**
     * Restituisce il vertice di partenza dell'arco.
     *
     * @return il vertice di partenza
     */
    @Override
    public V getStart() {
        return start;
    }

    /**
     * Restituisce il vertice di arrivo dell'arco.
     *
     * @return il vertice di arrivo
     */
    @Override
    public V getEnd() {
        return end;
    }

    /**
     * Restituisce l'etichetta dell'arco.
     *
     * @return l'etichetta dell'arco
     */
    @Override
    public L getLabel() {
        return label;
    }
}
