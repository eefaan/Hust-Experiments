import java.util.NoSuchElementException;
public class Main{
    public static void main(String[] argvs){
    	Queue<Integer> que = new Queue<Integer>();
    	int i;
        int dump = 20;
        
        // add test
        for(i = 0; i < dump; ++i)
            que.add(i);
        System.out.println("insert dump done");
        // add more data
        try{
            que.add(123);
        }
        catch (IllegalStateException e) {
            System.out.println("insert overflow");
        }
        // add exception test
        try{
            que.add(null);
        }
        catch (NullPointerException e) {
            System.out.println("insert error");
        }
        System.out.println("--- insert test done. ---");
        
        
        // remove test
        for(i = 0; i < dump; ++i)
        	System.out.println(que.remove());
        System.out.println("remove dump done");    
        // remove exception test
        try {    
            que.remove();
        } catch (NoSuchElementException e) {
            System.out.println("remove error");
        }
        System.out.println("--- remove test done. ---");
        
        
        // poll null test
        System.out.println(que.poll());
        // poll test
        que.add(100);
        System.out.println(que.poll());
        System.out.println("--- poll test done. ---");
        
        
        // offer test
        que = new Queue<Integer>();
        for(i = 0; i < dump; ++i)
            que.offer(i);
        System.out.println("offer");
        System.out.println("--- offer test done. ---");
        
        
        // peek and element test
        System.out.println(que.peek());
        System.out.println(que.peek());
        System.out.println(que.element());
        System.out.println(que.element());
        // element error test
        for(i = 0; i < dump; ++i){
            que.remove();
        }
        try {
        	que.element();
        }
        catch (NoSuchElementException e){
        	System.out.println("element error");
        }
        que.peek();
        System.out.println("--- peek and element test done. ---");
        
        // two stack test
        for(i = 0; i < dump; ++i) // clear the que
        	que.poll();
        que.add(1);
        que.add(2);
        que.add(3);
        que.remove();
        for(i = 0; i < dump/2; ++i)
        	que.add(i);
        try {
        	que.add(1);
        }
        catch (IllegalStateException e) {
        	System.out.println("insert overflow");
        }
        que.remove();
        que.remove();
        for(i = 0; i < dump/2; ++i)
        	que.remove();
        try {
        	que.remove();
        }
        catch (NoSuchElementException e) {
        	System.out.println("remove overflow");
        }
        
    }
}