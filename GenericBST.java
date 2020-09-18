// Juan Gonzalez



import java.io.*;
import java.util.*;

//contains data and refrences to children
class Node<Generic extends Comparable<Generic>>
{
	Generic data;
	Node<Generic> left, right;

	Node(Generic data)
	{
		this.data = data;
	}
}

public class GenericBST<Generic extends Comparable<Generic>>
{
	private Node<Generic> root;
	//puts data into the tree
	//recursive kick-off
	public void insert(Generic data)
	{
		root = insert(root, data);
	}
	//puts data into the tree
	private Node<Generic> insert(Node<Generic> root, Generic data)
	{
		//sees if data belongs left of the current node or right of it
		if (root == null)
		{
			return new Node<Generic>(data);
		}
		else if (data.compareTo(root.data) < 0)
		{
			root.left = insert(root.left, data);
		}
		else if (data.compareTo(root.data) > 0)
		{
			root.right = insert(root.right, data);
		}
		else
		{
			// disallowing insertion of duplicate values
			;
		}
		//return places it
		return root;
	}

	//find and delete a piece of data
	//recursive kick-off
	public void delete(Generic data)
	{
		root = delete(root, data);
	}

	//finds and delete a node from the tree, recursively
	//fixes it if deleted had children
	//no broken families allowed =)
	private Node<Generic> delete(Node<Generic> root, Generic data)
	{
		//find data
		if (root == null)
		{
			return null;
		}
		else if (data.compareTo(root.data) < 0)
		{
			root.left = delete(root.left, data);
		}
		else if (data.compareTo(root.data) > 0)
		{
			root.right = delete(root.right, data);
		}
		//data found, remove
		else
		{
			if (root.left == null && root.right == null)
			{
				return null;
			}
			else if (root.right == null)
			{
				return root.left;
			}
			else if (root.left == null)
			{
				return root.right;
			}
			//fix tree, node had children.
			else
			{
				root.data = findMax(root.left);
				root.left = delete(root.left, root.data);
			}
		}
		//return new tree
		return root;
	}

	// This method assumes root is non-null, since this is only called by
	// delete() on the left subtree, and only when that subtree is non-empty.
	private Generic findMax(Node<Generic> root)
	{
		while (root.right != null)
		{
			root = root.right;
		}

		return root.data;
	}

	// Returns true if the value is contained in the BST, false otherwise.
	// recursive kick-off
	public boolean contains(Generic data)
	{
		return contains(root, data);
	}
	//recursively checks to see if value is in the tree
	private boolean contains(Node<Generic> root, Generic data)
	{
		if (root == null)
		{
			return false;
		}
		else if (data.compareTo(root.data) < 0)
		{
			return contains(root.left, data);
		}
		else if (data.compareTo(root.data) > 0)
		{
			return contains(root.right, data);
		}
		else
		{
			return true;
		}
	}
	//recursive kick-off function
	public void inorder()
	{
		System.out.print("In-order Traversal:");
		inorder(root);
		System.out.println();
	}
	//read and print tree in  in-order, left root right. recursive function.
	private void inorder(Node<Generic> root)
	{
		if (root == null)
			return;

		inorder(root.left);
		System.out.print(" " + root.data);
		inorder(root.right);
	}
	//recursive kick-off function
	public void preorder()
	{
		System.out.print("Pre-order Traversal:");
		preorder(root);
		System.out.println();
	}

	//read and print tree in pre-order, root left right. recursive function.
	private void preorder(Node<Generic> root)
	{
		if (root == null)
			return;

		System.out.print(" " + root.data);
		preorder(root.left);
		preorder(root.right);
	}
	//kick off recursive traversal
	public void postorder()
	{
		System.out.print("Post-order Traversal:");
		postorder(root);
		System.out.println();
	}
	//read and print tree in post order, left right root. recursive function.
	private void postorder(Node<Generic> root)
	{
		if (root == null)
			return;

		postorder(root.left);
		postorder(root.right);
		System.out.print(" " + root.data);
	}

}
