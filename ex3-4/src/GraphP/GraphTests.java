package GraphP;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.Collection;
public class GraphTests {
    private Graph<Integer, String> graph;
    private Graph<Integer, String> Undirected_graph;
    @Before
    public void setUp() {
        graph = new Graph<>(true, true);
        Undirected_graph = new Graph<>(false, true); // Grafo non orientato e etichettato
    }

    @Test
    public void testAddNode() {
        Assert.assertTrue(graph.addNode(1));
        Assert.assertTrue(graph.addNode(2));
        Assert.assertFalse(graph.addNode(1));
        Assert.assertTrue(Undirected_graph.addNode(1));
        Assert.assertTrue(Undirected_graph.addNode(2));
        Assert.assertFalse(Undirected_graph.addNode(1));
    }

    @Test
    public void testAddEdge() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addNode(3);
        Undirected_graph.addNode(1);
        Undirected_graph.addNode(2);
        Undirected_graph.addNode(3);

        Assert.assertTrue(graph.addEdge(1, 2, "A"));
        Assert.assertTrue(graph.addEdge(1, 3, "B"));
        Assert.assertFalse(graph.addEdge(1, 2, "C"));
        Assert.assertFalse(graph.addEdge(1, 4, "D"));
        Assert.assertTrue(Undirected_graph.addEdge(1, 2, "A"));
        Assert.assertTrue(Undirected_graph.addEdge(1, 3, "B"));
        Assert.assertFalse(Undirected_graph.addEdge(1, 2, "C"));
        Assert.assertFalse(Undirected_graph.addEdge(1, 4, "D"));
    }

    @Test
    public void testContainsNode() {
        graph.addNode(1);
        Undirected_graph.addNode(1);
        Assert.assertTrue(graph.containsNode(1));
        Assert.assertFalse(graph.containsNode(2));
        Assert.assertTrue(Undirected_graph.containsNode(1));
        Assert.assertFalse(Undirected_graph.containsNode(2));
    }

    @Test
    public void testContainsEdge() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addEdge(1, 2, "A");
        Undirected_graph.addNode(1);
        Undirected_graph.addNode(2);
        Undirected_graph.addEdge(1, 2, "A");
        Assert.assertTrue(graph.containsEdge(1, 2));
        Assert.assertFalse(graph.containsEdge(2, 1));
        Assert.assertFalse(graph.containsEdge(1, 3));
        Assert.assertTrue(Undirected_graph.containsEdge(1, 2));
        Assert.assertTrue(Undirected_graph.containsEdge(2, 1));
        Assert.assertFalse(graph.containsEdge(1, 3));
    }

    @Test
    public void testRemoveNode() {
        graph.addNode(1);
        Undirected_graph.addNode(1);
        Assert.assertTrue(graph.removeNode(1));
        Assert.assertFalse(graph.removeNode(2));
        Assert.assertTrue(Undirected_graph.removeNode(1));
        Assert.assertFalse(Undirected_graph.removeNode(2));
    }

    @Test
    public void testRemoveEdge() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addEdge(1, 2, "A");
        Undirected_graph.addNode(1);
        Undirected_graph.addNode(2);
        Undirected_graph.addEdge(1, 2, "A");
        Assert.assertTrue(graph.removeEdge(1, 2));
        Assert.assertFalse(graph.removeEdge(1, 2));
        Assert.assertTrue(Undirected_graph.removeEdge(1, 2));
        Assert.assertFalse(Undirected_graph.removeEdge(1, 2));

    }

    @Test
    public void testNumNodes() {
        graph.addNode(1);
        graph.addNode(2);
        Undirected_graph.addNode(1);
        Undirected_graph.addNode(2);
        Assert.assertEquals(2, graph.numNodes());
        Assert.assertEquals(2, Undirected_graph.numNodes());
    }

    @Test
    public void testNumEdges() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addEdge(1, 2, "A");
        Undirected_graph.addNode(1);
        Undirected_graph.addNode(2);
        Undirected_graph.addEdge(1, 2, "A");
        Assert.assertEquals(1, graph.numEdges());
        Assert.assertEquals(1, Undirected_graph.numEdges());
    }

    @Test
    public void testGetNodes() {
        graph.addNode(1);
        graph.addNode(2);
        Collection<Integer> nodes = graph.getNodes();
        Undirected_graph.addNode(1);
        Undirected_graph.addNode(2);
        Collection<Integer> U_nodes = Undirected_graph.getNodes();
        Assert.assertEquals(2, nodes.size());
        Assert.assertTrue(nodes.contains(1));
        Assert.assertTrue(nodes.contains(2));
        Assert.assertEquals(2, U_nodes.size());
        Assert.assertTrue(U_nodes.contains(1));
        Assert.assertTrue(U_nodes.contains(2));
    }

    @Test
    public void testGetEdges() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addEdge(1, 2, "A");
        Collection<AbstractEdge<Integer, String>> edges = graph.getEdges();
        Assert.assertEquals(1, edges.size());
        AbstractEdge<Integer, String> edge = edges.iterator().next();
        Assert.assertEquals(1, (int) edge.getStart());
        Assert.assertEquals(2, (int) edge.getEnd());
        Assert.assertEquals("A", edge.getLabel());

        Undirected_graph.addNode(1);
        Undirected_graph.addNode(2);
        Undirected_graph.addEdge(1, 2, "A");

        Collection<AbstractEdge<Integer, String>> U_edges = Undirected_graph.getEdges();
        Assert.assertEquals(2, U_edges.size());

        boolean hasEdge12 = false;
        boolean hasEdge21 = false;

        for (AbstractEdge<Integer, String> U_edge : U_edges) {
            int start = U_edge.getStart();
            int end = U_edge.getEnd();
            String label = U_edge.getLabel();

            if (start == 1 && end == 2 && label.equals("A")) {
                hasEdge12 = true;
            } else if (start == 2 && end == 1 && label.equals("A")) {
                hasEdge21 = true;
            }
        }

        Assert.assertTrue(hasEdge12);
        Assert.assertTrue(hasEdge21);



    }

    @Test
    public void testGetNeighbours() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addNode(3);
        graph.addEdge(1, 2, "A");
        graph.addEdge(1, 3, "B");
        Collection<Integer> neighbours = graph.getNeighbours(1);
        Assert.assertEquals(2, neighbours.size());
        Assert.assertTrue(neighbours.contains(2));
        Assert.assertTrue(neighbours.contains(3));

        Undirected_graph.addNode(1);
        Undirected_graph.addNode(2);
        Undirected_graph.addNode(3);
        Undirected_graph.addEdge(1, 2, "A");
        Undirected_graph.addEdge(1, 3, "B");

        Collection<Integer> U_neighbours = Undirected_graph.getNeighbours(1);
        Assert.assertEquals(2, U_neighbours.size());
        Assert.assertTrue(U_neighbours.contains(2));
        Assert.assertTrue(U_neighbours.contains(3));
    }

    @Test
    public void testGetLabel() {
        graph.addNode(1);
        graph.addNode(2);
        graph.addEdge(1, 2, "A");
        Assert.assertEquals("A", graph.getLabel(1, 2));
        Assert.assertNull(graph.getLabel(2, 1));
        Assert.assertNull(graph.getLabel(1, 3));

        Undirected_graph.addNode(1);
        Undirected_graph.addNode(2);
        Undirected_graph.addEdge(1, 2, "A");

        Assert.assertEquals("A", Undirected_graph.getLabel(1, 2));
        Assert.assertEquals("A", Undirected_graph.getLabel(2, 1));
        Assert.assertNull(Undirected_graph.getLabel(1, 3));
    }


}

