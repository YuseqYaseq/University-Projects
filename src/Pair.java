/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * 
 * Pair class template
 * 
 * @param <T1> 1st of the pair
 * @param <T2> 2nd of the pair
 */

public class Pair<T1,T2> {
	public T1 l;
	public T2 r;
	
	Pair(T1 t1, T2 t2)
	{
		l = t1; r = t2;
	}
}
