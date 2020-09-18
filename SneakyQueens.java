/*
Juan Gonzalez
*/
import java.util.*;

public class SneakyQueens
{
  public static boolean allTheQueensAreSafe(ArrayList<String> coordinateStrings,int boardSize)
  {
    //too many queens, pigeon hole principle!!!!
    if(coordinateStrings.size()>boardSize)
      return false;
    /*
    coord holds the x and y coordinates of queen
    bpos holds y=1x+b, the b
    bneg holds y=-1x+b, the b
    the last two are frequency arrays for x and y
    */
    int[][] coord = new int[coordinateStrings.size()][2];
    int[] bpos = new int[boardSize*2+2];
    int[] bneg = new int[boardSize*2+2];
    int[] xcheck = new int[boardSize+1];
    int[] ycheck = new int[boardSize+1];

    for(int i=0;i<coordinateStrings.size();i++)
    {
      String temp=coordinateStrings.get(i);
      String first=temp.split("(\\d)")[0];//get char sequence
      coord[i][0]=conv(first);//convert to int

      coord[i][1]=conv(temp.substring(first.length()));//2 for 1


    }
    //very angry realization that y-x can be negative, so shifted
    int ughhhhhhh=(boardSize*2+2)/2;

    for(int i=0;i<coord.length;i++)
    {
      /*
      Check to see if they share a b in y=mx+b
      2 b checks for m=1 and m=-1
      also check to see if y or x hit twice.
      */
       if(++bpos[ (coord[i][1]-coord[i][0])+ughhhhhhh ]>1 ||
          ++bneg[ coord[i][1]+coord[i][0] ]>1             ||
          ++ycheck[ coord[i][1] ]>1                       ||
          ++xcheck[ coord[i][0] ]>1                        )
          return false;
    }
    return true;
  }

  private static int conv(String factor)
  {
    int retVal=0;
    try
    {
      //if its a normal number we good
      return Integer.parseInt(factor);

    }catch(Exception e)
    {
      //base 26 conversion. power is inverted so start from end.
      for(int i=factor.length()-1;i>=0;i-- )
      {
        int reali= (factor.length()-1) -i;
        retVal+=((factor.charAt(i)-'a')+1)*Math.pow(26,reali);
      }
      return retVal;
    }
  }

}
