import java.util.concurrent.*;
import java.util.Set;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * unpublished entry type
 * Mandatory fields:	title
 * 						author
 * 						note
 */

public class unpublished extends Entry {
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException
	{
		mkey = key;
		Set<String> set = m.keySet();
		hm = m;
		
		//czy sa obowiazkowe pola
		Contains("author");
		Contains("title");
		Contains("note");
		
		//usun ignorowane
		for(String s : set)
		{
			switch(s)
			{
			case "author":
			case "title":
			case "note":
			case "opt":
			case "month":
			case "year":
			case "key": break;
			default:
				hm.remove(s);
			}
		}
	}
}
