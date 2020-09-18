// Juan Gonzalez
import java.util.*;
import java.io.*;

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

public class TopoPath
{
  public static boolean hasTopoPath(String filename)
  {
    ArrayList<Node> graph = readIn(filename);

    int zeros=0;
    int start =0;

    //must have exactly one vertex to start a path
    //zero means there is no valid sort
    // 2 or more means there are unreachable nodes in the graph
    for(int i =0; i< graph.size();i++)
    {
      if(graph.get(i).inZero())
      {
        start =i;
        if(++zeros>1)
          return false;
      }
    }
    return zeros!=0 && containsPath(graph,start);
  }

  //find valid TopoPath if one exists return true
  private static boolean containsPath(ArrayList<Node> graph, int start)
  {
    Node current = graph.get(start);
    Node next = null;
    int vertices=1;

    do
    {
      current.visit();
      next = nextNode(current);
      current = next;//move along
      vertices++;

    }while(next!=null);

    vertices--;//do while counting error
    //should have visited each one once
    return graph.size()==vertices;
  }
  //retrieve a node for the next part of our path
  //if none is valid return null indicating end of path
  private static Node nextNode(Node current)
  {
    for(int i = 0; i< current.numbOfEdges();i++)
    {
      //must have zero incoming and must not have visited it
      if(current.getEdge(i).inZero() && !current.getEdge(i).didVisit())
        return current.getEdge(i);
    }
    return null;
  }

  private static ArrayList<Node> readIn( String filename)
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
