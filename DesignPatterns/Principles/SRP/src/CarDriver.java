
public class CarDriver implements IDriver {
	private ICar _car;
	@Override
	public void setCar(ICar car) {
		// TODO Auto-generated method stub
		this._car = car;
	}

	@Override
	public void drive() {
		// TODO Auto-generated method stub
		this._car.run();
	}

}
