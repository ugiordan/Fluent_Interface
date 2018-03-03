#include <iostream>

/**
 * Fluent pattern with struct
 */
struct UserStruct {
	
	UserStruct &WithName(std::string name) {
		this->name = std::move(name);
		return *this;
	}
	
	UserStruct &WithAge(const int age) {
		this->age = age;
		return *this;
	}
	
	std::unique_ptr<UserStruct> Build() {
		return std::make_unique<UserStruct>(*this);
	};
	
	std::string name{};
	int age{};
};

/**
 * Fluent pattern with class.
 * Needs Getter to access data members.
 */
class UserClass {

public:
	
	UserClass &WithName(std::string name) {
		this->name = std::move(name);
		return *this;
	}
	
	UserClass &WithAge(const int age) {
		this->age = age;
		return *this;
	}
	
	std::unique_ptr<UserClass> Build() {
		return std::make_unique<UserClass>(*this);
	};
	
	const std::string &GetName() const {
		return name;
	}
	
	int GetAge() const {
		return age;
	}

private:
	std::string name{};
	int age{};
};


/**
 * Fluent pattern with interface class.
 */
class User {
public:
	friend class UserFluentInterface;
	
public:
	const std::string &GetName() const {
		return name;
	}
	
	int GetAge() const {
		return age;
	}

private:
	void SetName(std::string name) {
		this->name = std::move(name);
	}
	
	void SetAge(const int age) {
		this->age = age;
	}
	
private:
	std::string name{};
	int age{};
};

class UserFluentInterface {
public:
	
	UserFluentInterface() {
		user_ptr_.reset(new User());
	}
	
	UserFluentInterface &WithName(std::string name) {
		user_ptr_->SetName(std::move(name));
		return *this;
	}
	
	UserFluentInterface &WithAge(const int age) {
		user_ptr_->SetAge(age);
		return *this;
	}
	
	std::unique_ptr<User> Build() {
		return std::move(user_ptr_);
	};

private:
	std::unique_ptr<User> user_ptr_;
};

int main() {
	
	// Fluent with Struct
	auto user_struct = UserStruct()
			.WithName("Pippo")
			.WithAge(30)
			.Build();
	
	std::cout << "Fluent with struct " << std::endl;
	std::cout << "Name: " << user_struct->name << std::endl;
	std::cout << "Age: " << user_struct->age << std::endl << std::endl;
	
	// Fluent with class
	auto user_class = UserClass()
			.WithName("Pippo")
			.WithAge(30)
			.Build();
	
	std::cout << "Fluent with class " << std::endl;
	std::cout << "Name: " << user_class->GetName() << std::endl;
	std::cout << "Age: " << user_class->GetAge() << std::endl << std::endl;
	
	// Fluent with interface class
	auto user_interfance = UserFluentInterface()
			.WithName("Pippo")
			.WithAge(30)
			.Build();
	
	std::cout << "Fluent with interface class " << std::endl;
	std::cout << "Name: " << user_interfance->GetName() << std::endl;
	std::cout << "Age: " << user_interfance->GetAge() << std::endl;
	return 0;
}