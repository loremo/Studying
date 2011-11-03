import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public class BreadthSearch {
	
	private List<State> solution = new ArrayList<State>();
	private List<State> solutionTracking = new ArrayList<State>();
	private List<State> path = new ArrayList<State>();
	
	State start, finish;

	public void getSolution(){
		getSolution_rek(finish);
		Collections.reverse(path);
		System.out.println(path);
	}
	public void getSolution_rek(State current) {
		path.add(current);
		int index = -1;
		if (current == this.start)
			return;		
		for (State s : current.getFollowingStates()){
			if (index == -1){
				for (State ss : solutionTracking){
					if (ss.equals(s))
						System.out.println("lolol");
				}
				if(solutionTracking.contains(s)){
					System.out.println("lol");
				}
				index = solutionTracking.indexOf(s);
			}
			if (solutionTracking.indexOf(s) < index && solutionTracking.indexOf(s) != -1)
				index = solutionTracking.indexOf(s);
		}
		getSolution_rek(solutionTracking.get(index));
	}
	
	public void solve(State first, State finish){
		this.start = first;
		this.finish = finish;
		first.setVisited(true);
		solution.add(first);	
		solutionTracking.add(first);
		solve_rek(first, finish);
	}	

	public void solve_rek(State current, State finish){
		State next = solution.remove(0);
		next.setVisited(true);
		if (next.equals(finish)){
			/*System.out.println("Loesung gefunden!");
			System.out.println(solutionTracking.contains(finish));
			State i = solutionTracking.get(solutionTracking.indexOf(finish));*/
			ArrayList<State> output = new ArrayList<State>();
			for (State i = solutionTracking.get(solutionTracking.indexOf(finish)); !i.equals(start); i = i.getParent()){
				output.add(i);
			}
			for (int i = output.size() -1 ; i >= 0; --i){
				System.out.print(output.get(i));
			}
			//System.out.println(solutionTracking);
			return;
		}
		for (State s : next.getFollowingStates()){
			solution.add(s);	
			solutionTracking.add(s);
			((SokobanState)s).setParent(current);
			//s.setVisited(true);
		}
		solve_rek(solution.get(0), finish);
	}
}
