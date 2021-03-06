import java.util.ArrayList;
import java.util.List;


public class DepthSearch {
	
	private List<State> solution = new ArrayList<State>();

	public void solve(State current, State finish){
		solution.add(current);
		if (current.equals(finish)){
			System.out.println(solution);
			solution = null; // stops the algorithm from further execution (produces exception -> catch)
			return;
		} else {
			for (State s : current.getFollowingStates()){
				s.setVisited();
				solve(s, finish);
			}
		}	
		solution.remove(solution.size()-1);
	}
}
