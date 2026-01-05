package GraphP;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class GraphTestsRunner {
    public static void main(String[] args) {
        Result result = JUnitCore.runClasses(GraphTests.class);

        if (result.wasSuccessful()) {
            System.out.println("All tests passed successfully.");
        } else {
            System.out.println("Test failures occurred:");

            for (Failure failure : result.getFailures()) {
                System.out.println(failure.toString());
            }
        }
    }
}

