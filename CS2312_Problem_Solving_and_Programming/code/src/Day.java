

public class Day implements Cloneable,Comparable<Day>{
	
	private int year;
	private int month;
	private int day;
	private static final String MonthNames = "JanFebMarAprMayJunJulAugSepOctNovDec";
	
	public Day(int y, int m, int d) {
		this.year=y;
		this.month=m;
		this.day=d;		
	}
	
	public Day(String sDay) {
		set(sDay);
	}
	
	public void set(String sDay) {
		String[] sDayParts = sDay.split("-");
		this.year = Integer.parseInt(sDayParts[2]);
		this.day = Integer.parseInt(sDayParts[0]);
		this.month = MonthNames.indexOf(sDayParts[1])/3+1;
	}
	

	// check if a given year is a leap year
	static public boolean isLeapYear(int y)
	{
		if (y%400==0)
			return true;
		else if (y%100==0)
			return false;
		else if (y%4==0)
			return true;
		else
			return false;
	}
	
	// check if y,m,d valid
	static public boolean valid(int y, int m, int d)
	{
		if (m<1 || m>12 || d<1) return false;
		switch(m){
			case 1: case 3: case 5: case 7:
			case 8: case 10: case 12:
					 return d<=31; 
			case 4: case 6: case 9: case 11:
					 return d<=30; 
			case 2:
					 if (isLeapYear(y))
						 return d<=29; 
					 else
						 return d<=28; 
		}
		return false;
	}
	
	private boolean isEndOfAMonth() 
    {
        if (valid(year,month,day+1)) //A smart methd: check whether (year month [day+1]) is still a valid date
            return false;
        else
            return true;
    }
     
    private Day next() 
    {
        if (isEndOfAMonth())
            if (month==12)
                return new Day(year+1,1,1); //Since the current day is the end of the year, the next day should be Jan 01
            else
                return new Day(year,month+1,1); // <== your task: first day of next month
        else
            return new Day(year,month,day+1); // <== your task: next day of current month
    }
	
	static public int elapse(Day d1, Day d2) {
		int ans = 0;
		if(d1.compareTo(d2)<0) {
			for(Day tmpDay = d1.clone();tmpDay.compareTo(d2)!=0;tmpDay=tmpDay.next()) {
				ans++;
			}
		}
		else {
			for(Day tmpDay = d2.clone();tmpDay.compareTo(d1)!=0;tmpDay=tmpDay.next()) {
				ans++;
			}
			ans = -ans;
		}
		return ans+1;
	}
	
	// Return a string for the day like dd MMM yyyy
	public String toString() {
		return day+"-"+ MonthNames.substring((month-1)*3,month*3) + "-"+ year;
	}
	
	public Day clone() {
		Day copy = null;
		try {
			copy = (Day) super.clone();
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return copy;
	}

	@Override
	public int compareTo(Day otherDay) {
		int tmpDate1 = this.year*10000+this.month*100+this.day;
		int tmpDate2 = otherDay.year*10000+otherDay.month*100+otherDay.day;
		return tmpDate1-tmpDate2;
	}
}
