#include<iostream>
#include<limits>
#include<vector>
using namespace std;

class product{
    public:
        int id;
        string name;
        double price;
        int quantity;  
};

class customer{
    public:
        string name;
        string email;
        string phone;
        string address;
        string paymentMethod;
};

vector<product>products;
vector<product>cart;
customer currentCustomer;

// Forward declarations
void bill();
void mainMenu();

void addProducts(){
    products.push_back({101,"Shoes",999,10});
    products.push_back({102,"T-shirt",399,12});
    products.push_back({103,"Watch",349,8});
    products.push_back({104,"Geans",1099,13});
    products.push_back({105,"Belt",149,15});
}

void displayProducts(){
    cout<<"<=============PRODUCTS============>\n";

    for(auto p : products){
        cout<<"ID : "<<p.id<<"\n";
        cout<<"Name : "<<p.name<<"\n";
        cout<<"Price : "<<p.price<<"\n";
        cout<<"Quantity : "<<p.quantity<<"\n";

        cout<<"------------------------------\n";
    }    
}

void searchProduct(){
    string name;

    cout<<"\nSearch products : ";
    cin>>name;

    bool found=false;

    for(auto p : products){
        if(p.name==name){
            cout<<"\nProduct Found!\n";

            cout<<"\nID : "<<p.id<<"\n";
            cout<<"Name : "<<p.name<<"\n";
            cout<<"Price : "<<p.price<<"\n";
            cout<<"Available Quantity : "<<p.quantity<<"\n";
            found=true;

            cout<<"\nDo you want to add this product to cart? (y/n): ";
            char choice;
            cin>>choice;

            if(choice=='y' || choice=='Y'){
                int qty;
                cout<<"Enter quantity: ";
                cin>>qty;

                if(qty<=0){
                    cout<<"Invalid quantity!\n";
                    break;
                }

                if(qty>p.quantity){
                    cout<<"Only "<<p.quantity<<" items available in stock!\n";
                    break;
                }

                bool alreadyInCart=false;
                for(auto& cartProduct : cart){
                    if(cartProduct.id==p.id){
                        alreadyInCart=true;
                        if(cartProduct.quantity+qty <= p.quantity){
                            cartProduct.quantity += qty;
                            cout<<"\nProduct quantity updated in cart!\n";
                        }
                        else{
                            cout<<"\nStock limit would be exceeded!\n";
                        }
                        break;
                    }
                }

                if(!alreadyInCart){
                    p.quantity=qty;
                    cart.push_back(p);
                    cout<<"\nProduct added to cart!\n";
                }
            }
            else{
                cout<<"Product not added to cart.\n";
            }
            break;
        }
    }
    if(found==false){
        cout<<"Product not found !\n";
    }
}

void displayCart(){
    cout<<"\n=========CART========\n";
    double total=0;
    double subtotal=0;

    if(cart.empty()){
        cout<<"Cart is empty !\n";
        return;
    }
    
    for(auto p : cart){
        cout<<p.name<<" "<<"Rs. "<<p.price<<" x "<<p.quantity<<"\n";

        subtotal=p.price*p.quantity;
        total=total+subtotal;
    }    
    
    cout<<"---------------------\n";
    cout<<"Total = Rs. "<<total<<"\n";

}

void removeFromCart(){
    cin.ignore();
    string name;

    cout<<"Enter product name to remove : ";
    cin>>name;

    bool found=false;
    for(auto i=cart.begin();i!=cart.end();i++){
        if(i->name==name){
            cout<<i->name<<" removed from cart.\n";
            cart.erase(i);
            found=true;
            break;       
        }
    }
    if(found==false){
        cout<<"Product is not found in cart !\n";
    }
}

void increaseQuantity(){
    cin.ignore();
    string name;

    cout<<"Enter product name to increase : ";
    cin>>name;

    bool found=false;
    for(auto& i : cart){
        if(i.name==name){
            for(auto p : products){
                if(p.id==i.id && i.quantity>=p.quantity){
                    cout<<"Available stock limit reached.\n";
                    found=true;
                    return;
                }
            }
            i.quantity++;
            cout<<"Quantity increased.\n";
            found=true;
            break;
        }
    }
    if(found==false){
        cout<<"Product not found !\n";
        return;
    }    
} 

void decreaseQuantity(){
    cin.ignore();
    string name;

    cout<<"Enter product name to decrease : ";
    cin>>name;

    bool found=false;
    for(auto i=cart.begin();i!=cart.end();i++){
        if(i->name==name){
            if(i->quantity<=1){
                cout<<"Quantity cannot be less than 1.\n";
                found=true;
                break;
            }
            i->quantity--;
            cout<<"Quantity decreased.\n";
            found=true;
            break;
        }
    }
    if(found==false){
        cout<<"Product not found !\n";
        return;
    }    
}

void cartManagement(){
    int choice;

    do{
        cout<<"\n==========CART MANAGEMENT========\n";
        cout<<"1. Search Products\n";
        cout<<"2. View Cart\n";
        cout<<"3. Increase Quantity\n";
        cout<<"4. Decrease Quantity\n";
        cout<<"5. Remove Product\n";
        cout<<"6. Checkout\n";
        cout<<"7. Back\n";

        cout<<"Enter your choice : ";
        if(!(cin>>choice)){
            cin.clear();
            cin.ignore();
            cout<<"Invalid input! Please enter a number from 1 to 7.\n";
            continue;
        }

        if(choice==1){
            searchProduct();
        }
        else if(choice==2){
            displayCart();
            
        }
        else if(choice==3){
            increaseQuantity();
            
        }
        else if(choice==4){
            decreaseQuantity();
            
        }
        else if(choice==5){
            removeFromCart();
            
        }
        else if(choice==6){
            if(cart.empty()){
                cout<<"Cart is empty! Add products first.\n";
            }
            else{
                bill();
            }
            break;
        }
        else if(choice==7){
            break;
        }
        else{
            cout<<"Invalid Choice !";
        }       
    }
    while(choice!=7);
}

