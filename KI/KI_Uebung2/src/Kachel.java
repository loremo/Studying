
public class Kachel {
	private String name;
	private boolean flag = false;
	private Kachel 	oben, rechtsOben, rechtsUnten,
					unten, linktsUnten, linksOben = null;
	
	public Kachel(String n){
		name = n;
	}
	
	public boolean getFlag(){
		return flag;
	}
	public void setFlag(){
		flag = true;
	}
	
	public String getName(){
		return name;
	}
	
	public Kachel getNachbar (Richtung r){
		switch (r) {
		case OBEN:
			return oben;
		case RECHTSOBEN:
			return rechtsOben;
		case RECHTSUNTEN:
			return rechtsUnten;
		case UNTEN:
			return unten;
		case LINKSUNTEN:
			return linktsUnten;
		case LINKSOBEN:
			return linksOben;

		default:
			return null;
		}
	}
	
	public void setNachbar (Richtung r, Kachel k){
		switch (r) {
		case OBEN:
			oben = k;
			break;
		case RECHTSOBEN:
			rechtsOben = k;
			break;
		case RECHTSUNTEN:
			rechtsUnten = k;
			break;
		case UNTEN:
			unten = k;
			break;
		case LINKSUNTEN:
			linktsUnten = k;
			break;
		case LINKSOBEN:
			linksOben = k;
			break;
		default:
		}
	}
	
	public boolean isNachbar (Kachel k){
		if (k != null) {
			for (Richtung r : Richtung.values()){
				if (this.getNachbar(r) == k )
					return true;
			}
		}
		return false;
	}
	
	public enum Richtung {
		OBEN, RECHTSOBEN, RECHTSUNTEN,
		UNTEN, LINKSUNTEN, LINKSOBEN
	}
}
