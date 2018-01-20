
public class Test {
	public static void main(String[] args)
	{
		CarDriver dr = new CarDriver();
		Benz benz = new Benz();
		BMW bmw = new BMW();
		dr.setCar(benz);
		dr.drive();
		
		dr.setCar(bmw);
		dr.drive();
	}
}
