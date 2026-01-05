package PriorityQueue;


import java.util.Comparator;
import java.util.*;

/**
 * Questa classe rappresenta una coda prioritaria implementata utilizzando un heap binario.
 * La coda prioritaria mantiene gli elementi in base alla loro priorità, definita da un comparatore fornito.
 *
 * @param <E> il tipo degli elementi nella coda prioritaria
 */
public class PriorityQueue<E> implements AbstractQueue<E> {
    private Comparator<E> comparator;
    private Map<E, Integer> elementIndexMap;
    private List<E> heap;

    /**
     * Crea una nuova istanza di PriorityQueue con il comparatore specificato.
     *
     * @param comparator il comparatore utilizzato per definire la priorità degli elementi
     */
    public PriorityQueue(Comparator<E> comparator) throws PriorityQueueException {
        if(comparator==null) throw new PriorityQueueException("comparator is null");
        this.comparator = comparator;
        this.elementIndexMap = new HashMap<>();
        this.heap = new ArrayList<>();
    }

    /**
     * Verifica se la coda prioritaria è vuota.
     *
     * @return true se la coda prioritaria è vuota, false altrimenti
     */
    public boolean empty() {
        return heap.isEmpty();
    }

    /**
     * Inserisce l'elemento specificato nella coda prioritaria.
     *
     * @param e l'elemento da inserire
     * @return true se l'elemento è stato inserito con successo, false se l'elemento è già presente nella coda prioritaria
     */
    public boolean push(E e) {
        if (contains(e)) {
            return false; // Non permettere duplicati
        }
        int index = heap.size();
        heap.add(e);
        elementIndexMap.put(e, index);
        heapifyUp(index);
        return true;
    }

    /**
     * Verifica se l'elemento specificato è presente nella coda prioritaria.
     *
     * @param e l'elemento da cercare
     * @return true se l'elemento è presente nella coda prioritaria, false altrimenti
     */
    public boolean contains(E e) {
        return elementIndexMap.containsKey(e);
    }

    /**
     * Restituisce l'elemento con la priorità più alta nella coda prioritaria, senza rimuoverlo.
     *
     * @return l'elemento con la priorità più alta
     * @throws PriorityQueueException se la coda prioritaria è vuota
     */
    public E top() throws PriorityQueueException {
        if (empty()) {
            throw new PriorityQueueException("La coda prioritaria è vuota");
        }
        return heap.get(0);
    }

    /**
     * Rimuove e restituisce l'elemento con la priorità più alta dalla coda prioritaria.
     *
     * @throws PriorityQueueException se la coda prioritaria è vuota
     */
    public void pop() throws PriorityQueueException {
        if (empty()) {
            throw new PriorityQueueException("La coda prioritaria è vuota");
        }
        int lastIndex = heap.size() - 1;
        swap(0, lastIndex);
        elementIndexMap.remove(heap.get(lastIndex));
        heap.remove(lastIndex);
        heapifyDown(0);
    }

    /**
     * Rimuove l'elemento specificato dalla coda prioritaria.
     *
     * @param e l'elemento da rimuovere
     * @return true se l'elemento è stato rimosso con successo, false se l'elemento non è presente nella coda prioritaria
     */
    public boolean remove(E e) {
        if (!contains(e)) {
            return false;
        }
        int index = elementIndexMap.get(e);
        int lastIndex = heap.size() - 1;
        swap(index, lastIndex);
        elementIndexMap.remove(e);
        heap.remove(lastIndex);
        if (index == lastIndex) {
            heapifyDown(index);
        } else {
            heapifyUp(index);
            heapifyDown(index);
        }
        return true;
    }

    /**
     * Aumenta la priorità dell'elemento specificato sostituendolo con un nuovo elemento.
     *
     * @param el l'elemento da aggiornare
     * @param e2 il nuovo elemento con la priorità più alta
     * @throws PriorityQueueException se uno dei parametri non è valido per il metodo increasePriority
     */
    public void increasePriority(E el, E e2) throws PriorityQueueException {

        int index = elementIndexMap.get(el);
        heap.set(index, e2);
        elementIndexMap.remove(el);
        elementIndexMap.put(e2, index);
        if (compareElements(e2, heap.get((index - 1) / 2)) < 0) {
            heapifyUp(index);
        } else {
            heapifyDown(index);
        }
    }

    /**
     * Ripristina la proprietà di heap dall'elemento specificato verso l'alto.
     *
     * @param index l'indice dell'elemento da heapificare verso l'alto
     */
    private void heapifyUp(int index) {
        if (index == 0) {
            return;
        }

        int parentIndex = (index - 1) / 2;
        if (index > 0 && compareElements(heap.get(index), heap.get(parentIndex)) < 0) {
            swap(index, parentIndex);
            heapifyUp(parentIndex);
        }
    }

    /**
     * Ripristina la proprietà di heap dall'elemento specificato verso il basso.
     *
     * @param index l'indice dell'elemento da heapificare verso il basso
     */
    private void heapifyDown(int index) {
        int size = heap.size();

        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        int smallestChildIndex = index;
        if (leftChildIndex < size && compareElements(heap.get(leftChildIndex), heap.get(smallestChildIndex)) < 0) {
            smallestChildIndex = leftChildIndex;
        }
        if (rightChildIndex < size && compareElements(heap.get(rightChildIndex), heap.get(smallestChildIndex)) < 0) {
            smallestChildIndex = rightChildIndex;
        }

        if (smallestChildIndex != index) {
            swap(index, smallestChildIndex);
            heapifyDown(smallestChildIndex);
        }
    }

    /**
     * Scambia gli elementi agli indici specificati nell'heap.
     *
     * @param i l'indice del primo elemento
     * @param j l'indice del secondo elemento
     */
    private void swap(int i, int j) {
        E element1 = heap.get(i);
        E element2 = heap.get(j);
        heap.set(i, element2);
        heap.set(j, element1);
        elementIndexMap.put(element1, j); // Aggiorna l'indice del primo elemento
        elementIndexMap.put(element2, i); // Aggiorna l'indice del secondo elemento
    }



    /**
     * Confronta due elementi utilizzando il comparatore specificato.
     *
     * @param e1 il primo elemento
     * @param e2 il secondo elemento
     * @return un valore negativo se e1 è inferiore a e2, zero se sono uguali, un valore positivo se e1 è superiore a e2
     */
    private int compareElements(E e1, E e2) {
        return comparator.compare(e1, e2);
    }
}
