import java.util.concurrent.*;
import java.util.Set;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Incollection entry type
 * Mandatory fields:	title
 * 						author
 * 						booktitle
 * 						publisher
 * 						year
 */

public class incollection extends Entry {
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException
	{
		mkey = key;
		Set<String> set = m.keySet();
		hm = m;
		
		//czy sa obowiazkowe pola
		Contains("author");
		Contains("title");
		Contains("booktitle");
		Contains("publisher");
		Contains("year");
		
		//usun ignorowane
		for(String s : set)
		{
			switch(s)
			{
			case "author":
			case "title":
			case "booktitle":
			case "publisher":
			case "year":
			case "opt":
			case "editor":
			case "volume":
			case "number":
			case "series":
			case "type":
			case "chapter":
			case "pages":
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
