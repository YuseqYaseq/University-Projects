import java.util.concurrent.*;
import java.util.Set;

/**
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * Inproceedings entry type
 * Mandatory fields:	title
 * 						author
 * 						booktitle
 * 						year
 */

public class inproceedings extends Entry { //również pod nazwą conference
	public void UpdateInfo(ConcurrentHashMap<String, String> m, String key) throws MandatoryFieldEmptyException
	{
		mkey = key;
		Set<String> set = m.keySet();
		hm = m;
		
		//czy sa obowiazkowe pola
		Contains("author");
		Contains("title");
		Contains("booktitle");
		Contains("year");
		
		//usun ignorowane
		for(String s : set)
		{
			switch(s)
			{
			case "author":
			case "title":
			case "booktitle":
			case "year":
			case "opt":
			case "editor":
			case "volume":
			case "number":
			case "series":
			case "pages":
			case "address":
			case "month":
			case "organization":
			case "publisher":
			case "note":
			case "key": break;
			default:
				hm.remove(s);
			}
		}
	}
}
