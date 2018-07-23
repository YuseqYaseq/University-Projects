import static org.junit.Assert.*;
import java.util.*;

import org.junit.Test;

public class ParserTest {

	@Test
	public void OpenTest() {
		
		
		Vector<Entry> v;
		String s1 = "@misc{z, author = 123}";
		String s2 = "@misc{z, opt = \"\",}";
		String s3 = "@misc{z, title={zz},howpublished=\"aa\"}";
		String s4 = "@misc{z, month=jan}";
		String s5 = "@String {stest = \"{is it working?}\"}\r\n" + 
				"@String {stest2 = {\"is it still working?\"}}\r\n" + 
				"@String {yet = \" yet?\"}\r\n" + 
				"@String {stest3 = \"anything \" # {broken} # yet}\r\n" + 
				"\r\n" + 
				"@misc {s1, author = stest, opt = stest2, month = stest3, title = stest # stest2 # {.}}\r\n" + 
				"\r\n" + 
				"@misc{s2, author = 123 # stest, opt = stest # 123}\r\n" + 
				"@misc{s3, author = \"aa\" # stest3, opt = \"bb\" # stest # \"cc\"}\r\n" + 
				"@misc{s4, author = {{dbrackets}} # stest}";
		
		v = Parser.P.Open(s1);
		if(!v.get(0).hm.get("author").equals("123")) fail("S1");
		if(!v.get(0).mkey.equals("z")) fail("S1 - key" + v.get(0).mkey);
		
		v = Parser.P.Open(s2);
		if(!v.get(0).hm.get("opt").equals("")) fail("S2");
		
		v = Parser.P.Open(s3);
		if(!v.get(0).hm.get("title").equals("zz")) fail("S3 - title");
		if(!v.get(0).hm.get("howpublished").equals("aa")) fail("S3 - hp");
		
		v = Parser.P.Open(s4);
		if(!v.get(0).hm.get("month").equals("January")) fail("S4");
		
		v = Parser.P.Open(s5);
		if(!v.get(0).hm.get("author").equals("{is it working?}")) fail("S5 - author");
		if(!v.get(0).hm.get("opt").equals("\"is it still working?\"")) fail("S5 - opt");
		if(!v.get(0).hm.get("month").equals("anything broken yet?")) fail("S5 - month");
		if(!v.get(0).hm.get("title").equals("{is it working?}\"is it still working?\".")) fail("S5 - title");
		
		if(!v.get(1).hm.get("author").equals("123{is it working?}")) fail("S5 -1- author");
		if(!v.get(1).hm.get("opt").equals("{is it working?}123")) fail("S5 -1- opt");
		
		if(!v.get(2).hm.get("author").equals("aaanything broken yet?")) fail("S5 -2- author");
		if(!v.get(2).hm.get("opt").equals("bb{is it working?}cc")) fail("S5 -2- opt");
		
		if(!v.get(3).hm.get("author").equals("{dbrackets}{is it working?}")) fail("S5 -3- author");
	}

}
