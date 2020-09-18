// Juan Gonzalez
import java.io.*;
import java.util.*;

//class is reused and slightly extended from last assignment
class Node
{
  private int incoming;
  private ArrayList<Node> edges;
  private boolean visited;

  public Node()
  {
    incoming =0;
    visited = false;
    edges = new ArrayList<Node>();
  }
  public boolean didVisit()
  {
    return visited;
  }
  //visit vertex and reduce incoming for edges
  public void visit()
  {
    visited = true;
    for(Node temp : edges)
    {
      temp.reduceIn();
    }
  }
  //undo changes
  public void backtrack()
  {
    visited = false;
    for(Node temp : edges)
    {
      temp.increaseIn();
    }
  }

  public Node getEdge(int e)
  {
    if(e>=edges.size() || e<0)
      return null;

    return edges.get(e);
  }
  public void addEdge(Node e)
  {
    edges.add(e);
  }
  public boolean inZero()
  {
    return incoming==0;
  }
  public void reduceIn()
  {
    if(incoming ==0)
      return;

    incoming--;
  }
  public void increaseIn()
  {
    incoming++;
  }
  public int numbOfEdges()
  {
    return edges.size();
  }
}

public class TopolALLgical
{

  public static HashSet<String> allTopologicalSorts(String filename)
  {
    ArrayList<Node> graph = readIn(filename);
    ret= new HashSet<String>();

    if(graph ==null)
    {
      return TopolALLgical.ret;
    }

    permuteSorts(graph);
    return TopolALLgical.ret;
  }
  public static HashSet<String> ret;

  //recursive implementation, backtrack inherent
  private static void permuteSorts(ArrayList<Node> graph)
  {
    seek(graph,0,new String[graph.size()]);
  }

  private static void seek(ArrayList<Node> graph, int i,String[] path)
  {
    //base case, we got a full path
    if(i== path.length)
    {
      ret.add(assemble(path));
      return;
    }

    for(int j=0;j<graph.size();j++)
    {
      //check if visited and if it has zero incoming edges
      if(!graph.get(j).didVisit() && graph.get(j).inZero())
      {
        //visit the vertex
        graph.get(j).visit();
        path[i]=Integer.toString(j+1);
        //do next step
        seek(graph,i+1,path);
        //undo work and get back to searching
        graph.get(j).backtrack();
      }
    }
  }
  //assemble string from steps taken
  private static String assemble(String[] set)
  {
    String temp = new String();
    int i;
    for(i=0;i< set.length-1;i++)
    {
      temp+=set[i]+" ";
    }
    return temp +set[i];
  }
  private static ArrayList<Node> readIn(String filename)
  {
    try
    {
      Scanner in = new Scanner(new File(filename));

      //add in all vertices to graph
      int nodes = in.nextInt();
      ArrayList<Node> vertices = new ArrayList<>(nodes);
      for(int i =0;i< nodes;i++)
        vertices.add(new Node());
      //add edges to graph
      for(int i =0;i< nodes;i++)
      {
        int edges= in.nextInt();
        Node current = vertices.get(i);
        //add all edges on this line
        for(int j =0;j<edges;j++)
        {
          int linked = in.nextInt();
          //link number decides vertix pulled
          Node next = vertices.get(linked-1);
          next.increaseIn();
          current.addEdge(next);
        }

      }

      in.close();
      return vertices;
    }catch(Exception e)
    {
      e.printStackTrace();
      return null;
    }
  }
}
