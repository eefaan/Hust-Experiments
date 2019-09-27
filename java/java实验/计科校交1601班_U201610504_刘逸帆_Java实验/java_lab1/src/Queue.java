import java.util.Stack;
import java.util.NoSuchElementException;

public class Queue<E> extends Stack<E>{
	public final int dump = 10;
    private  Stack<E> stk;
    
    // first stk: stk, second: super
    public Queue( ){
    	stk = new Stack<E>();
    }
    
	public boolean add(E e) throws IllegalStateException, ClassCastException, NullPointerException, IllegalArgumentException{
		if (e==null) {// if the specified element is null and this queue does not permit null elements
			throw new NullPointerException();
		}
		if (stk.size() == dump) {
			if (this.isEmpty()) {
				while (!stk.isEmpty()) {
					this.push(stk.pop());
				}
				stk.push(e);
			}
			else {
				throw new IllegalStateException();
			}
		}
		else {
			stk.push(e);
		}
		return true;
	}
	
	public boolean offer(E e) throws ClassCastException, NullPointerException, IllegalArgumentException{
		if (e==null) {// if the specified element is null and this queue does not permit null elements
			throw new NullPointerException();
		}
		if (stk.size() == dump) {
			if (this.isEmpty()) {
				while (!stk.isEmpty()) {
					this.push(stk.pop());
				}
				stk.push(e);
			}
			else {
				return false;
			}
		}
		else {
			stk.push(e);
		}
		return true;
	}
	
    public E remove( ) throws NoSuchElementException {
    	if(this.isEmpty()) {
	        if(stk.isEmpty()) {// if this queue is empty
	        	throw new NoSuchElementException();	
	        }
	        else {// move items from 'stk' to 'this' 
	        	while(!stk.isEmpty()) {
	        		this.push(stk.pop());
	        	}
	        	return this.pop();
	        }
		}
	    else {
	        return this.pop();
        }
    }
    
    public E poll( ) {
    	if(this.isEmpty()) {
	        if(stk.isEmpty()) {// if this queue is empty
	        	return null;	
	        }
	        else {// move items in 'stk' to 'this' 
	        	while(!stk.isEmpty()) {
	        		this.push(stk.pop());
	        	}
	        	return this.pop();
	        }
		}
	    else {
	        return this.pop();
        }
    }
    
    public E element( ) throws NoSuchElementException {  /* 在此插入代码*/  
    	if(this.isEmpty()) {
	        if(stk.isEmpty()) {// if this queue is empty
	        	throw new NoSuchElementException();	
	        }
	        else {
	        	while(!stk.isEmpty()) {
	        		this.push(stk.pop());
	        	}
	        	return super.lastElement();
	        }
		}
	    else {// move items in 'stk' to 'this' 
	    	return super.lastElement();
	    }
    }
    
    public E peek ( ) {  /* 在此插入代码*/   
    	if(this.isEmpty()) {
	        if(stk.isEmpty()) {// if this queue is empty
	        	return null;
	        }
	        else {// move items in 'stk' to 'this' 
	        	while(!stk.isEmpty()) {
	        		this.push(stk.pop());
	        	}
	        	return super.lastElement();
	        }
		}
	    else {
	    	return super.lastElement();
	    }
    }
}