void bill(){
    cin.ignore();
    cout<<"\n==========BILL========\n";
    
    // Customer Details
    cout<<"\n--- Enter Customer Details ---\n";
    cout<<"Name: ";
    getline(cin, currentCustomer.name);
    
    cout<<"Email: ";
    getline(cin, currentCustomer.email);
    
    cout<<"Phone: ";
    getline(cin, currentCustomer.phone);
    
    cout<<"Address: ";
    getline(cin, currentCustomer.address);
    
    // Display cart
    cout<<"\n--- Order Summary ---\n";
    double subtotal=0;
    for(auto p : cart){
        double itemTotal = p.price * p.quantity;
        cout<<p.name<<" x "<<p.quantity<<" = Rs. "<<itemTotal<<"\n";
        subtotal += itemTotal;
    }
    
    // Discount
    double discount=0;
    cout<<"\nDo you have a coupon? (y/n): ";
    char couponChoice;
    cin>>couponChoice;
    
    if(couponChoice=='y' || couponChoice=='Y'){
        cin.ignore();
        string coupon;
        cout<<"Enter coupon code: ";
        getline(cin, coupon);
        
        if(coupon=="SAVE10"){
            discount = subtotal * 0.10;
            cout<<"Coupon applied! 10% discount: Rs. "<<discount<<"\n";
        }
        else if(coupon=="SAVE20"){
            discount = subtotal * 0.20;
            cout<<"Coupon applied! 20% discount: Rs. "<<discount<<"\n";
        }
        else{
            cout<<"Invalid coupon code!\n";
        }
    }
    
    // Tax
    double taxableAmount = subtotal - discount;
    double tax = taxableAmount * 0.05; // 5% GST
    double total = taxableAmount + tax;
    
    cout<<"\n--- Bill Details ---\n";
    cout<<"Subtotal: Rs. "<<subtotal<<"\n";
    cout<<"Discount: Rs. "<<discount<<"\n";
    cout<<"Tax (5%): Rs. "<<tax<<"\n";
    cout<<"Total Amount: Rs. "<<total<<"\n";
    
    // Payment Method
    cout<<"\n--- Payment Method ---\n";
    cout<<"1. Credit/Debit Card\n";
    cout<<"2. Net Banking\n";
    cout<<"3. Cash on Delivery\n";
    cout<<"4. UPI\n";
    cout<<"Enter your choice: ";
    
    int paymentChoice;
    cin>>paymentChoice;
    
    switch(paymentChoice){
        case 1:
            currentCustomer.paymentMethod = "Credit/Debit Card";
            break;
        case 2:
            currentCustomer.paymentMethod = "Net Banking";
            break;
        case 3:
            currentCustomer.paymentMethod = "Cash on Delivery";
            break;
        case 4:
            currentCustomer.paymentMethod = "UPI";
            break;
        default:
            cout<<"Invalid choice! Using Cash on Delivery.\n";
            currentCustomer.paymentMethod = "Cash on Delivery";
    }
    
    // Print Receipt
    cout<<"\n========== RECEIPT ==========\n";
    cout<<"Thank you for your order!\n\n";
    cout<<"Customer Name: "<<currentCustomer.name<<"\n";
    cout<<"Email: "<<currentCustomer.email<<"\n";
    cout<<"Phone: "<<currentCustomer.phone<<"\n";
    cout<<"Address: "<<currentCustomer.address<<"\n\n";
    
    cout<<"--- Items Ordered ---\n";
    for(auto p : cart){
        double itemTotal = p.price * p.quantity;
        cout<<p.name<<" x "<<p.quantity<<" = Rs. "<<itemTotal<<"\n";
    }
    
    cout<<"\nSubtotal: Rs. "<<subtotal<<"\n";
    cout<<"Discount: Rs. "<<discount<<"\n";
    cout<<"Tax (5%): Rs. "<<tax<<"\n";
    cout<<"TOTAL: Rs. "<<total<<"\n\n";
    cout<<"Payment Method: "<<currentCustomer.paymentMethod<<"\n";
    cout<<"Status: Order Confirmed!\n";
    cout<<"=============================\n";
    
    // Clear cart after checkout
    cart.clear();
    cout<<"\nThank you! Your order has been placed.\n";
}

void mainMenu(){
    int choice;
    
    do{
        cout<<"\n*===================================*\n";
        cout<<"     WELCOME TO E-COMMERCE STORE   \n";
        cout<<"*===================================*\n";
        cout<<"1. View All Products\n";
        cout<<"2. Search Product\n";
        cout<<"3. Cart Management\n";
        cout<<"4. Bill\n";
        cout<<"5. Exit\n";
        cout<<"-------------------------------------\n";
        cout<<"Enter your choice: ";
        
        if(!(cin>>choice)){
            cin.clear();
            cin.ignore(10000, '\n');
            cout<<"Invalid input! Please enter a number from 1 to 5.\n";
            continue;
        }
        
        switch(choice){
            case 1:
                displayProducts();
                break;
            case 2:
                searchProduct();
                break;
            case 3:
                cartManagement();
                break;
            case 4:
                if(cart.empty()){
                    cout<<"Cart is empty! Add products first.\n";
                }
                else{
                    bill();
                }
                break;
            case 5:
                cout<<"\nThank you for visiting! Goodbye!\n";
                break;
            default:
                cout<<"Invalid choice! Please try again.\n";
        }
    }
    while(choice!=5);
}

int main(){
    addProducts();
    mainMenu();

    return 0;

}