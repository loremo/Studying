import java.util.ArrayList;

public interface State {	
	public void setParent(State s);
	public State getParent();
	public boolean equals(Object o);
	public ArrayList<State> getFollowingStates();
	public void setVisited();
	public boolean visited();
}
