import java.util.*;

/**
 * 
 * @author Józef Jasek <jozefjasek@gmail.com>
 * 
 * Singleton BiBData class
 * 
 * <p>
 * Contains all Entries found by Parser. Can perform special operations on the data.
 * <p>
 */

public class BiBData {
	
	private BiBData() {}
	
	
	/**
	 * Singleton instance of BiBData
	 */
	static BiBData B = new BiBData();
	
	
	/**
	 * Saves collection created by parser for later use. Must be called before performing operations on data.
	 * @param ve Collection of Entries
	 * @param f Character to replace the frame
	 */
	void Set(Vector<Entry> ve, char f)
	{
		v = ve;
		this.f = f;
	}
	
	
	/**
	 * Draws all Entries
	 */
	public void Draw() {
		
		for(Entry en : v)
		{
			en.Draw(f);
			System.out.println("\n\n");
		}
	}
	
	/**
	 * Finds all Entries which contain matching key and value
	 * @param key Key to match
	 * @param val Value to match
	 * @return Collection of all found Entries
	 */
	public Vector<Entry> FindAll(String key, String val)
	{
		Vector<Entry> ve = new Vector<Entry>();
		if(key.equals("author") || key.equals("editor"))
		{
			Vector<String> authors = new Vector<String>();
			for(Entry e : v) {
				if(e.hm.containsKey(key)) {
					authors = e.toAuthor(e.hm.get(key));
					for(String st : authors)
					{
						if(st.equals(val))ve.add(e);
					}
				}
			}
		}
		else
		{
			for(Entry e : v) {
				if(e.hm.containsKey(key)) {
					if(e.hm.get(key).equals(val))ve.add(e);
				}
			}	
		}
		return ve;
	}
	
	/**
	 * Finds all Entries of said category
	 * @param category Category to find
	 * @return Collection of all found Entries
	 */
	public Vector<Entry> FindCategory(String category)
	{
		Vector<Entry> ve = new Vector<Entry>();
		for(Entry e : v)
		{
			if(e.getClass().getSimpleName().toLowerCase().equals(category.toLowerCase())) ve.add(e);
		}
		return ve;
	}
	
	private Vector<Entry> v;
	private char f;
}
