import java.util.*;
import java.util.concurrent.*;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Book entry type
 * Mandatory fields:	author or editor
 * 						title
 * 						publisher
 * 						year
 */

public class book extends Entry {
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException
	{
		mkey = key;
		hm = m;
		
		//czy sa obowiazkowe pola
		Contains("author", "editor");
		Contains("title");
		Contains("publisher");
		Contains("year");
		
		//usun ignorowane
		//Iterator it = hm.entrySet().iterator();
		//while(it.hasNext())
		Set<String> set = hm.keySet();
		for(String s : set)
		{
			
			switch(s)
			{
			case "author":
			case "editor":
			case "title":
			case "publisher":
			case "year":
			case "volume":
			case "series":
			case "address":
			case "edition":
			case "month":
			case "note":
			case "key": break;
			default:
				hm.remove(s);
			}
		}
	}
}
