import java.util.*;
import java.io.*;
import gnu.getopt.*;

/**	
 * @author Jozef Jasek <jozefjasek@gmail.com>
 * @version 1.0
 */
class ParserSystem
{
	/**
	 * Main function
	 * <p>
	 * Takes BiBTeX file and converts it into an object-oriented structure.
	 * If no additional keys/values specified draws all found Entries
	 * <p>
	 * @param args 
	 * -p [path]		: Path to BibTeX file
	 * -k [key]			: Draw Entries with this key matching next value
	 * -w [value]		: Draw Entries with this value matching previous key
	 * -o [character]	: Frame Entries with a new character
	 */
	static public void main(String[] args)
	{
		Getopt g = new Getopt("Parser", args, "p:k:w:o:");
		int c;
		String fileName = "";
		String tekst3 = "";
		Vector<Pair<String, String>> authorNames = new Vector<Pair<String,String>>();
		Vector<String> categoryNames = new Vector<String>();
		char frame = '*';
		String receivedkey = "";
		while((c = g.getopt()) != -1)
		{
			
			switch(c)
			{
			case 112/*p*/: fileName = g.getOptarg(); break;
			case 107/*k*/: receivedkey = g.getOptarg(); break;
			case 119/*w*/: if(receivedkey.toLowerCase().equals("category"))
							{
								categoryNames.add(g.getOptarg());
								break;
							}
							authorNames.add(new Pair<String, String>(receivedkey, g.getOptarg()));
							break;
			case 111/*o*/: frame = g.getOptarg().charAt(0); break;
			}
		}
		try
		{
			for(Scanner sc = new Scanner(new File(fileName)); sc.hasNext(); ) {
				  String line = sc.nextLine();
				  tekst3 += line;
				}
		}catch(FileNotFoundException e)
		{
			System.out.println("File not found!");
		}
		tekst3 = tekst3.replace("\n", "");
		tekst3 = tekst3.replace("	", "");
		tekst3 = tekst3.replace("\r", "");
		BiBData.B.Set(Parser.P.Open(tekst3), frame);
		
		if(!authorNames.isEmpty())
		{
			Vector <Vector<Entry>> data = new Vector<Vector<Entry>>();
			for(Pair<String, String> name : authorNames)
			{
				data.add( BiBData.B.FindAll(name.l.toLowerCase(), name.r) );
			}
			int i = 0;
			for(Vector<Entry> v : data) {
				System.out.println("For " + authorNames.get(i).l.toLowerCase() + " " + authorNames.get(i).r + ":");
				for(Entry e : v)
				{
					e.Draw(frame);
					System.out.println();
				}
				i++;
			}
		}
		if(!categoryNames.isEmpty())
		{
			Vector <Vector<Entry>> data = new Vector<Vector<Entry>>();
			for(String name : categoryNames)
			{
				data.add( BiBData.B.FindCategory(name) );
			}
			int i = 0;
			for(Vector<Entry> v : data) {
				System.out.println("For category " + categoryNames.get(i) + ":");
				for(Entry e : v)
				{
					e.Draw(frame);
					System.out.println();
				}
				i++;
			}
		}
		if(categoryNames.isEmpty() && authorNames.isEmpty())
		{
			BiBData.B.Draw();
		}
	}
	
}