
public interface IUserInfo {
	void setUserID(String userID);
	String getUserID();
	void setPassword(String password);
	String getPassword();
	void setUserName(String userName);
	String getUserName();
	boolean changePassword(String oldPassword, String newPassword);
	boolean deleteUser();
	void mapUser();
	boolean addOrd(int orgID);
	boolean addRole(int roleID);
}
