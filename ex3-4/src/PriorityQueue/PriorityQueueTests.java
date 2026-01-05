package PriorityQueue;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.*;

public class PriorityQueueTests {
    private PriorityQueue<Integer> priorityQueue;
    private Comparator<Integer>comparator=Comparator.naturalOrder();
    private PriorityQueue<String> priorityQueue_String;
    private Comparator<String> comparator_String = Comparator.naturalOrder();
    @Before
    public void setup() throws PriorityQueueException {
        priorityQueue = new PriorityQueue<>(comparator);
        priorityQueue_String = new PriorityQueue<>(comparator_String);
    }



    @Test
    public void testEmptyPriorityQueue() {
        Assert.assertTrue(priorityQueue_String.empty());
        Assert.assertTrue(priorityQueue.empty());
    }

    @Test
    public void testPush() {
        priorityQueue.push(10);
        priorityQueue_String.push("banana");
        Assert.assertFalse(priorityQueue.empty());
        Assert.assertFalse(priorityQueue.empty());
    }

    @Test
    public void testContains() {
        priorityQueue.push(10);
        priorityQueue_String.push("apple");
        Assert.assertTrue(priorityQueue.contains(10));
        Assert.assertFalse(priorityQueue.contains(20));
        Assert.assertTrue(priorityQueue_String.contains("apple"));
        Assert.assertFalse(priorityQueue_String.contains("orange"));
        
    }

    @Test
    public void testTop() throws PriorityQueueException {
        priorityQueue.push(10);
        priorityQueue.push(20);
        priorityQueue.push(30);
        priorityQueue_String.push("apple");
        priorityQueue_String.push("banana");
        priorityQueue_String.push("cherry");
        
        Assert.assertEquals(Integer.valueOf(10), priorityQueue.top());
        Assert.assertEquals("apple", priorityQueue_String.top());
    }

    @Test
    public void testPop()throws PriorityQueueException {
        priorityQueue.push(10);
        priorityQueue.push(20);
        priorityQueue.push(30);
        priorityQueue.pop();
        priorityQueue_String.push("apple");
        priorityQueue_String.push("banana");
        priorityQueue_String.push("cherry");
        priorityQueue_String.pop();
       
        Assert.assertEquals(Integer.valueOf(20), priorityQueue.top());
        Assert.assertFalse(priorityQueue.contains(10));

        Assert.assertEquals("banana", priorityQueue_String.top());
        Assert.assertFalse(priorityQueue_String.contains("apple"));
    }

    @Test
    public void testRemove()throws PriorityQueueException {
        priorityQueue.push(10);
        priorityQueue.push(20);
        priorityQueue.push(30);
        priorityQueue_String.push("apple");
        priorityQueue_String.push("banana");
        priorityQueue_String.push("cherry");
        
        Assert.assertTrue(priorityQueue.remove(20));
        Assert.assertFalse(priorityQueue.contains(20));
        Assert.assertEquals(Integer.valueOf(10), priorityQueue.top());

        Assert.assertTrue(priorityQueue_String.remove("banana"));
        Assert.assertFalse(priorityQueue_String.contains("banana"));
        Assert.assertEquals("apple", priorityQueue_String.top());
    }

    @Test
    public void testIncreasePriority() throws PriorityQueueException {
        priorityQueue.push(10);
        priorityQueue.push(20);
        priorityQueue.push(30);
        priorityQueue.increasePriority(10, 5);

        priorityQueue_String.push("apple");
        priorityQueue_String.push("banana");
        priorityQueue_String.push("cherry");
        priorityQueue_String.increasePriority("apple", "apricot");
        

        Assert.assertEquals(Integer.valueOf(5), priorityQueue.top());

        Assert.assertEquals("apricot", priorityQueue_String.top());
    }
    

    

   

   

   

   

    

   

    


}
