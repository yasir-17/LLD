# include <iostream>
# include <vector>
# include <unordered_map>
# include <string>

using namespace std;

// Cart 

class cartService {
    private:    
        unordered_map<int, FoodMenuService> cart;
    
        public:
            cartService() {}

            bool addFood(FoodMenuService food) {
                cart[food.getID()] = food;
                return true;
            }

            bool removeFood(FoodMenuService food) {
                if (cart.find(food.getID()) == cart.end()) {
                    return false;
                }

                cart.erase(food.getID());
                return true;
            }

            bool checkOut() {
                int totalAmount = 0;
                for (auto it : cart) {
                    FoodMenuService food = it.second;
                    totalAmount += food.getPrice();
                }

                cout << "Total price is " << totalAmount;
                return true;
            }
};

// User

class UserService {
    private:
        int id;
        string email;
        string phone;
        cartService cart;

    public:
        UserService(int id, string email, string phone): id(id), email(email), phone(phone) {}

        int getId() const { return id; }
        string getEmail() const { return email; }
        string getPhone() const { return phone; }
        
        void setEmail(string newEmail) {
            email = newEmail;
        }

        void setPhone(string newPhone) {
            phone = newPhone;
        }

        void addFood(FoodMenuService food) {
            cart.addFood(food);
        }

        void removeFood(FoodMenuService food) {
            cart.removeFood(food);
        }

        bool checkOut() {
            return cart.checkOut();
        }
};

// Food Menu

class FoodMenuService {
    private:
        int id;
        string name;
        int price;
        string type;
    public:
        FoodMenuService(int id, string name, int price, string type): id(id), name(name), price(price), type(type) {}

        int getID() const { return id; }
        int getPrice() const { return price; }
        string getName() const { return name; }
        string getType() const { return type; }

        void setName(string newName) {
            name = newName;
        }

        void setPrice(int newPrice) {
            price = newPrice;
        }
};


// Resturant

class ResturantService {
    private:
        int id;
        string name;
        string cityName;
        unordered_map<int, FoodMenuService> foodMenu; // {foodMenuId, foodMenu}
    
        public:
            ResturantService(int id, string name, string city): id(id), name(name), cityName(city) {}

            int getID() const { return id; }
            string getName() const { return name; }
            string getcityName() const { return cityName; }

            bool addFoodItem(FoodMenuService food) {
                foodMenu[food.getID()] = food;
                return true;
            }

            unordered_map<int, FoodMenuService> getFoodMenu() {
                return foodMenu;
            }

            bool deleteFoodItem(FoodMenuService food) {
                int foodId = food.getID();
                if (foodMenu.find(foodId) == foodMenu.end()) {
                    cout << "No food found";
                    return false;
                }
                foodMenu.erase(foodId);

                return true;
            }

            bool updateFoodItem(int foodId, string newName, int newPrice) {
                if (foodMenu.find(foodId) == foodMenu.end()) {
                    cout << "No food item found";
                    return false;
                }

                FoodMenuService food = foodMenu[foodId];
                food.setName(newName);
                food.setPrice(newPrice);
                foodMenu[foodId] = food;
                return true;
            }
};

// Order food

class UberEatsService {
    private:
        unordered_map<int, UserService> users;
        unordered_map<int, ResturantService> resturants;
    
    public:
        UberEatsService();

        bool addUsers(int id, string email, string phone) {
            users[id] = UserService(id, email, phone);
            return true;
        }

        bool deleteUsers(int id) {
            if (users.find(id) == users.end()) {
                return false;
            }
            users.erase(id);
            return true;
        }

        bool addResturants(int id, string name, string city) {
            resturants[id] = ResturantService(id, name, city);
            return true;
        }

        vector<ResturantService> searchReasturant(string city) {
            vector<ResturantService> results;
            for (auto it : resturants) {
                if (it.second.getcityName() == city) {
                    results.push_back(it.second);
                }
            }
            return results;
        }

        vector<FoodMenuService> searchFoods(vector<ResturantService> res, string type) {
            vector<FoodMenuService> results;
            for (auto& r: res) {
                unordered_map<int, FoodMenuService> foodMenu = r.getFoodMenu();  

                for (const auto& it: foodMenu) {  
                    if (it.second.getType() == type) 
                        results.push_back(it.second);  
                    }
                }
            return results;
        }

        bool addFoodToCart(UserService& user, string city, string foodType) {

            vector<ResturantService> res = searchReasturant(city);
            if (res.empty()) {
                cout << "No resturant in the given city";
                return false;
            }

            vector<FoodMenuService> foods = searchFoods(res, foodType);

            if (foods.empty()) {
                return false;
            }

            user.addFood(foods[0]);
        }

        bool orderFood(UserService& user) {
            user.checkOut();
        }

};