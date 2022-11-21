//package pass1;
//
//public class pass1 {
//
//	public static void main(String[] args) {
//		// TODO Auto-generated method stub
//		System.out.println("Hello!!");
//	}
//
//}
package pass1;

import java.io.*;
import java.util.*;

public class pass1
{
	public static void main(String[] args)
	{
		Vector<String> pntab = new Vector<String>();
		Vector<KPDTAB> kpdtab = new Vector<KPDTAB>();
		Vector<MNT> mnt = new Vector<MNT>();
		Vector<MDT> mdt = new Vector<MDT>();
	 	
		//pass1 start
        try
        {
            File Obj = new File("sample.txt");
            Scanner Reader = new Scanner(Obj);
    		boolean begin = false;
            while (Reader.hasNextLine())
            {
                String data = Reader.nextLine();
                String[] tokens = data.split("\t");
                if(tokens[0].equals("MACRO"))
                {
                	begin = true;
                	continue;
                }
                else if(tokens[0].equals("MEND"))
                {
                	pntab.clear();
                	MDT obj = new MDT("MEND", " ", " ");
                	mdt.add(obj);
                	continue;
                }
                
                if(begin)
                {
                	int pp = 0;
                	int kp = 0;
                	int mdtp = mdt.size();
                	int kpdtp = kpdtab.size();
                	String name = tokens[0];
                	for(int i=1; i<tokens.length; i++)
                	{
                		if(tokens[i].contains("="))
                		{
                			kp++;
                			String[] temp = tokens[i].split("=");
                			if(temp.length == 1)
                			{
                				KPDTAB obj = new KPDTAB(temp[0].replace("&", ""), " ");
                				kpdtab.add(obj);
                				pntab.add(temp[0].replace("&", ""));
                			}
                			else
                			{
                				KPDTAB obj = new KPDTAB(temp[0].replace("&", ""), temp[1]);
                				kpdtab.add(obj);
                				pntab.add(temp[0].replace("&", ""));
                			}
                		}
                		else
                		{
                			pp++;
                			pntab.add(tokens[i].replace("&", ""));
                		}
                	}
                	if(kp == 0)
                		kpdtp = -1;
                	MNT obj = new MNT(name, pp, kp, mdtp, kpdtp);
                	mnt.add(obj);
                	begin = false;
                	continue;
                }
                else
                {
                	String label = tokens[0];
                	String operand1;
                	String operand2;
                	if(tokens[1].contains("="))
                	{
                		operand1 = tokens[1];
                	}
                	else
                	{
                		operand1 = tokens[1].replace("&", "");
                		operand1 = "p," + pntab.indexOf(operand1);
                	}
                	if(tokens[2].contains("="))
                	{
                		operand2 = tokens[2];
                	}
                	else
                	{
                		operand2 = tokens[2].replace("&", "");
                		operand2 = "p," + pntab.indexOf(operand2);
                	}
                	
                	MDT obj = new MDT(label, operand1, operand2);
                	mdt.add(obj);
                }
            }
            Reader.close();
        }
        catch (FileNotFoundException e)
        {
            System.out.println("File not found or error opening the file!!");
        }
        
        //Writing into file MNT
        try
        {
        	FileWriter writer = new FileWriter("MNT.txt", true);
        	for(int i=0; i<mnt.size(); i++)
        	{
        		MNT obj = mnt.get(i);
        		writer.write(obj.name + "\t" + obj.pp + "\t" + obj.kp + "\t" + obj.mdtp + "\t" + obj.kpdtp + "\n");
        	}
        	writer.close();
        }
        catch(IOException e)
        {
        	System.out.println("An error has occurred.");
        }
        
        //Writing into file KPDTAB
        try
        {
        	FileWriter writer = new FileWriter("KPDTAB.txt", true);
        	for(int i=0; i<kpdtab.size(); i++)
        	{
        		KPDTAB obj = kpdtab.get(i);
        		writer.write(obj.name + "\t" + obj.value + "\n");
        	}
        	writer.close();
        }
        catch(IOException e)
        {
        	System.out.println("An error has occurred.");
        }
        
        //Writing into file MDT
        try
        {
        	FileWriter writer = new FileWriter("MDT.txt", true);
        	for(int i=0; i<mdt.size(); i++)
        	{
        		MDT obj = mdt.get(i);
        		writer.write(obj.label + "\t" + obj.operand1 + "\t" + obj.operand2 + "\n");
        	}
        	writer.close();
        }
        catch(IOException e)
        {
        	System.out.println("An error has occurred.");
        }
	}
}

