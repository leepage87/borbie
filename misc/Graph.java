import java.util.*;

public class Graph <E> {

    private Map<Vertex<E>, ArrayList<Vertex<E>>> edgeList;


    public Graph () {
        edgeList = new HashMap<Vertex<E>, ArrayList<Vertex<E>>>();
    }

    // add a new edge to this graph
    public void add (E from, E to) {
	// get the 2 vertices or construct them if they are new
	// and add them to the list of vertices
	Vertex<E> fromV = this.getVertex(from);
	Vertex<E> toV = this.getVertex(to);
        if (fromV == null) {
            fromV = new Vertex<E>(from);
	}
	if (toV == null) {
	    toV = new Vertex<E>(to);
	}

	// if this is a new source or dest vertex, add an entry for it to the
	// adjacency list
        if (!edgeList.containsKey(fromV)) 
	    edgeList.put(fromV, new ArrayList<Vertex<E>>());
        if (!edgeList.containsKey(toV)) 
	    edgeList.put(toV, new ArrayList<Vertex<E>>());

	// increment the indegree of "to" vertex for this edge
	toV.inDegree++;
        // add the to adjacency list for the "from" vertex for this edge
        edgeList.get(fromV).add(toV);

    }

    // takes a label and returns the Vertex with that label
    private Vertex<E> getVertex(E label) {
	for (Vertex<E> v : edgeList.keySet()) {
            if (label.equals(v.label))
		return v;
	}
	return null;
    }

    public String toString() {
	String result = "";
	for (Vertex<E> v : edgeList.keySet())
	    result += v + "--> " + edgeList.get(v) + "\n";
	return result;
    }

    // produce a clone of this graph
    public Graph<E> clone() {
	Graph<E> graphCl = new Graph<E>();
	for (Vertex<E> v : this.edgeList.keySet()) {
	    Vertex<E> vCl = v.clone();
	    ArrayList<Vertex<E>> adjListCl = new ArrayList<Vertex<E>>();
	    graphCl.edgeList.put(vCl, adjListCl);
	}

	for (Vertex<E> v : this.edgeList.keySet()) {
	    // get the list for this vertex
	    ArrayList<Vertex<E>> adjList = this.edgeList.get(v);
	    // get the clone for this vertex
	    Vertex<E> vCl = graphCl.getVertex(v.label);
	    // get vCl's adj list
	    ArrayList<Vertex<E>> adjListCl = graphCl.edgeList.get(vCl);
	    // for each w on the adj list for v
            for (Vertex<E> w : adjList) {
                // get the clone vertex
		Vertex <E> wCl = graphCl.getVertex(w.label);
		// add to the clone's adj list
		adjListCl.add(wCl);
	    }
	    // put in the clone adj list
	    graphCl.edgeList.put(vCl, adjListCl);
	}
	return graphCl;
    }

    // stub: return a topological sort of this graph
    // should not destroy the graph
    public String topSort() {
	return null;
    }
}



class Vertex <E> {
    E label;
    int inDegree;

    public Vertex (E label) {
	this(label, 0);
    }

    public Vertex (E label, int inDegree) {
	this.label = label;
	this.inDegree = inDegree;
    }

    public String toString() {
	return label + ":" + inDegree;
    } 

    public Vertex<E> clone() {
        return new Vertex<E>(label, inDegree);
    }   
}



