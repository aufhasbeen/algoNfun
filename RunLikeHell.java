// Juan Gonzalez
public class RunLikeHell
{
  public static int maxGain( int [] blocks )
  {
    //result storage
    int[][] gains = new int[blocks.length+1][2];

    for(int i=blocks.length-1;i>=0;i--)
    {
      //fill in if last taken, just simply look ahead
      gains[i][1] = gains[i+1][0];

      //fill in last NOT taken, max of
      //if we did and didn't take the current
      gains[i][0] = Math.max(gains[i+1][1]+blocks[i],gains[i+1][0]);
    }
    //result should be the largest of if we
    //took or didn't take the first one
    return Math.max(gains[0][0],gains[0][1]);
  }
}
