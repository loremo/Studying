import java.util.ArrayList;
import java.util.List;


public class DepthSearch {
	
	private List<State> solution = new ArrayList<State>();

	public void solve(State current, State finish){
		if (current.equals(finish)){
			System.out.println(solution);
		} else {
			for (State s : current.getFollowingStates()){
				solution.add(s);
				s.setVisited(true);
				solve(s, finish);
				solution.remove(solution.size()-1);
			}
		}
	}

}
