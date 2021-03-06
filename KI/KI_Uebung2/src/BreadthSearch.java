import java.util.ArrayList;
import java.util.List;

public class BreadthSearch {
	
	private List<State> solution = new ArrayList<State>();
	private List<State> solutionTracking = new ArrayList<State>();
	
	State start, finish;
	
	
	public void solve(State first, State finish){
		this.start = first;
		this.finish = finish;
		first.setVisited();
		solution.add(first);	
		solutionTracking.add(first);
		solve_rek(first, finish);
	}	
	
	public void solve_rek(State current, State finish){
		State next = solution.remove(0);
		if (next.equals(finish)){
			printSolution();
			solution = null; // stops the algorithm from further execution (produces exception -> catch)
			return;
		}
		for (State s : next.getFollowingStates()){
			solution.add(s);	
			solutionTracking.add(s);
			s.setParent(current);
			s.setVisited();
		}
		solve_rek(solution.get(0), finish);
	}
	
	public void printSolution(){
		ArrayList<State> output = new ArrayList<State>();
		for (State i = solutionTracking.get(solutionTracking.indexOf(finish)); !i.equals(start); i = i.getParent()){
			output.add(i); // reversing the list from: finish->...->start to start->...->finish
		}
		output.add(start);
		for (int i = output.size() -1 ; i >= 0; --i){
			System.out.print(output.get(i));
		}
	}
}
