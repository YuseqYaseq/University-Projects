import java.util.concurrent.*;
import java.util.Set;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Misc entry type
 * No mandatory fields
 */

public class misc extends Entry {
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException
	{
		mkey = key;
		Set<String> set = m.keySet();
		hm = m;
		
		//czy sa obowiazkowe pola
		//brak obowiazkowych
		
		//usun ignorowane
		for(String s : set)
		{
			switch(s)
			{
			case "opt":
			case "author":
			case "title":
			case "howpublished":
			case "month":
			case "year":
			case "note":
			case "key": break;
			default:
				hm.remove(s);
			}
		}
	}
}
